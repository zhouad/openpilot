#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8215112940017755867);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1173819570397538874);
void pose_H_mod_fun(double *state, double *out_8295691051147185807);
void pose_f_fun(double *state, double dt, double *out_5130330965522153001);
void pose_F_fun(double *state, double dt, double *out_488534431383752290);
void pose_h_4(double *state, double *unused, double *out_8441742047814671654);
void pose_H_4(double *state, double *unused, double *out_7694699903545492360);
void pose_h_10(double *state, double *unused, double *out_1124287673941347069);
void pose_H_10(double *state, double *unused, double *out_8452541670693679658);
void pose_h_13(double *state, double *unused, double *out_157612946214320216);
void pose_H_13(double *state, double *unused, double *out_84068695228791431);
void pose_h_14(double *state, double *unused, double *out_5323712927848765653);
void pose_H_14(double *state, double *unused, double *out_3731459047206007831);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}