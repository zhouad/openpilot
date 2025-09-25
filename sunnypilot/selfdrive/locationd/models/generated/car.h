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
void car_err_fun(double *nom_x, double *delta_x, double *out_497411416085616360);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4833570427681397891);
void car_H_mod_fun(double *state, double *out_1671451718469889604);
void car_f_fun(double *state, double dt, double *out_7688883402641383999);
void car_F_fun(double *state, double dt, double *out_906172446396236554);
void car_h_25(double *state, double *unused, double *out_7655302679692222819);
void car_H_25(double *state, double *unused, double *out_6575143543654554444);
void car_h_24(double *state, double *unused, double *out_8836079831736825888);
void car_H_24(double *state, double *unused, double *out_6178498239300694949);
void car_h_30(double *state, double *unused, double *out_1482414604991628363);
void car_H_30(double *state, double *unused, double *out_9093476502161803071);
void car_h_26(double *state, double *unused, double *out_5907775520289859896);
void car_H_26(double *state, double *unused, double *out_2833640224780498220);
void car_h_27(double *state, double *unused, double *out_5789768126356483152);
void car_H_27(double *state, double *unused, double *out_6918713190361378160);
void car_h_29(double *state, double *unused, double *out_4160315266089328472);
void car_H_29(double *state, double *unused, double *out_8843036227233356361);
void car_h_28(double *state, double *unused, double *out_2798394555448358256);
void car_H_28(double *state, double *unused, double *out_4521308829406664681);
void car_h_31(double *state, double *unused, double *out_3028176137196656356);
void car_H_31(double *state, double *unused, double *out_2207432122547146744);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}