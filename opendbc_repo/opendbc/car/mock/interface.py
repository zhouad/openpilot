#!/usr/bin/env python3
from opendbc.car import structs
from opendbc.car.interfaces import CarInterfaceBase
from opendbc.car.mock.carcontroller import CarController
from opendbc.car.mock.carstate import CarState


# mocked car interface for dashcam mode
class CarInterface(CarInterfaceBase):
  CarState = CarState
  CarController = CarController

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate, fingerprint, car_fw, experimental_long, dp_params, docs) -> structs.CarParams:
    ret.brand = "mock"
    ret.mass = 1700.
    ret.wheelbase = 2.70
    ret.centerToFront = ret.wheelbase * 0.5
    ret.steerRatio = 13.
    ret.dashcamOnly = True
    return ret
