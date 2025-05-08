#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_370478261474098247);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2754704753635741812);
void car_H_mod_fun(double *state, double *out_3683481686615348312);
void car_f_fun(double *state, double dt, double *out_2191088460119330414);
void car_F_fun(double *state, double dt, double *out_9073829423060190499);
void car_h_25(double *state, double *unused, double *out_8958950060573646875);
void car_H_25(double *state, double *unused, double *out_8587173511800013152);
void car_h_24(double *state, double *unused, double *out_930064219770468569);
void car_H_24(double *state, double *unused, double *out_3283998755318020363);
void car_h_30(double *state, double *unused, double *out_1195684803752974434);
void car_H_30(double *state, double *unused, double *out_2942880220417921709);
void car_h_26(double *state, double *unused, double *out_4232470855197307119);
void car_H_26(double *state, double *unused, double *out_4845670192925956928);
void car_h_27(double *state, double *unused, double *out_4421376494417562018);
void car_H_27(double *state, double *unused, double *out_5117643532218346620);
void car_h_29(double *state, double *unused, double *out_4146182432133056129);
void car_H_29(double *state, double *unused, double *out_6831006259087897653);
void car_h_28(double *state, double *unused, double *out_7025781815226259669);
void car_H_28(double *state, double *unused, double *out_6533338797552123389);
void car_h_31(double *state, double *unused, double *out_8886375855522541187);
void car_H_31(double *state, double *unused, double *out_8617819473676973580);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}