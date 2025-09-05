#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6360695334706395645);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3498794849105875793);
void pose_H_mod_fun(double *state, double *out_9153131841173163388);
void pose_f_fun(double *state, double dt, double *out_5731900164957455748);
void pose_F_fun(double *state, double dt, double *out_552344081412747464);
void pose_h_4(double *state, double *unused, double *out_2352995918424077902);
void pose_H_4(double *state, double *unused, double *out_6019390153745438975);
void pose_h_10(double *state, double *unused, double *out_577009537073488637);
void pose_H_10(double *state, double *unused, double *out_1175900786030612795);
void pose_h_13(double *state, double *unused, double *out_4589151815082178536);
void pose_H_13(double *state, double *unused, double *out_4816722711647411712);
void pose_h_14(double *state, double *unused, double *out_4921164340780417902);
void pose_H_14(double *state, double *unused, double *out_8464113063624628112);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}