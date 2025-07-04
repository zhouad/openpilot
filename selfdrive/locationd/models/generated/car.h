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
void car_err_fun(double *nom_x, double *delta_x, double *out_911903194658884293);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5779663419065305557);
void car_H_mod_fun(double *state, double *out_3279590390747204942);
void car_f_fun(double *state, double dt, double *out_4327379576481858684);
void car_F_fun(double *state, double dt, double *out_3077082935718334244);
void car_h_25(double *state, double *unused, double *out_2385054709657547755);
void car_H_25(double *state, double *unused, double *out_1292631630641773223);
void car_h_24(double *state, double *unused, double *out_5916792586470950082);
void car_H_24(double *state, double *unused, double *out_3465281229647272789);
void car_h_30(double *state, double *unused, double *out_562671280697937206);
void car_H_30(double *state, double *unused, double *out_5624058710849843532);
void car_h_26(double *state, double *unused, double *out_8902103621004773645);
void car_H_26(double *state, double *unused, double *out_5034134949515829447);
void car_h_27(double *state, double *unused, double *out_6411254754608449385);
void car_H_27(double *state, double *unused, double *out_3449295399049418621);
void car_h_29(double *state, double *unused, double *out_5564344548358782851);
void car_H_29(double *state, double *unused, double *out_1735932672179867588);
void car_h_28(double *state, double *unused, double *out_3598702651338596002);
void car_H_28(double *state, double *unused, double *out_3346466344889662986);
void car_h_31(double *state, double *unused, double *out_8180416713297954676);
void car_H_31(double *state, double *unused, double *out_1261985668764812795);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}