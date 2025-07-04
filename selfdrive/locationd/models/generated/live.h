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
void live_H(double *in_vec, double *out_5353894543392087576);
void live_err_fun(double *nom_x, double *delta_x, double *out_6516309622000207042);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6624053904164944585);
void live_H_mod_fun(double *state, double *out_4379910092575934237);
void live_f_fun(double *state, double dt, double *out_2743805046257990915);
void live_F_fun(double *state, double dt, double *out_6172740135105437635);
void live_h_4(double *state, double *unused, double *out_8170091984957025191);
void live_H_4(double *state, double *unused, double *out_1167562289255796791);
void live_h_9(double *state, double *unused, double *out_8901310597700495956);
void live_H_9(double *state, double *unused, double *out_6119656646008650679);
void live_h_10(double *state, double *unused, double *out_213490747221838475);
void live_H_10(double *state, double *unused, double *out_603747889056534408);
void live_h_12(double *state, double *unused, double *out_188972104099036825);
void live_H_12(double *state, double *unused, double *out_7548820666298529787);
void live_h_35(double *state, double *unused, double *out_8830316288917152529);
void live_H_35(double *state, double *unused, double *out_4803257633973516078);
void live_h_32(double *state, double *unused, double *out_1911181193904865184);
void live_H_32(double *state, double *unused, double *out_2019599469555098485);
void live_h_13(double *state, double *unused, double *out_8747754753628633936);
void live_H_13(double *state, double *unused, double *out_8662610900706561754);
void live_h_14(double *state, double *unused, double *out_8901310597700495956);
void live_H_14(double *state, double *unused, double *out_6119656646008650679);
void live_h_33(double *state, double *unused, double *out_3992743446442020556);
void live_H_33(double *state, double *unused, double *out_1652700629334658474);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}