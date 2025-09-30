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
void err_fun(double *nom_x, double *delta_x, double *out_4724708977981708405) {
   out_4724708977981708405[0] = delta_x[0] + nom_x[0];
   out_4724708977981708405[1] = delta_x[1] + nom_x[1];
   out_4724708977981708405[2] = delta_x[2] + nom_x[2];
   out_4724708977981708405[3] = delta_x[3] + nom_x[3];
   out_4724708977981708405[4] = delta_x[4] + nom_x[4];
   out_4724708977981708405[5] = delta_x[5] + nom_x[5];
   out_4724708977981708405[6] = delta_x[6] + nom_x[6];
   out_4724708977981708405[7] = delta_x[7] + nom_x[7];
   out_4724708977981708405[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5126129424661047506) {
   out_5126129424661047506[0] = -nom_x[0] + true_x[0];
   out_5126129424661047506[1] = -nom_x[1] + true_x[1];
   out_5126129424661047506[2] = -nom_x[2] + true_x[2];
   out_5126129424661047506[3] = -nom_x[3] + true_x[3];
   out_5126129424661047506[4] = -nom_x[4] + true_x[4];
   out_5126129424661047506[5] = -nom_x[5] + true_x[5];
   out_5126129424661047506[6] = -nom_x[6] + true_x[6];
   out_5126129424661047506[7] = -nom_x[7] + true_x[7];
   out_5126129424661047506[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1147635393640717535) {
   out_1147635393640717535[0] = 1.0;
   out_1147635393640717535[1] = 0;
   out_1147635393640717535[2] = 0;
   out_1147635393640717535[3] = 0;
   out_1147635393640717535[4] = 0;
   out_1147635393640717535[5] = 0;
   out_1147635393640717535[6] = 0;
   out_1147635393640717535[7] = 0;
   out_1147635393640717535[8] = 0;
   out_1147635393640717535[9] = 0;
   out_1147635393640717535[10] = 1.0;
   out_1147635393640717535[11] = 0;
   out_1147635393640717535[12] = 0;
   out_1147635393640717535[13] = 0;
   out_1147635393640717535[14] = 0;
   out_1147635393640717535[15] = 0;
   out_1147635393640717535[16] = 0;
   out_1147635393640717535[17] = 0;
   out_1147635393640717535[18] = 0;
   out_1147635393640717535[19] = 0;
   out_1147635393640717535[20] = 1.0;
   out_1147635393640717535[21] = 0;
   out_1147635393640717535[22] = 0;
   out_1147635393640717535[23] = 0;
   out_1147635393640717535[24] = 0;
   out_1147635393640717535[25] = 0;
   out_1147635393640717535[26] = 0;
   out_1147635393640717535[27] = 0;
   out_1147635393640717535[28] = 0;
   out_1147635393640717535[29] = 0;
   out_1147635393640717535[30] = 1.0;
   out_1147635393640717535[31] = 0;
   out_1147635393640717535[32] = 0;
   out_1147635393640717535[33] = 0;
   out_1147635393640717535[34] = 0;
   out_1147635393640717535[35] = 0;
   out_1147635393640717535[36] = 0;
   out_1147635393640717535[37] = 0;
   out_1147635393640717535[38] = 0;
   out_1147635393640717535[39] = 0;
   out_1147635393640717535[40] = 1.0;
   out_1147635393640717535[41] = 0;
   out_1147635393640717535[42] = 0;
   out_1147635393640717535[43] = 0;
   out_1147635393640717535[44] = 0;
   out_1147635393640717535[45] = 0;
   out_1147635393640717535[46] = 0;
   out_1147635393640717535[47] = 0;
   out_1147635393640717535[48] = 0;
   out_1147635393640717535[49] = 0;
   out_1147635393640717535[50] = 1.0;
   out_1147635393640717535[51] = 0;
   out_1147635393640717535[52] = 0;
   out_1147635393640717535[53] = 0;
   out_1147635393640717535[54] = 0;
   out_1147635393640717535[55] = 0;
   out_1147635393640717535[56] = 0;
   out_1147635393640717535[57] = 0;
   out_1147635393640717535[58] = 0;
   out_1147635393640717535[59] = 0;
   out_1147635393640717535[60] = 1.0;
   out_1147635393640717535[61] = 0;
   out_1147635393640717535[62] = 0;
   out_1147635393640717535[63] = 0;
   out_1147635393640717535[64] = 0;
   out_1147635393640717535[65] = 0;
   out_1147635393640717535[66] = 0;
   out_1147635393640717535[67] = 0;
   out_1147635393640717535[68] = 0;
   out_1147635393640717535[69] = 0;
   out_1147635393640717535[70] = 1.0;
   out_1147635393640717535[71] = 0;
   out_1147635393640717535[72] = 0;
   out_1147635393640717535[73] = 0;
   out_1147635393640717535[74] = 0;
   out_1147635393640717535[75] = 0;
   out_1147635393640717535[76] = 0;
   out_1147635393640717535[77] = 0;
   out_1147635393640717535[78] = 0;
   out_1147635393640717535[79] = 0;
   out_1147635393640717535[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5224857696349368422) {
   out_5224857696349368422[0] = state[0];
   out_5224857696349368422[1] = state[1];
   out_5224857696349368422[2] = state[2];
   out_5224857696349368422[3] = state[3];
   out_5224857696349368422[4] = state[4];
   out_5224857696349368422[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5224857696349368422[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5224857696349368422[7] = state[7];
   out_5224857696349368422[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5873942743940990608) {
   out_5873942743940990608[0] = 1;
   out_5873942743940990608[1] = 0;
   out_5873942743940990608[2] = 0;
   out_5873942743940990608[3] = 0;
   out_5873942743940990608[4] = 0;
   out_5873942743940990608[5] = 0;
   out_5873942743940990608[6] = 0;
   out_5873942743940990608[7] = 0;
   out_5873942743940990608[8] = 0;
   out_5873942743940990608[9] = 0;
   out_5873942743940990608[10] = 1;
   out_5873942743940990608[11] = 0;
   out_5873942743940990608[12] = 0;
   out_5873942743940990608[13] = 0;
   out_5873942743940990608[14] = 0;
   out_5873942743940990608[15] = 0;
   out_5873942743940990608[16] = 0;
   out_5873942743940990608[17] = 0;
   out_5873942743940990608[18] = 0;
   out_5873942743940990608[19] = 0;
   out_5873942743940990608[20] = 1;
   out_5873942743940990608[21] = 0;
   out_5873942743940990608[22] = 0;
   out_5873942743940990608[23] = 0;
   out_5873942743940990608[24] = 0;
   out_5873942743940990608[25] = 0;
   out_5873942743940990608[26] = 0;
   out_5873942743940990608[27] = 0;
   out_5873942743940990608[28] = 0;
   out_5873942743940990608[29] = 0;
   out_5873942743940990608[30] = 1;
   out_5873942743940990608[31] = 0;
   out_5873942743940990608[32] = 0;
   out_5873942743940990608[33] = 0;
   out_5873942743940990608[34] = 0;
   out_5873942743940990608[35] = 0;
   out_5873942743940990608[36] = 0;
   out_5873942743940990608[37] = 0;
   out_5873942743940990608[38] = 0;
   out_5873942743940990608[39] = 0;
   out_5873942743940990608[40] = 1;
   out_5873942743940990608[41] = 0;
   out_5873942743940990608[42] = 0;
   out_5873942743940990608[43] = 0;
   out_5873942743940990608[44] = 0;
   out_5873942743940990608[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5873942743940990608[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5873942743940990608[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5873942743940990608[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5873942743940990608[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5873942743940990608[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5873942743940990608[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5873942743940990608[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5873942743940990608[53] = -9.8000000000000007*dt;
   out_5873942743940990608[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5873942743940990608[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5873942743940990608[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5873942743940990608[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5873942743940990608[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5873942743940990608[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5873942743940990608[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5873942743940990608[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5873942743940990608[62] = 0;
   out_5873942743940990608[63] = 0;
   out_5873942743940990608[64] = 0;
   out_5873942743940990608[65] = 0;
   out_5873942743940990608[66] = 0;
   out_5873942743940990608[67] = 0;
   out_5873942743940990608[68] = 0;
   out_5873942743940990608[69] = 0;
   out_5873942743940990608[70] = 1;
   out_5873942743940990608[71] = 0;
   out_5873942743940990608[72] = 0;
   out_5873942743940990608[73] = 0;
   out_5873942743940990608[74] = 0;
   out_5873942743940990608[75] = 0;
   out_5873942743940990608[76] = 0;
   out_5873942743940990608[77] = 0;
   out_5873942743940990608[78] = 0;
   out_5873942743940990608[79] = 0;
   out_5873942743940990608[80] = 1;
}
void h_25(double *state, double *unused, double *out_1380271847665989609) {
   out_1380271847665989609[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2830062547978729467) {
   out_2830062547978729467[0] = 0;
   out_2830062547978729467[1] = 0;
   out_2830062547978729467[2] = 0;
   out_2830062547978729467[3] = 0;
   out_2830062547978729467[4] = 0;
   out_2830062547978729467[5] = 0;
   out_2830062547978729467[6] = 1;
   out_2830062547978729467[7] = 0;
   out_2830062547978729467[8] = 0;
}
void h_24(double *state, double *unused, double *out_8094530808421281060) {
   out_8094530808421281060[0] = state[4];
   out_8094530808421281060[1] = state[5];
}
void H_24(double *state, double *unused, double *out_658041141853804222) {
   out_658041141853804222[0] = 0;
   out_658041141853804222[1] = 0;
   out_658041141853804222[2] = 0;
   out_658041141853804222[3] = 0;
   out_658041141853804222[4] = 1;
   out_658041141853804222[5] = 0;
   out_658041141853804222[6] = 0;
   out_658041141853804222[7] = 0;
   out_658041141853804222[8] = 0;
   out_658041141853804222[9] = 0;
   out_658041141853804222[10] = 0;
   out_658041141853804222[11] = 0;
   out_658041141853804222[12] = 0;
   out_658041141853804222[13] = 0;
   out_658041141853804222[14] = 1;
   out_658041141853804222[15] = 0;
   out_658041141853804222[16] = 0;
   out_658041141853804222[17] = 0;
}
void h_30(double *state, double *unused, double *out_5207556078810305554) {
   out_5207556078810305554[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2700723600835489397) {
   out_2700723600835489397[0] = 0;
   out_2700723600835489397[1] = 0;
   out_2700723600835489397[2] = 0;
   out_2700723600835489397[3] = 0;
   out_2700723600835489397[4] = 1;
   out_2700723600835489397[5] = 0;
   out_2700723600835489397[6] = 0;
   out_2700723600835489397[7] = 0;
   out_2700723600835489397[8] = 0;
}
void h_26(double *state, double *unused, double *out_205882811149459909) {
   out_205882811149459909[0] = state[7];
}
void H_26(double *state, double *unused, double *out_911440770895326757) {
   out_911440770895326757[0] = 0;
   out_911440770895326757[1] = 0;
   out_911440770895326757[2] = 0;
   out_911440770895326757[3] = 0;
   out_911440770895326757[4] = 0;
   out_911440770895326757[5] = 0;
   out_911440770895326757[6] = 0;
   out_911440770895326757[7] = 1;
   out_911440770895326757[8] = 0;
}
void h_27(double *state, double *unused, double *out_8383034551459055388) {
   out_8383034551459055388[0] = state[3];
}
void H_27(double *state, double *unused, double *out_525960289035064486) {
   out_525960289035064486[0] = 0;
   out_525960289035064486[1] = 0;
   out_525960289035064486[2] = 0;
   out_525960289035064486[3] = 1;
   out_525960289035064486[4] = 0;
   out_525960289035064486[5] = 0;
   out_525960289035064486[6] = 0;
   out_525960289035064486[7] = 0;
   out_525960289035064486[8] = 0;
}
void h_29(double *state, double *unused, double *out_8237514727238400417) {
   out_8237514727238400417[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3210954945149881581) {
   out_3210954945149881581[0] = 0;
   out_3210954945149881581[1] = 1;
   out_3210954945149881581[2] = 0;
   out_3210954945149881581[3] = 0;
   out_3210954945149881581[4] = 0;
   out_3210954945149881581[5] = 0;
   out_3210954945149881581[6] = 0;
   out_3210954945149881581[7] = 0;
   out_3210954945149881581[8] = 0;
}
void h_28(double *state, double *unused, double *out_3157127335623730441) {
   out_3157127335623730441[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6269801454904017121) {
   out_6269801454904017121[0] = 1;
   out_6269801454904017121[1] = 0;
   out_6269801454904017121[2] = 0;
   out_6269801454904017121[3] = 0;
   out_6269801454904017121[4] = 0;
   out_6269801454904017121[5] = 0;
   out_6269801454904017121[6] = 0;
   out_6269801454904017121[7] = 0;
   out_6269801454904017121[8] = 0;
}
void h_31(double *state, double *unused, double *out_5822944109319996361) {
   out_5822944109319996361[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2860708509855689895) {
   out_2860708509855689895[0] = 0;
   out_2860708509855689895[1] = 0;
   out_2860708509855689895[2] = 0;
   out_2860708509855689895[3] = 0;
   out_2860708509855689895[4] = 0;
   out_2860708509855689895[5] = 0;
   out_2860708509855689895[6] = 0;
   out_2860708509855689895[7] = 0;
   out_2860708509855689895[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4724708977981708405) {
  err_fun(nom_x, delta_x, out_4724708977981708405);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5126129424661047506) {
  inv_err_fun(nom_x, true_x, out_5126129424661047506);
}
void car_H_mod_fun(double *state, double *out_1147635393640717535) {
  H_mod_fun(state, out_1147635393640717535);
}
void car_f_fun(double *state, double dt, double *out_5224857696349368422) {
  f_fun(state,  dt, out_5224857696349368422);
}
void car_F_fun(double *state, double dt, double *out_5873942743940990608) {
  F_fun(state,  dt, out_5873942743940990608);
}
void car_h_25(double *state, double *unused, double *out_1380271847665989609) {
  h_25(state, unused, out_1380271847665989609);
}
void car_H_25(double *state, double *unused, double *out_2830062547978729467) {
  H_25(state, unused, out_2830062547978729467);
}
void car_h_24(double *state, double *unused, double *out_8094530808421281060) {
  h_24(state, unused, out_8094530808421281060);
}
void car_H_24(double *state, double *unused, double *out_658041141853804222) {
  H_24(state, unused, out_658041141853804222);
}
void car_h_30(double *state, double *unused, double *out_5207556078810305554) {
  h_30(state, unused, out_5207556078810305554);
}
void car_H_30(double *state, double *unused, double *out_2700723600835489397) {
  H_30(state, unused, out_2700723600835489397);
}
void car_h_26(double *state, double *unused, double *out_205882811149459909) {
  h_26(state, unused, out_205882811149459909);
}
void car_H_26(double *state, double *unused, double *out_911440770895326757) {
  H_26(state, unused, out_911440770895326757);
}
void car_h_27(double *state, double *unused, double *out_8383034551459055388) {
  h_27(state, unused, out_8383034551459055388);
}
void car_H_27(double *state, double *unused, double *out_525960289035064486) {
  H_27(state, unused, out_525960289035064486);
}
void car_h_29(double *state, double *unused, double *out_8237514727238400417) {
  h_29(state, unused, out_8237514727238400417);
}
void car_H_29(double *state, double *unused, double *out_3210954945149881581) {
  H_29(state, unused, out_3210954945149881581);
}
void car_h_28(double *state, double *unused, double *out_3157127335623730441) {
  h_28(state, unused, out_3157127335623730441);
}
void car_H_28(double *state, double *unused, double *out_6269801454904017121) {
  H_28(state, unused, out_6269801454904017121);
}
void car_h_31(double *state, double *unused, double *out_5822944109319996361) {
  h_31(state, unused, out_5822944109319996361);
}
void car_H_31(double *state, double *unused, double *out_2860708509855689895) {
  H_31(state, unused, out_2860708509855689895);
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
