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
void car_err_fun(double *nom_x, double *delta_x, double *out_4724708977981708405);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5126129424661047506);
void car_H_mod_fun(double *state, double *out_1147635393640717535);
void car_f_fun(double *state, double dt, double *out_5224857696349368422);
void car_F_fun(double *state, double dt, double *out_5873942743940990608);
void car_h_25(double *state, double *unused, double *out_1380271847665989609);
void car_H_25(double *state, double *unused, double *out_2830062547978729467);
void car_h_24(double *state, double *unused, double *out_8094530808421281060);
void car_H_24(double *state, double *unused, double *out_658041141853804222);
void car_h_30(double *state, double *unused, double *out_5207556078810305554);
void car_H_30(double *state, double *unused, double *out_2700723600835489397);
void car_h_26(double *state, double *unused, double *out_205882811149459909);
void car_H_26(double *state, double *unused, double *out_911440770895326757);
void car_h_27(double *state, double *unused, double *out_8383034551459055388);
void car_H_27(double *state, double *unused, double *out_525960289035064486);
void car_h_29(double *state, double *unused, double *out_8237514727238400417);
void car_H_29(double *state, double *unused, double *out_3210954945149881581);
void car_h_28(double *state, double *unused, double *out_3157127335623730441);
void car_H_28(double *state, double *unused, double *out_6269801454904017121);
void car_h_31(double *state, double *unused, double *out_5822944109319996361);
void car_H_31(double *state, double *unused, double *out_2860708509855689895);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}