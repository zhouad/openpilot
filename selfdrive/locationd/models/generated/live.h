#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_8256577121296403758);
void live_err_fun(double *nom_x, double *delta_x, double *out_7356205350758974129);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_2101148154720658072);
void live_H_mod_fun(double *state, double *out_1559586737427390206);
void live_f_fun(double *state, double dt, double *out_7251794637018685419);
void live_F_fun(double *state, double dt, double *out_8567902040814167170);
void live_h_4(double *state, double *unused, double *out_906302487838240379);
void live_H_4(double *state, double *unused, double *out_2596917562682606019);
void live_h_9(double *state, double *unused, double *out_9009102261343482123);
void live_H_9(double *state, double *unused, double *out_2838107209312196664);
void live_h_10(double *state, double *unused, double *out_4955300569969297432);
void live_H_10(double *state, double *unused, double *out_5242975150653558988);
void live_h_12(double *state, double *unused, double *out_5387068740478992380);
void live_H_12(double *state, double *unused, double *out_7616373970714567814);
void live_h_35(double *state, double *unused, double *out_8231047437164215001);
void live_H_35(double *state, double *unused, double *out_8084807070669970093);
void live_h_32(double *state, double *unused, double *out_104442129232571274);
void live_H_32(double *state, double *unused, double *out_5301148906251552500);
void live_h_13(double *state, double *unused, double *out_6414480357703011048);
void live_H_13(double *state, double *unused, double *out_7791348496031812102);
void live_h_14(double *state, double *unused, double *out_9009102261343482123);
void live_H_14(double *state, double *unused, double *out_2838107209312196664);
void live_h_33(double *state, double *unused, double *out_1439639673297395824);
void live_H_33(double *state, double *unused, double *out_9114136624694070999);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}