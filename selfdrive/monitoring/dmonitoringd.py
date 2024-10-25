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

class DriverMonitoring:
  def __init__(self, rhd_saved, always_on, hands_on_wheel_monitoring):
    self.rhd_saved = rhd_saved
    self.always_on = always_on
    self.hands_on_wheel_monitoring = hands_on_wheel_monitoring

  def run_step(self, sm):
    # Always set driver state to focused
    self.driver_focused = True

  def get_state_packet(self, valid):
    dat = messaging.new_message('driverMonitoringState')
    dat.driverMonitoringState = {
      'driverFocused': self.driver_focused,
      'valid': valid,
    }
    return dat

  def get_sp_state_packet(self, valid):
    sp_dat = messaging.new_message('driverMonitoringStateSP')
    sp_dat.driverMonitoringStateSP = {
      'driverFocused': self.driver_focused,
      'valid': valid,
    }
    return sp_dat

def main():
  dmonitoringd_thread()


if __name__ == '__main__':
  main()
