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
void err_fun(double *nom_x, double *delta_x, double *out_370478261474098247) {
   out_370478261474098247[0] = delta_x[0] + nom_x[0];
   out_370478261474098247[1] = delta_x[1] + nom_x[1];
   out_370478261474098247[2] = delta_x[2] + nom_x[2];
   out_370478261474098247[3] = delta_x[3] + nom_x[3];
   out_370478261474098247[4] = delta_x[4] + nom_x[4];
   out_370478261474098247[5] = delta_x[5] + nom_x[5];
   out_370478261474098247[6] = delta_x[6] + nom_x[6];
   out_370478261474098247[7] = delta_x[7] + nom_x[7];
   out_370478261474098247[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2754704753635741812) {
   out_2754704753635741812[0] = -nom_x[0] + true_x[0];
   out_2754704753635741812[1] = -nom_x[1] + true_x[1];
   out_2754704753635741812[2] = -nom_x[2] + true_x[2];
   out_2754704753635741812[3] = -nom_x[3] + true_x[3];
   out_2754704753635741812[4] = -nom_x[4] + true_x[4];
   out_2754704753635741812[5] = -nom_x[5] + true_x[5];
   out_2754704753635741812[6] = -nom_x[6] + true_x[6];
   out_2754704753635741812[7] = -nom_x[7] + true_x[7];
   out_2754704753635741812[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3683481686615348312) {
   out_3683481686615348312[0] = 1.0;
   out_3683481686615348312[1] = 0.0;
   out_3683481686615348312[2] = 0.0;
   out_3683481686615348312[3] = 0.0;
   out_3683481686615348312[4] = 0.0;
   out_3683481686615348312[5] = 0.0;
   out_3683481686615348312[6] = 0.0;
   out_3683481686615348312[7] = 0.0;
   out_3683481686615348312[8] = 0.0;
   out_3683481686615348312[9] = 0.0;
   out_3683481686615348312[10] = 1.0;
   out_3683481686615348312[11] = 0.0;
   out_3683481686615348312[12] = 0.0;
   out_3683481686615348312[13] = 0.0;
   out_3683481686615348312[14] = 0.0;
   out_3683481686615348312[15] = 0.0;
   out_3683481686615348312[16] = 0.0;
   out_3683481686615348312[17] = 0.0;
   out_3683481686615348312[18] = 0.0;
   out_3683481686615348312[19] = 0.0;
   out_3683481686615348312[20] = 1.0;
   out_3683481686615348312[21] = 0.0;
   out_3683481686615348312[22] = 0.0;
   out_3683481686615348312[23] = 0.0;
   out_3683481686615348312[24] = 0.0;
   out_3683481686615348312[25] = 0.0;
   out_3683481686615348312[26] = 0.0;
   out_3683481686615348312[27] = 0.0;
   out_3683481686615348312[28] = 0.0;
   out_3683481686615348312[29] = 0.0;
   out_3683481686615348312[30] = 1.0;
   out_3683481686615348312[31] = 0.0;
   out_3683481686615348312[32] = 0.0;
   out_3683481686615348312[33] = 0.0;
   out_3683481686615348312[34] = 0.0;
   out_3683481686615348312[35] = 0.0;
   out_3683481686615348312[36] = 0.0;
   out_3683481686615348312[37] = 0.0;
   out_3683481686615348312[38] = 0.0;
   out_3683481686615348312[39] = 0.0;
   out_3683481686615348312[40] = 1.0;
   out_3683481686615348312[41] = 0.0;
   out_3683481686615348312[42] = 0.0;
   out_3683481686615348312[43] = 0.0;
   out_3683481686615348312[44] = 0.0;
   out_3683481686615348312[45] = 0.0;
   out_3683481686615348312[46] = 0.0;
   out_3683481686615348312[47] = 0.0;
   out_3683481686615348312[48] = 0.0;
   out_3683481686615348312[49] = 0.0;
   out_3683481686615348312[50] = 1.0;
   out_3683481686615348312[51] = 0.0;
   out_3683481686615348312[52] = 0.0;
   out_3683481686615348312[53] = 0.0;
   out_3683481686615348312[54] = 0.0;
   out_3683481686615348312[55] = 0.0;
   out_3683481686615348312[56] = 0.0;
   out_3683481686615348312[57] = 0.0;
   out_3683481686615348312[58] = 0.0;
   out_3683481686615348312[59] = 0.0;
   out_3683481686615348312[60] = 1.0;
   out_3683481686615348312[61] = 0.0;
   out_3683481686615348312[62] = 0.0;
   out_3683481686615348312[63] = 0.0;
   out_3683481686615348312[64] = 0.0;
   out_3683481686615348312[65] = 0.0;
   out_3683481686615348312[66] = 0.0;
   out_3683481686615348312[67] = 0.0;
   out_3683481686615348312[68] = 0.0;
   out_3683481686615348312[69] = 0.0;
   out_3683481686615348312[70] = 1.0;
   out_3683481686615348312[71] = 0.0;
   out_3683481686615348312[72] = 0.0;
   out_3683481686615348312[73] = 0.0;
   out_3683481686615348312[74] = 0.0;
   out_3683481686615348312[75] = 0.0;
   out_3683481686615348312[76] = 0.0;
   out_3683481686615348312[77] = 0.0;
   out_3683481686615348312[78] = 0.0;
   out_3683481686615348312[79] = 0.0;
   out_3683481686615348312[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2191088460119330414) {
   out_2191088460119330414[0] = state[0];
   out_2191088460119330414[1] = state[1];
   out_2191088460119330414[2] = state[2];
   out_2191088460119330414[3] = state[3];
   out_2191088460119330414[4] = state[4];
   out_2191088460119330414[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2191088460119330414[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2191088460119330414[7] = state[7];
   out_2191088460119330414[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9073829423060190499) {
   out_9073829423060190499[0] = 1;
   out_9073829423060190499[1] = 0;
   out_9073829423060190499[2] = 0;
   out_9073829423060190499[3] = 0;
   out_9073829423060190499[4] = 0;
   out_9073829423060190499[5] = 0;
   out_9073829423060190499[6] = 0;
   out_9073829423060190499[7] = 0;
   out_9073829423060190499[8] = 0;
   out_9073829423060190499[9] = 0;
   out_9073829423060190499[10] = 1;
   out_9073829423060190499[11] = 0;
   out_9073829423060190499[12] = 0;
   out_9073829423060190499[13] = 0;
   out_9073829423060190499[14] = 0;
   out_9073829423060190499[15] = 0;
   out_9073829423060190499[16] = 0;
   out_9073829423060190499[17] = 0;
   out_9073829423060190499[18] = 0;
   out_9073829423060190499[19] = 0;
   out_9073829423060190499[20] = 1;
   out_9073829423060190499[21] = 0;
   out_9073829423060190499[22] = 0;
   out_9073829423060190499[23] = 0;
   out_9073829423060190499[24] = 0;
   out_9073829423060190499[25] = 0;
   out_9073829423060190499[26] = 0;
   out_9073829423060190499[27] = 0;
   out_9073829423060190499[28] = 0;
   out_9073829423060190499[29] = 0;
   out_9073829423060190499[30] = 1;
   out_9073829423060190499[31] = 0;
   out_9073829423060190499[32] = 0;
   out_9073829423060190499[33] = 0;
   out_9073829423060190499[34] = 0;
   out_9073829423060190499[35] = 0;
   out_9073829423060190499[36] = 0;
   out_9073829423060190499[37] = 0;
   out_9073829423060190499[38] = 0;
   out_9073829423060190499[39] = 0;
   out_9073829423060190499[40] = 1;
   out_9073829423060190499[41] = 0;
   out_9073829423060190499[42] = 0;
   out_9073829423060190499[43] = 0;
   out_9073829423060190499[44] = 0;
   out_9073829423060190499[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9073829423060190499[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9073829423060190499[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9073829423060190499[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9073829423060190499[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9073829423060190499[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9073829423060190499[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9073829423060190499[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9073829423060190499[53] = -9.8000000000000007*dt;
   out_9073829423060190499[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9073829423060190499[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9073829423060190499[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9073829423060190499[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9073829423060190499[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9073829423060190499[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9073829423060190499[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9073829423060190499[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9073829423060190499[62] = 0;
   out_9073829423060190499[63] = 0;
   out_9073829423060190499[64] = 0;
   out_9073829423060190499[65] = 0;
   out_9073829423060190499[66] = 0;
   out_9073829423060190499[67] = 0;
   out_9073829423060190499[68] = 0;
   out_9073829423060190499[69] = 0;
   out_9073829423060190499[70] = 1;
   out_9073829423060190499[71] = 0;
   out_9073829423060190499[72] = 0;
   out_9073829423060190499[73] = 0;
   out_9073829423060190499[74] = 0;
   out_9073829423060190499[75] = 0;
   out_9073829423060190499[76] = 0;
   out_9073829423060190499[77] = 0;
   out_9073829423060190499[78] = 0;
   out_9073829423060190499[79] = 0;
   out_9073829423060190499[80] = 1;
}
void h_25(double *state, double *unused, double *out_8958950060573646875) {
   out_8958950060573646875[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8587173511800013152) {
   out_8587173511800013152[0] = 0;
   out_8587173511800013152[1] = 0;
   out_8587173511800013152[2] = 0;
   out_8587173511800013152[3] = 0;
   out_8587173511800013152[4] = 0;
   out_8587173511800013152[5] = 0;
   out_8587173511800013152[6] = 1;
   out_8587173511800013152[7] = 0;
   out_8587173511800013152[8] = 0;
}
void h_24(double *state, double *unused, double *out_930064219770468569) {
   out_930064219770468569[0] = state[4];
   out_930064219770468569[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3283998755318020363) {
   out_3283998755318020363[0] = 0;
   out_3283998755318020363[1] = 0;
   out_3283998755318020363[2] = 0;
   out_3283998755318020363[3] = 0;
   out_3283998755318020363[4] = 1;
   out_3283998755318020363[5] = 0;
   out_3283998755318020363[6] = 0;
   out_3283998755318020363[7] = 0;
   out_3283998755318020363[8] = 0;
   out_3283998755318020363[9] = 0;
   out_3283998755318020363[10] = 0;
   out_3283998755318020363[11] = 0;
   out_3283998755318020363[12] = 0;
   out_3283998755318020363[13] = 0;
   out_3283998755318020363[14] = 1;
   out_3283998755318020363[15] = 0;
   out_3283998755318020363[16] = 0;
   out_3283998755318020363[17] = 0;
}
void h_30(double *state, double *unused, double *out_1195684803752974434) {
   out_1195684803752974434[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2942880220417921709) {
   out_2942880220417921709[0] = 0;
   out_2942880220417921709[1] = 0;
   out_2942880220417921709[2] = 0;
   out_2942880220417921709[3] = 0;
   out_2942880220417921709[4] = 1;
   out_2942880220417921709[5] = 0;
   out_2942880220417921709[6] = 0;
   out_2942880220417921709[7] = 0;
   out_2942880220417921709[8] = 0;
}
void h_26(double *state, double *unused, double *out_4232470855197307119) {
   out_4232470855197307119[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4845670192925956928) {
   out_4845670192925956928[0] = 0;
   out_4845670192925956928[1] = 0;
   out_4845670192925956928[2] = 0;
   out_4845670192925956928[3] = 0;
   out_4845670192925956928[4] = 0;
   out_4845670192925956928[5] = 0;
   out_4845670192925956928[6] = 0;
   out_4845670192925956928[7] = 1;
   out_4845670192925956928[8] = 0;
}
void h_27(double *state, double *unused, double *out_4421376494417562018) {
   out_4421376494417562018[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5117643532218346620) {
   out_5117643532218346620[0] = 0;
   out_5117643532218346620[1] = 0;
   out_5117643532218346620[2] = 0;
   out_5117643532218346620[3] = 1;
   out_5117643532218346620[4] = 0;
   out_5117643532218346620[5] = 0;
   out_5117643532218346620[6] = 0;
   out_5117643532218346620[7] = 0;
   out_5117643532218346620[8] = 0;
}
void h_29(double *state, double *unused, double *out_4146182432133056129) {
   out_4146182432133056129[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6831006259087897653) {
   out_6831006259087897653[0] = 0;
   out_6831006259087897653[1] = 1;
   out_6831006259087897653[2] = 0;
   out_6831006259087897653[3] = 0;
   out_6831006259087897653[4] = 0;
   out_6831006259087897653[5] = 0;
   out_6831006259087897653[6] = 0;
   out_6831006259087897653[7] = 0;
   out_6831006259087897653[8] = 0;
}
void h_28(double *state, double *unused, double *out_7025781815226259669) {
   out_7025781815226259669[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6533338797552123389) {
   out_6533338797552123389[0] = 1;
   out_6533338797552123389[1] = 0;
   out_6533338797552123389[2] = 0;
   out_6533338797552123389[3] = 0;
   out_6533338797552123389[4] = 0;
   out_6533338797552123389[5] = 0;
   out_6533338797552123389[6] = 0;
   out_6533338797552123389[7] = 0;
   out_6533338797552123389[8] = 0;
}
void h_31(double *state, double *unused, double *out_8886375855522541187) {
   out_8886375855522541187[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8617819473676973580) {
   out_8617819473676973580[0] = 0;
   out_8617819473676973580[1] = 0;
   out_8617819473676973580[2] = 0;
   out_8617819473676973580[3] = 0;
   out_8617819473676973580[4] = 0;
   out_8617819473676973580[5] = 0;
   out_8617819473676973580[6] = 0;
   out_8617819473676973580[7] = 0;
   out_8617819473676973580[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_370478261474098247) {
  err_fun(nom_x, delta_x, out_370478261474098247);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2754704753635741812) {
  inv_err_fun(nom_x, true_x, out_2754704753635741812);
}
void car_H_mod_fun(double *state, double *out_3683481686615348312) {
  H_mod_fun(state, out_3683481686615348312);
}
void car_f_fun(double *state, double dt, double *out_2191088460119330414) {
  f_fun(state,  dt, out_2191088460119330414);
}
void car_F_fun(double *state, double dt, double *out_9073829423060190499) {
  F_fun(state,  dt, out_9073829423060190499);
}
void car_h_25(double *state, double *unused, double *out_8958950060573646875) {
  h_25(state, unused, out_8958950060573646875);
}
void car_H_25(double *state, double *unused, double *out_8587173511800013152) {
  H_25(state, unused, out_8587173511800013152);
}
void car_h_24(double *state, double *unused, double *out_930064219770468569) {
  h_24(state, unused, out_930064219770468569);
}
void car_H_24(double *state, double *unused, double *out_3283998755318020363) {
  H_24(state, unused, out_3283998755318020363);
}
void car_h_30(double *state, double *unused, double *out_1195684803752974434) {
  h_30(state, unused, out_1195684803752974434);
}
void car_H_30(double *state, double *unused, double *out_2942880220417921709) {
  H_30(state, unused, out_2942880220417921709);
}
void car_h_26(double *state, double *unused, double *out_4232470855197307119) {
  h_26(state, unused, out_4232470855197307119);
}
void car_H_26(double *state, double *unused, double *out_4845670192925956928) {
  H_26(state, unused, out_4845670192925956928);
}
void car_h_27(double *state, double *unused, double *out_4421376494417562018) {
  h_27(state, unused, out_4421376494417562018);
}
void car_H_27(double *state, double *unused, double *out_5117643532218346620) {
  H_27(state, unused, out_5117643532218346620);
}
void car_h_29(double *state, double *unused, double *out_4146182432133056129) {
  h_29(state, unused, out_4146182432133056129);
}
void car_H_29(double *state, double *unused, double *out_6831006259087897653) {
  H_29(state, unused, out_6831006259087897653);
}
void car_h_28(double *state, double *unused, double *out_7025781815226259669) {
  h_28(state, unused, out_7025781815226259669);
}
void car_H_28(double *state, double *unused, double *out_6533338797552123389) {
  H_28(state, unused, out_6533338797552123389);
}
void car_h_31(double *state, double *unused, double *out_8886375855522541187) {
  h_31(state, unused, out_8886375855522541187);
}
void car_H_31(double *state, double *unused, double *out_8617819473676973580) {
  H_31(state, unused, out_8617819473676973580);
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
