#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7661590215377839666);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_867942321893475263);
void pose_H_mod_fun(double *state, double *out_3310708289553390566);
void pose_f_fun(double *state, double dt, double *out_8818314056008048446);
void pose_F_fun(double *state, double dt, double *out_2885434936790366260);
void pose_h_4(double *state, double *unused, double *out_7861660616364934295);
void pose_H_4(double *state, double *unused, double *out_2112760807670492462);
void pose_h_10(double *state, double *unused, double *out_896930610882370113);
void pose_H_10(double *state, double *unused, double *out_107142426047667165);
void pose_h_13(double *state, double *unused, double *out_6097667701153012788);
void pose_H_13(double *state, double *unused, double *out_1099513017661840339);
void pose_h_14(double *state, double *unused, double *out_7028840117111836812);
void pose_H_14(double *state, double *unused, double *out_5195549239965864758);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}