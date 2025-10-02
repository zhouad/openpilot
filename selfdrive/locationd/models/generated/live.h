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
void live_H(double *in_vec, double *out_5758408186925393532);
void live_err_fun(double *nom_x, double *delta_x, double *out_180185448712572281);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4396804282860757599);
void live_H_mod_fun(double *state, double *out_6447116989609664619);
void live_f_fun(double *state, double dt, double *out_342877095328119037);
void live_F_fun(double *state, double dt, double *out_8253129903815406582);
void live_h_4(double *state, double *unused, double *out_867594404448767272);
void live_H_4(double *state, double *unused, double *out_8400184455233509659);
void live_h_9(double *state, double *unused, double *out_371672585217068510);
void live_H_9(double *state, double *unused, double *out_1112965519969062189);
void live_h_10(double *state, double *unused, double *out_8346954944710380205);
void live_H_10(double *state, double *unused, double *out_568806180655431122);
void live_h_12(double *state, double *unused, double *out_8202495502726701333);
void live_H_12(double *state, double *unused, double *out_3380728047201547864);
void live_h_35(double *state, double *unused, double *out_8221778976482916253);
void live_H_35(double *state, double *unused, double *out_5033522397860902283);
void live_h_32(double *state, double *unused, double *out_1561841119683335435);
void live_H_32(double *state, double *unused, double *out_4902357612920161814);
void live_h_13(double *state, double *unused, double *out_1494423759973491701);
void live_H_13(double *state, double *unused, double *out_6361310615393362190);
void live_h_14(double *state, double *unused, double *out_371672585217068510);
void live_H_14(double *state, double *unused, double *out_1112965519969062189);
void live_h_33(double *state, double *unused, double *out_8855959415348729283);
void live_H_33(double *state, double *unused, double *out_1882965393222044679);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}