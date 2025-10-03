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
void live_H(double *in_vec, double *out_6330864412356249095);
void live_err_fun(double *nom_x, double *delta_x, double *out_2184138268403689368);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6227291690067643035);
void live_H_mod_fun(double *state, double *out_2920090350307623128);
void live_f_fun(double *state, double dt, double *out_6894308160155303963);
void live_F_fun(double *state, double dt, double *out_9123483619647982274);
void live_h_4(double *state, double *unused, double *out_1894937552768048796);
void live_H_4(double *state, double *unused, double *out_5989735521063437686);
void live_h_9(double *state, double *unused, double *out_4294315309452820316);
void live_H_9(double *state, double *unused, double *out_3100873968783358344);
void live_h_10(double *state, double *unused, double *out_1396005915906487718);
void live_H_10(double *state, double *unused, double *out_168727971127988768);
void live_h_12(double *state, double *unused, double *out_1321807637606364574);
void live_H_12(double *state, double *unused, double *out_5368636496015844019);
void live_h_35(double *state, double *unused, double *out_5458938299250784412);
void live_H_35(double *state, double *unused, double *out_2623073463690830310);
void live_h_32(double *state, double *unused, double *out_1023469487165117247);
void live_H_32(double *state, double *unused, double *out_4267912973401729912);
void live_h_13(double *state, double *unused, double *out_4833626518094377599);
void live_H_13(double *state, double *unused, double *out_1185785277283463649);
void live_h_14(double *state, double *unused, double *out_4294315309452820316);
void live_H_14(double *state, double *unused, double *out_3100873968783358344);
void live_h_33(double *state, double *unused, double *out_7622321916297613419);
void live_H_33(double *state, double *unused, double *out_527483540948027294);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}