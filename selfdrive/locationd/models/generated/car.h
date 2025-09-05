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
void car_err_fun(double *nom_x, double *delta_x, double *out_6552679409720063083);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_375450875847608461);
void car_H_mod_fun(double *state, double *out_8454853977093352772);
void car_f_fun(double *state, double dt, double *out_992240007066989833);
void car_F_fun(double *state, double dt, double *out_6632803905489520127);
void car_h_25(double *state, double *unused, double *out_1516450530651524889);
void car_H_25(double *state, double *unused, double *out_3551162151908687932);
void car_h_24(double *state, double *unused, double *out_4218575999364657751);
void car_H_24(double *state, double *unused, double *out_1373947728301537959);
void car_h_30(double *state, double *unused, double *out_6376488964232998470);
void car_H_30(double *state, double *unused, double *out_1032829193401439305);
void car_h_26(double *state, double *unused, double *out_8794407296729096557);
void car_H_26(double *state, double *unused, double *out_246636182147887331);
void car_h_27(double *state, double *unused, double *out_3221695518855289041);
void car_H_27(double *state, double *unused, double *out_3207592505201864216);
void car_h_29(double *state, double *unused, double *out_5671213592062704000);
void car_H_29(double *state, double *unused, double *out_522597849087047121);
void car_h_28(double *state, double *unused, double *out_2463845373694470231);
void car_H_28(double *state, double *unused, double *out_5604996866156577695);
void car_h_31(double *state, double *unused, double *out_4324439413990751749);
void car_H_31(double *state, double *unused, double *out_872844284381238807);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}