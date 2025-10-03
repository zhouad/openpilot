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
void err_fun(double *nom_x, double *delta_x, double *out_1019116046903339868) {
   out_1019116046903339868[0] = delta_x[0] + nom_x[0];
   out_1019116046903339868[1] = delta_x[1] + nom_x[1];
   out_1019116046903339868[2] = delta_x[2] + nom_x[2];
   out_1019116046903339868[3] = delta_x[3] + nom_x[3];
   out_1019116046903339868[4] = delta_x[4] + nom_x[4];
   out_1019116046903339868[5] = delta_x[5] + nom_x[5];
   out_1019116046903339868[6] = delta_x[6] + nom_x[6];
   out_1019116046903339868[7] = delta_x[7] + nom_x[7];
   out_1019116046903339868[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5227289756004260955) {
   out_5227289756004260955[0] = -nom_x[0] + true_x[0];
   out_5227289756004260955[1] = -nom_x[1] + true_x[1];
   out_5227289756004260955[2] = -nom_x[2] + true_x[2];
   out_5227289756004260955[3] = -nom_x[3] + true_x[3];
   out_5227289756004260955[4] = -nom_x[4] + true_x[4];
   out_5227289756004260955[5] = -nom_x[5] + true_x[5];
   out_5227289756004260955[6] = -nom_x[6] + true_x[6];
   out_5227289756004260955[7] = -nom_x[7] + true_x[7];
   out_5227289756004260955[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3146254179526665886) {
   out_3146254179526665886[0] = 1.0;
   out_3146254179526665886[1] = 0.0;
   out_3146254179526665886[2] = 0.0;
   out_3146254179526665886[3] = 0.0;
   out_3146254179526665886[4] = 0.0;
   out_3146254179526665886[5] = 0.0;
   out_3146254179526665886[6] = 0.0;
   out_3146254179526665886[7] = 0.0;
   out_3146254179526665886[8] = 0.0;
   out_3146254179526665886[9] = 0.0;
   out_3146254179526665886[10] = 1.0;
   out_3146254179526665886[11] = 0.0;
   out_3146254179526665886[12] = 0.0;
   out_3146254179526665886[13] = 0.0;
   out_3146254179526665886[14] = 0.0;
   out_3146254179526665886[15] = 0.0;
   out_3146254179526665886[16] = 0.0;
   out_3146254179526665886[17] = 0.0;
   out_3146254179526665886[18] = 0.0;
   out_3146254179526665886[19] = 0.0;
   out_3146254179526665886[20] = 1.0;
   out_3146254179526665886[21] = 0.0;
   out_3146254179526665886[22] = 0.0;
   out_3146254179526665886[23] = 0.0;
   out_3146254179526665886[24] = 0.0;
   out_3146254179526665886[25] = 0.0;
   out_3146254179526665886[26] = 0.0;
   out_3146254179526665886[27] = 0.0;
   out_3146254179526665886[28] = 0.0;
   out_3146254179526665886[29] = 0.0;
   out_3146254179526665886[30] = 1.0;
   out_3146254179526665886[31] = 0.0;
   out_3146254179526665886[32] = 0.0;
   out_3146254179526665886[33] = 0.0;
   out_3146254179526665886[34] = 0.0;
   out_3146254179526665886[35] = 0.0;
   out_3146254179526665886[36] = 0.0;
   out_3146254179526665886[37] = 0.0;
   out_3146254179526665886[38] = 0.0;
   out_3146254179526665886[39] = 0.0;
   out_3146254179526665886[40] = 1.0;
   out_3146254179526665886[41] = 0.0;
   out_3146254179526665886[42] = 0.0;
   out_3146254179526665886[43] = 0.0;
   out_3146254179526665886[44] = 0.0;
   out_3146254179526665886[45] = 0.0;
   out_3146254179526665886[46] = 0.0;
   out_3146254179526665886[47] = 0.0;
   out_3146254179526665886[48] = 0.0;
   out_3146254179526665886[49] = 0.0;
   out_3146254179526665886[50] = 1.0;
   out_3146254179526665886[51] = 0.0;
   out_3146254179526665886[52] = 0.0;
   out_3146254179526665886[53] = 0.0;
   out_3146254179526665886[54] = 0.0;
   out_3146254179526665886[55] = 0.0;
   out_3146254179526665886[56] = 0.0;
   out_3146254179526665886[57] = 0.0;
   out_3146254179526665886[58] = 0.0;
   out_3146254179526665886[59] = 0.0;
   out_3146254179526665886[60] = 1.0;
   out_3146254179526665886[61] = 0.0;
   out_3146254179526665886[62] = 0.0;
   out_3146254179526665886[63] = 0.0;
   out_3146254179526665886[64] = 0.0;
   out_3146254179526665886[65] = 0.0;
   out_3146254179526665886[66] = 0.0;
   out_3146254179526665886[67] = 0.0;
   out_3146254179526665886[68] = 0.0;
   out_3146254179526665886[69] = 0.0;
   out_3146254179526665886[70] = 1.0;
   out_3146254179526665886[71] = 0.0;
   out_3146254179526665886[72] = 0.0;
   out_3146254179526665886[73] = 0.0;
   out_3146254179526665886[74] = 0.0;
   out_3146254179526665886[75] = 0.0;
   out_3146254179526665886[76] = 0.0;
   out_3146254179526665886[77] = 0.0;
   out_3146254179526665886[78] = 0.0;
   out_3146254179526665886[79] = 0.0;
   out_3146254179526665886[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9033859238508349648) {
   out_9033859238508349648[0] = state[0];
   out_9033859238508349648[1] = state[1];
   out_9033859238508349648[2] = state[2];
   out_9033859238508349648[3] = state[3];
   out_9033859238508349648[4] = state[4];
   out_9033859238508349648[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9033859238508349648[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9033859238508349648[7] = state[7];
   out_9033859238508349648[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1223629188143286099) {
   out_1223629188143286099[0] = 1;
   out_1223629188143286099[1] = 0;
   out_1223629188143286099[2] = 0;
   out_1223629188143286099[3] = 0;
   out_1223629188143286099[4] = 0;
   out_1223629188143286099[5] = 0;
   out_1223629188143286099[6] = 0;
   out_1223629188143286099[7] = 0;
   out_1223629188143286099[8] = 0;
   out_1223629188143286099[9] = 0;
   out_1223629188143286099[10] = 1;
   out_1223629188143286099[11] = 0;
   out_1223629188143286099[12] = 0;
   out_1223629188143286099[13] = 0;
   out_1223629188143286099[14] = 0;
   out_1223629188143286099[15] = 0;
   out_1223629188143286099[16] = 0;
   out_1223629188143286099[17] = 0;
   out_1223629188143286099[18] = 0;
   out_1223629188143286099[19] = 0;
   out_1223629188143286099[20] = 1;
   out_1223629188143286099[21] = 0;
   out_1223629188143286099[22] = 0;
   out_1223629188143286099[23] = 0;
   out_1223629188143286099[24] = 0;
   out_1223629188143286099[25] = 0;
   out_1223629188143286099[26] = 0;
   out_1223629188143286099[27] = 0;
   out_1223629188143286099[28] = 0;
   out_1223629188143286099[29] = 0;
   out_1223629188143286099[30] = 1;
   out_1223629188143286099[31] = 0;
   out_1223629188143286099[32] = 0;
   out_1223629188143286099[33] = 0;
   out_1223629188143286099[34] = 0;
   out_1223629188143286099[35] = 0;
   out_1223629188143286099[36] = 0;
   out_1223629188143286099[37] = 0;
   out_1223629188143286099[38] = 0;
   out_1223629188143286099[39] = 0;
   out_1223629188143286099[40] = 1;
   out_1223629188143286099[41] = 0;
   out_1223629188143286099[42] = 0;
   out_1223629188143286099[43] = 0;
   out_1223629188143286099[44] = 0;
   out_1223629188143286099[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1223629188143286099[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1223629188143286099[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1223629188143286099[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1223629188143286099[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1223629188143286099[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1223629188143286099[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1223629188143286099[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1223629188143286099[53] = -9.8000000000000007*dt;
   out_1223629188143286099[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1223629188143286099[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1223629188143286099[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1223629188143286099[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1223629188143286099[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1223629188143286099[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1223629188143286099[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1223629188143286099[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1223629188143286099[62] = 0;
   out_1223629188143286099[63] = 0;
   out_1223629188143286099[64] = 0;
   out_1223629188143286099[65] = 0;
   out_1223629188143286099[66] = 0;
   out_1223629188143286099[67] = 0;
   out_1223629188143286099[68] = 0;
   out_1223629188143286099[69] = 0;
   out_1223629188143286099[70] = 1;
   out_1223629188143286099[71] = 0;
   out_1223629188143286099[72] = 0;
   out_1223629188143286099[73] = 0;
   out_1223629188143286099[74] = 0;
   out_1223629188143286099[75] = 0;
   out_1223629188143286099[76] = 0;
   out_1223629188143286099[77] = 0;
   out_1223629188143286099[78] = 0;
   out_1223629188143286099[79] = 0;
   out_1223629188143286099[80] = 1;
}
void h_25(double *state, double *unused, double *out_1581925918488859021) {
   out_1581925918488859021[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3350768780363364065) {
   out_3350768780363364065[0] = 0;
   out_3350768780363364065[1] = 0;
   out_3350768780363364065[2] = 0;
   out_3350768780363364065[3] = 0;
   out_3350768780363364065[4] = 0;
   out_3350768780363364065[5] = 0;
   out_3350768780363364065[6] = 1;
   out_3350768780363364065[7] = 0;
   out_3350768780363364065[8] = 0;
}
void h_24(double *state, double *unused, double *out_6550999019738618712) {
   out_6550999019738618712[0] = state[4];
   out_6550999019738618712[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1922725502549648529) {
   out_1922725502549648529[0] = 0;
   out_1922725502549648529[1] = 0;
   out_1922725502549648529[2] = 0;
   out_1922725502549648529[3] = 0;
   out_1922725502549648529[4] = 1;
   out_1922725502549648529[5] = 0;
   out_1922725502549648529[6] = 0;
   out_1922725502549648529[7] = 0;
   out_1922725502549648529[8] = 0;
   out_1922725502549648529[9] = 0;
   out_1922725502549648529[10] = 0;
   out_1922725502549648529[11] = 0;
   out_1922725502549648529[12] = 0;
   out_1922725502549648529[13] = 0;
   out_1922725502549648529[14] = 1;
   out_1922725502549648529[15] = 0;
   out_1922725502549648529[16] = 0;
   out_1922725502549648529[17] = 0;
}
void h_30(double *state, double *unused, double *out_5219375446742881371) {
   out_5219375446742881371[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7878465110490972263) {
   out_7878465110490972263[0] = 0;
   out_7878465110490972263[1] = 0;
   out_7878465110490972263[2] = 0;
   out_7878465110490972263[3] = 0;
   out_7878465110490972263[4] = 1;
   out_7878465110490972263[5] = 0;
   out_7878465110490972263[6] = 0;
   out_7878465110490972263[7] = 0;
   out_7878465110490972263[8] = 0;
}
void h_26(double *state, double *unused, double *out_2943846629129829237) {
   out_2943846629129829237[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7092272099237420289) {
   out_7092272099237420289[0] = 0;
   out_7092272099237420289[1] = 0;
   out_7092272099237420289[2] = 0;
   out_7092272099237420289[3] = 0;
   out_7092272099237420289[4] = 0;
   out_7092272099237420289[5] = 0;
   out_7092272099237420289[6] = 0;
   out_7092272099237420289[7] = 1;
   out_7092272099237420289[8] = 0;
}
void h_27(double *state, double *unused, double *out_5420836785304206758) {
   out_5420836785304206758[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5654871039307029046) {
   out_5654871039307029046[0] = 0;
   out_5654871039307029046[1] = 0;
   out_5654871039307029046[2] = 0;
   out_5654871039307029046[3] = 1;
   out_5654871039307029046[4] = 0;
   out_5654871039307029046[5] = 0;
   out_5654871039307029046[6] = 0;
   out_5654871039307029046[7] = 0;
   out_5654871039307029046[8] = 0;
}
void h_29(double *state, double *unused, double *out_5822691331419358888) {
   out_5822691331419358888[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7368233766176580079) {
   out_7368233766176580079[0] = 0;
   out_7368233766176580079[1] = 1;
   out_7368233766176580079[2] = 0;
   out_7368233766176580079[3] = 0;
   out_7368233766176580079[4] = 0;
   out_7368233766176580079[5] = 0;
   out_7368233766176580079[6] = 0;
   out_7368233766176580079[7] = 0;
   out_7368233766176580079[8] = 0;
}
void h_28(double *state, double *unused, double *out_8457622836748539443) {
   out_8457622836748539443[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5996111290463440963) {
   out_5996111290463440963[0] = 1;
   out_5996111290463440963[1] = 0;
   out_5996111290463440963[2] = 0;
   out_5996111290463440963[3] = 0;
   out_5996111290463440963[4] = 0;
   out_5996111290463440963[5] = 0;
   out_5996111290463440963[6] = 0;
   out_5996111290463440963[7] = 0;
   out_5996111290463440963[8] = 0;
}
void h_31(double *state, double *unused, double *out_7749039958459993324) {
   out_7749039958459993324[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7718480201470771765) {
   out_7718480201470771765[0] = 0;
   out_7718480201470771765[1] = 0;
   out_7718480201470771765[2] = 0;
   out_7718480201470771765[3] = 0;
   out_7718480201470771765[4] = 0;
   out_7718480201470771765[5] = 0;
   out_7718480201470771765[6] = 0;
   out_7718480201470771765[7] = 0;
   out_7718480201470771765[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1019116046903339868) {
  err_fun(nom_x, delta_x, out_1019116046903339868);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5227289756004260955) {
  inv_err_fun(nom_x, true_x, out_5227289756004260955);
}
void car_H_mod_fun(double *state, double *out_3146254179526665886) {
  H_mod_fun(state, out_3146254179526665886);
}
void car_f_fun(double *state, double dt, double *out_9033859238508349648) {
  f_fun(state,  dt, out_9033859238508349648);
}
void car_F_fun(double *state, double dt, double *out_1223629188143286099) {
  F_fun(state,  dt, out_1223629188143286099);
}
void car_h_25(double *state, double *unused, double *out_1581925918488859021) {
  h_25(state, unused, out_1581925918488859021);
}
void car_H_25(double *state, double *unused, double *out_3350768780363364065) {
  H_25(state, unused, out_3350768780363364065);
}
void car_h_24(double *state, double *unused, double *out_6550999019738618712) {
  h_24(state, unused, out_6550999019738618712);
}
void car_H_24(double *state, double *unused, double *out_1922725502549648529) {
  H_24(state, unused, out_1922725502549648529);
}
void car_h_30(double *state, double *unused, double *out_5219375446742881371) {
  h_30(state, unused, out_5219375446742881371);
}
void car_H_30(double *state, double *unused, double *out_7878465110490972263) {
  H_30(state, unused, out_7878465110490972263);
}
void car_h_26(double *state, double *unused, double *out_2943846629129829237) {
  h_26(state, unused, out_2943846629129829237);
}
void car_H_26(double *state, double *unused, double *out_7092272099237420289) {
  H_26(state, unused, out_7092272099237420289);
}
void car_h_27(double *state, double *unused, double *out_5420836785304206758) {
  h_27(state, unused, out_5420836785304206758);
}
void car_H_27(double *state, double *unused, double *out_5654871039307029046) {
  H_27(state, unused, out_5654871039307029046);
}
void car_h_29(double *state, double *unused, double *out_5822691331419358888) {
  h_29(state, unused, out_5822691331419358888);
}
void car_H_29(double *state, double *unused, double *out_7368233766176580079) {
  H_29(state, unused, out_7368233766176580079);
}
void car_h_28(double *state, double *unused, double *out_8457622836748539443) {
  h_28(state, unused, out_8457622836748539443);
}
void car_H_28(double *state, double *unused, double *out_5996111290463440963) {
  H_28(state, unused, out_5996111290463440963);
}
void car_h_31(double *state, double *unused, double *out_7749039958459993324) {
  h_31(state, unused, out_7749039958459993324);
}
void car_H_31(double *state, double *unused, double *out_7718480201470771765) {
  H_31(state, unused, out_7718480201470771765);
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
