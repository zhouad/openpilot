from openpilot.common.params import Params
from opendbc.car import Bus, structs, get_safety_config, uds
from opendbc.car.toyota.carstate import CarState
from opendbc.car.toyota.carcontroller import CarController
from opendbc.car.toyota.radar_interface import RadarInterface
from opendbc.car.toyota.values import Ecu, CAR, DBC, ToyotaFlags, CarControllerParams, TSS2_CAR, RADAR_ACC_CAR, NO_DSU_CAR, \
                                                  MIN_ACC_SPEED, EPS_SCALE, UNSUPPORTED_DSU_CAR, NO_STOP_TIMER_CAR, ANGLE_CONTROL_CAR, \
                                                  ToyotaSafetyFlags, SECOC_CAR
from opendbc.car.disable_ecu import disable_ecu
from opendbc.car.interfaces import CarInterfaceBase
from opendbc.sunnypilot.car.toyota.values import ToyotaSafetyFlagsSP, ToyotaFlagsSP

SteerControlType = structs.CarParams.SteerControlType


class CarInterface(CarInterfaceBase):
  CarState = CarState
  CarController = CarController
  RadarInterface = RadarInterface

  @staticmethod
  def get_pid_accel_limits(CP, current_speed, cruise_speed):
    return CarControllerParams(CP).ACCEL_MIN, CarControllerParams(CP).ACCEL_MAX

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate, fingerprint, car_fw, alpha_long, is_release, docs) -> structs.CarParams:
    ret.brand = "toyota"
    ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.toyota)]
    ret.safetyConfigs[0].safetyParam = EPS_SCALE[candidate]

    # BRAKE_MODULE is on a different address for these cars
    if DBC[candidate][Bus.pt] == "toyota_new_mc_pt_generated":
      ret.safetyConfigs[0].safetyParam |= ToyotaSafetyFlags.ALT_BRAKE.value

    if ret.flags & ToyotaFlags.SECOC.value:
      ret.secOcRequired = True
      ret.safetyConfigs[0].safetyParam |= ToyotaSafetyFlags.SECOC.value
      ret.dashcamOnly = is_release

    if candidate in ANGLE_CONTROL_CAR:
      ret.steerControlType = SteerControlType.angle
      ret.safetyConfigs[0].safetyParam |= ToyotaSafetyFlags.LTA.value

      # LTA control can be more delayed and winds up more often
      ret.steerActuatorDelay = 0.18
      ret.steerLimitTimer = 0.8
    else:
      CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)

      ret.steerActuatorDelay = 0.12  # Default delay, Prius has larger delay
      ret.steerLimitTimer = 0.4

    stop_and_go = candidate in TSS2_CAR

    # In TSS2 cars, the camera does long control
    found_ecus = [fw.ecu for fw in car_fw]
    ret.enableDsu = len(found_ecus) > 0 and Ecu.dsu not in found_ecus and candidate not in (NO_DSU_CAR | UNSUPPORTED_DSU_CAR)

    if Ecu.hybrid in found_ecus:
      ret.flags |= ToyotaFlags.HYBRID.value

    # sdsu dp
    sdsu_active = False

    if not (candidate in (RADAR_ACC_CAR | NO_DSU_CAR)) and 0x2FF in fingerprint[0]:
      print("----------------------------------------------")
      print("SDSU detected!")
      print("----------------------------------------------")
      ret.enableDsu = False
      sdsu_active = True
      stop_and_go = True
      ret.flags |= ToyotaFlags.SMART_DSU.value
      ret.alphaLongitudinalAvailable = False
      ret.safetyConfigs[0].safetyParam |= ToyotaSafetyFlags.SDSU.value

    if candidate == CAR.TOYOTA_PRIUS:
      stop_and_go = True
      # Only give steer angle deadzone to for bad angle sensor prius
      for fw in car_fw:
        if fw.ecu == "eps" and not fw.fwVersion == b'8965B47060\x00\x00\x00\x00\x00\x00':
          ret.steerActuatorDelay = 0.25
          CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning, steering_angle_deadzone_deg=0.2)

    elif candidate in (CAR.LEXUS_RX, CAR.LEXUS_RX_TSS2):
      stop_and_go = True
      ret.wheelSpeedFactor = 1.035

    elif candidate in (CAR.TOYOTA_AVALON, CAR.TOYOTA_AVALON_2019, CAR.TOYOTA_AVALON_TSS2):
      # starting from 2019, all Avalon variants have stop and go
      # https://engage.toyota.com/static/images/toyota_safety_sense/TSS_Applicability_Chart.pdf
      stop_and_go = candidate != CAR.TOYOTA_AVALON

    elif candidate in (CAR.TOYOTA_RAV4_TSS2, CAR.TOYOTA_RAV4_TSS2_2022, CAR.TOYOTA_RAV4_TSS2_2023, CAR.TOYOTA_RAV4_PRIME, CAR.TOYOTA_SIENNA_4TH_GEN):
      ret.lateralTuning.init('pid')
      ret.lateralTuning.pid.kiBP = [0.0]
      ret.lateralTuning.pid.kpBP = [0.0]
      ret.lateralTuning.pid.kpV = [0.6]
      ret.lateralTuning.pid.kiV = [0.1]
      ret.lateralTuning.pid.kf = 0.00007818594

      # 2019+ RAV4 TSS2 uses two different steering racks and specific tuning seems to be necessary.
      # See https://github.com/commaai/openpilot/pull/21429#issuecomment-873652891
      for fw in car_fw:
        if fw.ecu == "eps" and (fw.fwVersion.startswith(b'\x02') or fw.fwVersion in [b'8965B42181\x00\x00\x00\x00\x00\x00']):
          ret.lateralTuning.pid.kpV = [0.15]
          ret.lateralTuning.pid.kiV = [0.05]
          ret.lateralTuning.pid.kf = 0.00004
          break

    elif candidate in (CAR.TOYOTA_CHR, CAR.TOYOTA_CAMRY, CAR.TOYOTA_SIENNA, CAR.LEXUS_CTH, CAR.LEXUS_NX):
      # TODO: Some of these platforms are not advertised to have full range ACC, are they similar to SNG_WITHOUT_DSU cars?
      stop_and_go = True

    # TODO: these models can do stop and go, but unclear if it requires sDSU or unplugging DSU.
    #  For now, don't list stop and go functionality in the docs
    if ret.flags & ToyotaFlags.SNG_WITHOUT_DSU:
      stop_and_go = stop_and_go or (ret.enableDsu and not docs)

    ret.centerToFront = ret.wheelbase * 0.44

    # TODO: Some TSS-P platforms have BSM, but are flipped based on region or driving direction.
    # Detect flipped signals and enable for C-HR and others
    ret.enableBsm = 0x3F6 in fingerprint[0] and candidate in TSS2_CAR

    # No radar dbc for cars without DSU which are not TSS 2.0
    # TODO: make an adas dbc file for dsu-less models
    ret.radarUnavailable = Bus.radar not in DBC[candidate] or candidate in (NO_DSU_CAR - TSS2_CAR)

    # since we don't yet parse radar on TSS2/TSS-P radar-based ACC cars, gate longitudinal behind experimental toggle
    if candidate in (RADAR_ACC_CAR | NO_DSU_CAR):
      ret.alphaLongitudinalAvailable = candidate in RADAR_ACC_CAR

      # Disabling radar is only supported on TSS2 radar-ACC cars
      if alpha_long and candidate in RADAR_ACC_CAR:
        ret.flags |= ToyotaFlags.DISABLE_RADAR.value

    # openpilot longitudinal enabled by default:
    #  - cars w/ DSU disconnected
    #  - TSS2 cars with camera sending ACC_CONTROL where we can block it
    #  - SDSU equipped cars
    # openpilot longitudinal behind experimental long toggle:
    #  - TSS2 radar ACC cars (disables radar)

    ret.openpilotLongitudinalControl = ret.enableDsu or \
      candidate in (TSS2_CAR - RADAR_ACC_CAR) or \
      bool(ret.flags & ToyotaFlags.DISABLE_RADAR.value) or \
      sdsu_active

    if Params().get_bool("ToyotaStockLongitudinal"):
      ret.openpilotLongitudinalControl = False
      ret.alphaLongitudinalAvailable = False

    ret.autoResumeSng = ret.openpilotLongitudinalControl and candidate in NO_STOP_TIMER_CAR

    if not ret.openpilotLongitudinalControl:
      ret.safetyConfigs[0].safetyParam |= ToyotaSafetyFlags.STOCK_LONGITUDINAL.value

    # min speed to enable ACC. if car can do stop and go, then set enabling speed
    # to a negative value, so it won't matter.
    ret.minEnableSpeed = -1. if stop_and_go else MIN_ACC_SPEED
    sp_tss2_long_tune = Params().get_bool("ToyotaTSS2Long")

    if candidate in TSS2_CAR:
      ret.flags |= ToyotaFlags.RAISED_ACCEL_LIMIT.value

      ret.vEgoStopping = 0.25
      ret.vEgoStarting = 0.25
      if candidate == CAR.TOYOTA_RAV4_TSS2:
        ret.stoppingDecelRate = 0.03 if sp_tss2_long_tune else 0.3   # reach stopping target smoothly
      else:
        ret.stoppingDecelRate = 0.003 if sp_tss2_long_tune else 0.3  # reach stopping target smoothly

      # Hybrids have much quicker longitudinal actuator response
      if ret.flags & ToyotaFlags.HYBRID.value:
        ret.longitudinalActuatorDelay = 0.05

    return ret

  @staticmethod
  def _get_params_sp(stock_cp: structs.CarParams, ret: structs.CarParamsSP, candidate, fingerprint: dict[int, dict[int, int]],
                     car_fw: list[structs.CarParams.CarFw], alpha_long: bool, docs: bool) -> structs.CarParamsSP:
    if candidate in UNSUPPORTED_DSU_CAR:
      ret.safetyParam |= ToyotaSafetyFlagsSP.UNSUPPORTED_DSU

    sp_toyota_auto_brake_hold = Params().get_bool("ToyotaAutoHold")
    sp_toyota_enhanced_bsm = Params().get_bool("ToyotaEnhancedBsm")
    if sp_toyota_enhanced_bsm and candidate in (TSS2_CAR - SECOC_CAR):
      ret.flags |= ToyotaFlagsSP.SP_ENHANCED_BSM.value
    if candidate == CAR.TOYOTA_PRIUS_TSS2:
      ret.flags |= ToyotaFlagsSP.SP_NEED_DEBUG_BSM.value
    if sp_toyota_auto_brake_hold and candidate in (TSS2_CAR - RADAR_ACC_CAR - SECOC_CAR) and (stock_cp.flags & ToyotaFlags.HYBRID.value):
      ret.flags |= ToyotaFlagsSP.SP_AUTO_BRAKE_HOLD.value


    return ret

  @staticmethod
  def init(CP, CP_SP, can_recv, can_send):
    # disable radar if alpha longitudinal toggled on radar-ACC car
    if CP.flags & ToyotaFlags.DISABLE_RADAR.value:
      communication_control = bytes([uds.SERVICE_TYPE.COMMUNICATION_CONTROL, uds.CONTROL_TYPE.ENABLE_RX_DISABLE_TX, uds.MESSAGE_TYPE.NORMAL])
      disable_ecu(can_recv, can_send, bus=0, addr=0x750, sub_addr=0xf, com_cont_req=communication_control)
