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
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_911903194658884293) {
   out_911903194658884293[0] = delta_x[0] + nom_x[0];
   out_911903194658884293[1] = delta_x[1] + nom_x[1];
   out_911903194658884293[2] = delta_x[2] + nom_x[2];
   out_911903194658884293[3] = delta_x[3] + nom_x[3];
   out_911903194658884293[4] = delta_x[4] + nom_x[4];
   out_911903194658884293[5] = delta_x[5] + nom_x[5];
   out_911903194658884293[6] = delta_x[6] + nom_x[6];
   out_911903194658884293[7] = delta_x[7] + nom_x[7];
   out_911903194658884293[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5779663419065305557) {
   out_5779663419065305557[0] = -nom_x[0] + true_x[0];
   out_5779663419065305557[1] = -nom_x[1] + true_x[1];
   out_5779663419065305557[2] = -nom_x[2] + true_x[2];
   out_5779663419065305557[3] = -nom_x[3] + true_x[3];
   out_5779663419065305557[4] = -nom_x[4] + true_x[4];
   out_5779663419065305557[5] = -nom_x[5] + true_x[5];
   out_5779663419065305557[6] = -nom_x[6] + true_x[6];
   out_5779663419065305557[7] = -nom_x[7] + true_x[7];
   out_5779663419065305557[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3279590390747204942) {
   out_3279590390747204942[0] = 1.0;
   out_3279590390747204942[1] = 0;
   out_3279590390747204942[2] = 0;
   out_3279590390747204942[3] = 0;
   out_3279590390747204942[4] = 0;
   out_3279590390747204942[5] = 0;
   out_3279590390747204942[6] = 0;
   out_3279590390747204942[7] = 0;
   out_3279590390747204942[8] = 0;
   out_3279590390747204942[9] = 0;
   out_3279590390747204942[10] = 1.0;
   out_3279590390747204942[11] = 0;
   out_3279590390747204942[12] = 0;
   out_3279590390747204942[13] = 0;
   out_3279590390747204942[14] = 0;
   out_3279590390747204942[15] = 0;
   out_3279590390747204942[16] = 0;
   out_3279590390747204942[17] = 0;
   out_3279590390747204942[18] = 0;
   out_3279590390747204942[19] = 0;
   out_3279590390747204942[20] = 1.0;
   out_3279590390747204942[21] = 0;
   out_3279590390747204942[22] = 0;
   out_3279590390747204942[23] = 0;
   out_3279590390747204942[24] = 0;
   out_3279590390747204942[25] = 0;
   out_3279590390747204942[26] = 0;
   out_3279590390747204942[27] = 0;
   out_3279590390747204942[28] = 0;
   out_3279590390747204942[29] = 0;
   out_3279590390747204942[30] = 1.0;
   out_3279590390747204942[31] = 0;
   out_3279590390747204942[32] = 0;
   out_3279590390747204942[33] = 0;
   out_3279590390747204942[34] = 0;
   out_3279590390747204942[35] = 0;
   out_3279590390747204942[36] = 0;
   out_3279590390747204942[37] = 0;
   out_3279590390747204942[38] = 0;
   out_3279590390747204942[39] = 0;
   out_3279590390747204942[40] = 1.0;
   out_3279590390747204942[41] = 0;
   out_3279590390747204942[42] = 0;
   out_3279590390747204942[43] = 0;
   out_3279590390747204942[44] = 0;
   out_3279590390747204942[45] = 0;
   out_3279590390747204942[46] = 0;
   out_3279590390747204942[47] = 0;
   out_3279590390747204942[48] = 0;
   out_3279590390747204942[49] = 0;
   out_3279590390747204942[50] = 1.0;
   out_3279590390747204942[51] = 0;
   out_3279590390747204942[52] = 0;
   out_3279590390747204942[53] = 0;
   out_3279590390747204942[54] = 0;
   out_3279590390747204942[55] = 0;
   out_3279590390747204942[56] = 0;
   out_3279590390747204942[57] = 0;
   out_3279590390747204942[58] = 0;
   out_3279590390747204942[59] = 0;
   out_3279590390747204942[60] = 1.0;
   out_3279590390747204942[61] = 0;
   out_3279590390747204942[62] = 0;
   out_3279590390747204942[63] = 0;
   out_3279590390747204942[64] = 0;
   out_3279590390747204942[65] = 0;
   out_3279590390747204942[66] = 0;
   out_3279590390747204942[67] = 0;
   out_3279590390747204942[68] = 0;
   out_3279590390747204942[69] = 0;
   out_3279590390747204942[70] = 1.0;
   out_3279590390747204942[71] = 0;
   out_3279590390747204942[72] = 0;
   out_3279590390747204942[73] = 0;
   out_3279590390747204942[74] = 0;
   out_3279590390747204942[75] = 0;
   out_3279590390747204942[76] = 0;
   out_3279590390747204942[77] = 0;
   out_3279590390747204942[78] = 0;
   out_3279590390747204942[79] = 0;
   out_3279590390747204942[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4327379576481858684) {
   out_4327379576481858684[0] = state[0];
   out_4327379576481858684[1] = state[1];
   out_4327379576481858684[2] = state[2];
   out_4327379576481858684[3] = state[3];
   out_4327379576481858684[4] = state[4];
   out_4327379576481858684[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4327379576481858684[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4327379576481858684[7] = state[7];
   out_4327379576481858684[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3077082935718334244) {
   out_3077082935718334244[0] = 1;
   out_3077082935718334244[1] = 0;
   out_3077082935718334244[2] = 0;
   out_3077082935718334244[3] = 0;
   out_3077082935718334244[4] = 0;
   out_3077082935718334244[5] = 0;
   out_3077082935718334244[6] = 0;
   out_3077082935718334244[7] = 0;
   out_3077082935718334244[8] = 0;
   out_3077082935718334244[9] = 0;
   out_3077082935718334244[10] = 1;
   out_3077082935718334244[11] = 0;
   out_3077082935718334244[12] = 0;
   out_3077082935718334244[13] = 0;
   out_3077082935718334244[14] = 0;
   out_3077082935718334244[15] = 0;
   out_3077082935718334244[16] = 0;
   out_3077082935718334244[17] = 0;
   out_3077082935718334244[18] = 0;
   out_3077082935718334244[19] = 0;
   out_3077082935718334244[20] = 1;
   out_3077082935718334244[21] = 0;
   out_3077082935718334244[22] = 0;
   out_3077082935718334244[23] = 0;
   out_3077082935718334244[24] = 0;
   out_3077082935718334244[25] = 0;
   out_3077082935718334244[26] = 0;
   out_3077082935718334244[27] = 0;
   out_3077082935718334244[28] = 0;
   out_3077082935718334244[29] = 0;
   out_3077082935718334244[30] = 1;
   out_3077082935718334244[31] = 0;
   out_3077082935718334244[32] = 0;
   out_3077082935718334244[33] = 0;
   out_3077082935718334244[34] = 0;
   out_3077082935718334244[35] = 0;
   out_3077082935718334244[36] = 0;
   out_3077082935718334244[37] = 0;
   out_3077082935718334244[38] = 0;
   out_3077082935718334244[39] = 0;
   out_3077082935718334244[40] = 1;
   out_3077082935718334244[41] = 0;
   out_3077082935718334244[42] = 0;
   out_3077082935718334244[43] = 0;
   out_3077082935718334244[44] = 0;
   out_3077082935718334244[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3077082935718334244[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3077082935718334244[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3077082935718334244[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3077082935718334244[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3077082935718334244[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3077082935718334244[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3077082935718334244[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3077082935718334244[53] = -9.8000000000000007*dt;
   out_3077082935718334244[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3077082935718334244[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3077082935718334244[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3077082935718334244[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3077082935718334244[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3077082935718334244[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3077082935718334244[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3077082935718334244[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3077082935718334244[62] = 0;
   out_3077082935718334244[63] = 0;
   out_3077082935718334244[64] = 0;
   out_3077082935718334244[65] = 0;
   out_3077082935718334244[66] = 0;
   out_3077082935718334244[67] = 0;
   out_3077082935718334244[68] = 0;
   out_3077082935718334244[69] = 0;
   out_3077082935718334244[70] = 1;
   out_3077082935718334244[71] = 0;
   out_3077082935718334244[72] = 0;
   out_3077082935718334244[73] = 0;
   out_3077082935718334244[74] = 0;
   out_3077082935718334244[75] = 0;
   out_3077082935718334244[76] = 0;
   out_3077082935718334244[77] = 0;
   out_3077082935718334244[78] = 0;
   out_3077082935718334244[79] = 0;
   out_3077082935718334244[80] = 1;
}
void h_25(double *state, double *unused, double *out_2385054709657547755) {
   out_2385054709657547755[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1292631630641773223) {
   out_1292631630641773223[0] = 0;
   out_1292631630641773223[1] = 0;
   out_1292631630641773223[2] = 0;
   out_1292631630641773223[3] = 0;
   out_1292631630641773223[4] = 0;
   out_1292631630641773223[5] = 0;
   out_1292631630641773223[6] = 1;
   out_1292631630641773223[7] = 0;
   out_1292631630641773223[8] = 0;
}
void h_24(double *state, double *unused, double *out_5916792586470950082) {
   out_5916792586470950082[0] = state[4];
   out_5916792586470950082[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3465281229647272789) {
   out_3465281229647272789[0] = 0;
   out_3465281229647272789[1] = 0;
   out_3465281229647272789[2] = 0;
   out_3465281229647272789[3] = 0;
   out_3465281229647272789[4] = 1;
   out_3465281229647272789[5] = 0;
   out_3465281229647272789[6] = 0;
   out_3465281229647272789[7] = 0;
   out_3465281229647272789[8] = 0;
   out_3465281229647272789[9] = 0;
   out_3465281229647272789[10] = 0;
   out_3465281229647272789[11] = 0;
   out_3465281229647272789[12] = 0;
   out_3465281229647272789[13] = 0;
   out_3465281229647272789[14] = 1;
   out_3465281229647272789[15] = 0;
   out_3465281229647272789[16] = 0;
   out_3465281229647272789[17] = 0;
}
void h_30(double *state, double *unused, double *out_562671280697937206) {
   out_562671280697937206[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5624058710849843532) {
   out_5624058710849843532[0] = 0;
   out_5624058710849843532[1] = 0;
   out_5624058710849843532[2] = 0;
   out_5624058710849843532[3] = 0;
   out_5624058710849843532[4] = 1;
   out_5624058710849843532[5] = 0;
   out_5624058710849843532[6] = 0;
   out_5624058710849843532[7] = 0;
   out_5624058710849843532[8] = 0;
}
void h_26(double *state, double *unused, double *out_8902103621004773645) {
   out_8902103621004773645[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5034134949515829447) {
   out_5034134949515829447[0] = 0;
   out_5034134949515829447[1] = 0;
   out_5034134949515829447[2] = 0;
   out_5034134949515829447[3] = 0;
   out_5034134949515829447[4] = 0;
   out_5034134949515829447[5] = 0;
   out_5034134949515829447[6] = 0;
   out_5034134949515829447[7] = 1;
   out_5034134949515829447[8] = 0;
}
void h_27(double *state, double *unused, double *out_6411254754608449385) {
   out_6411254754608449385[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3449295399049418621) {
   out_3449295399049418621[0] = 0;
   out_3449295399049418621[1] = 0;
   out_3449295399049418621[2] = 0;
   out_3449295399049418621[3] = 1;
   out_3449295399049418621[4] = 0;
   out_3449295399049418621[5] = 0;
   out_3449295399049418621[6] = 0;
   out_3449295399049418621[7] = 0;
   out_3449295399049418621[8] = 0;
}
void h_29(double *state, double *unused, double *out_5564344548358782851) {
   out_5564344548358782851[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1735932672179867588) {
   out_1735932672179867588[0] = 0;
   out_1735932672179867588[1] = 1;
   out_1735932672179867588[2] = 0;
   out_1735932672179867588[3] = 0;
   out_1735932672179867588[4] = 0;
   out_1735932672179867588[5] = 0;
   out_1735932672179867588[6] = 0;
   out_1735932672179867588[7] = 0;
   out_1735932672179867588[8] = 0;
}
void h_28(double *state, double *unused, double *out_3598702651338596002) {
   out_3598702651338596002[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3346466344889662986) {
   out_3346466344889662986[0] = 1;
   out_3346466344889662986[1] = 0;
   out_3346466344889662986[2] = 0;
   out_3346466344889662986[3] = 0;
   out_3346466344889662986[4] = 0;
   out_3346466344889662986[5] = 0;
   out_3346466344889662986[6] = 0;
   out_3346466344889662986[7] = 0;
   out_3346466344889662986[8] = 0;
}
void h_31(double *state, double *unused, double *out_8180416713297954676) {
   out_8180416713297954676[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1261985668764812795) {
   out_1261985668764812795[0] = 0;
   out_1261985668764812795[1] = 0;
   out_1261985668764812795[2] = 0;
   out_1261985668764812795[3] = 0;
   out_1261985668764812795[4] = 0;
   out_1261985668764812795[5] = 0;
   out_1261985668764812795[6] = 0;
   out_1261985668764812795[7] = 0;
   out_1261985668764812795[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_911903194658884293) {
  err_fun(nom_x, delta_x, out_911903194658884293);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5779663419065305557) {
  inv_err_fun(nom_x, true_x, out_5779663419065305557);
}
void car_H_mod_fun(double *state, double *out_3279590390747204942) {
  H_mod_fun(state, out_3279590390747204942);
}
void car_f_fun(double *state, double dt, double *out_4327379576481858684) {
  f_fun(state,  dt, out_4327379576481858684);
}
void car_F_fun(double *state, double dt, double *out_3077082935718334244) {
  F_fun(state,  dt, out_3077082935718334244);
}
void car_h_25(double *state, double *unused, double *out_2385054709657547755) {
  h_25(state, unused, out_2385054709657547755);
}
void car_H_25(double *state, double *unused, double *out_1292631630641773223) {
  H_25(state, unused, out_1292631630641773223);
}
void car_h_24(double *state, double *unused, double *out_5916792586470950082) {
  h_24(state, unused, out_5916792586470950082);
}
void car_H_24(double *state, double *unused, double *out_3465281229647272789) {
  H_24(state, unused, out_3465281229647272789);
}
void car_h_30(double *state, double *unused, double *out_562671280697937206) {
  h_30(state, unused, out_562671280697937206);
}
void car_H_30(double *state, double *unused, double *out_5624058710849843532) {
  H_30(state, unused, out_5624058710849843532);
}
void car_h_26(double *state, double *unused, double *out_8902103621004773645) {
  h_26(state, unused, out_8902103621004773645);
}
void car_H_26(double *state, double *unused, double *out_5034134949515829447) {
  H_26(state, unused, out_5034134949515829447);
}
void car_h_27(double *state, double *unused, double *out_6411254754608449385) {
  h_27(state, unused, out_6411254754608449385);
}
void car_H_27(double *state, double *unused, double *out_3449295399049418621) {
  H_27(state, unused, out_3449295399049418621);
}
void car_h_29(double *state, double *unused, double *out_5564344548358782851) {
  h_29(state, unused, out_5564344548358782851);
}
void car_H_29(double *state, double *unused, double *out_1735932672179867588) {
  H_29(state, unused, out_1735932672179867588);
}
void car_h_28(double *state, double *unused, double *out_3598702651338596002) {
  h_28(state, unused, out_3598702651338596002);
}
void car_H_28(double *state, double *unused, double *out_3346466344889662986) {
  H_28(state, unused, out_3346466344889662986);
}
void car_h_31(double *state, double *unused, double *out_8180416713297954676) {
  h_31(state, unused, out_8180416713297954676);
}
void car_H_31(double *state, double *unused, double *out_1261985668764812795) {
  H_31(state, unused, out_1261985668764812795);
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
