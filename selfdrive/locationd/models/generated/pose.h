#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6950291583245326091);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7864587791361010025);
void pose_H_mod_fun(double *state, double *out_5486619309331330377);
void pose_f_fun(double *state, double dt, double *out_1235871428435988271);
void pose_F_fun(double *state, double dt, double *out_6226252063534521061);
void pose_h_4(double *state, double *unused, double *out_3900248353984202260);
void pose_H_4(double *state, double *unused, double *out_4732458307276617770);
void pose_h_10(double *state, double *unused, double *out_5710312720723321812);
void pose_H_10(double *state, double *unused, double *out_1994324288274465262);
void pose_h_13(double *state, double *unused, double *out_6587030294683941770);
void pose_H_13(double *state, double *unused, double *out_1520184481944284969);
void pose_h_14(double *state, double *unused, double *out_5256678746065369612);
void pose_H_14(double *state, double *unused, double *out_7815246739571990066);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}