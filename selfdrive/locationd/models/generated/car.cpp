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
void err_fun(double *nom_x, double *delta_x, double *out_5502167403095710991) {
   out_5502167403095710991[0] = delta_x[0] + nom_x[0];
   out_5502167403095710991[1] = delta_x[1] + nom_x[1];
   out_5502167403095710991[2] = delta_x[2] + nom_x[2];
   out_5502167403095710991[3] = delta_x[3] + nom_x[3];
   out_5502167403095710991[4] = delta_x[4] + nom_x[4];
   out_5502167403095710991[5] = delta_x[5] + nom_x[5];
   out_5502167403095710991[6] = delta_x[6] + nom_x[6];
   out_5502167403095710991[7] = delta_x[7] + nom_x[7];
   out_5502167403095710991[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3774316406736780008) {
   out_3774316406736780008[0] = -nom_x[0] + true_x[0];
   out_3774316406736780008[1] = -nom_x[1] + true_x[1];
   out_3774316406736780008[2] = -nom_x[2] + true_x[2];
   out_3774316406736780008[3] = -nom_x[3] + true_x[3];
   out_3774316406736780008[4] = -nom_x[4] + true_x[4];
   out_3774316406736780008[5] = -nom_x[5] + true_x[5];
   out_3774316406736780008[6] = -nom_x[6] + true_x[6];
   out_3774316406736780008[7] = -nom_x[7] + true_x[7];
   out_3774316406736780008[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1624587115349650366) {
   out_1624587115349650366[0] = 1.0;
   out_1624587115349650366[1] = 0.0;
   out_1624587115349650366[2] = 0.0;
   out_1624587115349650366[3] = 0.0;
   out_1624587115349650366[4] = 0.0;
   out_1624587115349650366[5] = 0.0;
   out_1624587115349650366[6] = 0.0;
   out_1624587115349650366[7] = 0.0;
   out_1624587115349650366[8] = 0.0;
   out_1624587115349650366[9] = 0.0;
   out_1624587115349650366[10] = 1.0;
   out_1624587115349650366[11] = 0.0;
   out_1624587115349650366[12] = 0.0;
   out_1624587115349650366[13] = 0.0;
   out_1624587115349650366[14] = 0.0;
   out_1624587115349650366[15] = 0.0;
   out_1624587115349650366[16] = 0.0;
   out_1624587115349650366[17] = 0.0;
   out_1624587115349650366[18] = 0.0;
   out_1624587115349650366[19] = 0.0;
   out_1624587115349650366[20] = 1.0;
   out_1624587115349650366[21] = 0.0;
   out_1624587115349650366[22] = 0.0;
   out_1624587115349650366[23] = 0.0;
   out_1624587115349650366[24] = 0.0;
   out_1624587115349650366[25] = 0.0;
   out_1624587115349650366[26] = 0.0;
   out_1624587115349650366[27] = 0.0;
   out_1624587115349650366[28] = 0.0;
   out_1624587115349650366[29] = 0.0;
   out_1624587115349650366[30] = 1.0;
   out_1624587115349650366[31] = 0.0;
   out_1624587115349650366[32] = 0.0;
   out_1624587115349650366[33] = 0.0;
   out_1624587115349650366[34] = 0.0;
   out_1624587115349650366[35] = 0.0;
   out_1624587115349650366[36] = 0.0;
   out_1624587115349650366[37] = 0.0;
   out_1624587115349650366[38] = 0.0;
   out_1624587115349650366[39] = 0.0;
   out_1624587115349650366[40] = 1.0;
   out_1624587115349650366[41] = 0.0;
   out_1624587115349650366[42] = 0.0;
   out_1624587115349650366[43] = 0.0;
   out_1624587115349650366[44] = 0.0;
   out_1624587115349650366[45] = 0.0;
   out_1624587115349650366[46] = 0.0;
   out_1624587115349650366[47] = 0.0;
   out_1624587115349650366[48] = 0.0;
   out_1624587115349650366[49] = 0.0;
   out_1624587115349650366[50] = 1.0;
   out_1624587115349650366[51] = 0.0;
   out_1624587115349650366[52] = 0.0;
   out_1624587115349650366[53] = 0.0;
   out_1624587115349650366[54] = 0.0;
   out_1624587115349650366[55] = 0.0;
   out_1624587115349650366[56] = 0.0;
   out_1624587115349650366[57] = 0.0;
   out_1624587115349650366[58] = 0.0;
   out_1624587115349650366[59] = 0.0;
   out_1624587115349650366[60] = 1.0;
   out_1624587115349650366[61] = 0.0;
   out_1624587115349650366[62] = 0.0;
   out_1624587115349650366[63] = 0.0;
   out_1624587115349650366[64] = 0.0;
   out_1624587115349650366[65] = 0.0;
   out_1624587115349650366[66] = 0.0;
   out_1624587115349650366[67] = 0.0;
   out_1624587115349650366[68] = 0.0;
   out_1624587115349650366[69] = 0.0;
   out_1624587115349650366[70] = 1.0;
   out_1624587115349650366[71] = 0.0;
   out_1624587115349650366[72] = 0.0;
   out_1624587115349650366[73] = 0.0;
   out_1624587115349650366[74] = 0.0;
   out_1624587115349650366[75] = 0.0;
   out_1624587115349650366[76] = 0.0;
   out_1624587115349650366[77] = 0.0;
   out_1624587115349650366[78] = 0.0;
   out_1624587115349650366[79] = 0.0;
   out_1624587115349650366[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7007240483040271081) {
   out_7007240483040271081[0] = state[0];
   out_7007240483040271081[1] = state[1];
   out_7007240483040271081[2] = state[2];
   out_7007240483040271081[3] = state[3];
   out_7007240483040271081[4] = state[4];
   out_7007240483040271081[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7007240483040271081[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7007240483040271081[7] = state[7];
   out_7007240483040271081[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3417649342865291063) {
   out_3417649342865291063[0] = 1;
   out_3417649342865291063[1] = 0;
   out_3417649342865291063[2] = 0;
   out_3417649342865291063[3] = 0;
   out_3417649342865291063[4] = 0;
   out_3417649342865291063[5] = 0;
   out_3417649342865291063[6] = 0;
   out_3417649342865291063[7] = 0;
   out_3417649342865291063[8] = 0;
   out_3417649342865291063[9] = 0;
   out_3417649342865291063[10] = 1;
   out_3417649342865291063[11] = 0;
   out_3417649342865291063[12] = 0;
   out_3417649342865291063[13] = 0;
   out_3417649342865291063[14] = 0;
   out_3417649342865291063[15] = 0;
   out_3417649342865291063[16] = 0;
   out_3417649342865291063[17] = 0;
   out_3417649342865291063[18] = 0;
   out_3417649342865291063[19] = 0;
   out_3417649342865291063[20] = 1;
   out_3417649342865291063[21] = 0;
   out_3417649342865291063[22] = 0;
   out_3417649342865291063[23] = 0;
   out_3417649342865291063[24] = 0;
   out_3417649342865291063[25] = 0;
   out_3417649342865291063[26] = 0;
   out_3417649342865291063[27] = 0;
   out_3417649342865291063[28] = 0;
   out_3417649342865291063[29] = 0;
   out_3417649342865291063[30] = 1;
   out_3417649342865291063[31] = 0;
   out_3417649342865291063[32] = 0;
   out_3417649342865291063[33] = 0;
   out_3417649342865291063[34] = 0;
   out_3417649342865291063[35] = 0;
   out_3417649342865291063[36] = 0;
   out_3417649342865291063[37] = 0;
   out_3417649342865291063[38] = 0;
   out_3417649342865291063[39] = 0;
   out_3417649342865291063[40] = 1;
   out_3417649342865291063[41] = 0;
   out_3417649342865291063[42] = 0;
   out_3417649342865291063[43] = 0;
   out_3417649342865291063[44] = 0;
   out_3417649342865291063[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3417649342865291063[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3417649342865291063[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3417649342865291063[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3417649342865291063[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3417649342865291063[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3417649342865291063[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3417649342865291063[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3417649342865291063[53] = -9.8100000000000005*dt;
   out_3417649342865291063[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3417649342865291063[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3417649342865291063[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3417649342865291063[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3417649342865291063[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3417649342865291063[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3417649342865291063[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3417649342865291063[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3417649342865291063[62] = 0;
   out_3417649342865291063[63] = 0;
   out_3417649342865291063[64] = 0;
   out_3417649342865291063[65] = 0;
   out_3417649342865291063[66] = 0;
   out_3417649342865291063[67] = 0;
   out_3417649342865291063[68] = 0;
   out_3417649342865291063[69] = 0;
   out_3417649342865291063[70] = 1;
   out_3417649342865291063[71] = 0;
   out_3417649342865291063[72] = 0;
   out_3417649342865291063[73] = 0;
   out_3417649342865291063[74] = 0;
   out_3417649342865291063[75] = 0;
   out_3417649342865291063[76] = 0;
   out_3417649342865291063[77] = 0;
   out_3417649342865291063[78] = 0;
   out_3417649342865291063[79] = 0;
   out_3417649342865291063[80] = 1;
}
void h_25(double *state, double *unused, double *out_8870524108734237637) {
   out_8870524108734237637[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1469431157442746142) {
   out_1469431157442746142[0] = 0;
   out_1469431157442746142[1] = 0;
   out_1469431157442746142[2] = 0;
   out_1469431157442746142[3] = 0;
   out_1469431157442746142[4] = 0;
   out_1469431157442746142[5] = 0;
   out_1469431157442746142[6] = 1;
   out_1469431157442746142[7] = 0;
   out_1469431157442746142[8] = 0;
}
void h_24(double *state, double *unused, double *out_2970532528807155776) {
   out_2970532528807155776[0] = state[4];
   out_2970532528807155776[1] = state[5];
}
void H_24(double *state, double *unused, double *out_703218441562753424) {
   out_703218441562753424[0] = 0;
   out_703218441562753424[1] = 0;
   out_703218441562753424[2] = 0;
   out_703218441562753424[3] = 0;
   out_703218441562753424[4] = 1;
   out_703218441562753424[5] = 0;
   out_703218441562753424[6] = 0;
   out_703218441562753424[7] = 0;
   out_703218441562753424[8] = 0;
   out_703218441562753424[9] = 0;
   out_703218441562753424[10] = 0;
   out_703218441562753424[11] = 0;
   out_703218441562753424[12] = 0;
   out_703218441562753424[13] = 0;
   out_703218441562753424[14] = 1;
   out_703218441562753424[15] = 0;
   out_703218441562753424[16] = 0;
   out_703218441562753424[17] = 0;
}
void h_30(double *state, double *unused, double *out_977584613849714278) {
   out_977584613849714278[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3987764115949994769) {
   out_3987764115949994769[0] = 0;
   out_3987764115949994769[1] = 0;
   out_3987764115949994769[2] = 0;
   out_3987764115949994769[3] = 0;
   out_3987764115949994769[4] = 1;
   out_3987764115949994769[5] = 0;
   out_3987764115949994769[6] = 0;
   out_3987764115949994769[7] = 0;
   out_3987764115949994769[8] = 0;
}
void h_26(double *state, double *unused, double *out_7610578067955127130) {
   out_7610578067955127130[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2272072161431310082) {
   out_2272072161431310082[0] = 0;
   out_2272072161431310082[1] = 0;
   out_2272072161431310082[2] = 0;
   out_2272072161431310082[3] = 0;
   out_2272072161431310082[4] = 0;
   out_2272072161431310082[5] = 0;
   out_2272072161431310082[6] = 0;
   out_2272072161431310082[7] = 1;
   out_2272072161431310082[8] = 0;
}
void h_27(double *state, double *unused, double *out_4574546697314468334) {
   out_4574546697314468334[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6211358187133937986) {
   out_6211358187133937986[0] = 0;
   out_6211358187133937986[1] = 0;
   out_6211358187133937986[2] = 0;
   out_6211358187133937986[3] = 1;
   out_6211358187133937986[4] = 0;
   out_6211358187133937986[5] = 0;
   out_6211358187133937986[6] = 0;
   out_6211358187133937986[7] = 0;
   out_6211358187133937986[8] = 0;
}
void h_29(double *state, double *unused, double *out_6025178089943351501) {
   out_6025178089943351501[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4497995460264386953) {
   out_4497995460264386953[0] = 0;
   out_4497995460264386953[1] = 1;
   out_4497995460264386953[2] = 0;
   out_4497995460264386953[3] = 0;
   out_4497995460264386953[4] = 0;
   out_4497995460264386953[5] = 0;
   out_4497995460264386953[6] = 0;
   out_4497995460264386953[7] = 0;
   out_4497995460264386953[8] = 0;
}
void h_28(double *state, double *unused, double *out_7611332748758801019) {
   out_7611332748758801019[0] = state[0];
}
void H_28(double *state, double *unused, double *out_584403556805143621) {
   out_584403556805143621[0] = 1;
   out_584403556805143621[1] = 0;
   out_584403556805143621[2] = 0;
   out_584403556805143621[3] = 0;
   out_584403556805143621[4] = 0;
   out_584403556805143621[5] = 0;
   out_584403556805143621[6] = 0;
   out_584403556805143621[7] = 0;
   out_584403556805143621[8] = 0;
}
void h_31(double *state, double *unused, double *out_2805384738624963043) {
   out_2805384738624963043[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2898280263664661558) {
   out_2898280263664661558[0] = 0;
   out_2898280263664661558[1] = 0;
   out_2898280263664661558[2] = 0;
   out_2898280263664661558[3] = 0;
   out_2898280263664661558[4] = 0;
   out_2898280263664661558[5] = 0;
   out_2898280263664661558[6] = 0;
   out_2898280263664661558[7] = 0;
   out_2898280263664661558[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5502167403095710991) {
  err_fun(nom_x, delta_x, out_5502167403095710991);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3774316406736780008) {
  inv_err_fun(nom_x, true_x, out_3774316406736780008);
}
void car_H_mod_fun(double *state, double *out_1624587115349650366) {
  H_mod_fun(state, out_1624587115349650366);
}
void car_f_fun(double *state, double dt, double *out_7007240483040271081) {
  f_fun(state,  dt, out_7007240483040271081);
}
void car_F_fun(double *state, double dt, double *out_3417649342865291063) {
  F_fun(state,  dt, out_3417649342865291063);
}
void car_h_25(double *state, double *unused, double *out_8870524108734237637) {
  h_25(state, unused, out_8870524108734237637);
}
void car_H_25(double *state, double *unused, double *out_1469431157442746142) {
  H_25(state, unused, out_1469431157442746142);
}
void car_h_24(double *state, double *unused, double *out_2970532528807155776) {
  h_24(state, unused, out_2970532528807155776);
}
void car_H_24(double *state, double *unused, double *out_703218441562753424) {
  H_24(state, unused, out_703218441562753424);
}
void car_h_30(double *state, double *unused, double *out_977584613849714278) {
  h_30(state, unused, out_977584613849714278);
}
void car_H_30(double *state, double *unused, double *out_3987764115949994769) {
  H_30(state, unused, out_3987764115949994769);
}
void car_h_26(double *state, double *unused, double *out_7610578067955127130) {
  h_26(state, unused, out_7610578067955127130);
}
void car_H_26(double *state, double *unused, double *out_2272072161431310082) {
  H_26(state, unused, out_2272072161431310082);
}
void car_h_27(double *state, double *unused, double *out_4574546697314468334) {
  h_27(state, unused, out_4574546697314468334);
}
void car_H_27(double *state, double *unused, double *out_6211358187133937986) {
  H_27(state, unused, out_6211358187133937986);
}
void car_h_29(double *state, double *unused, double *out_6025178089943351501) {
  h_29(state, unused, out_6025178089943351501);
}
void car_H_29(double *state, double *unused, double *out_4497995460264386953) {
  H_29(state, unused, out_4497995460264386953);
}
void car_h_28(double *state, double *unused, double *out_7611332748758801019) {
  h_28(state, unused, out_7611332748758801019);
}
void car_H_28(double *state, double *unused, double *out_584403556805143621) {
  H_28(state, unused, out_584403556805143621);
}
void car_h_31(double *state, double *unused, double *out_2805384738624963043) {
  h_31(state, unused, out_2805384738624963043);
}
void car_H_31(double *state, double *unused, double *out_2898280263664661558) {
  H_31(state, unused, out_2898280263664661558);
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
