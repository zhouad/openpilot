"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import math

from cereal import messaging, custom
from opendbc.car import structs
from opendbc.car.interfaces import ACCEL_MIN
from openpilot.common.params import Params
from openpilot.selfdrive.car.cruise import V_CRUISE_UNSET
from openpilot.sunnypilot.selfdrive.controls.lib.dec.dec import DynamicExperimentalController
from openpilot.sunnypilot.models.helpers import get_active_bundle

from openpilot.sunnypilot.selfdrive.controls.lib.vibe_personality.vibe_personality import VibePersonalityController
from openpilot.sunnypilot.selfdrive.controls.lib.speed_limit_controller.speed_limit_controller import SpeedLimitController
from openpilot.sunnypilot.selfdrive.selfdrived.events import EventsSP
from openpilot.sunnypilot.selfdrive.controls.lib.vision_turn_controller import VisionTurnController
DecState = custom.LongitudinalPlanSP.DynamicExperimentalControl.DynamicExperimentalControlState


class LongitudinalPlannerSP:
  def __init__(self, CP: structs.CarParams, mpc):
    self.events_sp = EventsSP()

    self.dec = DynamicExperimentalController(CP, mpc)
    self.vibe_controller = VibePersonalityController()
    self.slc = SpeedLimitController(CP)
    self.v_tsc = VisionTurnController(CP)
    self.transition_init()
    self.generation = int(model_bundle.generation) if (model_bundle := get_active_bundle()) else None

  @property
  def mlsim(self) -> bool:
    # If we don't have a generation set, we assume it's default model. Which as of today are mlsim.
    return bool(self.generation is None or self.generation >= 11)

  def get_mpc_mode(self) -> str | None:
    if not self.dec.active():
      return None

    return self.dec.mode()

  def transition_init(self) -> None:
    self._params = Params()
    self._transition_counter = 0
    self._transition_steps = 40
    self._last_mode = 'acc'

  def handle_mode_transition(self, mode: str) -> None:
    if self._last_mode != mode:
      if mode == 'blended':
        self._transition_counter = 0
      self._last_mode = mode

  def blend_accel_transition(self, mpc_accel: float, e2e_accel: float, v_ego: float) -> float:
    if self._params.get_bool("BlendAccToE2ETransition"):
      if self._transition_counter < self._transition_steps:
        self._transition_counter += 1
        progress = self._transition_counter / self._transition_steps
        if v_ego > 5.0 and e2e_accel < 0.0:
          # use k2.0 and normalize midpoint at 0.5
          sigmoid = 1.0 / (1.0 + math.exp(-2.0 * (abs(e2e_accel / ACCEL_MIN) - 0.5)))
          blend_factor = 1.0 - (1.0 - progress) * (1.0 - sigmoid)
          blended = mpc_accel + (e2e_accel - mpc_accel) * blend_factor
          return blended
        else:
          blended = mpc_accel + (e2e_accel - mpc_accel) * progress
          return blended
    return min(mpc_accel, e2e_accel)

  def update_v_cruise(self, sm: messaging.SubMaster, v_ego: float, a_ego: float, v_cruise: float) -> float:
    self.events_sp.clear()

    self.slc.update(sm, v_ego, a_ego, v_cruise, self.events_sp)

    v_cruise_slc = self.slc.speed_limit_offseted if self.slc.is_active else V_CRUISE_UNSET

    self.v_tsc.update(sm, sm['carControl'].enabled, v_ego, a_ego, v_cruise)
    v_cruise_v_tsc = self.v_tsc.v_turn if self.v_tsc.is_active else V_CRUISE_UNSET

    cruise_speeds = [v_cruise]

    if self.v_tsc.is_active and v_cruise_v_tsc != V_CRUISE_UNSET:
      cruise_speeds.append(v_cruise_v_tsc)
    if self.slc.is_active and v_cruise_slc != V_CRUISE_UNSET:
      cruise_speeds.append(v_cruise_slc)

    v_cruise_final = min(cruise_speeds)
    return v_cruise_final

  def update(self, sm: messaging.SubMaster) -> None:
    self.dec.update(sm)
    self.vibe_controller.update()

  def publish_longitudinal_plan_sp(self, sm: messaging.SubMaster, pm: messaging.PubMaster) -> None:
    plan_sp_send = messaging.new_message('longitudinalPlanSP')

    plan_sp_send.valid = sm.all_checks(service_list=['carState', 'controlsState'])

    longitudinalPlanSP = plan_sp_send.longitudinalPlanSP
    longitudinalPlanSP.events = self.events_sp.to_msg()

    # Dynamic Experimental Control
    dec = longitudinalPlanSP.dec
    dec.state = DecState.blended if self.dec.mode() == 'blended' else DecState.acc
    dec.enabled = self.dec.enabled()
    dec.active = self.dec.active()

    # Vision Turn Speed Control
    visionTurnSpeedControl = longitudinalPlanSP.visionTurnSpeedControl
    visionTurnSpeedControl.state = self.v_tsc.state
    visionTurnSpeedControl.velocity = float(self.v_tsc.v_turn)
    visionTurnSpeedControl.currentLateralAccel = float(self.v_tsc.current_lat_acc)
    visionTurnSpeedControl.maxPredictedLateralAccel = float(self.v_tsc.max_pred_lat_acc)

    # Speed Limit Control
    slc = longitudinalPlanSP.slc
    slc.state = self.slc.state
    slc.enabled = self.slc.is_enabled
    slc.active = self.slc.is_active
    slc.speedLimit = float(self.slc.speed_limit)
    slc.speedLimitOffset = float(self.slc.speed_limit_offset)
    slc.distToSpeedLimit = float(self.slc.distance)

    pm.send('longitudinalPlanSP', plan_sp_send)
