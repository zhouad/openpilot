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
void car_err_fun(double *nom_x, double *delta_x, double *out_1019116046903339868);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5227289756004260955);
void car_H_mod_fun(double *state, double *out_3146254179526665886);
void car_f_fun(double *state, double dt, double *out_9033859238508349648);
void car_F_fun(double *state, double dt, double *out_1223629188143286099);
void car_h_25(double *state, double *unused, double *out_1581925918488859021);
void car_H_25(double *state, double *unused, double *out_3350768780363364065);
void car_h_24(double *state, double *unused, double *out_6550999019738618712);
void car_H_24(double *state, double *unused, double *out_1922725502549648529);
void car_h_30(double *state, double *unused, double *out_5219375446742881371);
void car_H_30(double *state, double *unused, double *out_7878465110490972263);
void car_h_26(double *state, double *unused, double *out_2943846629129829237);
void car_H_26(double *state, double *unused, double *out_7092272099237420289);
void car_h_27(double *state, double *unused, double *out_5420836785304206758);
void car_H_27(double *state, double *unused, double *out_5654871039307029046);
void car_h_29(double *state, double *unused, double *out_5822691331419358888);
void car_H_29(double *state, double *unused, double *out_7368233766176580079);
void car_h_28(double *state, double *unused, double *out_8457622836748539443);
void car_H_28(double *state, double *unused, double *out_5996111290463440963);
void car_h_31(double *state, double *unused, double *out_7749039958459993324);
void car_H_31(double *state, double *unused, double *out_7718480201470771765);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}