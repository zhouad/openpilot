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
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7336400755353116814) {
   out_7336400755353116814[0] = delta_x[0] + nom_x[0];
   out_7336400755353116814[1] = delta_x[1] + nom_x[1];
   out_7336400755353116814[2] = delta_x[2] + nom_x[2];
   out_7336400755353116814[3] = delta_x[3] + nom_x[3];
   out_7336400755353116814[4] = delta_x[4] + nom_x[4];
   out_7336400755353116814[5] = delta_x[5] + nom_x[5];
   out_7336400755353116814[6] = delta_x[6] + nom_x[6];
   out_7336400755353116814[7] = delta_x[7] + nom_x[7];
   out_7336400755353116814[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_563874706792395429) {
   out_563874706792395429[0] = -nom_x[0] + true_x[0];
   out_563874706792395429[1] = -nom_x[1] + true_x[1];
   out_563874706792395429[2] = -nom_x[2] + true_x[2];
   out_563874706792395429[3] = -nom_x[3] + true_x[3];
   out_563874706792395429[4] = -nom_x[4] + true_x[4];
   out_563874706792395429[5] = -nom_x[5] + true_x[5];
   out_563874706792395429[6] = -nom_x[6] + true_x[6];
   out_563874706792395429[7] = -nom_x[7] + true_x[7];
   out_563874706792395429[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5735286983792797603) {
   out_5735286983792797603[0] = 1.0;
   out_5735286983792797603[1] = 0.0;
   out_5735286983792797603[2] = 0.0;
   out_5735286983792797603[3] = 0.0;
   out_5735286983792797603[4] = 0.0;
   out_5735286983792797603[5] = 0.0;
   out_5735286983792797603[6] = 0.0;
   out_5735286983792797603[7] = 0.0;
   out_5735286983792797603[8] = 0.0;
   out_5735286983792797603[9] = 0.0;
   out_5735286983792797603[10] = 1.0;
   out_5735286983792797603[11] = 0.0;
   out_5735286983792797603[12] = 0.0;
   out_5735286983792797603[13] = 0.0;
   out_5735286983792797603[14] = 0.0;
   out_5735286983792797603[15] = 0.0;
   out_5735286983792797603[16] = 0.0;
   out_5735286983792797603[17] = 0.0;
   out_5735286983792797603[18] = 0.0;
   out_5735286983792797603[19] = 0.0;
   out_5735286983792797603[20] = 1.0;
   out_5735286983792797603[21] = 0.0;
   out_5735286983792797603[22] = 0.0;
   out_5735286983792797603[23] = 0.0;
   out_5735286983792797603[24] = 0.0;
   out_5735286983792797603[25] = 0.0;
   out_5735286983792797603[26] = 0.0;
   out_5735286983792797603[27] = 0.0;
   out_5735286983792797603[28] = 0.0;
   out_5735286983792797603[29] = 0.0;
   out_5735286983792797603[30] = 1.0;
   out_5735286983792797603[31] = 0.0;
   out_5735286983792797603[32] = 0.0;
   out_5735286983792797603[33] = 0.0;
   out_5735286983792797603[34] = 0.0;
   out_5735286983792797603[35] = 0.0;
   out_5735286983792797603[36] = 0.0;
   out_5735286983792797603[37] = 0.0;
   out_5735286983792797603[38] = 0.0;
   out_5735286983792797603[39] = 0.0;
   out_5735286983792797603[40] = 1.0;
   out_5735286983792797603[41] = 0.0;
   out_5735286983792797603[42] = 0.0;
   out_5735286983792797603[43] = 0.0;
   out_5735286983792797603[44] = 0.0;
   out_5735286983792797603[45] = 0.0;
   out_5735286983792797603[46] = 0.0;
   out_5735286983792797603[47] = 0.0;
   out_5735286983792797603[48] = 0.0;
   out_5735286983792797603[49] = 0.0;
   out_5735286983792797603[50] = 1.0;
   out_5735286983792797603[51] = 0.0;
   out_5735286983792797603[52] = 0.0;
   out_5735286983792797603[53] = 0.0;
   out_5735286983792797603[54] = 0.0;
   out_5735286983792797603[55] = 0.0;
   out_5735286983792797603[56] = 0.0;
   out_5735286983792797603[57] = 0.0;
   out_5735286983792797603[58] = 0.0;
   out_5735286983792797603[59] = 0.0;
   out_5735286983792797603[60] = 1.0;
   out_5735286983792797603[61] = 0.0;
   out_5735286983792797603[62] = 0.0;
   out_5735286983792797603[63] = 0.0;
   out_5735286983792797603[64] = 0.0;
   out_5735286983792797603[65] = 0.0;
   out_5735286983792797603[66] = 0.0;
   out_5735286983792797603[67] = 0.0;
   out_5735286983792797603[68] = 0.0;
   out_5735286983792797603[69] = 0.0;
   out_5735286983792797603[70] = 1.0;
   out_5735286983792797603[71] = 0.0;
   out_5735286983792797603[72] = 0.0;
   out_5735286983792797603[73] = 0.0;
   out_5735286983792797603[74] = 0.0;
   out_5735286983792797603[75] = 0.0;
   out_5735286983792797603[76] = 0.0;
   out_5735286983792797603[77] = 0.0;
   out_5735286983792797603[78] = 0.0;
   out_5735286983792797603[79] = 0.0;
   out_5735286983792797603[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_346464760395709430) {
   out_346464760395709430[0] = state[0];
   out_346464760395709430[1] = state[1];
   out_346464760395709430[2] = state[2];
   out_346464760395709430[3] = state[3];
   out_346464760395709430[4] = state[4];
   out_346464760395709430[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_346464760395709430[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_346464760395709430[7] = state[7];
   out_346464760395709430[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8533956319147983344) {
   out_8533956319147983344[0] = 1;
   out_8533956319147983344[1] = 0;
   out_8533956319147983344[2] = 0;
   out_8533956319147983344[3] = 0;
   out_8533956319147983344[4] = 0;
   out_8533956319147983344[5] = 0;
   out_8533956319147983344[6] = 0;
   out_8533956319147983344[7] = 0;
   out_8533956319147983344[8] = 0;
   out_8533956319147983344[9] = 0;
   out_8533956319147983344[10] = 1;
   out_8533956319147983344[11] = 0;
   out_8533956319147983344[12] = 0;
   out_8533956319147983344[13] = 0;
   out_8533956319147983344[14] = 0;
   out_8533956319147983344[15] = 0;
   out_8533956319147983344[16] = 0;
   out_8533956319147983344[17] = 0;
   out_8533956319147983344[18] = 0;
   out_8533956319147983344[19] = 0;
   out_8533956319147983344[20] = 1;
   out_8533956319147983344[21] = 0;
   out_8533956319147983344[22] = 0;
   out_8533956319147983344[23] = 0;
   out_8533956319147983344[24] = 0;
   out_8533956319147983344[25] = 0;
   out_8533956319147983344[26] = 0;
   out_8533956319147983344[27] = 0;
   out_8533956319147983344[28] = 0;
   out_8533956319147983344[29] = 0;
   out_8533956319147983344[30] = 1;
   out_8533956319147983344[31] = 0;
   out_8533956319147983344[32] = 0;
   out_8533956319147983344[33] = 0;
   out_8533956319147983344[34] = 0;
   out_8533956319147983344[35] = 0;
   out_8533956319147983344[36] = 0;
   out_8533956319147983344[37] = 0;
   out_8533956319147983344[38] = 0;
   out_8533956319147983344[39] = 0;
   out_8533956319147983344[40] = 1;
   out_8533956319147983344[41] = 0;
   out_8533956319147983344[42] = 0;
   out_8533956319147983344[43] = 0;
   out_8533956319147983344[44] = 0;
   out_8533956319147983344[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8533956319147983344[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8533956319147983344[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8533956319147983344[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8533956319147983344[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8533956319147983344[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8533956319147983344[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8533956319147983344[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8533956319147983344[53] = -9.8000000000000007*dt;
   out_8533956319147983344[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8533956319147983344[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8533956319147983344[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8533956319147983344[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8533956319147983344[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8533956319147983344[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8533956319147983344[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8533956319147983344[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8533956319147983344[62] = 0;
   out_8533956319147983344[63] = 0;
   out_8533956319147983344[64] = 0;
   out_8533956319147983344[65] = 0;
   out_8533956319147983344[66] = 0;
   out_8533956319147983344[67] = 0;
   out_8533956319147983344[68] = 0;
   out_8533956319147983344[69] = 0;
   out_8533956319147983344[70] = 1;
   out_8533956319147983344[71] = 0;
   out_8533956319147983344[72] = 0;
   out_8533956319147983344[73] = 0;
   out_8533956319147983344[74] = 0;
   out_8533956319147983344[75] = 0;
   out_8533956319147983344[76] = 0;
   out_8533956319147983344[77] = 0;
   out_8533956319147983344[78] = 0;
   out_8533956319147983344[79] = 0;
   out_8533956319147983344[80] = 1;
}
void h_25(double *state, double *unused, double *out_8865985810845833767) {
   out_8865985810845833767[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3457901242119439634) {
   out_3457901242119439634[0] = 0;
   out_3457901242119439634[1] = 0;
   out_3457901242119439634[2] = 0;
   out_3457901242119439634[3] = 0;
   out_3457901242119439634[4] = 0;
   out_3457901242119439634[5] = 0;
   out_3457901242119439634[6] = 1;
   out_3457901242119439634[7] = 0;
   out_3457901242119439634[8] = 0;
}
void h_24(double *state, double *unused, double *out_8805399835663073913) {
   out_8805399835663073913[0] = state[4];
   out_8805399835663073913[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5630550841124939200) {
   out_5630550841124939200[0] = 0;
   out_5630550841124939200[1] = 0;
   out_5630550841124939200[2] = 0;
   out_5630550841124939200[3] = 0;
   out_5630550841124939200[4] = 1;
   out_5630550841124939200[5] = 0;
   out_5630550841124939200[6] = 0;
   out_5630550841124939200[7] = 0;
   out_5630550841124939200[8] = 0;
   out_5630550841124939200[9] = 0;
   out_5630550841124939200[10] = 0;
   out_5630550841124939200[11] = 0;
   out_5630550841124939200[12] = 0;
   out_5630550841124939200[13] = 0;
   out_5630550841124939200[14] = 1;
   out_5630550841124939200[15] = 0;
   out_5630550841124939200[16] = 0;
   out_5630550841124939200[17] = 0;
}
void h_30(double *state, double *unused, double *out_226108334127291883) {
   out_226108334127291883[0] = state[4];
}
void H_30(double *state, double *unused, double *out_939568283612191007) {
   out_939568283612191007[0] = 0;
   out_939568283612191007[1] = 0;
   out_939568283612191007[2] = 0;
   out_939568283612191007[3] = 0;
   out_939568283612191007[4] = 1;
   out_939568283612191007[5] = 0;
   out_939568283612191007[6] = 0;
   out_939568283612191007[7] = 0;
   out_939568283612191007[8] = 0;
}
void h_26(double *state, double *unused, double *out_4775564933533553762) {
   out_4775564933533553762[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7199404560993495858) {
   out_7199404560993495858[0] = 0;
   out_7199404560993495858[1] = 0;
   out_7199404560993495858[2] = 0;
   out_7199404560993495858[3] = 0;
   out_7199404560993495858[4] = 0;
   out_7199404560993495858[5] = 0;
   out_7199404560993495858[6] = 0;
   out_7199404560993495858[7] = 1;
   out_7199404560993495858[8] = 0;
}
void h_27(double *state, double *unused, double *out_6053433707575980384) {
   out_6053433707575980384[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1284025787571752210) {
   out_1284025787571752210[0] = 0;
   out_1284025787571752210[1] = 0;
   out_1284025787571752210[2] = 0;
   out_1284025787571752210[3] = 1;
   out_1284025787571752210[4] = 0;
   out_1284025787571752210[5] = 0;
   out_1284025787571752210[6] = 0;
   out_1284025787571752210[7] = 0;
   out_1284025787571752210[8] = 0;
}
void h_29(double *state, double *unused, double *out_6029716387831755371) {
   out_6029716387831755371[0] = state[1];
}
void H_29(double *state, double *unused, double *out_429336939297798823) {
   out_429336939297798823[0] = 0;
   out_429336939297798823[1] = 1;
   out_429336939297798823[2] = 0;
   out_429336939297798823[3] = 0;
   out_429336939297798823[4] = 0;
   out_429336939297798823[5] = 0;
   out_429336939297798823[6] = 0;
   out_429336939297798823[7] = 0;
   out_429336939297798823[8] = 0;
}
void h_28(double *state, double *unused, double *out_7391637098472725587) {
   out_7391637098472725587[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5511735956367329397) {
   out_5511735956367329397[0] = 1;
   out_5511735956367329397[1] = 0;
   out_5511735956367329397[2] = 0;
   out_5511735956367329397[3] = 0;
   out_5511735956367329397[4] = 0;
   out_5511735956367329397[5] = 0;
   out_5511735956367329397[6] = 0;
   out_5511735956367329397[7] = 0;
   out_5511735956367329397[8] = 0;
}
void h_31(double *state, double *unused, double *out_8590791748561327878) {
   out_8590791748561327878[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3427255280242479206) {
   out_3427255280242479206[0] = 0;
   out_3427255280242479206[1] = 0;
   out_3427255280242479206[2] = 0;
   out_3427255280242479206[3] = 0;
   out_3427255280242479206[4] = 0;
   out_3427255280242479206[5] = 0;
   out_3427255280242479206[6] = 0;
   out_3427255280242479206[7] = 0;
   out_3427255280242479206[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7336400755353116814) {
  err_fun(nom_x, delta_x, out_7336400755353116814);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_563874706792395429) {
  inv_err_fun(nom_x, true_x, out_563874706792395429);
}
void car_H_mod_fun(double *state, double *out_5735286983792797603) {
  H_mod_fun(state, out_5735286983792797603);
}
void car_f_fun(double *state, double dt, double *out_346464760395709430) {
  f_fun(state,  dt, out_346464760395709430);
}
void car_F_fun(double *state, double dt, double *out_8533956319147983344) {
  F_fun(state,  dt, out_8533956319147983344);
}
void car_h_25(double *state, double *unused, double *out_8865985810845833767) {
  h_25(state, unused, out_8865985810845833767);
}
void car_H_25(double *state, double *unused, double *out_3457901242119439634) {
  H_25(state, unused, out_3457901242119439634);
}
void car_h_24(double *state, double *unused, double *out_8805399835663073913) {
  h_24(state, unused, out_8805399835663073913);
}
void car_H_24(double *state, double *unused, double *out_5630550841124939200) {
  H_24(state, unused, out_5630550841124939200);
}
void car_h_30(double *state, double *unused, double *out_226108334127291883) {
  h_30(state, unused, out_226108334127291883);
}
void car_H_30(double *state, double *unused, double *out_939568283612191007) {
  H_30(state, unused, out_939568283612191007);
}
void car_h_26(double *state, double *unused, double *out_4775564933533553762) {
  h_26(state, unused, out_4775564933533553762);
}
void car_H_26(double *state, double *unused, double *out_7199404560993495858) {
  H_26(state, unused, out_7199404560993495858);
}
void car_h_27(double *state, double *unused, double *out_6053433707575980384) {
  h_27(state, unused, out_6053433707575980384);
}
void car_H_27(double *state, double *unused, double *out_1284025787571752210) {
  H_27(state, unused, out_1284025787571752210);
}
void car_h_29(double *state, double *unused, double *out_6029716387831755371) {
  h_29(state, unused, out_6029716387831755371);
}
void car_H_29(double *state, double *unused, double *out_429336939297798823) {
  H_29(state, unused, out_429336939297798823);
}
void car_h_28(double *state, double *unused, double *out_7391637098472725587) {
  h_28(state, unused, out_7391637098472725587);
}
void car_H_28(double *state, double *unused, double *out_5511735956367329397) {
  H_28(state, unused, out_5511735956367329397);
}
void car_h_31(double *state, double *unused, double *out_8590791748561327878) {
  h_31(state, unused, out_8590791748561327878);
}
void car_H_31(double *state, double *unused, double *out_3427255280242479206) {
  H_31(state, unused, out_3427255280242479206);
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
