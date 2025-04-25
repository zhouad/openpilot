"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

from opendbc.car import structs
from opendbc.car.hyundai.values import HyundaiFlags
from opendbc.sunnypilot.car.hyundai.longitudinal.longitudinal_config import CarTuningConfig, TUNING_CONFIGS, CAR_SPECIFIC_CONFIGS


def get_car_config(CP: structs.CarParams) -> CarTuningConfig:
  # Get car type flags from specific configs or determine from car flags
  car_config = CAR_SPECIFIC_CONFIGS.get(CP.carFingerprint)
  # If car is not in specific configs, determine from flags
  if car_config is None:
    if CP.flags & HyundaiFlags.CANFD:
      car_config = TUNING_CONFIGS["CANFD"]
    elif CP.flags & HyundaiFlags.EV:
      car_config = TUNING_CONFIGS["EV"]
    elif CP.flags & HyundaiFlags.HYBRID:
      car_config = TUNING_CONFIGS["HYBRID"]
    else:
      car_config = TUNING_CONFIGS["DEFAULT"]

  return car_config


def get_longitudinal_tune(CP: structs.CarParams) -> None:
  config = get_car_config(CP)
  CP.vEgoStopping = config.v_ego_stopping
  CP.vEgoStarting = config.v_ego_starting
  CP.stoppingDecelRate = config.stopping_decel_rate
  CP.startingState = False
  CP.longitudinalActuatorDelay = config.longitudinal_actuator_delay
