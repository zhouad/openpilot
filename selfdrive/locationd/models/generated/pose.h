#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5992451308463414616);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7389899634648651549);
void pose_H_mod_fun(double *state, double *out_3435766699566864488);
void pose_f_fun(double *state, double dt, double *out_8749009569559483773);
void pose_F_fun(double *state, double dt, double *out_52750658265818918);
void pose_h_4(double *state, double *unused, double *out_5958124488714996433);
void pose_H_4(double *state, double *unused, double *out_2412315107185094233);
void pose_h_10(double *state, double *unused, double *out_1722102185314223216);
void pose_H_10(double *state, double *unused, double *out_9091090751848045599);
void pose_h_13(double *state, double *unused, double *out_6609880627909947861);
void pose_H_13(double *state, double *unused, double *out_5198316101131606696);
void pose_h_14(double *state, double *unused, double *out_925595179133717464);
void pose_H_14(double *state, double *unused, double *out_1550925749154390296);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}