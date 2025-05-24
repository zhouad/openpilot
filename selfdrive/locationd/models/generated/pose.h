#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3271959735080300269);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7212079695949744902);
void pose_H_mod_fun(double *state, double *out_5997326193381454730);
void pose_f_fun(double *state, double dt, double *out_6861504228684851862);
void pose_F_fun(double *state, double dt, double *out_7588529982742305973);
void pose_h_4(double *state, double *unused, double *out_6699510873064443946);
void pose_H_4(double *state, double *unused, double *out_3505056214270275544);
void pose_h_10(double *state, double *unused, double *out_624795893851869901);
void pose_H_10(double *state, double *unused, double *out_703039798711493596);
void pose_h_13(double *state, double *unused, double *out_3549684128180221096);
void pose_H_13(double *state, double *unused, double *out_328699249032248480);
void pose_h_14(double *state, double *unused, double *out_7824739296360248187);
void pose_H_14(double *state, double *unused, double *out_422267781974903248);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}