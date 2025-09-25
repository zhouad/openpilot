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
void live_H(double *in_vec, double *out_7192626465969426310);
void live_err_fun(double *nom_x, double *delta_x, double *out_8267414924958799098);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6790801154123303470);
void live_H_mod_fun(double *state, double *out_7578437124212003399);
void live_f_fun(double *state, double dt, double *out_7029063535498789077);
void live_F_fun(double *state, double dt, double *out_2753188682549842837);
void live_h_4(double *state, double *unused, double *out_7047424262828774852);
void live_H_4(double *state, double *unused, double *out_5908841931880971527);
void live_h_9(double *state, double *unused, double *out_5074359214044393374);
void live_H_9(double *state, double *unused, double *out_3019980379600892185);
void live_h_10(double *state, double *unused, double *out_6927010569651698419);
void live_H_10(double *state, double *unused, double *out_5151621143608136929);
void live_h_12(double *state, double *unused, double *out_4103364396423413669);
void live_H_12(double *state, double *unused, double *out_1758286381801478965);
void live_h_35(double *state, double *unused, double *out_531220340974882437);
void live_H_35(double *state, double *unused, double *out_2542179874508364151);
void live_h_32(double *state, double *unused, double *out_4916647171418676380);
void live_H_32(double *state, double *unused, double *out_8141590287375446384);
void live_h_13(double *state, double *unused, double *out_3726368511217429187);
void live_H_13(double *state, double *unused, double *out_7185551590990909283);
void live_h_14(double *state, double *unused, double *out_5074359214044393374);
void live_H_14(double *state, double *unused, double *out_3019980379600892185);
void live_h_33(double *state, double *unused, double *out_4271086258777626497);
void live_H_33(double *state, double *unused, double *out_608377130130493453);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}