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
void car_err_fun(double *nom_x, double *delta_x, double *out_995120164199457443);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6704959146488613277);
void car_H_mod_fun(double *state, double *out_4299846469589187995);
void car_f_fun(double *state, double dt, double *out_438127755532525700);
void car_F_fun(double *state, double dt, double *out_2940294730852415860);
void car_h_25(double *state, double *unused, double *out_848939978928586795);
void car_H_25(double *state, double *unused, double *out_4953709378208126384);
void car_h_24(double *state, double *unused, double *out_1907769209390582607);
void car_H_24(double *state, double *unused, double *out_7179417162186994946);
void car_h_30(double *state, double *unused, double *out_5306507216912073334);
void car_H_30(double *state, double *unused, double *out_6576344354009808477);
void car_h_26(double *state, double *unused, double *out_3458413542436267994);
void car_H_26(double *state, double *unused, double *out_1212206059334070160);
void car_h_27(double *state, double *unused, double *out_2426907833818869794);
void car_H_27(double *state, double *unused, double *out_2649607119264461403);
void car_h_29(double *state, double *unused, double *out_2702101896103375683);
void car_H_29(double *state, double *unused, double *out_5334601775379278498);
void car_h_28(double *state, double *unused, double *out_7428581101479715439);
void car_H_28(double *state, double *unused, double *out_7298232046944604749);
void car_h_31(double *state, double *unused, double *out_5522491424197460812);
void car_H_31(double *state, double *unused, double *out_4984355340085086812);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}