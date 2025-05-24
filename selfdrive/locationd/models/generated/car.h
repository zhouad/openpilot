#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_4624442741753145801);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4763729259609419538);
void car_H_mod_fun(double *state, double *out_1165402551737860898);
void car_f_fun(double *state, double dt, double *out_3753071707696038582);
void car_F_fun(double *state, double dt, double *out_9143542782728581509);
void car_h_25(double *state, double *unused, double *out_4834028724732154266);
void car_H_25(double *state, double *unused, double *out_6772912930606189732);
void car_h_24(double *state, double *unused, double *out_4101174789381641110);
void car_H_24(double *state, double *unused, double *out_4547205146627321170);
void car_h_30(double *state, double *unused, double *out_2929236532088518175);
void car_H_30(double *state, double *unused, double *out_143777410885427023);
void car_h_26(double *state, double *unused, double *out_7868162368309699099);
void car_H_26(double *state, double *unused, double *out_7932327824229305660);
void car_h_27(double *state, double *unused, double *out_4147940447274686499);
void car_H_27(double *state, double *unused, double *out_2030985900914997888);
void car_h_29(double *state, double *unused, double *out_3872746384990180610);
void car_H_29(double *state, double *unused, double *out_654008755199819207);
void car_h_28(double *state, double *unused, double *out_853732820386159146);
void car_H_28(double *state, double *unused, double *out_8826747644854079495);
void car_h_31(double *state, double *unused, double *out_5659680830519997122);
void car_H_31(double *state, double *unused, double *out_6742266968729229304);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}