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
void car_err_fun(double *nom_x, double *delta_x, double *out_5502167403095710991);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3774316406736780008);
void car_H_mod_fun(double *state, double *out_1624587115349650366);
void car_f_fun(double *state, double dt, double *out_7007240483040271081);
void car_F_fun(double *state, double dt, double *out_3417649342865291063);
void car_h_25(double *state, double *unused, double *out_8870524108734237637);
void car_H_25(double *state, double *unused, double *out_1469431157442746142);
void car_h_24(double *state, double *unused, double *out_2970532528807155776);
void car_H_24(double *state, double *unused, double *out_703218441562753424);
void car_h_30(double *state, double *unused, double *out_977584613849714278);
void car_H_30(double *state, double *unused, double *out_3987764115949994769);
void car_h_26(double *state, double *unused, double *out_7610578067955127130);
void car_H_26(double *state, double *unused, double *out_2272072161431310082);
void car_h_27(double *state, double *unused, double *out_4574546697314468334);
void car_H_27(double *state, double *unused, double *out_6211358187133937986);
void car_h_29(double *state, double *unused, double *out_6025178089943351501);
void car_H_29(double *state, double *unused, double *out_4497995460264386953);
void car_h_28(double *state, double *unused, double *out_7611332748758801019);
void car_H_28(double *state, double *unused, double *out_584403556805143621);
void car_h_31(double *state, double *unused, double *out_2805384738624963043);
void car_H_31(double *state, double *unused, double *out_2898280263664661558);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}