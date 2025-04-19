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
void car_err_fun(double *nom_x, double *delta_x, double *out_7336400755353116814);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_563874706792395429);
void car_H_mod_fun(double *state, double *out_5735286983792797603);
void car_f_fun(double *state, double dt, double *out_346464760395709430);
void car_F_fun(double *state, double dt, double *out_8533956319147983344);
void car_h_25(double *state, double *unused, double *out_8865985810845833767);
void car_H_25(double *state, double *unused, double *out_3457901242119439634);
void car_h_24(double *state, double *unused, double *out_8805399835663073913);
void car_H_24(double *state, double *unused, double *out_5630550841124939200);
void car_h_30(double *state, double *unused, double *out_226108334127291883);
void car_H_30(double *state, double *unused, double *out_939568283612191007);
void car_h_26(double *state, double *unused, double *out_4775564933533553762);
void car_H_26(double *state, double *unused, double *out_7199404560993495858);
void car_h_27(double *state, double *unused, double *out_6053433707575980384);
void car_H_27(double *state, double *unused, double *out_1284025787571752210);
void car_h_29(double *state, double *unused, double *out_6029716387831755371);
void car_H_29(double *state, double *unused, double *out_429336939297798823);
void car_h_28(double *state, double *unused, double *out_7391637098472725587);
void car_H_28(double *state, double *unused, double *out_5511735956367329397);
void car_h_31(double *state, double *unused, double *out_8590791748561327878);
void car_H_31(double *state, double *unused, double *out_3427255280242479206);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}