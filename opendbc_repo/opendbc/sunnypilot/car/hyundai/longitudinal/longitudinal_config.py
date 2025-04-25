"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

from dataclasses import dataclass, field

from opendbc.car.hyundai.values import CAR


@dataclass
class CarTuningConfig:
  v_ego_stopping: float = 0.25
  v_ego_starting: float = 0.10
  stopping_decel_rate: float = 0.40
  lookahead_jerk_bp: list[float] = field(default_factory=lambda: [5., 20.])
  lookahead_jerk_upper_v: list[float] = field(default_factory=lambda: [0.25, 0.5])
  lookahead_jerk_lower_v: list[float] = field(default_factory=lambda: [0.15, 0.3])
  longitudinal_actuator_delay: float = 0.45
  jerk_limits: float = 3.3


# Default configurations for different car types
# Min jerk is set to 0.53 per (Horn et al., 2024)
TUNING_CONFIGS = {
  "CANFD": CarTuningConfig(
    stopping_decel_rate=0.275,
  ),
  "EV": CarTuningConfig(
    longitudinal_actuator_delay=0.45,
  ),
  "HYBRID": CarTuningConfig(
    v_ego_starting=0.12,
    stopping_decel_rate=0.30,
  ),
  "DEFAULT": CarTuningConfig(
    lookahead_jerk_bp=[2., 5., 20.],
    lookahead_jerk_upper_v=[0.25, 0.5, 1.0],
    lookahead_jerk_lower_v=[0.05, 0.10, 0.3],
  )
}

# Car-specific configs
CAR_SPECIFIC_CONFIGS = {
  CAR.KIA_NIRO_EV: CarTuningConfig(
    v_ego_stopping=0.1,
    stopping_decel_rate=0.1,
    lookahead_jerk_lower_v=[0.15, 0.4],
    jerk_limits=3.0,
    longitudinal_actuator_delay=0.25,
  ),
  CAR.HYUNDAI_IONIQ: CarTuningConfig(
    v_ego_stopping=0.25,
    stopping_decel_rate=0.4,
    jerk_limits=4.5,
    longitudinal_actuator_delay=0.45,
  )
}
