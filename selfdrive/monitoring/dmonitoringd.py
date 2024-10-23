#!/usr/bin/env python3
import gc

import cereal.messaging as messaging
from openpilot.common.params import Params
from openpilot.common.realtime import set_realtime_priority
from openpilot.selfdrive.monitoring.helpers import DriverMonitoring

class AlwaysFocusedDriverMonitoring(DriverMonitoring):
  def _get_distracted_types(self):
    # 总是返回空列表，表示没有分心类型
    return []

  def _update_states(self, driver_state, cal_rpy, car_speed, op_engaged):
    # 调用父类的 _update_states 方法
    super()._update_states(driver_state, cal_rpy, car_speed, op_engaged)
    # 确保 driver_distracted 总是为 False
    self.driver_distracted = False
    # 确保 awareness 总是为 1
    self.awareness = 1.0

  def _update_events(self, driver_engaged, op_engaged, standstill, wrong_gear, car_speed, steering_wheel_engaged):
    # 重置 events 为 None
    self._reset_events()
    # 不添加任何分心事件
    self.current_events = set()

def dmonitoringd_thread():
  gc.disable()
  set_realtime_priority(2)

  params = Params()
  pm = messaging.PubMaster(['driverMonitoringState', 'driverMonitoringStateSP'])
  sm = messaging.SubMaster(['driverStateV2', 'liveCalibration', 'carState', 'controlsState', 'modelV2'], poll='driverStateV2')

  # 使用自定义的 AlwaysFocusedDriverMonitoring 类
  DM = AlwaysFocusedDriverMonitoring(rhd_saved=params.get_bool("IsRhdDetected"), always_on=params.get_bool("AlwaysOnDM"), hands_on_wheel_monitoring=params.get_bool("HandsOnWheelMonitoring"))

  # 20Hz <- dmonitoringmodeld
  while True:
    sm.update()
    if not sm.updated['driverStateV2']:
      # iterate when model has new output
      continue

    valid = sm.all_checks()
    if valid:
      DM.run_step(sm)

    # publish
    dat = DM.get_state_packet(valid=valid)
    pm.send('driverMonitoringState', dat)

    sp_dat = DM.get_sp_state_packet(valid=valid)
    pm.send('driverMonitoringStateSP', sp_dat)

    # load live always-on toggle
    if sm['driverStateV2'].frameId % 40 == 1:
      DM.always_on = params.get_bool("AlwaysOnDM")
      DM.hands_on_wheel_monitoring = params.get_bool("HandsOnWheelMonitoring")

    # save rhd virtual toggle every 5 mins
    if (sm['driverStateV2'].frameId % 6000 == 0 and
     DM.wheelpos_learner.filtered_stat.n > DM.settings._WHEELPOS_FILTER_MIN_COUNT and
     DM.wheel_on_right == (DM.wheelpos_learner.filtered_stat.M > DM.settings._WHEELPOS_THRESHOLD)):
      params.put_bool_nonblocking("IsRhdDetected", DM.wheel_on_right)

def main():
  dmonitoringd_thread()


if __name__ == '__main__':
  main()
