import fcntl
import json
import math
import os
import socket
import struct
import subprocess
import threading
import time
import numpy as np
import zmq
from datetime import datetime

from ftplib import FTP
from cereal import log
import cereal.messaging as messaging
from openpilot.common.realtime import Ratekeeper, DT_MDL
from openpilot.common.params import Params
from openpilot.common.filter_simple import MyMovingAverage
from openpilot.system.hardware import PC, TICI
from openpilot.selfdrive.navd.helpers import Coordinate
from openpilot.common.conversions import Conversions as CV

try:
  from shapely.geometry import LineString
  SHAPELY_AVAILABLE = True
except ImportError:
  SHAPELY_AVAILABLE = False

NetworkType = log.DeviceState.NetworkType

BLINKER_NONE = 0
BLINKER_LEFT = 1
BLINKER_RIGHT = 2
BLINKER_BOTH = 3

nav_type_mapping = {
  12: ("turn", "left", 1),
  16: ("turn", "sharp left", 1),
  1000: ("turn", "slight left", 1),
  1001: ("turn", "slight right", 2),
  1002: ("fork", "slight left", 3),
  1003: ("fork", "slight right", 4),
  1006: ("off ramp", "left", 3),
  1007: ("off ramp", "right", 4),
  13: ("turn", "right", 2),
  19: ("turn", "sharp right", 2),
  102: ("off ramp", "slight left", 3),
  105: ("off ramp", "slight left", 3),
  112: ("off ramp", "slight left", 3),
  115: ("off ramp", "slight left", 3),
  101: ("off ramp", "slight right", 4),
  104: ("off ramp", "slight right", 4),
  111: ("off ramp", "slight right", 4),
  114: ("off ramp", "slight right", 4),
  7: ("fork", "left", 3),
  44: ("fork", "left", 3),
  17: ("fork", "left", 3),
  75: ("fork", "left", 3),
  76: ("fork", "left", 3),
  118: ("fork", "left", 3),
  6: ("fork", "right", 4),
  43: ("fork", "right", 4),
  73: ("fork", "right", 4),
  74: ("fork", "right", 4),
  123: ("fork", "right", 4),
  124: ("fork", "right", 4),
  117: ("fork", "right", 4),
  131: ("rotary", "slight right", 5),
  132: ("rotary", "slight right", 5),
  140: ("rotary", "slight left", 5),
  141: ("rotary", "slight left", 5),
  133: ("rotary", "right", 5),
  134: ("rotary", "sharp right", 5),
  135: ("rotary", "sharp right", 5),
  136: ("rotary", "sharp left", 5),
  137: ("rotary", "sharp left", 5),
  138: ("rotary", "sharp left", 5),
  139: ("rotary", "left", 5),
  142: ("rotary", "straight", 5),
  14: ("turn", "uturn", 5),
  201: ("arrive", "straight", 5),
  51: ("notification", "straight", None),
  52: ("notification", "straight", None),
  53: ("notification", "straight", None),
  54: ("notification", "straight", None),
  55: ("notification", "straight", None),
  153: ("", "", 6),  #TG
  154: ("", "", 6),  #TG
  249: ("", "", 6)   #TG
}

################ CarrotNavi
## 국가법령정보센터: 도로설계기준
#V_CURVE_LOOKUP_BP = [0., 1./800., 1./670., 1./560., 1./440., 1./360., 1./265., 1./190., 1./135., 1./85., 1./55., 1./30., 1./15.]
#V_CRUVE_LOOKUP_VALS = [300, 150, 120, 110, 100, 90, 80, 70, 60, 50, 45, 35, 30]
V_CURVE_LOOKUP_BP = [0., 1./800., 1./670., 1./560., 1./440., 1./360., 1./265., 1./190., 1./135., 1./85., 1./55., 1./30., 1./25.]
V_CRUVE_LOOKUP_VALS = [300, 150, 120, 110, 100, 90, 80, 70, 60, 50, 40, 15, 5]

# Haversine formula to calculate distance between two GPS coordinates
#haversine_cache = {}
def haversine(lon1, lat1, lon2, lat2):
    #key = (lon1, lat1, lon2, lat2)
    #if key in haversine_cache:
    #    return haversine_cache[key]

    R = 6371000  # Radius of Earth in meters
    phi1, phi2 = math.radians(lat1), math.radians(lat2)
    dphi = math.radians(lat2 - lat1)
    dlambda = math.radians(lon2 - lon1)

    a = math.sin(dphi / 2) ** 2 + math.cos(phi1) * math.cos(phi2) * math.sin(dlambda / 2) ** 2
    distance = 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))

    #haversine_cache[key] = distance
    return distance


# Get the closest point on a segment between two coordinates
def closest_point_on_segment(p1, p2, current_position):
    x1, y1 = p1
    x2, y2 = p2
    px, py = current_position

    dx = x2 - x1
    dy = y2 - y1
    if dx == 0 and dy == 0:
        return p1  # p1 and p2 are the same point

    # Parameter t is the projection factor onto the line segment
    t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy)
    t = max(0, min(1, t))  # Clamp t to the segment

    closest_x = x1 + t * dx
    closest_y = y1 + t * dy

    return (closest_x, closest_y)


# Get path after a certain distance from the current position
def get_path_after_distance(start_index, coordinates, current_position, distance_m):
    total_distance = 0
    path_after_distance = []
    closest_index = -1
    closest_point = None
    min_distance = float('inf')

    start_index = max(0, start_index - 2)

    # 가까운 점만 탐색하도록 수정
    for i in range(start_index, len(coordinates) - 1):
        p1 = coordinates[i]
        p2 = coordinates[i + 1]
        candidate_point = closest_point_on_segment(p1, p2, current_position)
        distance = haversine(current_position[0], current_position[1], candidate_point[0], candidate_point[1])

        if distance < min_distance:
            min_distance = distance
            closest_point = candidate_point
            closest_index = i
        elif distance > min_distance and min_distance < 10:
            break

    start_index = closest_index
    # Start from the closest point and calculate the path after the specified distance
    if closest_index != -1:
        path_after_distance.append(closest_point)

        path_after_distance.append(coordinates[closest_index + 1])
        total_distance = haversine(closest_point[0], closest_point[1], coordinates[closest_index + 1][0],
                                   coordinates[closest_index + 1][1])

        # Traverse the path forward from the next point
        for i in range(closest_index + 1, len(coordinates) - 1):
            coord1 = coordinates[i]
            coord2 = coordinates[i + 1]
            segment_distance = haversine(coord1[0], coord1[1], coord2[0], coord2[1])

            if total_distance + segment_distance >= distance_m and segment_distance > 0:
                remaining_distance = distance_m - total_distance
                ratio = remaining_distance / segment_distance
                interpolated_lon = coord1[0] + ratio * (coord2[0] - coord1[0])
                interpolated_lat = coord1[1] + ratio * (coord2[1] - coord1[1])
                path_after_distance.append((interpolated_lon, interpolated_lat))
                break

            total_distance += segment_distance
            path_after_distance.append(coord2)

    return path_after_distance, start_index, closest_point


def calculate_angle(point1, point2):
    delta_lon = point2[0] - point1[0]
    delta_lat = point2[1] - point1[1]
    return math.degrees(math.atan2(delta_lat, delta_lon))

# Convert GPS coordinates to relative x, y coordinates based on a reference point and heading
def gps_to_relative_xy(gps_path, reference_point, heading_deg):
    ref_lon, ref_lat = reference_point
    relative_coordinates = []

    # Convert heading from degrees to radians
    heading_rad = math.radians(heading_deg)

    for lon, lat in gps_path:
        # Convert lat/lon differences to meters (assuming small distances for simple approximation)
        x = (lon - ref_lon) * 40008000 * math.cos(math.radians(ref_lat)) / 360
        y = (lat - ref_lat) * 40008000 / 360

        # Rotate coordinates based on the heading angle to align with the car's direction
        x_rot = x * math.cos(heading_rad) - y * math.sin(heading_rad)
        y_rot = x * math.sin(heading_rad) + y * math.cos(heading_rad)

        relative_coordinates.append((y_rot, x_rot))

    return relative_coordinates


# Calculate curvature given three points using a faster vector-based method
#curvature_cache = {}
def calculate_curvature(p1, p2, p3):
    #key = (p1, p2, p3)
    #if key in curvature_cache:
    #    return curvature_cache[key]

    v1 = (p2[0] - p1[0], p2[1] - p1[1])
    v2 = (p3[0] - p2[0], p3[1] - p2[1])

    cross_product = v1[0] * v2[1] - v1[1] * v2[0]
    len_v1 = math.sqrt(v1[0] ** 2 + v1[1] ** 2)
    len_v2 = math.sqrt(v2[0] ** 2 + v2[1] ** 2)

    if len_v1 * len_v2 == 0:
        curvature = 0
    else:
        curvature = cross_product / (len_v1 * len_v2 * len_v1)

    #curvature_cache[key] = curvature
    return curvature

class CarrotMan:
  def __init__(self):
    self.xState = 0
    self.trafficState = 0
    self.controls_active = False
    self.xroadcate = 8
    self.v_cruise_kph = 255
    print("************************************************CarrotMan init************************************************")
    self.params = Params()
    self.params_memory = Params("/dev/shm/params")
    self.sm = messaging.SubMaster(['deviceState', 'carState', 'controlsState', 'longitudinalPlan', 'modelV2', 'carControl', 'liveLocationKalman', 'navInstruction', 'controlsStateSP', 'longitudinalPlanSP'])
    self.pm = messaging.PubMaster(['carrotMan', "navRoute"])

    self.carrot_serv = CarrotServ()

    self.show_panda_debug = False
    self.broadcast_ip = self.get_broadcast_address()
    self.broadcast_port = 7705
    self.carrot_man_port = 7706
    self.connection = None
    self.ip_address = "0.0.0.0"
    self.remote_addr = None

    self.esp32_broadcast_ip = self.get_broadcast_address()
    self.esp32_broadcast_port = 4210
    self.esp32_port = 4211
    self.esp32_connection = None
    self.esp32_ip_address = "0.0.0.0"
    self.esp32_remote_addr = None

    #new
    self.autoCurveSpeedFactor = 1.0
    self.autoCurveSpeedAggressiveness = 1.0
    self.autoCurveSpeedFactorH = 0.8
    self.autoCurveSpeedAggressivenessH = 1.2
    self.param_frame = 0
    self.ext_blinker = BLINKER_NONE
    self.esp32_clients = {}  # 保存多个客户端 {ip: last_seen_time}
    #new

    self.turn_speed_last = 250
    self.curvatureFilter = MyMovingAverage(20)
    self.carrot_curve_speed_params()

    self.carrot_zmq_thread = threading.Thread(target=self.carrot_cmd_zmq, args=[])
    self.carrot_zmq_thread.daemon = True
    self.carrot_zmq_thread.start()

    ##self.carrot_panda_debug_thread = threading.Thread(target=self.carrot_panda_debug, args=[])
    ##self.carrot_panda_debug_thread.daemon = True
    ##self.carrot_panda_debug_thread.start()

    self.carrot_route_thread = threading.Thread(target=self.carrot_route, args=[])
    self.carrot_route_thread.daemon = True
    self.carrot_route_thread.start()

    self.is_running = True
    threading.Thread(target=self.broadcast_version_info).start()

    self.esp32_is_running = True
    threading.Thread(target=self.resp_32_broadcast_info).start()

    threading.Thread(target=self.esp32_comm_thread).start()

    self.navi_points = []
    self.navi_points_start_index = 0
    self.navi_points_active = False
    self.navd_active = False

    self.active_carrot_last = False

    self.is_metric = self.params.get_bool("IsMetric")

  def get_broadcast_address(self):
    if PC:
      iface = b'br0'
    else:
      iface = b'wlan0'
    try:
      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        ip = fcntl.ioctl(
          s.fileno(),
          0x8919,
          struct.pack('256s', iface)
        )[20:24]
        return socket.inet_ntoa(ip)
    except (OSError, Exception):
      return None

  def get_local_ip(self):
      try:
          # 외부 서버와의 연결을 통해 로컬 IP 확인
          with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
              s.connect(("8.8.8.8", 80))  # Google DNS로 연결 시도
              return s.getsockname()[0]
      except Exception as e:
          return f"Error: {e}"

  # 브로드캐스트 메시지 전송
  def broadcast_version_info(self):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    frame = 0
    self.save_toggle_values()
    rk = Ratekeeper(10, print_delay_threshold=None)

    carrotIndex_last = self.carrot_serv.carrotIndex
    while self.is_running:
      try:
        if self.sm.alive['controlsState']:
          self.v_cruise_kph = self.sm['controlsState'].vCruise
        if self.carrot_serv.roadType >= 0:
          self.xroadcate = self.carrot_serv.roadType
          self.carrot_serv.xroadcate = self.xroadcate
        elif self.carrot_serv.roadType == -1: #-1表示根据巡航设定速度判断道路类型
          if self.v_cruise_kph < 85 or self.v_cruise_kph > 200:
            self.xroadcate = 8
          elif self.v_cruise_kph < 100:
            self.xroadcate = 0
          else:
            self.xroadcate = 1
          self.carrot_serv.xroadcate = self.xroadcate
        else: #-2
          xroadcate = 1 if self.carrot_serv.roadcate == 10 else 8
          if xroadcate == 1:
            if self.v_cruise_kph < 100:
              xroadcate = 0
          self.xroadcate = xroadcate
          self.carrot_serv.xroadcate = self.xroadcate

        self.sm.update(0)
        #if self.sm.updated['navRouteNavd']: #从navd.py发过来的
        #  self.send_routes(self.sm['navRouteNavd'].coordinates, True)
        remote_addr = self.remote_addr
        remote_ip = remote_addr[0] if remote_addr is not None else ""
        vturn_speed = self.carrot_curve_speed(self.sm)
        coords, distances, route_speed = self.carrot_navi_route()

        #print("coords=", coords) #print("curvatures=", curvatures)
        self.carrot_serv.update_navi(remote_ip, self.sm, self.pm, vturn_speed, coords, distances, route_speed)

        if frame % 20 == 0 or remote_addr is not None:
          try:
            self.broadcast_ip = self.get_broadcast_address() if remote_addr is None else remote_addr[0]
            if not PC:
              ip_address = socket.gethostbyname(socket.gethostname())
            else:
              ip_address = self.get_local_ip()
            if ip_address != self.ip_address:
              self.ip_address = ip_address
              self.remote_addr = None
            self.params_memory.put_nonblocking("NetworkAddress", self.ip_address)

            msg = self.make_send_message()
            if self.broadcast_ip is not None:
              dat = msg.encode('utf-8')
              sock.sendto(dat, (self.broadcast_ip, self.broadcast_port))
            #for i in range(1, 255):
            #  ip_tuple = socket.inet_aton(self.broadcast_ip)
            #  new_ip = ip_tuple[:-1] + bytes([i])
            #  address = (socket.inet_ntoa(new_ip), self.broadcast_port)
            #  sock.sendto(dat, address)

            if remote_addr is None:
              if (self.carrot_serv.showDebugLog & 32) > 0:
                print(f"Broadcasting: {self.broadcast_ip}:{msg}")
              if not self.navd_active:
                #print("clear path_points: navd_active: ", self.navd_active)
                self.navi_points = []
                self.navi_points_active = False

          except Exception as e:
            if self.connection:
              self.connection.close()
            self.connection = None
            if (self.carrot_serv.showDebugLog & 32) > 0:
              print(f"##### broadcast_error...: {e}")
            traceback.print_exc()

        rk.keep_time()
        frame += 1
      except Exception as e:
        if (self.carrot_serv.showDebugLog & 32) > 0:
          print(f"broadcast_version_info error...: {e}")
        traceback.print_exc()
        time.sleep(1)

  def esp32_comm_thread(self):
    while True:
      try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
          sock.settimeout(10)  # 超时10秒
          sock.bind(('0.0.0.0', self.esp32_port))
          print("#########esp32_comm_thread: UDP thread started...")

          while True:
            try:
              try:
                data, remote_addr = sock.recvfrom(4096)

                if not data:
                  raise ConnectionError("No data received")

                ip, port = remote_addr
                # 修改: 保存多个客户端地址及最后活跃时间
                if not hasattr(self, "esp32_clients"):
                  self.esp32_clients = {}  # {ip: last_seen_time}
                self.esp32_clients[ip] = time.time()

                try:
                  json_obj = json.loads(data.decode())
                  if "blinker" in json_obj:
                    ext_blinker = json_obj.get("blinker")
                    if ext_blinker in ["left", "stockleft"]:
                      self.ext_blinker = BLINKER_LEFT
                    elif ext_blinker in ["right", "stockright"]:
                      self.ext_blinker = BLINKER_RIGHT
                    else:
                      self.ext_blinker = BLINKER_NONE

                  if (self.carrot_serv.showDebugLog & 32) > 0:
                    print(json_obj)
                except Exception as e:
                  self.ext_blinker = BLINKER_NONE
                  if (self.carrot_serv.showDebugLog & 32) > 0:
                    print(f"esp32_comm_thread: json error...: {e}")
                    print(data)
              except TimeoutError:
                if (self.carrot_serv.showDebugLog & 32) > 0:
                  print("Waiting for data (timeout)...")
              except Exception as e:
                if (self.carrot_serv.showDebugLog & 32) > 0:
                  print(f"esp32_comm_thread: error...: {e}")
                break

              # 修改: 清理超过 10 秒未活跃的客户端
              now = time.time()
              self.esp32_clients = {ip: ts for ip, ts in self.esp32_clients.items() if now - ts < 10}

              if self.esp32_clients:
                self.carrot_serv.ext_state = len(self.esp32_clients)
              else:
                self.carrot_serv.ext_state = 0
                self.ext_blinker = BLINKER_NONE

              self.carrot_serv.ext_blinker = self.ext_blinker

            except Exception as e:
              if (self.carrot_serv.showDebugLog & 32) > 0:
                print(f"esp32_comm_thread: recv error...: {e}")
              break

          time.sleep(1)
      except Exception as e:
        if (self.carrot_serv.showDebugLog & 32) > 0:
          print(f"Network error, retrying...: {e}")
        time.sleep(2)

  def resp_32_broadcast_info(self):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    frame = 0
    blinker_frame = 0
    blinker_state = 0
    blinker_state_str = "none"
    active_str = "off"
    blinker_test = 0
    showDebugLog = 0
    rk = Ratekeeper(10, print_delay_threshold=None)
    extBlinkerCtrlTest = self.params.get_int("ExtBlinkerCtrlTest")
    blinker_test_cnt = 0
    broadcast_cnt = 0

    while self.esp32_is_running:
      if frame % 40 == 0:
        showDebugLog = self.params.get_int("ShowDebugLog")
      try:
        # 修改: 获取当前活跃客户端
        active_clients = list(getattr(self, "esp32_clients", {}).keys())

        if active_clients and ((showDebugLog & 1024) > 0 or extBlinkerCtrlTest):
          if 0 == (blinker_frame % 10):
            blinker_test = 1
            if (blinker_test_cnt >= 3) and ((showDebugLog & 1024) == 0):
              extBlinkerCtrlTest = 0
              blinker_state = 0
              blinker_test = 0
              blinker_state_str = "none"
              active_str = "off"
            else:
              blinker_state += 1
            if blinker_state == 1:
              blinker_state_str = "left"
              active_str = "on"
            elif blinker_state == 2:
              blinker_state_str = "right"
              active_str = "on"
            elif blinker_state == 3:
              blinker_state = 0
              blinker_state_str = "none"
              active_str = "off"
              blinker_test_cnt += 1
          blinker_frame += 1
        else:
          blinker_test = 0
          blinker_state_str = "none"
          active_str = "off"

        if (frame >= 600) and ((showDebugLog & 1024) == 0):
          extBlinkerCtrlTest = 0
          blinker_test = 0
          blinker_state_str = "none"
          active_str = "off"

        if frame % 20 == 0 or active_clients:
          try:
            if not PC:
              ip_address = socket.gethostbyname(socket.gethostname())
            else:
              ip_address = self.get_local_ip()
            if ip_address != self.esp32_ip_address:
              self.esp32_ip_address = ip_address
              self.esp32_clients = {}  # 修改: 本地 IP 变化时清空客户端

            msg = self.make_esp32_send_message(blinker_test, blinker_state_str, active_str)
            dat = msg.encode('utf-8')

            if active_clients:
              # 修改: 向所有客户端发送
              for ip in active_clients:
                try:
                  sock.sendto(dat, (ip, self.esp32_broadcast_port))
                except Exception as e:
                  if (self.carrot_serv.showDebugLog & 32) > 0:
                    print(f"sendto {ip} failed: {e}")
            if frame % 20 == 0 and broadcast_cnt < 60:
              # 修改: 无客户端 → 广播
              self.esp32_broadcast_ip = self.get_broadcast_address()
              if self.esp32_broadcast_ip is not None:
                sock.sendto(dat, (self.esp32_broadcast_ip, self.esp32_broadcast_port))
                broadcast_cnt += 1
                if (self.carrot_serv.showDebugLog & 32) > 0:
                  print(f"esp32 broadcasting: {self.esp32_broadcast_ip}:{self.esp32_broadcast_port},{msg}")

          except Exception as e:
            if self.esp32_connection:
              self.esp32_connection.close()
            self.esp32_connection = None
            if (self.carrot_serv.showDebugLog & 32) > 0:
              print(f"##### esp32_broadcast_error...: {e}")
            traceback.print_exc()

        rk.keep_time()
        frame += 1
      except Exception as e:
        if (self.carrot_serv.showDebugLog & 32) > 0:
          print(f"esp32_broadcast_info error...: {e}")
        traceback.print_exc()
        time.sleep(1)

  def carrot_navi_route(self):

    if self.carrot_serv.active_carrot > 1:
      if False and self.navd_active:  # mabox always active
        self.navd_active = False
        self.params.remove("NavDestination")
    if not self.navi_points_active or not SHAPELY_AVAILABLE or (self.carrot_serv.active_carrot <= 1 and not self.navd_active):
      #print(f"navi_points_active: {self.navi_points_active}, active_carrot: {self.carrot_serv.active_carrot}")
      if self.navi_points_active:
        print("navi_points_active: ", self.navi_points_active, "active_carrot: ", self.carrot_serv.active_carrot, "navd_active: ", self.navd_active)
        #haversine_cache.clear()
        #curvature_cache.clear()
        self.navi_points = []
        self.navi_points_active = False
        if self.active_carrot_last > 1:
          #self.params.remove("NavDestination")
          pass
      self.active_carrot_last = self.carrot_serv.active_carrot
      return [],[],300

    current_position = (self.carrot_serv.vpPosPointLon, self.carrot_serv.vpPosPointLat)
    heading_deg = self.carrot_serv.bearing

    distance_interval = 10.0
    out_speed = 300
    path, self.navi_points_start_index, start_point = get_path_after_distance(self.navi_points_start_index, self.navi_points, current_position, 300)
    relative_coords = []
    if path:
        #relative_coords = gps_to_relative_xy(path, current_position, heading_deg)
        relative_coords = gps_to_relative_xy(path, start_point, heading_deg)
        # Resample relative_coords at 5m intervals using LineString
        line = LineString(relative_coords)
        resampled_points = []
        resampled_distances = []
        current_distance = 0
        while current_distance <= line.length:
            point = line.interpolate(current_distance)
            resampled_points.append((point.x, point.y))
            resampled_distances.append(current_distance)
            current_distance += distance_interval

        curvatures = []
        distances = []
        distance = 10.0
        sample = 4
        if len(resampled_points) >= sample * 2 + 1:
            # Calculate curvatures and speeds based on curvature
            speeds = []
            for i in range(len(resampled_points) - sample * 2):
                distance += distance_interval
                p1, p2, p3 = resampled_points[i], resampled_points[i + sample], resampled_points[i + sample * 2]
                curvature = calculate_curvature(p1, p2, p3)
                curvatures.append(curvature)
                speed = np.interp(abs(curvature), V_CURVE_LOOKUP_BP, V_CRUVE_LOOKUP_VALS)
                if abs(curvature) < 0.02:
                  speed = max(speed, self.carrot_serv.nRoadLimitSpeed)
                speeds.append(speed)
                distances.append(distance)
            #print(f"curvatures= {[round(s, 4) for s in curvatures]}")
            #print(f"speeds= {[round(s, 1) for s in speeds]}")
            # Apply acceleration limits in reverse to adjust speeds
            accel_limit = self.carrot_serv.autoNaviSpeedDecelRate # m/s^2
            accel_limit_kmh = accel_limit * 3.6  # Convert to km/h per second
            out_speeds = [0] * len(speeds)
            out_speeds[-1] = speeds[-1]  # Set the last speed as the initial value
            v_ego_kph = self.sm['carState'].vEgo * 3.6

            time_delay = self.carrot_serv.autoNaviSpeedCtrlEnd
            time_wait = 0
            for i in range(len(speeds) - 2, -1, -1):
                target_speed = speeds[i]
                next_out_speed = out_speeds[i + 1]

                if target_speed < next_out_speed:
                  time_delay = max(0, ((v_ego_kph - target_speed) / accel_limit_kmh))
                  time_wait = - time_delay

                # Calculate time interval for the current segment based on speed
                time_interval = distance_interval / (next_out_speed / 3.6) if next_out_speed > 0 else 0

                time_apply = min(time_interval, max(0, time_interval + time_wait))

                # Calculate maximum allowed speed with acceleration limit
                max_allowed_speed = next_out_speed + (accel_limit_kmh * time_apply)
                adjusted_speed = min(target_speed, max_allowed_speed)

                #time_wait += time_interval
                time_wait += min(2.0, time_interval)

                out_speeds[i] = adjusted_speed

            #distance_advance = self.sm['carState'].vEgo * 3.0  # Advance distance by 3.0 seconds
            #out_speed = interp(distance_advance, distances, out_speeds)
            out_speed = out_speeds[0]
            #print(f"out_speeds= {[round(s, 1) for s in out_speeds]}")
    else:
        resampled_points = []
        resampled_distances = []
        curvatures = []
        speeds = []
        distances = []
        #self.params.remove("NavDestination")

    return resampled_points, resampled_distances, out_speed #speeds, distances


  def make_send_message(self):
    msg = {}
    msg['Carrot2'] = self.params.get("Version").decode('utf-8')
    isOnroad = self.params.get_bool("IsOnroad")
    msg['IsOnroad'] = isOnroad
    msg['CarrotRouteActive'] = self.navi_points_active
    msg['ip'] = self.ip_address
    msg['port'] = self.carrot_man_port
    self.controls_active = False
    self.xState = 0
    self.trafficState = 0
    v_ego_kph = 0
    log_carrot = ""
    v_cruise_kph = 0
    if not isOnroad:
      self.xState = 0
      self.trafficState = 0
    else:
      if self.sm.alive['carState']:
        carState = self.sm['carState']
        v_ego_kph = int(carState.vEgoCluster * 3.6 + 0.5)
        ##log_carrot = carState.logCarrot
      if self.sm.alive['controlsState']:
        control_state = self.sm['controlsState']
        self.controls_active = control_state.active
        v_cruise_kph = control_state.vCruise
      if self.sm.alive['longitudinalPlanSP']:
        lp = self.sm['longitudinalPlanSP']
        self.xState = lp.xState
        self.trafficState = lp.trafficState

    msg['log_carrot'] = log_carrot
    msg['v_cruise_kph'] = v_cruise_kph
    msg['v_ego_kph'] = v_ego_kph
    msg['tbt_dist'] = self.carrot_serv.xDistToTurn
    msg['sdi_dist'] = self.carrot_serv.xSpdDist
    msg['active'] = self.controls_active
    msg['xState'] = self.xState
    msg['trafficState'] = self.trafficState
    return json.dumps(msg)

  def make_esp32_send_message(self, blinker_test, blinker_state_str, active_str):
    msg = {}
    msg['ip'] = self.esp32_ip_address
    msg['port'] = self.esp32_port
    if 0 == blinker_test:
      if self.sm.alive['modelV2']:
        msg['blinker'] = self.sm['modelV2'].meta.blinker
      if self.sm.alive['controlsState']:
        control_state = self.sm['controlsState']
        msg['active'] = "on" if control_state.active else "off"
    else:
      msg['blinker'] = blinker_state_str
      msg['active'] = active_str

    return json.dumps(msg)

  def receive_fixed_length_data(self, sock, length):
    buffer = b""
    while len(buffer) < length:
      data = sock.recv(length - len(buffer))
      if not data:
        raise ConnectionError("Connection closed before receiving all data")
      buffer += data
    return buffer


  def carrot_man_thread(self):
    while True:
      try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
          sock.settimeout(10)  # 소켓 타임아웃 설정 (10초)
          sock.bind(('0.0.0.0', self.carrot_man_port))  # UDP 포트 바인딩
          print("#########carrot_man_thread: UDP thread started...")

          while True:
            try:
              #self.remote_addr = None
              # 데이터 수신 (UDP는 recvfrom 사용)
              try:
                data, remote_addr = sock.recvfrom(4096)  # 최대 4096 바이트 수신
                #print(f"Received data from {self.remote_addr}")

                if not data:
                  raise ConnectionError("No data received")

                if self.remote_addr is None:
                  print("Connected to: ", remote_addr)
                self.remote_addr = remote_addr
                try:
                  json_obj = json.loads(data.decode())
                  self.carrot_serv.update(json_obj)
                except Exception as e:
                  print(f"carrot_man_thread: json error...: {e}")
                  print(data)

                # 응답 메시지 생성 및 송신 (UDP는 sendto 사용)
                #try:
                #  msg = self.make_send_message()
                #  sock.sendto(msg.encode('utf-8'), self.remote_addr)
                #except Exception as e:
                #  print(f"carrot_man_thread: send error...: {e}")

              except TimeoutError:
                if (self.carrot_serv.showDebugLog & 32) > 0:
                  print("Waiting for data (timeout)...")
                self.remote_addr = None
                time.sleep(1)

              except Exception as e:
                print(f"carrot_man_thread: error...: {e}")
                self.remote_addr = None
                break

            except Exception as e:
              print(f"carrot_man_thread: recv error...: {e}")
              self.remote_addr = None
              break

          time.sleep(1)
      except Exception as e:
        self.remote_addr = None
        print(f"Network error, retrying...: {e}")
        time.sleep(2)


  def parse_kisa_data(self, data: bytes):
    result = {}

    try:
      decoded = data.decode('utf-8')
    except UnicodeDecodeError:
      print("Decoding error:", data)
      return result

    parts = decoded.split('/')
    for part in parts:
      if ':' in part:
        key, value = part.split(':', 1)
        try:
          result[key] = int(value)
        except ValueError:
          result[key] = value
    return result

  def kisa_app_thread(self):
    while True:
      try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
          sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
          sock.settimeout(10)  # 소켓 타임아웃 설정 (10초)
          sock.bind(('', 12345))  # UDP 포트 바인딩
          print("#########kisa_app_thread: UDP thread started...")

          while True:
            try:
              #self.remote_addr = None
              # 데이터 수신 (UDP는 recvfrom 사용)
              try:
                data, remote_addr = sock.recvfrom(4096)  # 최대 4096 바이트 수신
                #print(f"Received data from {self.remote_addr}")

                if not data:
                  raise ConnectionError("No data received")

                #if self.remote_addr is None:
                #  print("Connected to: ", remote_addr)
                #self.remote_addr = remote_addr
                try:
                  print(data)
                  kisa_data = self.parse_kisa_data(data)
                  self.carrot_serv.update_kisa(kisa_data)
                  #json_obj = json.loads(data.decode())
                  #print(json_obj)
                except Exception as e:
                  traceback.print_exc()
                  print(f"kisa_app_thread: json error...: {e}")
                  print(data)

              except TimeoutError:
                if (self.carrot_serv.showDebugLog & 32) > 0:
                  print("Waiting for data (timeout)...")
                #self.remote_addr = None
                time.sleep(1)

              except Exception as e:
                print(f"kisa_app_thread: error...: {e}")
                #self.remote_addr = None
                break

            except Exception as e:
              print(f"kisa_app_thread: recv error...: {e}")
              #self.remote_addr = None
              break

          time.sleep(1)
      except Exception as e:
        #self.remote_addr = None
        print(f"Network error, retrying...: {e}")
        time.sleep(2)

  def make_tmux_data(self):
    try:
      subprocess.run("rm /data/media/tmux.log; tmux capture-pane -pq -S-1000 > /data/media/tmux.log", shell=True, capture_output=True, text=False)
      subprocess.run("/data/openpilot/selfdrive/apilot.py", shell=True, capture_output=True, text=False)
    except Exception as e:
      print(f"TMUX creation error: {e}")
      return

  def send_tmux(self, ftp_password, tmux_why, send_settings=False):

    ftp_server = "shind0.synology.me"
    ftp_port = 8021
    ftp_username = "carrotpilot"
    ftp = FTP()
    ftp.connect(ftp_server, ftp_port)
    ftp.login(ftp_username, ftp_password)
    car_selected = Params().get("CarName")
    if car_selected is None:
      car_selected = "none"
    else:
      car_selected = car_selected.decode('utf-8')

    git_branch = Params().get("GitBranch").decode('utf-8')
    directory = git_branch + " " + car_selected + " " + Params().get("DongleId").decode('utf-8')
    current_time = datetime.now().strftime("%Y%m%d-%H%M%S")
    filename = tmux_why + "-" + current_time + "-" + git_branch + ".txt"

    try:
      ftp.mkd(directory)
    except Exception as e:
      print(f"Directory creation failed: {e}")
    ftp.cwd(directory)

    try:
      with open("/data/media/tmux.log", "rb") as file:
        ftp.storbinary(f'STOR {filename}', file)
    except Exception as e:
      print(f"ftp sending error...: {e}")

    if send_settings:
      self.save_toggle_values()
      try:
        #with open("/data/backup_params.json", "rb") as file:
        with open("/data/toggle_values.json", "rb") as file:
          ftp.storbinary(f'STOR toggles-{current_time}.json', file)
      except Exception as e:
        print(f"ftp params sending error...: {e}")

    ftp.quit()

  def carrot_panda_debug(self):
    #time.sleep(2)
    while True:
      if self.show_panda_debug:
        self.show_panda_debug = False
        try:
          subprocess.run("/data/openpilot/selfdrive/debug/debug_console_carrot.py", shell=True)
        except Exception as e:
          print(f"debug_console error: {e}")
          time.sleep(2)
      else:
        time.sleep(1)

  def save_toggle_values(self):
    try:
      import openpilot.system.fleetmanager.helpers as fleet

      toggle_values = fleet.get_all_toggle_values()
      file_path = os.path.join('/data', 'toggle_values.json')
      with open(file_path, 'w') as file:
        json.dump(toggle_values, file, indent=2)
    except Exception as e:
      print(f"save_toggle_values error: {e}")

  def carrot_cmd_zmq(self):

    context = zmq.Context()
    def setup_socket():
        socket = context.socket(zmq.REP)
        socket.bind("tcp://*:7710")
        poller = zmq.Poller()
        poller.register(socket, zmq.POLLIN)
        return socket, poller

    socket, poller = setup_socket()
    isOnroadCount = 0
    is_tmux_sent = False

    print("#########carrot_cmd_zmq: thread started...")
    while True:
      try:
        socks = dict(poller.poll(100))

        if socket in socks and socks[socket] == zmq.POLLIN:
          message = socket.recv(zmq.NOBLOCK)
          print(f"Received:7710 request: {message}")
          json_obj = json.loads(message.decode())
        else:
          json_obj = None

        if json_obj is None:
          pass
        elif 'echo_cmd' in json_obj:
          try:
            result = subprocess.run(json_obj['echo_cmd'], shell=True, capture_output=True, text=False)
            exitStatus = result.returncode
            try:
              stdout = result.stdout.decode('utf-8')
              stderr = result.stderr.decode('utf-8')
            except UnicodeDecodeError:
              stdout = result.stdout.decode('euc-kr', 'ignore')
              stderr = result.stderr.decode('euc-kr', 'ignore')

            echo = json.dumps({"echo_cmd": json_obj['echo_cmd'], "exitStatus": exitStatus, "result": stdout, "error": stderr})
          except Exception as e:
            echo = json.dumps({"echo_cmd": json_obj['echo_cmd'], "exitStatus": exitStatus, "result": "", "error": f"exception error: {str(e)}"})
          #print(echo)
          socket.send(echo.encode())
        elif 'tmux_send' in json_obj:
          pass

      except Exception as e:
        print(f"carrot_cmd_zmq error: {e}")
        socket.close()
        time.sleep(1)
        socket, poller = setup_socket()

  def recvall(self, sock, n):
    """n바이트를 수신할 때까지 반복적으로 데이터를 받는 함수"""
    data = bytearray()
    while len(data) < n:
      packet = sock.recv(n - len(data))
      if not packet:
        return None
      data.extend(packet)
    return data

  def receive_double(self, sock):
    double_data = self.recvall(sock, 8)  # Double은 8바이트
    return struct.unpack('!d', double_data)[0]

  def receive_float(self, sock):
    float_data = self.recvall(sock, 4)  # Float은 4바이트
    return struct.unpack('!f', float_data)[0]


  def send_routes(self, coords, from_navd=False):
    if from_navd:
      if len(coords) > 0:
        self.navi_points = [(c.longitude, c.latitude) for c in coords]
        self.navi_points_start_index = 0
        self.navi_points_active = True
        print("Received points from navd:", len(self.navi_points))
        self.navd_active = True

        # 경로수신 -> carrotman active되고 약간의 시간지연이 발생함..
        if not from_navd:
          self.carrot_serv.active_count = 80
          self.carrot_serv.active_sdi_count = self.carrot_serv.active_sdi_count_max
          self.carrot_serv.active_carrot = 2

        coords = [{"latitude": c.latitude, "longitude": c.longitude} for c in coords]
        #print("navdNaviPoints=", self.navi_points)
      else:
        print("Received points from navd: 0")
        self.navd_active = False

    msg = messaging.new_message('navRoute', valid=True)
    msg.navRoute.coordinates = coords
    self.pm.send('navRoute', msg)

  def carrot_route(self):
    host = '0.0.0.0'  # 혹은 다른 호스트 주소
    port = 7709  # 포트 번호

    try:
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()

        while True:
          print("################# waiting connection from CarrotMan route #####################")
          conn, addr = s.accept()
          with conn:
            print(f"Connected by {addr}")
            #self.clear_route()

            # 전체 데이터 크기 수신
            total_size_bytes = self.recvall(conn, 4)
            if not total_size_bytes:
              print("Connection closed or error occurred")
              continue
            try:
              total_size = struct.unpack('!I', total_size_bytes)[0]
              # 전체 데이터를 한 번에 수신
              all_data = self.recvall(conn, total_size)
              if all_data is None:
                  print("Connection closed or incomplete data received")
                  continue

              self.navi_points = []
              points = []
              for i in range(0, len(all_data), 8):
                x, y = struct.unpack('!ff', all_data[i:i+8])
                self.navi_points.append((x, y))
                coord = Coordinate.from_mapbox_tuple((x, y))
                points.append(coord)
              coords = [c.as_dict() for c in points]
              self.navi_points_start_index = 0
              self.navi_points_active = True
              print("Received points:", len(self.navi_points))
              #print("Received points:", self.navi_points)

              self.send_routes(coords)
              """
              try:
                module_name = "route_engine"
                class_name = "RouteEngine"
                moduel = importlib.import_module(module_name)
                cls = getattr(moduel, class_name)
                route_engine_instance = cls(name="Loaded at Runtime")

                route_engine_instance.send_route_coords(coords, True)
              except Exception as e:
                print(f"route_engine error: {e}")

              #msg = messaging.new_message('navRoute', valid=True)
              #msg.navRoute.coordinates = coords
              #self.pm.send('navRoute', msg)
              """

              if len(coords):
                dest = coords[-1]
                dest['place_name'] = "External Navi"
                self.params.put("NavDestination", json.dumps(dest))

            except Exception as e:
              print(e)
    except Exception as e:
      print("################# CarrotMan route server error #####################")
      print(e)

  def carrot_curve_speed_params(self):
    self.autoCurveSpeedFactor = self.params.get_int("AutoCurveSpeedFactor")*0.01
    self.autoCurveSpeedAggressiveness = self.params.get_int("AutoCurveSpeedAggressiveness")*0.01
    self.autoCurveSpeedFactorH = self.params.get_int("AutoCurveSpeedFactorH") * 0.01
    self.autoCurveSpeedAggressivenessH = self.params.get_int("AutoCurveSpeedAggressivenessH") * 0.01

  def carrot_curve_speed(self, sm):
    self.carrot_curve_speed_params()
    if not sm.alive['carState'] and not sm.alive['modelV2']:
        return 250
    #print(len(sm['modelV2'].orientationRate.z))
    if len(sm['modelV2'].orientationRate.z) == 0:
        return 250

    return self.vturn_speed(sm['carState'], sm)

  def vturn_speed(self, CS, sm):
    TARGET_LAT_A = 1.9  # m/s^2

    modelData = sm['modelV2']
    v_ego = max(CS.vEgo, 0.1)
    # Set the curve sensitivity
    #new
    if self.xroadcate > 1: #if self.carrot_serv.xroadcate > 1: #普通道路
      orientation_rate = np.array(modelData.orientationRate.z) * self.autoCurveSpeedFactor
    else: #高速公路
      orientation_rate = np.array(modelData.orientationRate.z) * self.autoCurveSpeedFactorH
    #new
    velocity = np.array(modelData.velocity.x)

    # Get the maximum lat accel from the model
    max_index = np.argmax(np.abs(orientation_rate))
    curv_direction = np.sign(orientation_rate[max_index])
    max_pred_lat_acc = np.amax(np.abs(orientation_rate) * velocity)

    # Get the maximum curve based on the current velocity
    max_curve = max_pred_lat_acc / (v_ego**2)

    # Set the target lateral acceleration
    #new
    if self.xroadcate > 1: #if self.carrot_serv.xroadcate > 1: #普通道路
      adjusted_target_lat_a = TARGET_LAT_A * self.autoCurveSpeedAggressiveness
    else: #高速公路
      adjusted_target_lat_a = TARGET_LAT_A * self.autoCurveSpeedAggressivenessH
    #new

    # Get the target velocity for the maximum curve
    #turnSpeed = max(abs(adjusted_target_lat_a / max_curve)**0.5  * 3.6, self.autoCurveSpeedLowerLimit)
    turnSpeed = max(abs(adjusted_target_lat_a / max_curve)**0.5  * 3.6, 5)
    turnSpeed = min(turnSpeed, 250)
    return turnSpeed * curv_direction

import collections
class CarrotServ:
  def __init__(self):
    self.atcType = "none"
    self.params = Params()
    self.params_memory = Params("/dev/shm/params")

    self.nRoadLimitSpeed = 30
    self.nRoadLimitSpeed_last = 30
    self.nRoadLimitSpeed_counter = 0

    self.active_carrot = 0     ## 1: CarrotMan Active, 2: sdi active , 3: speed decel active, 4: section active, 5: bump active, 6: speed limit active
    self.active_count = 0
    self.active_sdi_count = 0
    self.active_sdi_count_max = 200 # 20 sec

    self.active_kisa_count = 0

    self.nSdiType = -1
    self.nSdiSpeedLimit = 0
    self.nSdiSection = 0
    self.nSdiDist = 0
    self.nSdiBlockType = -1
    self.nSdiBlockSpeed = 0
    self.nSdiBlockDist = 0

    #new
    self.nSdiTypeLast = -1
    self.nSdiSpeedLimitLast = 0
    self.nSdiSectionLast = 0
    self.nSdiDistLast = 0
    self.nSdiBlockTypeLast = -1
    self.nSdiBlockSpeedLast = 0
    self.nSdiBlockDistLast = 0

    self.nSdiPlusTypeLast = -1
    self.autoNaviSpeedCtrlModeLast = -1
    self.autoNaviSpeedSafetyFactorLast = -1
    #new

    self.nTBTDist = 0
    self.nTBTTurnType = -1
    self.szTBTMainText = ""
    self.szNearDirName = ""
    self.szFarDirName = ""
    self.nTBTNextRoadWidth = 0

    self.nTBTDistNext = 0
    self.nTBTTurnTypeNext = -1
    self.szTBTMainTextNext = ""

    self.nGoPosDist = 0
    self.nGoPosTime = 0
    self.szPosRoadName = ""
    self.nSdiPlusType = -1
    self.nSdiPlusSpeedLimit = 0
    self.nSdiPlusDist = 0
    self.nSdiPlusBlockType = -1
    self.nSdiPlusBlockSpeed = 0
    self.nSdiPlusBlockDist = 0

    self.goalPosX = 0.0
    self.goalPosY = 0.0
    self.szGoalName = ""
    self.vpPosPointLatNavi = 0.0
    self.vpPosPointLonNavi = 0.0
    self.vpPosPointLat = 0.0
    self.vpPosPointLon = 0.0
    self.roadcate = 8

    self.nPosSpeed = 0.0
    self.nPosAngle = 0.0
    self.nPosAnglePhone = 0.0

    self.diff_angle_count = 0
    self.last_calculate_gps_time = 0
    self.last_update_gps_time = 0
    self.last_update_gps_time_phone = 0
    self.last_update_gps_time_navi = 0
    self.bearing_offset = 0.0
    self.bearing_measured = 0.0
    self.bearing = 0.0
    self.gps_valid = False

    self.gps_accuracy_phone = 0.0
    self.gps_accuracy_device = 0.0

    self.totalDistance = 0
    self.xSpdLimit = 0
    self.xSpdDist = 0
    self.xSpdType = -1

    self.xTurnInfo = -1
    self.xDistToTurn = 0
    self.xDistToTurnNav = 0
    self.xDistToTurnMax = 0
    self.xDistToTurnMaxCnt = 0 #最大转弯引导距离的次数
    self.xDistToTurnNavLast = 0
    self.xTurnInfoNext = -1
    self.xDistToTurnNext = 0

    self.navType, self.navModifier = "invalid", ""
    self.navTypeNext, self.navModifierNext = "invalid", ""

    self.carrotIndex = 0
    self.carrotCmdIndex = 0
    self.carrotCmd = ""
    self.carrotArg = ""
    self.carrotCmdIndex_last = 0

    self.traffic_light_q = collections.deque(maxlen=int(2.0/0.1))  # 2 secnods
    self.traffic_light_count = -1
    self.traffic_state = 0

    self.left_spd_sec = 0
    self.left_tbt_sec = 0
    self.left_sec = 100
    self.max_left_sec = 100
    self.carrot_left_sec = 100
    self.sdi_inform = False


    self.atc_paused = False
    self.atc_activate_count = 0
    self.gas_override_speed = 0
    self.gas_pressed_state = False
    self.source_last = "none"

    self.debugText = ""

    #new
    self.autoNaviSpeedBumpSpeed = 35.
    self.autoNaviSpeedBumpTime = 1
    self.autoNaviSpeedCtrlEnd = 7
    self.autoNaviSpeedCtrlMode = 3
    self.autoNaviSpeedSafetyFactor = 1.05
    self.autoNaviSpeedDecelRate = 0.8
    self.autoNaviCountDownMode = 0
    self.turnSpeedControlMode = 1
    self.mapTurnSpeedFactor = 1.
    self.autoTurnControlSpeedTurn = 20
    self.autoTurnMapChange = 0
    self.autoTurnControl = 2
    self.autoTurnControlTurnEnd = 6
    # self.autoNaviSpeedDecelRate = 0.8
    self.autoCurveSpeedLowerLimit = 30
    self.is_metric = True
    self.autoRoadSpeedLimitOffset = -1

    self.sameSpiCamFilter = 0
    self.autoTurnDistOffset = 0
    self.autoForkDistOffsetH = 1000
    self.autoDoForkDecalDistH = 50
    self.autoDoForkDecalDist = 20
    self.autoForkDistOffset = 30
    #self.autoDoForkCheckDistH = 0
    self.autoDoForkBlinkerDist = 15
    self.autoDoForkNavDist = 15
    #self.autoDoForkCheckDistH = 0
    self.autoDoForkBlinkerDistH = 30
    self.autoDoForkNavDistH = 50
    self.autoUpRoadLimit = 0
    self.autoUpRoadLimit40KMH = 15
    self.autoUpHighwayRoadLimit = 0
    self.autoUpHighwayRoadLimit40KMH = 15
    self.roadType = -1
    self.xroadcate = 8
    self.autoForkDecalRateH = 80
    self.autoForkSpeedMinH = 60
    self.autoKeepForkSpeedH = 5
    self.autoForkDecalRate = 80
    self.autoForkSpeedMin = 45
    self.autoKeepForkSpeed = 5
    self.showDebugLog = 0
    self.param_frame = 0
    self.atc_speed_decal = 0
    self.fork_speed_keep_time = -1
    self.nRoadLimitSpeedSend = 200
    self.cpSpdAndRoadLimit = 3
    self.ext_blinker = BLINKER_NONE
    self.ext_state = 0
    #new

    self.update_params()

  def update_params(self):
    if (self.param_frame % 10) == 0:
      self.autoNaviSpeedBumpSpeed = float(self.params.get_int("AutoNaviSpeedBumpSpeed"))
      self.autoNaviSpeedBumpTime = float(self.params.get_int("AutoNaviSpeedBumpTime"))
      self.autoNaviSpeedCtrlEnd = float(self.params.get_int("AutoNaviSpeedCtrlEnd"))
      self.autoNaviSpeedCtrlMode = self.params.get_int("AutoNaviSpeedCtrlMode")
      self.autoNaviSpeedSafetyFactor = float(self.params.get_int("AutoNaviSpeedSafetyFactor")) * 0.01
      self.autoNaviSpeedDecelRate = float(self.params.get_int("AutoNaviSpeedDecelRate")) * 0.01
      self.autoNaviCountDownMode = self.params.get_int("AutoNaviCountDownMode")
      self.turnSpeedControlMode= self.params.get_int("TurnSpeedControlMode")
      self.mapTurnSpeedFactor= self.params.get_float("MapTurnSpeedFactor") * 0.01

      self.autoTurnControlSpeedTurn = self.params.get_int("AutoTurnControlSpeedTurn")
      self.autoTurnMapChange = self.params.get_int("AutoTurnMapChange")
      self.autoTurnControl = self.params.get_int("AutoTurnControl")
      self.autoTurnControlTurnEnd = self.params.get_int("AutoTurnControlTurnEnd")
      #self.autoNaviSpeedDecelRate = float(self.params.get_int("AutoNaviSpeedDecelRate")) * 0.01
      self.autoCurveSpeedLowerLimit = int(self.params.get("AutoCurveSpeedLowerLimit"))
      self.is_metric = self.params.get_bool("IsMetric")
      self.autoRoadSpeedLimitOffset = self.params.get_int("AutoRoadSpeedLimitOffset")

      #new
      self.sameSpiCamFilter = self.params.get_int("SameSpiCamFilter")
      self.autoTurnDistOffset = self.params.get_int("AutoTurnDistOffset")
      self.autoForkDistOffset = self.params.get_int("AutoForkDistOffset")
      #self.autoDoForkCheckDist = self.params.get_int("AutoDoForkCheckDist")
      self.autoDoForkBlinkerDist = self.params.get_int("AutoDoForkBlinkerDist")
      self.autoDoForkNavDist = self.params.get_int("AutoDoForkNavDist")
      self.autoForkDistOffsetH = self.params.get_int("AutoForkDistOffsetH")
      self.autoDoForkDecalDistH = self.params.get_int("AutoDoForkDecalDistH")
      self.autoDoForkDecalDist = self.params.get_int("AutoDoForkDecalDist")
      #self.autoDoForkCheckDistH = self.params.get_int("AutoDoForkCheckDistH")
      self.autoDoForkBlinkerDistH = self.params.get_int("AutoDoForkBlinkerDistH")
      self.autoDoForkNavDistH = self.params.get_int("AutoDoForkNavDistH")
      self.autoUpRoadLimit = self.params.get_int("AutoUpRoadLimit")
      self.autoUpRoadLimit40KMH = self.params.get_int("AutoUpRoadLimit40KMH")
      self.autoUpHighwayRoadLimit = self.params.get_int("AutoUpHighwayRoadLimit")
      self.autoUpHighwayRoadLimit40KMH = self.params.get_int("AutoUpHighwayRoadLimit40KMH")
      self.roadType = self.params.get_int("RoadType")
      self.autoForkDecalRateH = float(self.params.get_int("AutoForkDecalRateH")) * 0.01
      self.autoForkSpeedMinH = self.params.get_int("AutoForkSpeedMinH")
      self.autoKeepForkSpeedH = self.params.get_int("AutoKeepForkSpeedH")
      self.autoForkDecalRate = float(self.params.get_int("AutoForkDecalRate")) * 0.01
      self.autoForkSpeedMin = self.params.get_int("AutoForkSpeedMin")
      self.autoKeepForkSpeed = self.params.get_int("AutoKeepForkSpeed")
      self.showDebugLog = self.params.get_int("ShowDebugLog")
      self.cpSpdAndRoadLimit = self.params.get_int("CpSpdAndRoadLimit")
    self.param_frame += 1
    #new

  def _update_cmd(self):
    if self.carrotCmdIndex != self.carrotCmdIndex_last:
      self.carrotCmdIndex_last = self.carrotCmdIndex
      command_handlers = {
        "DETECT": self._handle_detect_command,
      }

      handler = command_handlers.get(self.carrotCmd)
      if handler:
        handler(self.carrotArg)

    self.traffic_light_q.append((-1, -1, "none", 0.0))
    self.traffic_light_count -= 1
    if self.traffic_light_count < 0:
      self.traffic_light_count = -1
      self.traffic_state = 0

  def _handle_detect_command(self, xArg):
    elements = [e.strip() for e in xArg.split(',')]
    if len(elements) >= 4:
      try:
        state = elements[0]
        value1 = float(elements[1])
        value2 = float(elements[2])
        value3 = float(elements[3])
        self.traffic_light(value1, value2, state, value3)
        self.traffic_light_count = int(0.5 / 0.1)
      except ValueError:
        pass

  def traffic_light(self, x, y, color, cnf):
    traffic_red = 0
    traffic_green = 0
    traffic_left = 0
    traffic_red_trig = 0
    traffic_green_trig = 0
    traffic_left_trig = 0
    for pdata in self.traffic_light_q:
      px, py, pcolor,pcnf = pdata
      if abs(x - px) < 0.2 and abs(y - py) < 0.2:
        if pcolor in ["Green Light", "Left turn"]:
          if color in ["Red Light", "Yellow Light"]:
            traffic_red_trig += cnf
            traffic_red += cnf
          elif color in ["Green Light", "Left turn"]:
            traffic_green += cnf
        elif pcolor in ["Red Light", "Yellow Light"]:
          if color in ["Green Light"]: #, "Left turn"]:
            traffic_green_trig += cnf
            traffic_green += cnf
          elif color in ["Left turn"]:
            traffic_left_trig += cnf
            traffic_left += cnf
          elif color in ["Red Light", "Yellow Light"]:
            traffic_red += cnf

    #print(self.traffic_light_q)
    if traffic_red_trig > 0:
      self.traffic_state = 1
      #self._add_log("Red light triggered")
      #print("Red light triggered")
    elif traffic_green_trig > 0 and traffic_green > traffic_red:  #주변에 red light의 cnf보다 더 크면 출발... 감지오류로 출발하는경우가 생김.
      self.traffic_state = 2
      #self._add_log("Green light triggered")
      #print("Green light triggered")
    elif traffic_left_trig > 0:
      self.traffic_state = 3
    elif traffic_red > 0:
      self.traffic_state = 1
      #self._add_log("Red light continued")
      #print("Red light continued")
    elif traffic_green > 0:
      self.traffic_state = 2
      #self._add_log("Green light continued")
      #print("Green light continued")
    else:
      self.traffic_state = 0
      #print("TrafficLight none")

    self.traffic_light_q.append((x,y,color,cnf))

  def calculate_current_speed(self, left_dist, safe_speed_kph, safe_time, safe_decel_rate):
    safe_speed = safe_speed_kph / 3.6
    safe_dist = safe_speed * safe_time
    decel_dist = left_dist - safe_dist

    if decel_dist <= 0:
      return safe_speed_kph

    # v_i^2 = v_f^2 + 2ad
    temp = safe_speed**2 + 2 * safe_decel_rate * decel_dist  # 공식에서 감속 적용

    if temp < 0:
      speed_mps = safe_speed
    else:
      speed_mps = math.sqrt(temp)
    return max(safe_speed_kph, min(250, speed_mps * 3.6))

  def _update_tbt(self):
    #xTurnInfo : 1: left turn, 2: right turn, 3: left lane change, 4: right lane change, 5: rotary, 6: tg, 7: arrive or uturn
    turn_type_mapping = {
      12: ("turn", "left", 1),
      16: ("turn", "sharp left", 1),
      #new
      1000: ("turn", "slight left", 1),
      1001: ("turn", "slight right", 2),
      1002: ("fork", "slight left", 3),
      1003: ("fork", "slight right", 4),
      1006: ("off ramp", "left", 3),
      1007: ("off ramp", "right", 4),
      #new
      13: ("turn", "right", 2),
      19: ("turn", "sharp right", 2),
      102: ("off ramp", "slight left", 3),
      105: ("off ramp", "slight left", 3),
      112: ("off ramp", "slight left", 3),
      115: ("off ramp", "slight left", 3),
      101: ("off ramp", "slight right", 4),
      104: ("off ramp", "slight right", 4),
      111: ("off ramp", "slight right", 4),
      114: ("off ramp", "slight right", 4),
      7: ("fork", "left", 3),
      44: ("fork", "left", 3),
      17: ("fork", "left", 3),
      75: ("fork", "left", 3),
      76: ("fork", "left", 3),
      118: ("fork", "left", 3),
      6: ("fork", "right", 4),
      43: ("fork", "right", 4),
      73: ("fork", "right", 4),
      74: ("fork", "right", 4),
      123: ("fork", "right", 4),
      124: ("fork", "right", 4),
      117: ("fork", "right", 4),
      131: ("rotary", "slight right", 5),
      132: ("rotary", "slight right", 5),
      140: ("rotary", "slight left", 5),
      141: ("rotary", "slight left", 5),
      133: ("rotary", "right", 5),
      134: ("rotary", "sharp right", 5),
      135: ("rotary", "sharp right", 5),
      136: ("rotary", "sharp left", 5),
      137: ("rotary", "sharp left", 5),
      138: ("rotary", "sharp left", 5),
      139: ("rotary", "left", 5),
      142: ("rotary", "straight", 5),
      14: ("turn", "uturn", 7),
      201: ("arrive", "straight", 8),
      51: ("notification", "straight", 0),
      52: ("notification", "straight", 0),
      53: ("notification", "straight", 0),
      54: ("notification", "straight", 0),
      55: ("notification", "straight", 0),
      153: ("", "", 6),  #TG
      154: ("", "", 6),  #TG
      249: ("", "", 6)   #TG
    }

    if self.nTBTTurnType in turn_type_mapping:
      self.navType, self.navModifier, self.xTurnInfo = turn_type_mapping[self.nTBTTurnType]
    else:
      self.navType, self.navModifier, self.xTurnInfo = "invalid", "", -1

    if self.nTBTTurnTypeNext in turn_type_mapping:
      self.navTypeNext, self.navModifierNext, self.xTurnInfoNext = turn_type_mapping[self.nTBTTurnTypeNext]
    else:
      self.navTypeNext, self.navModifierNext, self.xTurnInfoNext = "invalid", "", -1

    if self.nTBTDist > 0 and self.xTurnInfo > 0:
      self.xDistToTurnNav = self.nTBTDist
      # 检测是否进入了下一个导航距离提示
      if self.xDistToTurnNav > (self.xDistToTurnNavLast + 20):  # 当距离路口距离比上次大于20米时，则记录为当前最大的路口距离
        self.xDistToTurnMax = self.xDistToTurnNav
        self.xDistToTurnMaxCnt += 1
      self.xDistToTurnNavLast = self.xDistToTurnNav  # 当前距离更新到上次距离时

      self.xDistToTurn = self.nTBTDist
    if self.nTBTDistNext > 0 and self.xTurnInfoNext > 0:
      self.xDistToTurnNext = self.nTBTDistNext + self.nTBTDist

  def _get_sdi_descr(self, nSdiType):
    sdi_types = {
      0: "信号超速",
      1: "超速 (固定式)",
      2: "区间测速开始",
      3: "区间测速结束",
      4: "区间测速中",
      5: "跟车抓拍摄像头",
      6: "闯红灯抓拍",
      7: "超速 (移动式)",
      8: "固定式超速危险区（箱式）",
      9: "公交专用车道区间",
      10: "可变车道抓拍",
      11: "应急车道监控点",
      12: "禁止强行并线",
      13: "交通信息采集点",
      14: "治安监控 CCTV",
      15: "超载车辆危险区",
      16: "货物装载不良抓拍",
      17: "违停抓拍点",
      18: "单行道",
      19: "铁路道口",
      20: "儿童保护区（学校路段开始）",
      21: "儿童保护区（学校路段结束）",
      22: "减速带",
      23: "LPG 加气站",
      24: "隧道路段",
      25: "服务区",
      26: "收费站",
      27: "大雾多发区",
      28: "危险化学品区域",
      29: "事故多发区",
      30: "急转弯区域",
      31: "急转弯路段1",
      32: "陡坡路段",
      33: "野生动物事故多发区",
      34: "右侧视野不良点",
      35: "视野不良点",
      36: "左侧视野不良点",
      37: "闯红灯多发路段",
      38: "超速行驶多发路段",
      39: "交通拥堵区域",
      40: "分向车道选择点",
      41: "行人乱穿事故多发点",
      42: "应急车道事故多发点",
      43: "超速事故多发点",
      44: "疲劳驾驶事故多发点",
      45: "事故多发点",
      46: "行人事故多发点",
      47: "车辆盗窃事故高发点",
      48: "落石危险区",
      49: "结冰危险区",
      50: "瓶颈路段",
      51: "汇入道路",
      52: "坠落危险区",
      53: "地下通道路段",
      54: "住宅密集区（交通缓解区）",
      55: "立交桥",
      56: "分岔点",
      57: "服务区（可加 LPG）",
      58: "桥梁",
      59: "制动装置事故多发点",
      60: "逆行事故多发点",
      61: "违规通行事故多发点",
      62: "目的地对面提示",
      63: "疲劳驾驶休息区提示",
      64: "老旧柴油车抓拍",
      65: "隧道内变道抓拍",
      66: ""
    }
    return sdi_types.get(nSdiType, "")

  def _update_sdi(self):

    #new
    if self.sameSpiCamFilter:
      if (self.nSdiTypeLast == self.nSdiType and self.nSdiSpeedLimitLast == self.nSdiSpeedLimit and
        self.nSdiDistLast == self.nSdiDist and self.nSdiPlusTypeLast == self.nSdiPlusType  and
        self.autoNaviSpeedCtrlModeLast == self.autoNaviSpeedCtrlMode and self.autoNaviSpeedSafetyFactorLast == self.autoNaviSpeedSafetyFactor):
        return

      self.nSdiTypeLast = self.nSdiType
      self.nSdiSpeedLimitLast = self.nSdiSpeedLimit
      self.nSdiDistLast = self.nSdiDist
      self.nSdiPlusTypeLast = self.nSdiPlusType
      self.autoNaviSpeedCtrlModeLast = self.autoNaviSpeedCtrlMode
      self.autoNaviSpeedSafetyFactorLast = self.autoNaviSpeedSafetyFactor
    #new

    #sdiBlockType
    # 1: startOSEPS:开始管制区间
    # 2: inOSEPS:区间管制中
    # 3: endOSEPS:区间管制结束
    # 0:不减速;1:超速摄像机;2:+事故防止带;3:+移动式摄像机
    if self.nSdiType in [0,1,2,3,4,7,8, 75, 76] and self.nSdiSpeedLimit > 0 and self.autoNaviSpeedCtrlMode > 0:
      self.xSpdLimit = self.nSdiSpeedLimit * self.autoNaviSpeedSafetyFactor
      self.xSpdDist = self.nSdiDist
      self.xSpdType = self.nSdiType
      if self.nSdiBlockType in [2,3]: #2区间测速起点 3终点
        self.xSpdDist = self.nSdiBlockDist
        self.xSpdType = 4
      elif self.nSdiType == 7 and self.autoNaviSpeedCtrlMode < 3: #7移动测速, autoNaviSpeedCtrlMode<3表示未设置移动测速限速
        self.xSpdLimit = self.xSpdDist = 0
      #new 人为把测速摄像头的距离减去100m
      #else:
      #  if self.nSdiDist > 100:
      #    self.xSpdDist = self.nSdiDist - 100
      #  else:
      #    self.xSpdDist = 0
      #new
    #elif (self.nSdiPlusType == 22 or self.nSdiType == 22) and self.roadcate > 1 and self.autoNaviSpeedCtrlMode >= 2: # 22-speed bump, roadcate:0,1: highway
    #elif (self.nSdiPlusType == 22 or self.nSdiType == 22) and self.xroadcate > 1 and self.autoNaviSpeedCtrlMode >= 2:  # 22-speed bump, roadcate:0,1: highway
    #  self.xSpdLimit = self.autoNaviSpeedBumpSpeed
    #  self.xSpdDist = self.nSdiPlusDist if self.nSdiPlusType == 22 else self.nSdiDist
    #  self.xSpdType = 22
    else:
      self.xSpdLimit = 0
      self.xSpdType = -1
      self.xSpdDist = 0

  def _update_gps(self, v_ego, sm):
    llk = 'liveLocationKalman'
    location = sm[llk]
    #print(f"location = {sm.valid[llk]}, {sm.updated[llk]}, {sm.recv_frame[llk]}, {sm.recv_time[llk]}")
    if not sm.updated['carState'] or not sm.updated['carControl']: # or not sm.updated[llk]:
      return self.nPosAngle
    CS = sm['carState']
    CC = sm['carControl']
    self.gps_valid = (location.status == log.LiveLocationKalman.Status.valid) and location.positionGeodetic.valid

    now = time.monotonic()
    gps_updated_phone = (now - self.last_update_gps_time_phone) < 3
    gps_updated_navi = (now - self.last_update_gps_time_navi) < 3

    bearing = self.nPosAngle
    if gps_updated_phone:
      self.bearing_offset = 0.0
    elif sm.valid[llk]:
      orientation = location.calibratedOrientationNED.value
      if len(orientation) >= 3:
        bearing = math.degrees(orientation[2])
      else:
        bearing = 0
      if self.gps_valid:
        self.bearing_offset = 0.0
      elif self.active_carrot > 0:
        bearing = self.nPosAnglePhone
        self.bearing_offset = 0.0

    #print(f"bearing = {bearing:.1f}, posA=={self.nPosAngle:.1f}, posP=={self.nPosAnglePhone:.1f}, offset={self.bearing_offset:.1f}, {gps_updated_phone}, {gps_updated_navi}")
    gpsDelayTimeAdjust = 0.0
    if gps_updated_navi:
      gpsDelayTimeAdjust = 1.0

    external_gps_update_timedout = not (gps_updated_phone or gps_updated_navi)
    #print(f"gps_valid = {self.gps_valid}, bearing = {bearing:.1f}, pos = {location.positionGeodetic.value[0]:.6f}, {location.positionGeodetic.value[1]:.6f}")
    if self.gps_valid and external_gps_update_timedout:    # 내부GPS가 자동하고 carrotman으로부터 gps신호가 없는경우
      self.vpPosPointLatNavi = location.positionGeodetic.value[0]
      self.vpPosPointLonNavi = location.positionGeodetic.value[1]
      self.last_calculate_gps_time = now #sm.recv_time[llk]
    elif gps_updated_navi:  # carrot navi로부터 gps신호가 수신되는 경우..
      if abs(self.bearing_measured - bearing) < 0.1:
          self.diff_angle_count += 1
      else:
          self.diff_angle_count = 0
      self.bearing_measured = bearing

      if self.diff_angle_count > 5: # 조향각도변화가 거의 없을때만 업데이트
        diff_angle = (self.nPosAngle - bearing) % 360
        if diff_angle > 180:
          diff_angle -= 360
        self.bearing_offset = self.bearing_offset * 0.9 + diff_angle * 0.1

    bearing_calculated = (bearing + self.bearing_offset) % 360

    dt = now - self.last_calculate_gps_time
    #print(f"dt = {dt:.1f}, {self.vpPosPointLatNavi}, {self.vpPosPointLonNavi}")
    if dt > 5.0:
      self.vpPosPointLat, self.vpPosPointLon = 0.0, 0.0
    elif dt == 0:
      self.vpPosPointLat, self.vpPosPointLon = self.vpPosPointLatNavi, self.vpPosPointLonNavi
    else:
      self.vpPosPointLat, self.vpPosPointLon = self.estimate_position(float(self.vpPosPointLatNavi), float(self.vpPosPointLonNavi), v_ego, bearing_calculated, dt + gpsDelayTimeAdjust)

    #self.debugText = " {} {:.1f},{:.1f}={:.1f}+{:.1f}".format(self.active_sdi_count, self.nPosAngle, bearing_calculated, bearing, self.bearing_offset)
    #print("nPosAngle = {:.1f},{:.1f} = {:.1f}+{:.1f}".format(self.nPosAngle, bearing_calculated, bearing, self.bearing_offset))

    return float(bearing_calculated)


  def estimate_position(self, lat, lon, speed, angle, dt):
    R = 6371000
    angle_rad = math.radians(angle)
    delta_d = speed * dt
    delta_lat = delta_d * math.cos(angle_rad) / R
    new_lat = lat + math.degrees(delta_lat)
    delta_lon = delta_d * math.sin(angle_rad) / (R * math.cos(math.radians(lat)))
    new_lon = lon + math.degrees(delta_lon)

    return new_lat, new_lon

  def update_auto_turn(self, v_ego_kph, sm, x_turn_info, x_dist_to_turn, check_steer=False):
    turn_speed = self.autoTurnControlSpeedTurn
    fork_speed = self.nRoadLimitSpeed
    stop_speed = 1
    turn_dist_for_speed = self.autoTurnControlTurnEnd * turn_speed / 3.6 # 5
    fork_dist_for_speed = self.autoTurnControlTurnEnd * fork_speed / 3.6 # 5
    stop_dist_for_speed = 5
    if self.xroadcate > 1:
      fork_dist_offset = self.autoForkDistOffset
      start_fork_dist = np.interp(self.nRoadLimitSpeed, [30, 50, 100], [160, 200, 350]) + fork_dist_offset
      do_fork_dist = fork_dist_for_speed + self.autoDoForkBlinkerDist
      do_speed_decal_dist = fork_dist_for_speed + self.autoDoForkDecalDist
      auto_decel_rate = self.autoForkDecalRate
      decel_speed_min = self.autoForkSpeedMin
      do_fork_nav_dist = self.autoDoForkNavDist
      fork_speed_keep_time = self.autoKeepForkSpeed
    else:
      fork_dist_offset = self.autoForkDistOffsetH
      start_fork_dist = np.interp(self.nRoadLimitSpeed, [30, 50, 100], [160, 200, 350]) + fork_dist_offset
      do_fork_dist = fork_dist_for_speed + self.autoDoForkBlinkerDistH
      do_speed_decal_dist = fork_dist_for_speed + self.autoDoForkDecalDistH
      auto_decel_rate = self.autoForkDecalRateH
      decel_speed_min = self.autoForkSpeedMinH
      do_fork_nav_dist = self.autoDoForkNavDistH
      fork_speed_keep_time = self.autoKeepForkSpeedH

    #对两个fork距离进行限制
    if do_fork_nav_dist > 0:
      do_fork_dist = max(do_fork_dist, do_fork_nav_dist)

    #对变道和转弯距离作一个限制，不能比最大路口距离的80%还大
    max_dist = self.xDistToTurnMax*0.8
    if do_fork_dist > max_dist:
      do_fork_dist = max_dist
    if start_fork_dist > max_dist:
      start_fork_dist = max_dist

    start_turn_dist = np.interp(self.nTBTNextRoadWidth, [5, 10], [43, 60]) + self.autoTurnDistOffset
    turn_info_mapping = {
        1: {"type": "turn left", "speed": turn_speed, "dist": turn_dist_for_speed, "start": start_fork_dist},
        2: {"type": "turn right", "speed": turn_speed, "dist": turn_dist_for_speed, "start": start_fork_dist},
        5: {"type": "straight", "speed": turn_speed, "dist": turn_dist_for_speed, "start": start_turn_dist},
        3: {"type": "fork left", "speed": fork_speed, "dist": do_fork_dist, "start": start_fork_dist},
        4: {"type": "fork right", "speed": fork_speed, "dist": do_fork_dist, "start": start_fork_dist},
        6: {"type": "straight", "speed": fork_speed, "dist": fork_dist_for_speed, "start": start_fork_dist},
        7: {"type": "straight", "speed": stop_speed, "dist": stop_dist_for_speed, "start": 1000},
        8: {"type": "straight", "speed": stop_speed, "dist": stop_dist_for_speed, "start": 1000},
    }

    default_mapping = {"type": "none", "speed": 0, "dist": 0, "start": 1000}

    mapping = turn_info_mapping.get(x_turn_info, default_mapping)

    atc_type = mapping["type"]
    atc_speed = mapping["speed"]
    atc_dist = mapping["dist"] #这个距离主要是用来提前减速的距离
    atc_start_dist = mapping["start"]
    atc_type_org = atc_type
    atc_speed_org = atc_speed

    #导航给出在转弯距离大于开始转弯距离时，进入准备阶段
    if x_dist_to_turn > atc_start_dist:
      atc_type += " prepare"
      if check_steer:
        self.atc_activate_count = min(0, self.atc_activate_count - 1)
    else:
      if check_steer:
        self.atc_activate_count = max(0, self.atc_activate_count + 1)

      if (atc_type in ["turn left", "turn right"]) and (x_dist_to_turn > start_turn_dist):
        atc_type = "atc left" if "left" in atc_type else "atc right" #类型为atc left/right只是进入转弯准备状态，并不是真的在执行转弯
      elif atc_type in ["fork left", "fork right"]: #说明x_dist_to_turn>do_fork_dist并且说明x_dist_to_turn <=atc_start_dist
        #atc_dist = do_speed_decal_dist #替换减速距离
        if (fork_dist_offset > 0) and (x_dist_to_turn > do_fork_dist): #设置了提前变道距离，并且剩余距离大于进入匝道口距离，则执行提前变道流程
          atc_type = "atc left" if "left" in atc_type else "atc right"
        elif (do_fork_nav_dist > 0) and (x_dist_to_turn <= do_fork_nav_dist): #设置了导航距离控制转弯后，如果距离小于设置值是立即变道
          atc_type += " now"
        if x_dist_to_turn < do_speed_decal_dist: #距离路口的距离小于设定值时要开始减速了，因为到匝道口前nRoadLimitSpeed其实没有变，所以只能用这种方法进行减速
          if auto_decel_rate > 0: #设置了减速比率
            if atc_speed > decel_speed_min: #只有车速大于60时才允许降速
              atc_speed = max(decel_speed_min, atc_speed*auto_decel_rate)
          if check_steer:
            self.atc_speed_decal = atc_speed #保存进匝道减速的目标速度
            self.fork_speed_keep_time = int(fork_speed_keep_time/DT_MDL) #重置时间
    #如果上面的条件都不成立，则atc_type直接就是查表得到的类型，即atc_type = mapping["type"]

    #是否保持进匝道时的速度
    if check_steer:
      if atc_type_org in ["fork left", "fork right"] and self.atc_speed_decal > 0:
        self.fork_speed_keep_time = min(-1, self.fork_speed_keep_time - 1)  # 保持速度的时间递减
        if self.fork_speed_keep_time > 0:
          atc_speed = min(atc_speed, self.atc_speed_decal) #保持之前的速度
        if self.fork_speed_keep_time == 0:
          self.atc_speed_decal = 0
      else:
        self.fork_speed_keep_time = -1
        self.atc_speed_decal = 0

    if self.autoTurnMapChange > 0 and check_steer:
      #print(f"x_dist_to_turn: {x_dist_to_turn}, atc_start_dist: {atc_start_dist}")
      #print(f"atc_activate_count: {self.atc_activate_count}")
      if self.atc_activate_count == 2:
        self.carrotCmdIndex += 100
        self.carrotCmd = "DISPLAY"
        self.carrotArg = "MAP"
      elif self.atc_activate_count == -50:
        self.carrotCmdIndex += 100
        self.carrotCmd = "DISPLAY"
        self.carrotArg = "ROAD"

    #处理在变道过程中，如果用户接管了方向盘，则退出变道
    if check_steer:
      if 0 <= x_dist_to_turn < atc_start_dist and atc_type in ["fork left", "fork right"]:
        if not self.atc_paused:
          steering_pressed = sm["carState"].steeringPressed
          steering_torque = sm["carState"].steeringTorque
          if steering_pressed and steering_torque < 0 and atc_type in ["fork left", "atc left"]:
            self.atc_paused = True
          elif steering_pressed and steering_torque > 0 and atc_type in ["fork right", "atc right"]:
            self.atc_paused = True
      else:
        self.atc_paused = False

      if self.atc_paused:
        atc_type += " canceled"
    # 处理在变道过程中，如果用户接管了方向盘，则退出变道

    atc_desired = 250
    if atc_speed > 0 and x_dist_to_turn > 0:
      decel = self.autoNaviSpeedDecelRate
      safe_sec = 2.0
      atc_desired = min(atc_desired, self.calculate_current_speed(x_dist_to_turn - atc_dist, atc_speed, safe_sec, decel))

    if (self.showDebugLog & 1) > 0 and check_steer:
      debugText = (f"***atc info: type={atc_type_org},{atc_type},xdist={x_dist_to_turn:.1f},max_xdist={self.xDistToTurnMax:.1f}(cnt:{self.xDistToTurnMaxCnt})," +
                   f"start_dist={atc_start_dist:.1f},atc_dist={atc_dist:.1f},fork_dist={do_fork_dist:.1f}," +
                   f"[fork_dist_offset={fork_dist_offset:.1f},nav_fork_dist={do_fork_nav_dist:.1f},dec_dist={do_speed_decal_dist:.1f}]," +
                   f"atc_speed={atc_speed_org:.1f},{atc_speed:.1f},fork keep:{self.fork_speed_keep_time:.1f}s,{self.atc_speed_decal:.1f}km/h,paused={self.atc_paused}"
                   )
      print(debugText)

    return atc_desired, atc_type, atc_speed, atc_dist

  def update_nav_instruction(self, sm):
    if sm.alive['navInstruction'] and sm.valid['navInstruction']:
      msg_nav = sm['navInstruction']

      self.nGoPosDist = int(msg_nav.distanceRemaining)
      self.nGoPosTime = int(msg_nav.timeRemaining)
      if self.active_kisa_count <= 0 and msg_nav.speedLimit > 0:
        self.nRoadLimitSpeed = max(30, round(msg_nav.speedLimit * CV.MS_TO_KPH))
      self.xDistToTurn = int(msg_nav.maneuverDistance)
      self.xDistToTurnNav = int(msg_nav.maneuverDistance)
      self.szTBTMainText = msg_nav.maneuverPrimaryText
      self.xTurnInfo = -1
      for key, value in nav_type_mapping.items():
        if value[0] == msg_nav.maneuverType and value[1] == msg_nav.maneuverModifier:
          self.xTurnInfo = value[2]
          break

      self.debugText = f"{self.nRoadLimitSpeed},{msg_nav.maneuverType},{msg_nav.maneuverModifier} "
      #print(msg_nav)
      #print(f"navInstruction: {self.xTurnInfo}, {self.xDistToTurn}, {self.szTBTMainText}")

  def update_kisa(self, data):
    self.active_kisa_count = 100
    if "kisawazecurrentspd" in data:
      pass
    if "kisawazeroadspdlimit" in data:
      road_limit_speed = data["kisawazeroadspdlimit"]
      if road_limit_speed > 0:
        print(f"kisawazeroadspdlimit: {road_limit_speed} km/h")
        if not self.is_metric:
          road_limit_speed *= CV.MPH_TO_KPH
        self.nRoadLimitSpeed = road_limit_speed
    if "kisawazealert" in data:
      pass
    if "kisawazeendalert" in data:
      pass
    if "kisawazeroadname" in data:
      print(f"kisawazeroadname: {data['kisawazeroadname']}")
      self.szPosRoadName = data["kisawazeroadname"]
    if "kisawazereportid" in data and "kisawazealertdist" in data:
      id_str = data["kisawazereportid"]
      dist_str = data["kisawazealertdist"].lower()
      import re
      match = re.search(r'(\d+)', dist_str)
      distance = int(match.group(1)) if match else 0
      if not self.is_metric:
        distance = int(distance * 0.3048)
      print(f"{id_str}: {distance} m")
      xSpdType = -1
      if 'camera' in id_str:
        xSpdType = 101    # 101: waze speed cam, 100: police
      elif 'police' in id_str:
        xSpdType = 100

      if xSpdType >= 0:
        offset = 5 if self.is_metric else 5 * CV.MPH_TO_KPH
        self.xSpdLimit = self.nRoadLimitSpeed + offset

        self.xSpdDist = distance
        self.xSpdType =xSpdType

  def update_navi(self, remote_ip, sm, pm, vturn_speed, coords, distances, route_speed):

    self.debugText = ""
    self.update_params()
    if sm.alive['carState'] and sm.alive['controlsStateSP']:
      CS = sm['carState']
      v_ego = CS.vEgo
      v_ego_kph = v_ego * 3.6
      distanceTraveled = sm['controlsStateSP'].distanceTraveled
      delta_dist = distanceTraveled - self.totalDistance
      self.totalDistance = distanceTraveled
      #if CS.speedLimit > 0 and self.active_carrot <= 1:
      #  self.nRoadLimitSpeed = CS.speedLimit
    else:
      v_ego = v_ego_kph = 0
      delta_dist = 0
      CS = None

    road_speed_limit_changed = True if self.nRoadLimitSpeed != self.nRoadLimitSpeed_last else False
    self.nRoadLimitSpeed_last = self.nRoadLimitSpeed
    #self.bearing = self.nPosAngle #self._update_gps(v_ego, sm)
    self.bearing = self._update_gps(v_ego, sm)

    #根据车辆行驶的距离更新导航的所有距离信息
    self.xSpdDist = max(self.xSpdDist - delta_dist, -1000)
    self.xDistToTurn = self.xDistToTurn - delta_dist
    self.xDistToTurnNext = self.xDistToTurnNext - delta_dist
    self.active_count = max(self.active_count - 1, 0)
    self.active_sdi_count = max(self.active_sdi_count - 1, 0)
    self.active_kisa_count = max(self.active_kisa_count - 1, 0)
    if self.active_kisa_count > 0:
      self.active_carrot = 2

    elif self.active_count > 0:
      self.active_carrot = 2 if self.active_sdi_count > 0 else 1
    else:
      self.active_carrot = 0

    if self.autoRoadSpeedLimitOffset >= 0 and self.active_carrot>=2:
      if self.nRoadLimitSpeed >= 30:
        road_speed_limit_offset = self.autoRoadSpeedLimitOffset
        if not self.is_metric:
          road_speed_limit_offset *= CV.KPH_TO_MPH
        limit_speed = self.nRoadLimitSpeed + road_speed_limit_offset
      #new
      elif self.nRoadLimitSpeed > 0:
        limit_speed = 30
      else:
        limit_speed = 200
      #new
    else:
      limit_speed = 200 #如果autoRoadSpeedLimitOffset小于0，说明道路限速不生效

    self.nRoadLimitSpeedSend = limit_speed

    if self.active_carrot <= 1:
      self.xSpdType = self.navType = self.xTurnInfo = self.xTurnInfoNext = -1
      self.nSdiType = self.nSdiBlockType = self.nSdiPlusBlockType = -1
      self.nTBTTurnType = self.nTBTTurnTypeNext = -1
      self.roadcate = 8
      self.nGoPosDist = 0
    if self.active_carrot <= 1 or self.active_kisa_count > 0:
      self.update_nav_instruction(sm)

    if self.xSpdType < 0 or (self.xSpdType not in [100,101] and self.xSpdDist <= 0) or (self.xSpdType in [100,101] and self.xSpdDist < -250):
      self.xSpdType = -1
      self.xSpdDist = self.xSpdLimit = 0
    if self.xTurnInfo < 0 or self.xDistToTurn < -50:
      if self.xDistToTurn > 0:
        self.xDistToTurn = 0
      self.xTurnInfo = -1
      self.xDistToTurnNext = 0
      self.xTurnInfoNext = -1

    sdi_speed = 250
    hda_active = False
    ### 超速摄影机和减速带减速处理
    if (self.xSpdDist > 0 or self.xSpdType in [100, 101]) and self.active_carrot > 0 and self.xSpdType != 22: #2025.9.16 add 不再处理减速带
      safe_sec = self.autoNaviSpeedBumpTime if self.xSpdType == 22 else self.autoNaviSpeedCtrlEnd
      decel = self.autoNaviSpeedDecelRate
      sdi_speed = min(sdi_speed, self.calculate_current_speed(self.xSpdDist, self.xSpdLimit, safe_sec, decel))
      self.active_carrot = 5 if self.xSpdType == 22 else 3
      if self.xSpdType == 4 or (self.xSpdType in [100, 101] and self.xSpdDist <= 0):
        sdi_speed = self.xSpdLimit
        self.active_carrot = 4
    sdi_speed_name = "hda" if hda_active else "bump" if self.xSpdType == 22 else "section" if self.xSpdType == 4 else "police" if self.xSpdType == 100 else "waze" if self.xSpdType == 101 else "cam"
    #elif CS is not None and CS.speedLimit > 0 and CS.speedLimitDistance > 0:
    #  sdi_speed = min(sdi_speed,
    #                  self.calculate_current_speed(CS.speedLimitDistance,
    #                                               CS.speedLimit * self.autoNaviSpeedSafetyFactor,
    #                                               self.autoNaviSpeedCtrlEnd,
    #                                               self.autoNaviSpeedDecelRate))
    #  #self.active_carrot = 6
    #  hda_active = True

    #print(f"sdi_speed: {sdi_speed}, hda_active: {hda_active}, xSpdType: {self.xSpdType}, xSpdDist: {self.xSpdDist}, active_carrot: {self.active_carrot}, v_ego_kph: {v_ego_kph}, nRoadLimitSpeed: {self.nRoadLimitSpeed}")
    ### TBT速度控制 self.atcSpeed, self.atcDist这两个变量均未用上
    atc_desired, self.atcType, _, _ = self.update_auto_turn(v_ego*3.6, sm, self.xTurnInfo, self.xDistToTurn, True)
    atc_desired_next, _, _, _ = self.update_auto_turn(v_ego*3.6, sm, self.xTurnInfoNext, self.xDistToTurnNext, False)

    if self.autoTurnControl not in [2, 3]:    # auto turn speed control
      atc_desired = atc_desired_next = 250
    if self.autoTurnControl not in [1,2]:    # auto turn control
      self.atcType = "none"

    speed_n_sources = [
      (atc_desired, "atc"),
      (atc_desired_next, "atc2"),
      #(sdi_speed, "hda" if hda_active else "bump" if self.xSpdType == 22 else "section" if self.xSpdType == 4 else "police" if self.xSpdType == 100 else "waze" if self.xSpdType == 101 else "cam"),
      #(limit_speed, "road"),
    ]
    if (self.cpSpdAndRoadLimit & 1) > 0:
      speed_n_sources.append((sdi_speed, "hda" if hda_active else "bump" if self.xSpdType == 22 else "section" if self.xSpdType == 4 else "police" if self.xSpdType == 100 else "waze" if self.xSpdType == 101 else "cam"))
    if (self.cpSpdAndRoadLimit & 2) > 0:
      speed_n_sources.append((limit_speed, "road"))
    if self.turnSpeedControlMode in [1,2]: #模式1和2均有视觉转弯控速,autoCurveSpeedLowerLimit为用户设置的最小转弯速度，vturn_speed这视觉计算的限速
      speed_n_sources.append((max(abs(vturn_speed), self.autoCurveSpeedLowerLimit), "vturn"))

    route_speed = max(route_speed * self.mapTurnSpeedFactor, self.autoCurveSpeedLowerLimit)
    if self.turnSpeedControlMode == 2:
      if -500 < self.xDistToTurn < 500:
        speed_n_sources.append((route_speed, "route"))
    elif self.turnSpeedControlMode == 3:
      speed_n_sources.append((route_speed, "route"))
      #speed_n_sources.append((self.calculate_current_speed(dist, speed * self.mapTurnSpeedFactor, 0, 1.2), "route"))

    desired_speed, source = min(speed_n_sources, key=lambda x: x[0])

    if CS is not None:
      if source != self.source_last:
        self.gas_override_speed = 0
        self.gas_pressed_state = CS.gasPressed
      if CS.vEgo < 0.1 or desired_speed > 150 or source in ["cam", "section", "police"] or CS.brakePressed or road_speed_limit_changed:
        self.gas_override_speed = 0
      elif CS.gasPressed and not self.gas_pressed_state:
        self.gas_override_speed = max(v_ego_kph, self.gas_override_speed)
      else:
        self.gas_pressed_state = False
      self.source_last = source

      if desired_speed < self.gas_override_speed:
        source = "gas"
        desired_speed = self.gas_override_speed

      self.debugText += f"route={route_speed:.1f}"#f"desired={desired_speed:.1f},{source},g={self.gas_override_speed:.0f}"

    #new 根据当前速度计算到转弯引导点需要的时间
    if self.xDistToTurn > 0:
      left_turn_sec = min(1000, int(min(200000,max(self.xDistToTurn - v_ego, 1)) / max(1, v_ego) + 0.5))
    else:
      left_turn_sec = 0
    #new

    left_spd_sec = 100
    left_tbt_sec = 100
    if self.autoNaviCountDownMode > 0:
      if self.xSpdType == 22 and self.autoNaviCountDownMode == 1: # speed bump
        pass
      else:
        if self.xSpdDist > 0:
          left_spd_sec = min(self.left_spd_sec, int(max(self.xSpdDist - v_ego, 1) / max(1, v_ego) + 0.5))

      if self.xDistToTurn > 0:
        left_tbt_sec = min(self.left_tbt_sec, int(max(self.xDistToTurn - v_ego, 1) / max(1, v_ego) + 0.5))

    self.left_spd_sec = left_spd_sec
    self.left_tbt_sec = left_tbt_sec

    left_sec = min(left_spd_sec, left_tbt_sec)

    if left_sec > 11:
      self.left_sec = 100
      self.max_left_sec = 100
    else:
      self.sdi_inform = True if source in ["cam", "hda"] else False
      self.max_left_sec = min(11, max(6, int(v_ego_kph/10) + 1))

    if left_sec != self.left_sec:
      if left_sec == self.max_left_sec and self.sdi_inform:
        self.carrot_left_sec = 11
      elif 1 <= left_sec < self.max_left_sec:
        self.carrot_left_sec = left_sec
      elif left_sec == 0 and self.left_sec == 1:
        self.carrot_left_sec = left_sec

      self.left_sec = left_sec

    self._update_cmd()
    msg = messaging.new_message('carrotMan')
    msg.valid = True
    msg.carrotMan.activeCarrot = self.active_carrot
    #msg.carrotMan.nRoadLimitSpeed = int(self.nRoadLimitSpeed)
    msg.carrotMan.nRoadLimitSpeed = int(self.nRoadLimitSpeedSend)
    msg.carrotMan.remote = remote_ip
    msg.carrotMan.xSpdType = int(self.xSpdType)
    msg.carrotMan.xSpdLimit = int(self.xSpdLimit)
    msg.carrotMan.xSdiSpeed = int(sdi_speed)
    msg.carrotMan.xSdiSpeedName = sdi_speed_name
    msg.carrotMan.xSpdDist = int(self.xSpdDist)
    msg.carrotMan.xSpdCountDown = int(left_spd_sec)
    msg.carrotMan.xTurnInfo = int(self.xTurnInfo)
    msg.carrotMan.xDistToTurn = int(self.xDistToTurn)
    msg.carrotMan.xTurnCountDown = int(left_tbt_sec)
    msg.carrotMan.atcType = self.atcType
    msg.carrotMan.vTurnSpeed = int(vturn_speed)
    msg.carrotMan.szPosRoadName = self.szPosRoadName + self.debugText
    msg.carrotMan.szTBTMainText = self.szTBTMainText
    msg.carrotMan.desiredSpeed = int(desired_speed)
    msg.carrotMan.desiredSource = source
    msg.carrotMan.carrotCmdIndex = int(self.carrotCmdIndex)
    msg.carrotMan.carrotCmd = self.carrotCmd
    msg.carrotMan.carrotArg = self.carrotArg
    msg.carrotMan.trafficState = self.traffic_state

    #new
    msg.carrotMan.xDistToTurnNav = int(self.xDistToTurnNav)
    msg.carrotMan.xDistToTurnNavLast = int(self.xDistToTurnNavLast)
    msg.carrotMan.xDistToTurnMax = int(self.xDistToTurnMax)
    msg.carrotMan.xDistToTurnMaxCnt = int(self.xDistToTurnMaxCnt)
    msg.carrotMan.xLeftTurnSec = int(left_turn_sec)
    msg.carrotMan.roadCate = int(self.xroadcate)
    msg.carrotMan.extBlinker = int(self.ext_blinker)
    msg.carrotMan.extState = int(self.ext_state)
    #new

    msg.carrotMan.xPosSpeed = float(v_ego_kph) #float(self.nPosSpeed)
    msg.carrotMan.xPosAngle = float(self.bearing)
    msg.carrotMan.xPosLat = float(self.vpPosPointLat)
    msg.carrotMan.xPosLon = float(self.vpPosPointLon)

    msg.carrotMan.nGoPosDist = self.nGoPosDist
    msg.carrotMan.nGoPosTime = self.nGoPosTime
    msg.carrotMan.szSdiDescr = self._get_sdi_descr(-1 if self.nSdiType == 0 and self.nSdiDist == 0 else self.nSdiType)

    #coords_str = ";".join([f"{x},{y}" for x, y in coords])
    coords_str = ";".join([f"{x:.2f},{y:.2f},{d:.2f}" for (x, y), d in zip(coords, distances, strict=False)])
    msg.carrotMan.naviPaths = coords_str

    msg.carrotMan.leftSec = int(self.carrot_left_sec)
    pm.send('carrotMan', msg)

  def update(self, json):
    if json is None:
      return
    if "carrotIndex" in json:
      self.carrotIndex = int(json.get("carrotIndex"))

    #print(json)
    #if self.carrotIndex % 60 == 0 and "epochTime" in json:
    #  # op는 ntp를 사용하기때문에... 필요없는 루틴으로 보임.
    #  timezone_remote = json.get("timezone", "Asia/Seoul")

    #  if not PC:
    #    self.set_time(int(json.get("epochTime")), timezone_remote)

      #self._update_system_time(int(json.get("epochTime")), timezone_remote)

    if "carrotCmd" in json:
      #print(json.get("carrotCmd"), json.get("carrotArg"))
      self.carrotCmdIndex = self.carrotIndex
      self.carrotCmd = json.get("carrotCmd")
      self.carrotArg = json.get("carrotArg")
      #print(f"carrotCmd = {self.carrotCmd}, {self.carrotArg}")

    self.active_count = 80
    now = time.monotonic()

    if "goalPosX" in json:
      self.goalPosX = float(json.get("goalPosX", self.goalPosX))
      self.goalPosY = float(json.get("goalPosY", self.goalPosY))
      self.szGoalName = json.get("szGoalName", self.szGoalName)

    if "nRoadLimitSpeed" in json:
      #print(json)
      self.active_sdi_count = self.active_sdi_count_max
      ### roadLimitSpeed
      nRoadLimitSpeed = int(json.get("nRoadLimitSpeed", 20))
      if nRoadLimitSpeed > 0:
        if nRoadLimitSpeed > 200:
          nRoadLimitSpeed = (nRoadLimitSpeed - 20) / 10
        elif nRoadLimitSpeed > 120:
          nRoadLimitSpeed = 120

        # 高速公路低限速值处理，低速是自动增加偏移值
        if nRoadLimitSpeed < 60 and ((self.xroadcate <= 1 and self.autoUpHighwayRoadLimit) or (self.xroadcate > 1 and self.autoUpRoadLimit)):  # 高速公路 (0,1: highway)
          if self.xroadcate <= 1:
            max_add_val = self.autoUpHighwayRoadLimit40KMH
          else:
            max_add_val = self.autoUpRoadLimit40KMH
          if nRoadLimitSpeed <= 40:
            add_val = max_add_val
          else:
            # 在40~60之间，线性从15减小到0
            add_val = max_add_val * (60 - nRoadLimitSpeed) / 20.0
          nRoadLimitSpeed = min(nRoadLimitSpeed + add_val, 60)
      else:
        nRoadLimitSpeed = 30
      #self.nRoadLimitSpeed = nRoadLimitSpeed
      if self.nRoadLimitSpeed != nRoadLimitSpeed:
        self.nRoadLimitSpeed_counter += 1
        if self.nRoadLimitSpeed_counter > 5:
          self.nRoadLimitSpeed = nRoadLimitSpeed
      else:
        self.nRoadLimitSpeed_counter = 0

      ### SDI
      self.nSdiType = int(json.get("nSdiType", -1))
      self.nSdiSpeedLimit = int(json.get("nSdiSpeedLimit", 0))
      self.nSdiSection = int(json.get("nSdiSection", -1))
      self.nSdiDist = int(json.get("nSdiDist", -1))
      self.nSdiBlockType = int(json.get("nSdiBlockType", -1))
      self.nSdiBlockSpeed = int(json.get("nSdiBlockSpeed", 0))
      self.nSdiBlockDist = int(json.get("nSdiBlockDist", 0))

      self.nSdiPlusType = int(json.get("nSdiPlusType", -1))
      self.nSdiPlusSpeedLimit = int(json.get("nSdiPlusSpeedLimit", 0))
      self.nSdiPlusDist = int(json.get("nSdiPlusDist", 0))
      self.nSdiPlusBlockType = int(json.get("nSdiPlusBlockType", -1))
      self.nSdiPlusBlockSpeed = int(json.get("nSdiPlusBlockSpeed", 0))
      self.nSdiPlusBlockDist = int(json.get("nSdiPlusBlockDist", 0))
      self.roadcate = int(json.get("roadcate", 0))

      ## GuidePoint
      self.nTBTDist = int(json.get("nTBTDist", 0))
      self.nTBTTurnType = int(json.get("nTBTTurnType", -1))
      self.szTBTMainText = json.get("szTBTMainText", "")
      self.szNearDirName = json.get("szNearDirName", "")
      self.szFarDirName = json.get("szFarDirName", "")

      self.nTBTNextRoadWidth = int(json.get("nTBTNextRoadWidth", 0))
      self.nTBTDistNext = int(json.get("nTBTDistNext", 0))
      self.nTBTTurnTypeNext = int(json.get("nTBTTurnTypeNext", -1))
      self.szTBTMainTextNext = json.get("szTBTMainText", "")

      self.nGoPosDist = int(json.get("nGoPosDist", 0))
      self.nGoPosTime = int(json.get("nGoPosTime", 0))
      self.szPosRoadName = json.get("szPosRoadName", "")
      if self.szPosRoadName == "null":
        self.szPosRoadName = ""

      self.vpPosPointLatNavi = float(json.get("vpPosPointLat", self.vpPosPointLatNavi))
      self.vpPosPointLonNavi = float(json.get("vpPosPointLon", self.vpPosPointLonNavi))
      self.last_update_gps_time_navi = self.last_calculate_gps_time = now
      self.nPosAngle = float(json.get("nPosAngle", self.nPosAngle))

      self.nPosSpeed = float(json.get("nPosSpeed", self.nPosSpeed))
      self._update_tbt()
      self._update_sdi()
      if (self.showDebugLog & 1) > 0:
        print(
          f"***sdi=T{self.nSdiType},S {self.nSdiSpeedLimit},PS {self.nSdiPlusType}," +
          f"spd=T {self.xSpdType},S {self.xSpdLimit},D {self.xSpdDist:.1f},RC {self.roadcate},xRC {self.xroadcate}, " +
          f"tbt=T {self.nTBTTurnType},D {self.nTBTDist}, " +
          f"xtbt=xT {self.xTurnInfo},xD {self.xDistToTurn:.1f}, " +
          f"next=T {self.nTBTTurnTypeNext},D {self.nTBTDistNext}, " +
          f"Road limit={nRoadLimitSpeed},{self.nRoadLimitSpeed}, cnt:{self.nRoadLimitSpeed_counter}"
        )
      #print(json)
    else:
      #print(json)
      pass

    # 3초간 navi 데이터가 없으면, phone gps로 업데이트
    if "latitude" in json:
      self.nPosAnglePhone = float(json.get("heading", self.nPosAngle))
      if (now - self.last_update_gps_time_navi) > 3.0:
        self.vpPosPointLatNavi = float(json.get("latitude", self.vpPosPointLatNavi))
        self.vpPosPointLonNavi = float(json.get("longitude", self.vpPosPointLonNavi))
        self.nPosAngle = self.nPosAnglePhone

        self.last_update_gps_time_phone = self.last_calculate_gps_time = now
        self.gps_accuracy_phone = float(json.get("accuracy", 0))
        self.nPosSpeed = float(json.get("gps_speed", 0))
        print(f"phone gps: {self.vpPosPointLatNavi}, {self.vpPosPointLonNavi}, {self.gps_accuracy_phone}, {self.nPosSpeed}")


import traceback

def main():
  print("CarrotManager Started")
  #print("Carrot GitBranch = {}, {}".format(Params().get("GitBranch"), Params().get("GitCommitDate")))
  carrot_man = CarrotMan()

  print(f"CarrotMan {carrot_man}")
  threading.Thread(target=carrot_man.kisa_app_thread).start()
  while True:
    try:
      carrot_man.carrot_man_thread()
    except Exception as e:
      print(f"carrot_man error...: {e}")
      traceback.print_exc()
      time.sleep(10)


if __name__ == "__main__":
  main()
