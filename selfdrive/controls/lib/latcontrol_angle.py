import math
import numpy as np

from cereal import log
from openpilot.selfdrive.controls.lib.latcontrol import LatControl

STEER_ANGLE_SATURATION_THRESHOLD = 2.5  # Degrees


class LatControlAngle(LatControl):
  def __init__(self, CP, CI):
    super().__init__(CP, CI)
    self.sat_check_min_speed = 5.
    self.angle_steers_des = 0.0
    #print(CP.carFingerprint, "using LatControlAngle")
    #self.factor = 0.5 if CP.carFingerprint in ["HYUNDAI_IONIQ_5_PE"] else 1.0
    #self.factor = 0.5
    #print("Angle factor", self.factor)

  def update(self, active, CS, VM, params, steer_limited_by_controls, desired_curvature, llk, curvature_limited, model_data=None):  
    angle_log = log.ControlsState.LateralAngleState.new_message()

    if not active:
      angle_log.active = False
      angle_steers_des = float(CS.steeringAngleDeg)
    else:
      angle_log.active = True
      angle_steers_des = math.degrees(VM.get_steer_from_curvature(-desired_curvature, CS.vEgo, params.roll))
      angle_steers_des += params.angleOffsetDeg #* self.factor

    angle_control_saturated = abs(angle_steers_des - CS.steeringAngleDeg) > STEER_ANGLE_SATURATION_THRESHOLD
    angle_log.saturated = bool(self._check_saturation(angle_control_saturated, CS, False, curvature_limited))
    angle_log.steeringAngleDeg = float(CS.steeringAngleDeg)
    angle_log.steeringAngleDesiredDeg = float(angle_steers_des) if not CS.steeringPressed else float(CS.steeringAngleDeg)
    return 0, float(angle_steers_des), angle_log
