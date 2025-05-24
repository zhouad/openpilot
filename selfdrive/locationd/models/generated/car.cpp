#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4624442741753145801) {
   out_4624442741753145801[0] = delta_x[0] + nom_x[0];
   out_4624442741753145801[1] = delta_x[1] + nom_x[1];
   out_4624442741753145801[2] = delta_x[2] + nom_x[2];
   out_4624442741753145801[3] = delta_x[3] + nom_x[3];
   out_4624442741753145801[4] = delta_x[4] + nom_x[4];
   out_4624442741753145801[5] = delta_x[5] + nom_x[5];
   out_4624442741753145801[6] = delta_x[6] + nom_x[6];
   out_4624442741753145801[7] = delta_x[7] + nom_x[7];
   out_4624442741753145801[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4763729259609419538) {
   out_4763729259609419538[0] = -nom_x[0] + true_x[0];
   out_4763729259609419538[1] = -nom_x[1] + true_x[1];
   out_4763729259609419538[2] = -nom_x[2] + true_x[2];
   out_4763729259609419538[3] = -nom_x[3] + true_x[3];
   out_4763729259609419538[4] = -nom_x[4] + true_x[4];
   out_4763729259609419538[5] = -nom_x[5] + true_x[5];
   out_4763729259609419538[6] = -nom_x[6] + true_x[6];
   out_4763729259609419538[7] = -nom_x[7] + true_x[7];
   out_4763729259609419538[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1165402551737860898) {
   out_1165402551737860898[0] = 1.0;
   out_1165402551737860898[1] = 0.0;
   out_1165402551737860898[2] = 0.0;
   out_1165402551737860898[3] = 0.0;
   out_1165402551737860898[4] = 0.0;
   out_1165402551737860898[5] = 0.0;
   out_1165402551737860898[6] = 0.0;
   out_1165402551737860898[7] = 0.0;
   out_1165402551737860898[8] = 0.0;
   out_1165402551737860898[9] = 0.0;
   out_1165402551737860898[10] = 1.0;
   out_1165402551737860898[11] = 0.0;
   out_1165402551737860898[12] = 0.0;
   out_1165402551737860898[13] = 0.0;
   out_1165402551737860898[14] = 0.0;
   out_1165402551737860898[15] = 0.0;
   out_1165402551737860898[16] = 0.0;
   out_1165402551737860898[17] = 0.0;
   out_1165402551737860898[18] = 0.0;
   out_1165402551737860898[19] = 0.0;
   out_1165402551737860898[20] = 1.0;
   out_1165402551737860898[21] = 0.0;
   out_1165402551737860898[22] = 0.0;
   out_1165402551737860898[23] = 0.0;
   out_1165402551737860898[24] = 0.0;
   out_1165402551737860898[25] = 0.0;
   out_1165402551737860898[26] = 0.0;
   out_1165402551737860898[27] = 0.0;
   out_1165402551737860898[28] = 0.0;
   out_1165402551737860898[29] = 0.0;
   out_1165402551737860898[30] = 1.0;
   out_1165402551737860898[31] = 0.0;
   out_1165402551737860898[32] = 0.0;
   out_1165402551737860898[33] = 0.0;
   out_1165402551737860898[34] = 0.0;
   out_1165402551737860898[35] = 0.0;
   out_1165402551737860898[36] = 0.0;
   out_1165402551737860898[37] = 0.0;
   out_1165402551737860898[38] = 0.0;
   out_1165402551737860898[39] = 0.0;
   out_1165402551737860898[40] = 1.0;
   out_1165402551737860898[41] = 0.0;
   out_1165402551737860898[42] = 0.0;
   out_1165402551737860898[43] = 0.0;
   out_1165402551737860898[44] = 0.0;
   out_1165402551737860898[45] = 0.0;
   out_1165402551737860898[46] = 0.0;
   out_1165402551737860898[47] = 0.0;
   out_1165402551737860898[48] = 0.0;
   out_1165402551737860898[49] = 0.0;
   out_1165402551737860898[50] = 1.0;
   out_1165402551737860898[51] = 0.0;
   out_1165402551737860898[52] = 0.0;
   out_1165402551737860898[53] = 0.0;
   out_1165402551737860898[54] = 0.0;
   out_1165402551737860898[55] = 0.0;
   out_1165402551737860898[56] = 0.0;
   out_1165402551737860898[57] = 0.0;
   out_1165402551737860898[58] = 0.0;
   out_1165402551737860898[59] = 0.0;
   out_1165402551737860898[60] = 1.0;
   out_1165402551737860898[61] = 0.0;
   out_1165402551737860898[62] = 0.0;
   out_1165402551737860898[63] = 0.0;
   out_1165402551737860898[64] = 0.0;
   out_1165402551737860898[65] = 0.0;
   out_1165402551737860898[66] = 0.0;
   out_1165402551737860898[67] = 0.0;
   out_1165402551737860898[68] = 0.0;
   out_1165402551737860898[69] = 0.0;
   out_1165402551737860898[70] = 1.0;
   out_1165402551737860898[71] = 0.0;
   out_1165402551737860898[72] = 0.0;
   out_1165402551737860898[73] = 0.0;
   out_1165402551737860898[74] = 0.0;
   out_1165402551737860898[75] = 0.0;
   out_1165402551737860898[76] = 0.0;
   out_1165402551737860898[77] = 0.0;
   out_1165402551737860898[78] = 0.0;
   out_1165402551737860898[79] = 0.0;
   out_1165402551737860898[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3753071707696038582) {
   out_3753071707696038582[0] = state[0];
   out_3753071707696038582[1] = state[1];
   out_3753071707696038582[2] = state[2];
   out_3753071707696038582[3] = state[3];
   out_3753071707696038582[4] = state[4];
   out_3753071707696038582[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3753071707696038582[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3753071707696038582[7] = state[7];
   out_3753071707696038582[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9143542782728581509) {
   out_9143542782728581509[0] = 1;
   out_9143542782728581509[1] = 0;
   out_9143542782728581509[2] = 0;
   out_9143542782728581509[3] = 0;
   out_9143542782728581509[4] = 0;
   out_9143542782728581509[5] = 0;
   out_9143542782728581509[6] = 0;
   out_9143542782728581509[7] = 0;
   out_9143542782728581509[8] = 0;
   out_9143542782728581509[9] = 0;
   out_9143542782728581509[10] = 1;
   out_9143542782728581509[11] = 0;
   out_9143542782728581509[12] = 0;
   out_9143542782728581509[13] = 0;
   out_9143542782728581509[14] = 0;
   out_9143542782728581509[15] = 0;
   out_9143542782728581509[16] = 0;
   out_9143542782728581509[17] = 0;
   out_9143542782728581509[18] = 0;
   out_9143542782728581509[19] = 0;
   out_9143542782728581509[20] = 1;
   out_9143542782728581509[21] = 0;
   out_9143542782728581509[22] = 0;
   out_9143542782728581509[23] = 0;
   out_9143542782728581509[24] = 0;
   out_9143542782728581509[25] = 0;
   out_9143542782728581509[26] = 0;
   out_9143542782728581509[27] = 0;
   out_9143542782728581509[28] = 0;
   out_9143542782728581509[29] = 0;
   out_9143542782728581509[30] = 1;
   out_9143542782728581509[31] = 0;
   out_9143542782728581509[32] = 0;
   out_9143542782728581509[33] = 0;
   out_9143542782728581509[34] = 0;
   out_9143542782728581509[35] = 0;
   out_9143542782728581509[36] = 0;
   out_9143542782728581509[37] = 0;
   out_9143542782728581509[38] = 0;
   out_9143542782728581509[39] = 0;
   out_9143542782728581509[40] = 1;
   out_9143542782728581509[41] = 0;
   out_9143542782728581509[42] = 0;
   out_9143542782728581509[43] = 0;
   out_9143542782728581509[44] = 0;
   out_9143542782728581509[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9143542782728581509[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9143542782728581509[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9143542782728581509[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9143542782728581509[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9143542782728581509[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9143542782728581509[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9143542782728581509[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9143542782728581509[53] = -9.8000000000000007*dt;
   out_9143542782728581509[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9143542782728581509[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9143542782728581509[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9143542782728581509[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9143542782728581509[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9143542782728581509[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9143542782728581509[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9143542782728581509[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9143542782728581509[62] = 0;
   out_9143542782728581509[63] = 0;
   out_9143542782728581509[64] = 0;
   out_9143542782728581509[65] = 0;
   out_9143542782728581509[66] = 0;
   out_9143542782728581509[67] = 0;
   out_9143542782728581509[68] = 0;
   out_9143542782728581509[69] = 0;
   out_9143542782728581509[70] = 1;
   out_9143542782728581509[71] = 0;
   out_9143542782728581509[72] = 0;
   out_9143542782728581509[73] = 0;
   out_9143542782728581509[74] = 0;
   out_9143542782728581509[75] = 0;
   out_9143542782728581509[76] = 0;
   out_9143542782728581509[77] = 0;
   out_9143542782728581509[78] = 0;
   out_9143542782728581509[79] = 0;
   out_9143542782728581509[80] = 1;
}
void h_25(double *state, double *unused, double *out_4834028724732154266) {
   out_4834028724732154266[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6772912930606189732) {
   out_6772912930606189732[0] = 0;
   out_6772912930606189732[1] = 0;
   out_6772912930606189732[2] = 0;
   out_6772912930606189732[3] = 0;
   out_6772912930606189732[4] = 0;
   out_6772912930606189732[5] = 0;
   out_6772912930606189732[6] = 1;
   out_6772912930606189732[7] = 0;
   out_6772912930606189732[8] = 0;
}
void h_24(double *state, double *unused, double *out_4101174789381641110) {
   out_4101174789381641110[0] = state[4];
   out_4101174789381641110[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4547205146627321170) {
   out_4547205146627321170[0] = 0;
   out_4547205146627321170[1] = 0;
   out_4547205146627321170[2] = 0;
   out_4547205146627321170[3] = 0;
   out_4547205146627321170[4] = 1;
   out_4547205146627321170[5] = 0;
   out_4547205146627321170[6] = 0;
   out_4547205146627321170[7] = 0;
   out_4547205146627321170[8] = 0;
   out_4547205146627321170[9] = 0;
   out_4547205146627321170[10] = 0;
   out_4547205146627321170[11] = 0;
   out_4547205146627321170[12] = 0;
   out_4547205146627321170[13] = 0;
   out_4547205146627321170[14] = 1;
   out_4547205146627321170[15] = 0;
   out_4547205146627321170[16] = 0;
   out_4547205146627321170[17] = 0;
}
void h_30(double *state, double *unused, double *out_2929236532088518175) {
   out_2929236532088518175[0] = state[4];
}
void H_30(double *state, double *unused, double *out_143777410885427023) {
   out_143777410885427023[0] = 0;
   out_143777410885427023[1] = 0;
   out_143777410885427023[2] = 0;
   out_143777410885427023[3] = 0;
   out_143777410885427023[4] = 1;
   out_143777410885427023[5] = 0;
   out_143777410885427023[6] = 0;
   out_143777410885427023[7] = 0;
   out_143777410885427023[8] = 0;
}
void h_26(double *state, double *unused, double *out_7868162368309699099) {
   out_7868162368309699099[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7932327824229305660) {
   out_7932327824229305660[0] = 0;
   out_7932327824229305660[1] = 0;
   out_7932327824229305660[2] = 0;
   out_7932327824229305660[3] = 0;
   out_7932327824229305660[4] = 0;
   out_7932327824229305660[5] = 0;
   out_7932327824229305660[6] = 0;
   out_7932327824229305660[7] = 1;
   out_7932327824229305660[8] = 0;
}
void h_27(double *state, double *unused, double *out_4147940447274686499) {
   out_4147940447274686499[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2030985900914997888) {
   out_2030985900914997888[0] = 0;
   out_2030985900914997888[1] = 0;
   out_2030985900914997888[2] = 0;
   out_2030985900914997888[3] = 1;
   out_2030985900914997888[4] = 0;
   out_2030985900914997888[5] = 0;
   out_2030985900914997888[6] = 0;
   out_2030985900914997888[7] = 0;
   out_2030985900914997888[8] = 0;
}
void h_29(double *state, double *unused, double *out_3872746384990180610) {
   out_3872746384990180610[0] = state[1];
}
void H_29(double *state, double *unused, double *out_654008755199819207) {
   out_654008755199819207[0] = 0;
   out_654008755199819207[1] = 1;
   out_654008755199819207[2] = 0;
   out_654008755199819207[3] = 0;
   out_654008755199819207[4] = 0;
   out_654008755199819207[5] = 0;
   out_654008755199819207[6] = 0;
   out_654008755199819207[7] = 0;
   out_654008755199819207[8] = 0;
}
void h_28(double *state, double *unused, double *out_853732820386159146) {
   out_853732820386159146[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8826747644854079495) {
   out_8826747644854079495[0] = 1;
   out_8826747644854079495[1] = 0;
   out_8826747644854079495[2] = 0;
   out_8826747644854079495[3] = 0;
   out_8826747644854079495[4] = 0;
   out_8826747644854079495[5] = 0;
   out_8826747644854079495[6] = 0;
   out_8826747644854079495[7] = 0;
   out_8826747644854079495[8] = 0;
}
void h_31(double *state, double *unused, double *out_5659680830519997122) {
   out_5659680830519997122[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6742266968729229304) {
   out_6742266968729229304[0] = 0;
   out_6742266968729229304[1] = 0;
   out_6742266968729229304[2] = 0;
   out_6742266968729229304[3] = 0;
   out_6742266968729229304[4] = 0;
   out_6742266968729229304[5] = 0;
   out_6742266968729229304[6] = 0;
   out_6742266968729229304[7] = 0;
   out_6742266968729229304[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4624442741753145801) {
  err_fun(nom_x, delta_x, out_4624442741753145801);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4763729259609419538) {
  inv_err_fun(nom_x, true_x, out_4763729259609419538);
}
void car_H_mod_fun(double *state, double *out_1165402551737860898) {
  H_mod_fun(state, out_1165402551737860898);
}
void car_f_fun(double *state, double dt, double *out_3753071707696038582) {
  f_fun(state,  dt, out_3753071707696038582);
}
void car_F_fun(double *state, double dt, double *out_9143542782728581509) {
  F_fun(state,  dt, out_9143542782728581509);
}
void car_h_25(double *state, double *unused, double *out_4834028724732154266) {
  h_25(state, unused, out_4834028724732154266);
}
void car_H_25(double *state, double *unused, double *out_6772912930606189732) {
  H_25(state, unused, out_6772912930606189732);
}
void car_h_24(double *state, double *unused, double *out_4101174789381641110) {
  h_24(state, unused, out_4101174789381641110);
}
void car_H_24(double *state, double *unused, double *out_4547205146627321170) {
  H_24(state, unused, out_4547205146627321170);
}
void car_h_30(double *state, double *unused, double *out_2929236532088518175) {
  h_30(state, unused, out_2929236532088518175);
}
void car_H_30(double *state, double *unused, double *out_143777410885427023) {
  H_30(state, unused, out_143777410885427023);
}
void car_h_26(double *state, double *unused, double *out_7868162368309699099) {
  h_26(state, unused, out_7868162368309699099);
}
void car_H_26(double *state, double *unused, double *out_7932327824229305660) {
  H_26(state, unused, out_7932327824229305660);
}
void car_h_27(double *state, double *unused, double *out_4147940447274686499) {
  h_27(state, unused, out_4147940447274686499);
}
void car_H_27(double *state, double *unused, double *out_2030985900914997888) {
  H_27(state, unused, out_2030985900914997888);
}
void car_h_29(double *state, double *unused, double *out_3872746384990180610) {
  h_29(state, unused, out_3872746384990180610);
}
void car_H_29(double *state, double *unused, double *out_654008755199819207) {
  H_29(state, unused, out_654008755199819207);
}
void car_h_28(double *state, double *unused, double *out_853732820386159146) {
  h_28(state, unused, out_853732820386159146);
}
void car_H_28(double *state, double *unused, double *out_8826747644854079495) {
  H_28(state, unused, out_8826747644854079495);
}
void car_h_31(double *state, double *unused, double *out_5659680830519997122) {
  h_31(state, unused, out_5659680830519997122);
}
void car_H_31(double *state, double *unused, double *out_6742266968729229304) {
  H_31(state, unused, out_6742266968729229304);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
