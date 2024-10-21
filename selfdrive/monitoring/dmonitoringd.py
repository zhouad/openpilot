#!/usr/bin/env python3
import gc

import cereal.messaging as messaging
from openpilot.common.params import Params
from openpilot.common.realtime import set_realtime_priority
from openpilot.selfdrive.monitoring.helpers import DriverMonitoring


def dmonitoringd_thread():
  gc.disable()
  set_realtime_priority(2)

  params = Params()
  pm = messaging.PubMaster(['driverMonitoringState', 'driverMonitoringStateSP'])
  sm = messaging.SubMaster(['driverStateV2', 'liveCalibration', 'carState', 'controlsState', 'modelV2'], poll='driverStateV2')

  DM = DriverMonitoring(rhd_saved=params.get_bool("IsRhdDetected"), always_on=params.get_bool("AlwaysOnDM"), hands_on_wheel_monitoring=params.get_bool("HandsOnWheelMonitoring"))

  # 覆盖 run_step 方法，使其始终报告驾驶员专注
  def always_attentive_run_step(sm):
    DM.driver_status.distracted = False
    DM.driver_status.awareness = 1.0  # 最大专注度
    DM.driver_status.face_detected = True
    DM.driver_status.face_orientation = [0.0, 0.0, 0.0]  # 假设面部方向正常
    DM.driver_status.eye_status = [1.0, 1.0]  # 假设双眼睁开
    DM.driver_status.blink_rate = 0.0  # 假设没有眨眼
    DM.driver_status.yawn_status = 0.0  # 假设没有打哈欠

  # 将覆盖的方法赋值给 DM 实例
  DM.run_step = always_attentive_run_step
  
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
