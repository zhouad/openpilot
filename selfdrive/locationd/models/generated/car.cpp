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
void err_fun(double *nom_x, double *delta_x, double *out_6552679409720063083) {
   out_6552679409720063083[0] = delta_x[0] + nom_x[0];
   out_6552679409720063083[1] = delta_x[1] + nom_x[1];
   out_6552679409720063083[2] = delta_x[2] + nom_x[2];
   out_6552679409720063083[3] = delta_x[3] + nom_x[3];
   out_6552679409720063083[4] = delta_x[4] + nom_x[4];
   out_6552679409720063083[5] = delta_x[5] + nom_x[5];
   out_6552679409720063083[6] = delta_x[6] + nom_x[6];
   out_6552679409720063083[7] = delta_x[7] + nom_x[7];
   out_6552679409720063083[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_375450875847608461) {
   out_375450875847608461[0] = -nom_x[0] + true_x[0];
   out_375450875847608461[1] = -nom_x[1] + true_x[1];
   out_375450875847608461[2] = -nom_x[2] + true_x[2];
   out_375450875847608461[3] = -nom_x[3] + true_x[3];
   out_375450875847608461[4] = -nom_x[4] + true_x[4];
   out_375450875847608461[5] = -nom_x[5] + true_x[5];
   out_375450875847608461[6] = -nom_x[6] + true_x[6];
   out_375450875847608461[7] = -nom_x[7] + true_x[7];
   out_375450875847608461[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8454853977093352772) {
   out_8454853977093352772[0] = 1.0;
   out_8454853977093352772[1] = 0.0;
   out_8454853977093352772[2] = 0.0;
   out_8454853977093352772[3] = 0.0;
   out_8454853977093352772[4] = 0.0;
   out_8454853977093352772[5] = 0.0;
   out_8454853977093352772[6] = 0.0;
   out_8454853977093352772[7] = 0.0;
   out_8454853977093352772[8] = 0.0;
   out_8454853977093352772[9] = 0.0;
   out_8454853977093352772[10] = 1.0;
   out_8454853977093352772[11] = 0.0;
   out_8454853977093352772[12] = 0.0;
   out_8454853977093352772[13] = 0.0;
   out_8454853977093352772[14] = 0.0;
   out_8454853977093352772[15] = 0.0;
   out_8454853977093352772[16] = 0.0;
   out_8454853977093352772[17] = 0.0;
   out_8454853977093352772[18] = 0.0;
   out_8454853977093352772[19] = 0.0;
   out_8454853977093352772[20] = 1.0;
   out_8454853977093352772[21] = 0.0;
   out_8454853977093352772[22] = 0.0;
   out_8454853977093352772[23] = 0.0;
   out_8454853977093352772[24] = 0.0;
   out_8454853977093352772[25] = 0.0;
   out_8454853977093352772[26] = 0.0;
   out_8454853977093352772[27] = 0.0;
   out_8454853977093352772[28] = 0.0;
   out_8454853977093352772[29] = 0.0;
   out_8454853977093352772[30] = 1.0;
   out_8454853977093352772[31] = 0.0;
   out_8454853977093352772[32] = 0.0;
   out_8454853977093352772[33] = 0.0;
   out_8454853977093352772[34] = 0.0;
   out_8454853977093352772[35] = 0.0;
   out_8454853977093352772[36] = 0.0;
   out_8454853977093352772[37] = 0.0;
   out_8454853977093352772[38] = 0.0;
   out_8454853977093352772[39] = 0.0;
   out_8454853977093352772[40] = 1.0;
   out_8454853977093352772[41] = 0.0;
   out_8454853977093352772[42] = 0.0;
   out_8454853977093352772[43] = 0.0;
   out_8454853977093352772[44] = 0.0;
   out_8454853977093352772[45] = 0.0;
   out_8454853977093352772[46] = 0.0;
   out_8454853977093352772[47] = 0.0;
   out_8454853977093352772[48] = 0.0;
   out_8454853977093352772[49] = 0.0;
   out_8454853977093352772[50] = 1.0;
   out_8454853977093352772[51] = 0.0;
   out_8454853977093352772[52] = 0.0;
   out_8454853977093352772[53] = 0.0;
   out_8454853977093352772[54] = 0.0;
   out_8454853977093352772[55] = 0.0;
   out_8454853977093352772[56] = 0.0;
   out_8454853977093352772[57] = 0.0;
   out_8454853977093352772[58] = 0.0;
   out_8454853977093352772[59] = 0.0;
   out_8454853977093352772[60] = 1.0;
   out_8454853977093352772[61] = 0.0;
   out_8454853977093352772[62] = 0.0;
   out_8454853977093352772[63] = 0.0;
   out_8454853977093352772[64] = 0.0;
   out_8454853977093352772[65] = 0.0;
   out_8454853977093352772[66] = 0.0;
   out_8454853977093352772[67] = 0.0;
   out_8454853977093352772[68] = 0.0;
   out_8454853977093352772[69] = 0.0;
   out_8454853977093352772[70] = 1.0;
   out_8454853977093352772[71] = 0.0;
   out_8454853977093352772[72] = 0.0;
   out_8454853977093352772[73] = 0.0;
   out_8454853977093352772[74] = 0.0;
   out_8454853977093352772[75] = 0.0;
   out_8454853977093352772[76] = 0.0;
   out_8454853977093352772[77] = 0.0;
   out_8454853977093352772[78] = 0.0;
   out_8454853977093352772[79] = 0.0;
   out_8454853977093352772[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_992240007066989833) {
   out_992240007066989833[0] = state[0];
   out_992240007066989833[1] = state[1];
   out_992240007066989833[2] = state[2];
   out_992240007066989833[3] = state[3];
   out_992240007066989833[4] = state[4];
   out_992240007066989833[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_992240007066989833[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_992240007066989833[7] = state[7];
   out_992240007066989833[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6632803905489520127) {
   out_6632803905489520127[0] = 1;
   out_6632803905489520127[1] = 0;
   out_6632803905489520127[2] = 0;
   out_6632803905489520127[3] = 0;
   out_6632803905489520127[4] = 0;
   out_6632803905489520127[5] = 0;
   out_6632803905489520127[6] = 0;
   out_6632803905489520127[7] = 0;
   out_6632803905489520127[8] = 0;
   out_6632803905489520127[9] = 0;
   out_6632803905489520127[10] = 1;
   out_6632803905489520127[11] = 0;
   out_6632803905489520127[12] = 0;
   out_6632803905489520127[13] = 0;
   out_6632803905489520127[14] = 0;
   out_6632803905489520127[15] = 0;
   out_6632803905489520127[16] = 0;
   out_6632803905489520127[17] = 0;
   out_6632803905489520127[18] = 0;
   out_6632803905489520127[19] = 0;
   out_6632803905489520127[20] = 1;
   out_6632803905489520127[21] = 0;
   out_6632803905489520127[22] = 0;
   out_6632803905489520127[23] = 0;
   out_6632803905489520127[24] = 0;
   out_6632803905489520127[25] = 0;
   out_6632803905489520127[26] = 0;
   out_6632803905489520127[27] = 0;
   out_6632803905489520127[28] = 0;
   out_6632803905489520127[29] = 0;
   out_6632803905489520127[30] = 1;
   out_6632803905489520127[31] = 0;
   out_6632803905489520127[32] = 0;
   out_6632803905489520127[33] = 0;
   out_6632803905489520127[34] = 0;
   out_6632803905489520127[35] = 0;
   out_6632803905489520127[36] = 0;
   out_6632803905489520127[37] = 0;
   out_6632803905489520127[38] = 0;
   out_6632803905489520127[39] = 0;
   out_6632803905489520127[40] = 1;
   out_6632803905489520127[41] = 0;
   out_6632803905489520127[42] = 0;
   out_6632803905489520127[43] = 0;
   out_6632803905489520127[44] = 0;
   out_6632803905489520127[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6632803905489520127[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6632803905489520127[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6632803905489520127[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6632803905489520127[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6632803905489520127[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6632803905489520127[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6632803905489520127[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6632803905489520127[53] = -9.8100000000000005*dt;
   out_6632803905489520127[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6632803905489520127[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6632803905489520127[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6632803905489520127[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6632803905489520127[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6632803905489520127[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6632803905489520127[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6632803905489520127[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6632803905489520127[62] = 0;
   out_6632803905489520127[63] = 0;
   out_6632803905489520127[64] = 0;
   out_6632803905489520127[65] = 0;
   out_6632803905489520127[66] = 0;
   out_6632803905489520127[67] = 0;
   out_6632803905489520127[68] = 0;
   out_6632803905489520127[69] = 0;
   out_6632803905489520127[70] = 1;
   out_6632803905489520127[71] = 0;
   out_6632803905489520127[72] = 0;
   out_6632803905489520127[73] = 0;
   out_6632803905489520127[74] = 0;
   out_6632803905489520127[75] = 0;
   out_6632803905489520127[76] = 0;
   out_6632803905489520127[77] = 0;
   out_6632803905489520127[78] = 0;
   out_6632803905489520127[79] = 0;
   out_6632803905489520127[80] = 1;
}
void h_25(double *state, double *unused, double *out_1516450530651524889) {
   out_1516450530651524889[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3551162151908687932) {
   out_3551162151908687932[0] = 0;
   out_3551162151908687932[1] = 0;
   out_3551162151908687932[2] = 0;
   out_3551162151908687932[3] = 0;
   out_3551162151908687932[4] = 0;
   out_3551162151908687932[5] = 0;
   out_3551162151908687932[6] = 1;
   out_3551162151908687932[7] = 0;
   out_3551162151908687932[8] = 0;
}
void h_24(double *state, double *unused, double *out_4218575999364657751) {
   out_4218575999364657751[0] = state[4];
   out_4218575999364657751[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1373947728301537959) {
   out_1373947728301537959[0] = 0;
   out_1373947728301537959[1] = 0;
   out_1373947728301537959[2] = 0;
   out_1373947728301537959[3] = 0;
   out_1373947728301537959[4] = 1;
   out_1373947728301537959[5] = 0;
   out_1373947728301537959[6] = 0;
   out_1373947728301537959[7] = 0;
   out_1373947728301537959[8] = 0;
   out_1373947728301537959[9] = 0;
   out_1373947728301537959[10] = 0;
   out_1373947728301537959[11] = 0;
   out_1373947728301537959[12] = 0;
   out_1373947728301537959[13] = 0;
   out_1373947728301537959[14] = 1;
   out_1373947728301537959[15] = 0;
   out_1373947728301537959[16] = 0;
   out_1373947728301537959[17] = 0;
}
void h_30(double *state, double *unused, double *out_6376488964232998470) {
   out_6376488964232998470[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1032829193401439305) {
   out_1032829193401439305[0] = 0;
   out_1032829193401439305[1] = 0;
   out_1032829193401439305[2] = 0;
   out_1032829193401439305[3] = 0;
   out_1032829193401439305[4] = 1;
   out_1032829193401439305[5] = 0;
   out_1032829193401439305[6] = 0;
   out_1032829193401439305[7] = 0;
   out_1032829193401439305[8] = 0;
}
void h_26(double *state, double *unused, double *out_8794407296729096557) {
   out_8794407296729096557[0] = state[7];
}
void H_26(double *state, double *unused, double *out_246636182147887331) {
   out_246636182147887331[0] = 0;
   out_246636182147887331[1] = 0;
   out_246636182147887331[2] = 0;
   out_246636182147887331[3] = 0;
   out_246636182147887331[4] = 0;
   out_246636182147887331[5] = 0;
   out_246636182147887331[6] = 0;
   out_246636182147887331[7] = 1;
   out_246636182147887331[8] = 0;
}
void h_27(double *state, double *unused, double *out_3221695518855289041) {
   out_3221695518855289041[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3207592505201864216) {
   out_3207592505201864216[0] = 0;
   out_3207592505201864216[1] = 0;
   out_3207592505201864216[2] = 0;
   out_3207592505201864216[3] = 1;
   out_3207592505201864216[4] = 0;
   out_3207592505201864216[5] = 0;
   out_3207592505201864216[6] = 0;
   out_3207592505201864216[7] = 0;
   out_3207592505201864216[8] = 0;
}
void h_29(double *state, double *unused, double *out_5671213592062704000) {
   out_5671213592062704000[0] = state[1];
}
void H_29(double *state, double *unused, double *out_522597849087047121) {
   out_522597849087047121[0] = 0;
   out_522597849087047121[1] = 1;
   out_522597849087047121[2] = 0;
   out_522597849087047121[3] = 0;
   out_522597849087047121[4] = 0;
   out_522597849087047121[5] = 0;
   out_522597849087047121[6] = 0;
   out_522597849087047121[7] = 0;
   out_522597849087047121[8] = 0;
}
void h_28(double *state, double *unused, double *out_2463845373694470231) {
   out_2463845373694470231[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5604996866156577695) {
   out_5604996866156577695[0] = 1;
   out_5604996866156577695[1] = 0;
   out_5604996866156577695[2] = 0;
   out_5604996866156577695[3] = 0;
   out_5604996866156577695[4] = 0;
   out_5604996866156577695[5] = 0;
   out_5604996866156577695[6] = 0;
   out_5604996866156577695[7] = 0;
   out_5604996866156577695[8] = 0;
}
void h_31(double *state, double *unused, double *out_4324439413990751749) {
   out_4324439413990751749[0] = state[8];
}
void H_31(double *state, double *unused, double *out_872844284381238807) {
   out_872844284381238807[0] = 0;
   out_872844284381238807[1] = 0;
   out_872844284381238807[2] = 0;
   out_872844284381238807[3] = 0;
   out_872844284381238807[4] = 0;
   out_872844284381238807[5] = 0;
   out_872844284381238807[6] = 0;
   out_872844284381238807[7] = 0;
   out_872844284381238807[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6552679409720063083) {
  err_fun(nom_x, delta_x, out_6552679409720063083);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_375450875847608461) {
  inv_err_fun(nom_x, true_x, out_375450875847608461);
}
void car_H_mod_fun(double *state, double *out_8454853977093352772) {
  H_mod_fun(state, out_8454853977093352772);
}
void car_f_fun(double *state, double dt, double *out_992240007066989833) {
  f_fun(state,  dt, out_992240007066989833);
}
void car_F_fun(double *state, double dt, double *out_6632803905489520127) {
  F_fun(state,  dt, out_6632803905489520127);
}
void car_h_25(double *state, double *unused, double *out_1516450530651524889) {
  h_25(state, unused, out_1516450530651524889);
}
void car_H_25(double *state, double *unused, double *out_3551162151908687932) {
  H_25(state, unused, out_3551162151908687932);
}
void car_h_24(double *state, double *unused, double *out_4218575999364657751) {
  h_24(state, unused, out_4218575999364657751);
}
void car_H_24(double *state, double *unused, double *out_1373947728301537959) {
  H_24(state, unused, out_1373947728301537959);
}
void car_h_30(double *state, double *unused, double *out_6376488964232998470) {
  h_30(state, unused, out_6376488964232998470);
}
void car_H_30(double *state, double *unused, double *out_1032829193401439305) {
  H_30(state, unused, out_1032829193401439305);
}
void car_h_26(double *state, double *unused, double *out_8794407296729096557) {
  h_26(state, unused, out_8794407296729096557);
}
void car_H_26(double *state, double *unused, double *out_246636182147887331) {
  H_26(state, unused, out_246636182147887331);
}
void car_h_27(double *state, double *unused, double *out_3221695518855289041) {
  h_27(state, unused, out_3221695518855289041);
}
void car_H_27(double *state, double *unused, double *out_3207592505201864216) {
  H_27(state, unused, out_3207592505201864216);
}
void car_h_29(double *state, double *unused, double *out_5671213592062704000) {
  h_29(state, unused, out_5671213592062704000);
}
void car_H_29(double *state, double *unused, double *out_522597849087047121) {
  H_29(state, unused, out_522597849087047121);
}
void car_h_28(double *state, double *unused, double *out_2463845373694470231) {
  h_28(state, unused, out_2463845373694470231);
}
void car_H_28(double *state, double *unused, double *out_5604996866156577695) {
  H_28(state, unused, out_5604996866156577695);
}
void car_h_31(double *state, double *unused, double *out_4324439413990751749) {
  h_31(state, unused, out_4324439413990751749);
}
void car_H_31(double *state, double *unused, double *out_872844284381238807) {
  H_31(state, unused, out_872844284381238807);
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
