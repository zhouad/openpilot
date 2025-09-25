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
void err_fun(double *nom_x, double *delta_x, double *out_497411416085616360) {
   out_497411416085616360[0] = delta_x[0] + nom_x[0];
   out_497411416085616360[1] = delta_x[1] + nom_x[1];
   out_497411416085616360[2] = delta_x[2] + nom_x[2];
   out_497411416085616360[3] = delta_x[3] + nom_x[3];
   out_497411416085616360[4] = delta_x[4] + nom_x[4];
   out_497411416085616360[5] = delta_x[5] + nom_x[5];
   out_497411416085616360[6] = delta_x[6] + nom_x[6];
   out_497411416085616360[7] = delta_x[7] + nom_x[7];
   out_497411416085616360[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4833570427681397891) {
   out_4833570427681397891[0] = -nom_x[0] + true_x[0];
   out_4833570427681397891[1] = -nom_x[1] + true_x[1];
   out_4833570427681397891[2] = -nom_x[2] + true_x[2];
   out_4833570427681397891[3] = -nom_x[3] + true_x[3];
   out_4833570427681397891[4] = -nom_x[4] + true_x[4];
   out_4833570427681397891[5] = -nom_x[5] + true_x[5];
   out_4833570427681397891[6] = -nom_x[6] + true_x[6];
   out_4833570427681397891[7] = -nom_x[7] + true_x[7];
   out_4833570427681397891[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1671451718469889604) {
   out_1671451718469889604[0] = 1.0;
   out_1671451718469889604[1] = 0.0;
   out_1671451718469889604[2] = 0.0;
   out_1671451718469889604[3] = 0.0;
   out_1671451718469889604[4] = 0.0;
   out_1671451718469889604[5] = 0.0;
   out_1671451718469889604[6] = 0.0;
   out_1671451718469889604[7] = 0.0;
   out_1671451718469889604[8] = 0.0;
   out_1671451718469889604[9] = 0.0;
   out_1671451718469889604[10] = 1.0;
   out_1671451718469889604[11] = 0.0;
   out_1671451718469889604[12] = 0.0;
   out_1671451718469889604[13] = 0.0;
   out_1671451718469889604[14] = 0.0;
   out_1671451718469889604[15] = 0.0;
   out_1671451718469889604[16] = 0.0;
   out_1671451718469889604[17] = 0.0;
   out_1671451718469889604[18] = 0.0;
   out_1671451718469889604[19] = 0.0;
   out_1671451718469889604[20] = 1.0;
   out_1671451718469889604[21] = 0.0;
   out_1671451718469889604[22] = 0.0;
   out_1671451718469889604[23] = 0.0;
   out_1671451718469889604[24] = 0.0;
   out_1671451718469889604[25] = 0.0;
   out_1671451718469889604[26] = 0.0;
   out_1671451718469889604[27] = 0.0;
   out_1671451718469889604[28] = 0.0;
   out_1671451718469889604[29] = 0.0;
   out_1671451718469889604[30] = 1.0;
   out_1671451718469889604[31] = 0.0;
   out_1671451718469889604[32] = 0.0;
   out_1671451718469889604[33] = 0.0;
   out_1671451718469889604[34] = 0.0;
   out_1671451718469889604[35] = 0.0;
   out_1671451718469889604[36] = 0.0;
   out_1671451718469889604[37] = 0.0;
   out_1671451718469889604[38] = 0.0;
   out_1671451718469889604[39] = 0.0;
   out_1671451718469889604[40] = 1.0;
   out_1671451718469889604[41] = 0.0;
   out_1671451718469889604[42] = 0.0;
   out_1671451718469889604[43] = 0.0;
   out_1671451718469889604[44] = 0.0;
   out_1671451718469889604[45] = 0.0;
   out_1671451718469889604[46] = 0.0;
   out_1671451718469889604[47] = 0.0;
   out_1671451718469889604[48] = 0.0;
   out_1671451718469889604[49] = 0.0;
   out_1671451718469889604[50] = 1.0;
   out_1671451718469889604[51] = 0.0;
   out_1671451718469889604[52] = 0.0;
   out_1671451718469889604[53] = 0.0;
   out_1671451718469889604[54] = 0.0;
   out_1671451718469889604[55] = 0.0;
   out_1671451718469889604[56] = 0.0;
   out_1671451718469889604[57] = 0.0;
   out_1671451718469889604[58] = 0.0;
   out_1671451718469889604[59] = 0.0;
   out_1671451718469889604[60] = 1.0;
   out_1671451718469889604[61] = 0.0;
   out_1671451718469889604[62] = 0.0;
   out_1671451718469889604[63] = 0.0;
   out_1671451718469889604[64] = 0.0;
   out_1671451718469889604[65] = 0.0;
   out_1671451718469889604[66] = 0.0;
   out_1671451718469889604[67] = 0.0;
   out_1671451718469889604[68] = 0.0;
   out_1671451718469889604[69] = 0.0;
   out_1671451718469889604[70] = 1.0;
   out_1671451718469889604[71] = 0.0;
   out_1671451718469889604[72] = 0.0;
   out_1671451718469889604[73] = 0.0;
   out_1671451718469889604[74] = 0.0;
   out_1671451718469889604[75] = 0.0;
   out_1671451718469889604[76] = 0.0;
   out_1671451718469889604[77] = 0.0;
   out_1671451718469889604[78] = 0.0;
   out_1671451718469889604[79] = 0.0;
   out_1671451718469889604[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7688883402641383999) {
   out_7688883402641383999[0] = state[0];
   out_7688883402641383999[1] = state[1];
   out_7688883402641383999[2] = state[2];
   out_7688883402641383999[3] = state[3];
   out_7688883402641383999[4] = state[4];
   out_7688883402641383999[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7688883402641383999[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7688883402641383999[7] = state[7];
   out_7688883402641383999[8] = state[8];
}
void F_fun(double *state, double dt, double *out_906172446396236554) {
   out_906172446396236554[0] = 1;
   out_906172446396236554[1] = 0;
   out_906172446396236554[2] = 0;
   out_906172446396236554[3] = 0;
   out_906172446396236554[4] = 0;
   out_906172446396236554[5] = 0;
   out_906172446396236554[6] = 0;
   out_906172446396236554[7] = 0;
   out_906172446396236554[8] = 0;
   out_906172446396236554[9] = 0;
   out_906172446396236554[10] = 1;
   out_906172446396236554[11] = 0;
   out_906172446396236554[12] = 0;
   out_906172446396236554[13] = 0;
   out_906172446396236554[14] = 0;
   out_906172446396236554[15] = 0;
   out_906172446396236554[16] = 0;
   out_906172446396236554[17] = 0;
   out_906172446396236554[18] = 0;
   out_906172446396236554[19] = 0;
   out_906172446396236554[20] = 1;
   out_906172446396236554[21] = 0;
   out_906172446396236554[22] = 0;
   out_906172446396236554[23] = 0;
   out_906172446396236554[24] = 0;
   out_906172446396236554[25] = 0;
   out_906172446396236554[26] = 0;
   out_906172446396236554[27] = 0;
   out_906172446396236554[28] = 0;
   out_906172446396236554[29] = 0;
   out_906172446396236554[30] = 1;
   out_906172446396236554[31] = 0;
   out_906172446396236554[32] = 0;
   out_906172446396236554[33] = 0;
   out_906172446396236554[34] = 0;
   out_906172446396236554[35] = 0;
   out_906172446396236554[36] = 0;
   out_906172446396236554[37] = 0;
   out_906172446396236554[38] = 0;
   out_906172446396236554[39] = 0;
   out_906172446396236554[40] = 1;
   out_906172446396236554[41] = 0;
   out_906172446396236554[42] = 0;
   out_906172446396236554[43] = 0;
   out_906172446396236554[44] = 0;
   out_906172446396236554[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_906172446396236554[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_906172446396236554[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_906172446396236554[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_906172446396236554[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_906172446396236554[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_906172446396236554[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_906172446396236554[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_906172446396236554[53] = -9.8100000000000005*dt;
   out_906172446396236554[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_906172446396236554[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_906172446396236554[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_906172446396236554[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_906172446396236554[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_906172446396236554[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_906172446396236554[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_906172446396236554[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_906172446396236554[62] = 0;
   out_906172446396236554[63] = 0;
   out_906172446396236554[64] = 0;
   out_906172446396236554[65] = 0;
   out_906172446396236554[66] = 0;
   out_906172446396236554[67] = 0;
   out_906172446396236554[68] = 0;
   out_906172446396236554[69] = 0;
   out_906172446396236554[70] = 1;
   out_906172446396236554[71] = 0;
   out_906172446396236554[72] = 0;
   out_906172446396236554[73] = 0;
   out_906172446396236554[74] = 0;
   out_906172446396236554[75] = 0;
   out_906172446396236554[76] = 0;
   out_906172446396236554[77] = 0;
   out_906172446396236554[78] = 0;
   out_906172446396236554[79] = 0;
   out_906172446396236554[80] = 1;
}
void h_25(double *state, double *unused, double *out_7655302679692222819) {
   out_7655302679692222819[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6575143543654554444) {
   out_6575143543654554444[0] = 0;
   out_6575143543654554444[1] = 0;
   out_6575143543654554444[2] = 0;
   out_6575143543654554444[3] = 0;
   out_6575143543654554444[4] = 0;
   out_6575143543654554444[5] = 0;
   out_6575143543654554444[6] = 1;
   out_6575143543654554444[7] = 0;
   out_6575143543654554444[8] = 0;
}
void h_24(double *state, double *unused, double *out_8836079831736825888) {
   out_8836079831736825888[0] = state[4];
   out_8836079831736825888[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6178498239300694949) {
   out_6178498239300694949[0] = 0;
   out_6178498239300694949[1] = 0;
   out_6178498239300694949[2] = 0;
   out_6178498239300694949[3] = 0;
   out_6178498239300694949[4] = 1;
   out_6178498239300694949[5] = 0;
   out_6178498239300694949[6] = 0;
   out_6178498239300694949[7] = 0;
   out_6178498239300694949[8] = 0;
   out_6178498239300694949[9] = 0;
   out_6178498239300694949[10] = 0;
   out_6178498239300694949[11] = 0;
   out_6178498239300694949[12] = 0;
   out_6178498239300694949[13] = 0;
   out_6178498239300694949[14] = 1;
   out_6178498239300694949[15] = 0;
   out_6178498239300694949[16] = 0;
   out_6178498239300694949[17] = 0;
}
void h_30(double *state, double *unused, double *out_1482414604991628363) {
   out_1482414604991628363[0] = state[4];
}
void H_30(double *state, double *unused, double *out_9093476502161803071) {
   out_9093476502161803071[0] = 0;
   out_9093476502161803071[1] = 0;
   out_9093476502161803071[2] = 0;
   out_9093476502161803071[3] = 0;
   out_9093476502161803071[4] = 1;
   out_9093476502161803071[5] = 0;
   out_9093476502161803071[6] = 0;
   out_9093476502161803071[7] = 0;
   out_9093476502161803071[8] = 0;
}
void h_26(double *state, double *unused, double *out_5907775520289859896) {
   out_5907775520289859896[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2833640224780498220) {
   out_2833640224780498220[0] = 0;
   out_2833640224780498220[1] = 0;
   out_2833640224780498220[2] = 0;
   out_2833640224780498220[3] = 0;
   out_2833640224780498220[4] = 0;
   out_2833640224780498220[5] = 0;
   out_2833640224780498220[6] = 0;
   out_2833640224780498220[7] = 1;
   out_2833640224780498220[8] = 0;
}
void h_27(double *state, double *unused, double *out_5789768126356483152) {
   out_5789768126356483152[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6918713190361378160) {
   out_6918713190361378160[0] = 0;
   out_6918713190361378160[1] = 0;
   out_6918713190361378160[2] = 0;
   out_6918713190361378160[3] = 1;
   out_6918713190361378160[4] = 0;
   out_6918713190361378160[5] = 0;
   out_6918713190361378160[6] = 0;
   out_6918713190361378160[7] = 0;
   out_6918713190361378160[8] = 0;
}
void h_29(double *state, double *unused, double *out_4160315266089328472) {
   out_4160315266089328472[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8843036227233356361) {
   out_8843036227233356361[0] = 0;
   out_8843036227233356361[1] = 1;
   out_8843036227233356361[2] = 0;
   out_8843036227233356361[3] = 0;
   out_8843036227233356361[4] = 0;
   out_8843036227233356361[5] = 0;
   out_8843036227233356361[6] = 0;
   out_8843036227233356361[7] = 0;
   out_8843036227233356361[8] = 0;
}
void h_28(double *state, double *unused, double *out_2798394555448358256) {
   out_2798394555448358256[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4521308829406664681) {
   out_4521308829406664681[0] = 1;
   out_4521308829406664681[1] = 0;
   out_4521308829406664681[2] = 0;
   out_4521308829406664681[3] = 0;
   out_4521308829406664681[4] = 0;
   out_4521308829406664681[5] = 0;
   out_4521308829406664681[6] = 0;
   out_4521308829406664681[7] = 0;
   out_4521308829406664681[8] = 0;
}
void h_31(double *state, double *unused, double *out_3028176137196656356) {
   out_3028176137196656356[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2207432122547146744) {
   out_2207432122547146744[0] = 0;
   out_2207432122547146744[1] = 0;
   out_2207432122547146744[2] = 0;
   out_2207432122547146744[3] = 0;
   out_2207432122547146744[4] = 0;
   out_2207432122547146744[5] = 0;
   out_2207432122547146744[6] = 0;
   out_2207432122547146744[7] = 0;
   out_2207432122547146744[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_497411416085616360) {
  err_fun(nom_x, delta_x, out_497411416085616360);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4833570427681397891) {
  inv_err_fun(nom_x, true_x, out_4833570427681397891);
}
void car_H_mod_fun(double *state, double *out_1671451718469889604) {
  H_mod_fun(state, out_1671451718469889604);
}
void car_f_fun(double *state, double dt, double *out_7688883402641383999) {
  f_fun(state,  dt, out_7688883402641383999);
}
void car_F_fun(double *state, double dt, double *out_906172446396236554) {
  F_fun(state,  dt, out_906172446396236554);
}
void car_h_25(double *state, double *unused, double *out_7655302679692222819) {
  h_25(state, unused, out_7655302679692222819);
}
void car_H_25(double *state, double *unused, double *out_6575143543654554444) {
  H_25(state, unused, out_6575143543654554444);
}
void car_h_24(double *state, double *unused, double *out_8836079831736825888) {
  h_24(state, unused, out_8836079831736825888);
}
void car_H_24(double *state, double *unused, double *out_6178498239300694949) {
  H_24(state, unused, out_6178498239300694949);
}
void car_h_30(double *state, double *unused, double *out_1482414604991628363) {
  h_30(state, unused, out_1482414604991628363);
}
void car_H_30(double *state, double *unused, double *out_9093476502161803071) {
  H_30(state, unused, out_9093476502161803071);
}
void car_h_26(double *state, double *unused, double *out_5907775520289859896) {
  h_26(state, unused, out_5907775520289859896);
}
void car_H_26(double *state, double *unused, double *out_2833640224780498220) {
  H_26(state, unused, out_2833640224780498220);
}
void car_h_27(double *state, double *unused, double *out_5789768126356483152) {
  h_27(state, unused, out_5789768126356483152);
}
void car_H_27(double *state, double *unused, double *out_6918713190361378160) {
  H_27(state, unused, out_6918713190361378160);
}
void car_h_29(double *state, double *unused, double *out_4160315266089328472) {
  h_29(state, unused, out_4160315266089328472);
}
void car_H_29(double *state, double *unused, double *out_8843036227233356361) {
  H_29(state, unused, out_8843036227233356361);
}
void car_h_28(double *state, double *unused, double *out_2798394555448358256) {
  h_28(state, unused, out_2798394555448358256);
}
void car_H_28(double *state, double *unused, double *out_4521308829406664681) {
  H_28(state, unused, out_4521308829406664681);
}
void car_h_31(double *state, double *unused, double *out_3028176137196656356) {
  h_31(state, unused, out_3028176137196656356);
}
void car_H_31(double *state, double *unused, double *out_2207432122547146744) {
  H_31(state, unused, out_2207432122547146744);
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
