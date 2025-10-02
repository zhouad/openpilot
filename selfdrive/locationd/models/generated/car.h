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
void car_err_fun(double *nom_x, double *delta_x, double *out_8930228301352433094);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3014327979078171337);
void car_H_mod_fun(double *state, double *out_7823236443685769931);
void car_f_fun(double *state, double dt, double *out_6955445627651503601);
void car_F_fun(double *state, double dt, double *out_6783243367174983829);
void car_h_25(double *state, double *unused, double *out_1245983289421766020);
void car_H_25(double *state, double *unused, double *out_1369951782226467306);
void car_h_24(double *state, double *unused, double *out_3631336312775449012);
void car_H_24(double *state, double *unused, double *out_7858113403842727919);
void car_h_30(double *state, double *unused, double *out_1521177351706271909);
void car_H_30(double *state, double *unused, double *out_5897648112354075504);
void car_h_26(double *state, double *unused, double *out_2464687204607934344);
void car_H_26(double *state, double *unused, double *out_5111455101100523530);
void car_h_27(double *state, double *unused, double *out_6247656557082611665);
void car_H_27(double *state, double *unused, double *out_3674054041170132287);
void car_h_29(double *state, double *unused, double *out_1515608699738060776);
void car_H_29(double *state, double *unused, double *out_5387416768039683320);
void car_h_28(double *state, double *unused, double *out_4557208722346930705);
void car_H_28(double *state, double *unused, double *out_7976928288600337722);
void car_h_31(double *state, double *unused, double *out_2696614682050649187);
void car_H_31(double *state, double *unused, double *out_5737663203333875006);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}