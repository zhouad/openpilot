#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3271959735080300269) {
   out_3271959735080300269[0] = delta_x[0] + nom_x[0];
   out_3271959735080300269[1] = delta_x[1] + nom_x[1];
   out_3271959735080300269[2] = delta_x[2] + nom_x[2];
   out_3271959735080300269[3] = delta_x[3] + nom_x[3];
   out_3271959735080300269[4] = delta_x[4] + nom_x[4];
   out_3271959735080300269[5] = delta_x[5] + nom_x[5];
   out_3271959735080300269[6] = delta_x[6] + nom_x[6];
   out_3271959735080300269[7] = delta_x[7] + nom_x[7];
   out_3271959735080300269[8] = delta_x[8] + nom_x[8];
   out_3271959735080300269[9] = delta_x[9] + nom_x[9];
   out_3271959735080300269[10] = delta_x[10] + nom_x[10];
   out_3271959735080300269[11] = delta_x[11] + nom_x[11];
   out_3271959735080300269[12] = delta_x[12] + nom_x[12];
   out_3271959735080300269[13] = delta_x[13] + nom_x[13];
   out_3271959735080300269[14] = delta_x[14] + nom_x[14];
   out_3271959735080300269[15] = delta_x[15] + nom_x[15];
   out_3271959735080300269[16] = delta_x[16] + nom_x[16];
   out_3271959735080300269[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7212079695949744902) {
   out_7212079695949744902[0] = -nom_x[0] + true_x[0];
   out_7212079695949744902[1] = -nom_x[1] + true_x[1];
   out_7212079695949744902[2] = -nom_x[2] + true_x[2];
   out_7212079695949744902[3] = -nom_x[3] + true_x[3];
   out_7212079695949744902[4] = -nom_x[4] + true_x[4];
   out_7212079695949744902[5] = -nom_x[5] + true_x[5];
   out_7212079695949744902[6] = -nom_x[6] + true_x[6];
   out_7212079695949744902[7] = -nom_x[7] + true_x[7];
   out_7212079695949744902[8] = -nom_x[8] + true_x[8];
   out_7212079695949744902[9] = -nom_x[9] + true_x[9];
   out_7212079695949744902[10] = -nom_x[10] + true_x[10];
   out_7212079695949744902[11] = -nom_x[11] + true_x[11];
   out_7212079695949744902[12] = -nom_x[12] + true_x[12];
   out_7212079695949744902[13] = -nom_x[13] + true_x[13];
   out_7212079695949744902[14] = -nom_x[14] + true_x[14];
   out_7212079695949744902[15] = -nom_x[15] + true_x[15];
   out_7212079695949744902[16] = -nom_x[16] + true_x[16];
   out_7212079695949744902[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5997326193381454730) {
   out_5997326193381454730[0] = 1.0;
   out_5997326193381454730[1] = 0.0;
   out_5997326193381454730[2] = 0.0;
   out_5997326193381454730[3] = 0.0;
   out_5997326193381454730[4] = 0.0;
   out_5997326193381454730[5] = 0.0;
   out_5997326193381454730[6] = 0.0;
   out_5997326193381454730[7] = 0.0;
   out_5997326193381454730[8] = 0.0;
   out_5997326193381454730[9] = 0.0;
   out_5997326193381454730[10] = 0.0;
   out_5997326193381454730[11] = 0.0;
   out_5997326193381454730[12] = 0.0;
   out_5997326193381454730[13] = 0.0;
   out_5997326193381454730[14] = 0.0;
   out_5997326193381454730[15] = 0.0;
   out_5997326193381454730[16] = 0.0;
   out_5997326193381454730[17] = 0.0;
   out_5997326193381454730[18] = 0.0;
   out_5997326193381454730[19] = 1.0;
   out_5997326193381454730[20] = 0.0;
   out_5997326193381454730[21] = 0.0;
   out_5997326193381454730[22] = 0.0;
   out_5997326193381454730[23] = 0.0;
   out_5997326193381454730[24] = 0.0;
   out_5997326193381454730[25] = 0.0;
   out_5997326193381454730[26] = 0.0;
   out_5997326193381454730[27] = 0.0;
   out_5997326193381454730[28] = 0.0;
   out_5997326193381454730[29] = 0.0;
   out_5997326193381454730[30] = 0.0;
   out_5997326193381454730[31] = 0.0;
   out_5997326193381454730[32] = 0.0;
   out_5997326193381454730[33] = 0.0;
   out_5997326193381454730[34] = 0.0;
   out_5997326193381454730[35] = 0.0;
   out_5997326193381454730[36] = 0.0;
   out_5997326193381454730[37] = 0.0;
   out_5997326193381454730[38] = 1.0;
   out_5997326193381454730[39] = 0.0;
   out_5997326193381454730[40] = 0.0;
   out_5997326193381454730[41] = 0.0;
   out_5997326193381454730[42] = 0.0;
   out_5997326193381454730[43] = 0.0;
   out_5997326193381454730[44] = 0.0;
   out_5997326193381454730[45] = 0.0;
   out_5997326193381454730[46] = 0.0;
   out_5997326193381454730[47] = 0.0;
   out_5997326193381454730[48] = 0.0;
   out_5997326193381454730[49] = 0.0;
   out_5997326193381454730[50] = 0.0;
   out_5997326193381454730[51] = 0.0;
   out_5997326193381454730[52] = 0.0;
   out_5997326193381454730[53] = 0.0;
   out_5997326193381454730[54] = 0.0;
   out_5997326193381454730[55] = 0.0;
   out_5997326193381454730[56] = 0.0;
   out_5997326193381454730[57] = 1.0;
   out_5997326193381454730[58] = 0.0;
   out_5997326193381454730[59] = 0.0;
   out_5997326193381454730[60] = 0.0;
   out_5997326193381454730[61] = 0.0;
   out_5997326193381454730[62] = 0.0;
   out_5997326193381454730[63] = 0.0;
   out_5997326193381454730[64] = 0.0;
   out_5997326193381454730[65] = 0.0;
   out_5997326193381454730[66] = 0.0;
   out_5997326193381454730[67] = 0.0;
   out_5997326193381454730[68] = 0.0;
   out_5997326193381454730[69] = 0.0;
   out_5997326193381454730[70] = 0.0;
   out_5997326193381454730[71] = 0.0;
   out_5997326193381454730[72] = 0.0;
   out_5997326193381454730[73] = 0.0;
   out_5997326193381454730[74] = 0.0;
   out_5997326193381454730[75] = 0.0;
   out_5997326193381454730[76] = 1.0;
   out_5997326193381454730[77] = 0.0;
   out_5997326193381454730[78] = 0.0;
   out_5997326193381454730[79] = 0.0;
   out_5997326193381454730[80] = 0.0;
   out_5997326193381454730[81] = 0.0;
   out_5997326193381454730[82] = 0.0;
   out_5997326193381454730[83] = 0.0;
   out_5997326193381454730[84] = 0.0;
   out_5997326193381454730[85] = 0.0;
   out_5997326193381454730[86] = 0.0;
   out_5997326193381454730[87] = 0.0;
   out_5997326193381454730[88] = 0.0;
   out_5997326193381454730[89] = 0.0;
   out_5997326193381454730[90] = 0.0;
   out_5997326193381454730[91] = 0.0;
   out_5997326193381454730[92] = 0.0;
   out_5997326193381454730[93] = 0.0;
   out_5997326193381454730[94] = 0.0;
   out_5997326193381454730[95] = 1.0;
   out_5997326193381454730[96] = 0.0;
   out_5997326193381454730[97] = 0.0;
   out_5997326193381454730[98] = 0.0;
   out_5997326193381454730[99] = 0.0;
   out_5997326193381454730[100] = 0.0;
   out_5997326193381454730[101] = 0.0;
   out_5997326193381454730[102] = 0.0;
   out_5997326193381454730[103] = 0.0;
   out_5997326193381454730[104] = 0.0;
   out_5997326193381454730[105] = 0.0;
   out_5997326193381454730[106] = 0.0;
   out_5997326193381454730[107] = 0.0;
   out_5997326193381454730[108] = 0.0;
   out_5997326193381454730[109] = 0.0;
   out_5997326193381454730[110] = 0.0;
   out_5997326193381454730[111] = 0.0;
   out_5997326193381454730[112] = 0.0;
   out_5997326193381454730[113] = 0.0;
   out_5997326193381454730[114] = 1.0;
   out_5997326193381454730[115] = 0.0;
   out_5997326193381454730[116] = 0.0;
   out_5997326193381454730[117] = 0.0;
   out_5997326193381454730[118] = 0.0;
   out_5997326193381454730[119] = 0.0;
   out_5997326193381454730[120] = 0.0;
   out_5997326193381454730[121] = 0.0;
   out_5997326193381454730[122] = 0.0;
   out_5997326193381454730[123] = 0.0;
   out_5997326193381454730[124] = 0.0;
   out_5997326193381454730[125] = 0.0;
   out_5997326193381454730[126] = 0.0;
   out_5997326193381454730[127] = 0.0;
   out_5997326193381454730[128] = 0.0;
   out_5997326193381454730[129] = 0.0;
   out_5997326193381454730[130] = 0.0;
   out_5997326193381454730[131] = 0.0;
   out_5997326193381454730[132] = 0.0;
   out_5997326193381454730[133] = 1.0;
   out_5997326193381454730[134] = 0.0;
   out_5997326193381454730[135] = 0.0;
   out_5997326193381454730[136] = 0.0;
   out_5997326193381454730[137] = 0.0;
   out_5997326193381454730[138] = 0.0;
   out_5997326193381454730[139] = 0.0;
   out_5997326193381454730[140] = 0.0;
   out_5997326193381454730[141] = 0.0;
   out_5997326193381454730[142] = 0.0;
   out_5997326193381454730[143] = 0.0;
   out_5997326193381454730[144] = 0.0;
   out_5997326193381454730[145] = 0.0;
   out_5997326193381454730[146] = 0.0;
   out_5997326193381454730[147] = 0.0;
   out_5997326193381454730[148] = 0.0;
   out_5997326193381454730[149] = 0.0;
   out_5997326193381454730[150] = 0.0;
   out_5997326193381454730[151] = 0.0;
   out_5997326193381454730[152] = 1.0;
   out_5997326193381454730[153] = 0.0;
   out_5997326193381454730[154] = 0.0;
   out_5997326193381454730[155] = 0.0;
   out_5997326193381454730[156] = 0.0;
   out_5997326193381454730[157] = 0.0;
   out_5997326193381454730[158] = 0.0;
   out_5997326193381454730[159] = 0.0;
   out_5997326193381454730[160] = 0.0;
   out_5997326193381454730[161] = 0.0;
   out_5997326193381454730[162] = 0.0;
   out_5997326193381454730[163] = 0.0;
   out_5997326193381454730[164] = 0.0;
   out_5997326193381454730[165] = 0.0;
   out_5997326193381454730[166] = 0.0;
   out_5997326193381454730[167] = 0.0;
   out_5997326193381454730[168] = 0.0;
   out_5997326193381454730[169] = 0.0;
   out_5997326193381454730[170] = 0.0;
   out_5997326193381454730[171] = 1.0;
   out_5997326193381454730[172] = 0.0;
   out_5997326193381454730[173] = 0.0;
   out_5997326193381454730[174] = 0.0;
   out_5997326193381454730[175] = 0.0;
   out_5997326193381454730[176] = 0.0;
   out_5997326193381454730[177] = 0.0;
   out_5997326193381454730[178] = 0.0;
   out_5997326193381454730[179] = 0.0;
   out_5997326193381454730[180] = 0.0;
   out_5997326193381454730[181] = 0.0;
   out_5997326193381454730[182] = 0.0;
   out_5997326193381454730[183] = 0.0;
   out_5997326193381454730[184] = 0.0;
   out_5997326193381454730[185] = 0.0;
   out_5997326193381454730[186] = 0.0;
   out_5997326193381454730[187] = 0.0;
   out_5997326193381454730[188] = 0.0;
   out_5997326193381454730[189] = 0.0;
   out_5997326193381454730[190] = 1.0;
   out_5997326193381454730[191] = 0.0;
   out_5997326193381454730[192] = 0.0;
   out_5997326193381454730[193] = 0.0;
   out_5997326193381454730[194] = 0.0;
   out_5997326193381454730[195] = 0.0;
   out_5997326193381454730[196] = 0.0;
   out_5997326193381454730[197] = 0.0;
   out_5997326193381454730[198] = 0.0;
   out_5997326193381454730[199] = 0.0;
   out_5997326193381454730[200] = 0.0;
   out_5997326193381454730[201] = 0.0;
   out_5997326193381454730[202] = 0.0;
   out_5997326193381454730[203] = 0.0;
   out_5997326193381454730[204] = 0.0;
   out_5997326193381454730[205] = 0.0;
   out_5997326193381454730[206] = 0.0;
   out_5997326193381454730[207] = 0.0;
   out_5997326193381454730[208] = 0.0;
   out_5997326193381454730[209] = 1.0;
   out_5997326193381454730[210] = 0.0;
   out_5997326193381454730[211] = 0.0;
   out_5997326193381454730[212] = 0.0;
   out_5997326193381454730[213] = 0.0;
   out_5997326193381454730[214] = 0.0;
   out_5997326193381454730[215] = 0.0;
   out_5997326193381454730[216] = 0.0;
   out_5997326193381454730[217] = 0.0;
   out_5997326193381454730[218] = 0.0;
   out_5997326193381454730[219] = 0.0;
   out_5997326193381454730[220] = 0.0;
   out_5997326193381454730[221] = 0.0;
   out_5997326193381454730[222] = 0.0;
   out_5997326193381454730[223] = 0.0;
   out_5997326193381454730[224] = 0.0;
   out_5997326193381454730[225] = 0.0;
   out_5997326193381454730[226] = 0.0;
   out_5997326193381454730[227] = 0.0;
   out_5997326193381454730[228] = 1.0;
   out_5997326193381454730[229] = 0.0;
   out_5997326193381454730[230] = 0.0;
   out_5997326193381454730[231] = 0.0;
   out_5997326193381454730[232] = 0.0;
   out_5997326193381454730[233] = 0.0;
   out_5997326193381454730[234] = 0.0;
   out_5997326193381454730[235] = 0.0;
   out_5997326193381454730[236] = 0.0;
   out_5997326193381454730[237] = 0.0;
   out_5997326193381454730[238] = 0.0;
   out_5997326193381454730[239] = 0.0;
   out_5997326193381454730[240] = 0.0;
   out_5997326193381454730[241] = 0.0;
   out_5997326193381454730[242] = 0.0;
   out_5997326193381454730[243] = 0.0;
   out_5997326193381454730[244] = 0.0;
   out_5997326193381454730[245] = 0.0;
   out_5997326193381454730[246] = 0.0;
   out_5997326193381454730[247] = 1.0;
   out_5997326193381454730[248] = 0.0;
   out_5997326193381454730[249] = 0.0;
   out_5997326193381454730[250] = 0.0;
   out_5997326193381454730[251] = 0.0;
   out_5997326193381454730[252] = 0.0;
   out_5997326193381454730[253] = 0.0;
   out_5997326193381454730[254] = 0.0;
   out_5997326193381454730[255] = 0.0;
   out_5997326193381454730[256] = 0.0;
   out_5997326193381454730[257] = 0.0;
   out_5997326193381454730[258] = 0.0;
   out_5997326193381454730[259] = 0.0;
   out_5997326193381454730[260] = 0.0;
   out_5997326193381454730[261] = 0.0;
   out_5997326193381454730[262] = 0.0;
   out_5997326193381454730[263] = 0.0;
   out_5997326193381454730[264] = 0.0;
   out_5997326193381454730[265] = 0.0;
   out_5997326193381454730[266] = 1.0;
   out_5997326193381454730[267] = 0.0;
   out_5997326193381454730[268] = 0.0;
   out_5997326193381454730[269] = 0.0;
   out_5997326193381454730[270] = 0.0;
   out_5997326193381454730[271] = 0.0;
   out_5997326193381454730[272] = 0.0;
   out_5997326193381454730[273] = 0.0;
   out_5997326193381454730[274] = 0.0;
   out_5997326193381454730[275] = 0.0;
   out_5997326193381454730[276] = 0.0;
   out_5997326193381454730[277] = 0.0;
   out_5997326193381454730[278] = 0.0;
   out_5997326193381454730[279] = 0.0;
   out_5997326193381454730[280] = 0.0;
   out_5997326193381454730[281] = 0.0;
   out_5997326193381454730[282] = 0.0;
   out_5997326193381454730[283] = 0.0;
   out_5997326193381454730[284] = 0.0;
   out_5997326193381454730[285] = 1.0;
   out_5997326193381454730[286] = 0.0;
   out_5997326193381454730[287] = 0.0;
   out_5997326193381454730[288] = 0.0;
   out_5997326193381454730[289] = 0.0;
   out_5997326193381454730[290] = 0.0;
   out_5997326193381454730[291] = 0.0;
   out_5997326193381454730[292] = 0.0;
   out_5997326193381454730[293] = 0.0;
   out_5997326193381454730[294] = 0.0;
   out_5997326193381454730[295] = 0.0;
   out_5997326193381454730[296] = 0.0;
   out_5997326193381454730[297] = 0.0;
   out_5997326193381454730[298] = 0.0;
   out_5997326193381454730[299] = 0.0;
   out_5997326193381454730[300] = 0.0;
   out_5997326193381454730[301] = 0.0;
   out_5997326193381454730[302] = 0.0;
   out_5997326193381454730[303] = 0.0;
   out_5997326193381454730[304] = 1.0;
   out_5997326193381454730[305] = 0.0;
   out_5997326193381454730[306] = 0.0;
   out_5997326193381454730[307] = 0.0;
   out_5997326193381454730[308] = 0.0;
   out_5997326193381454730[309] = 0.0;
   out_5997326193381454730[310] = 0.0;
   out_5997326193381454730[311] = 0.0;
   out_5997326193381454730[312] = 0.0;
   out_5997326193381454730[313] = 0.0;
   out_5997326193381454730[314] = 0.0;
   out_5997326193381454730[315] = 0.0;
   out_5997326193381454730[316] = 0.0;
   out_5997326193381454730[317] = 0.0;
   out_5997326193381454730[318] = 0.0;
   out_5997326193381454730[319] = 0.0;
   out_5997326193381454730[320] = 0.0;
   out_5997326193381454730[321] = 0.0;
   out_5997326193381454730[322] = 0.0;
   out_5997326193381454730[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6861504228684851862) {
   out_6861504228684851862[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6861504228684851862[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6861504228684851862[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6861504228684851862[3] = dt*state[12] + state[3];
   out_6861504228684851862[4] = dt*state[13] + state[4];
   out_6861504228684851862[5] = dt*state[14] + state[5];
   out_6861504228684851862[6] = state[6];
   out_6861504228684851862[7] = state[7];
   out_6861504228684851862[8] = state[8];
   out_6861504228684851862[9] = state[9];
   out_6861504228684851862[10] = state[10];
   out_6861504228684851862[11] = state[11];
   out_6861504228684851862[12] = state[12];
   out_6861504228684851862[13] = state[13];
   out_6861504228684851862[14] = state[14];
   out_6861504228684851862[15] = state[15];
   out_6861504228684851862[16] = state[16];
   out_6861504228684851862[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7588529982742305973) {
   out_7588529982742305973[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7588529982742305973[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7588529982742305973[2] = 0;
   out_7588529982742305973[3] = 0;
   out_7588529982742305973[4] = 0;
   out_7588529982742305973[5] = 0;
   out_7588529982742305973[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7588529982742305973[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7588529982742305973[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7588529982742305973[9] = 0;
   out_7588529982742305973[10] = 0;
   out_7588529982742305973[11] = 0;
   out_7588529982742305973[12] = 0;
   out_7588529982742305973[13] = 0;
   out_7588529982742305973[14] = 0;
   out_7588529982742305973[15] = 0;
   out_7588529982742305973[16] = 0;
   out_7588529982742305973[17] = 0;
   out_7588529982742305973[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7588529982742305973[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7588529982742305973[20] = 0;
   out_7588529982742305973[21] = 0;
   out_7588529982742305973[22] = 0;
   out_7588529982742305973[23] = 0;
   out_7588529982742305973[24] = 0;
   out_7588529982742305973[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7588529982742305973[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7588529982742305973[27] = 0;
   out_7588529982742305973[28] = 0;
   out_7588529982742305973[29] = 0;
   out_7588529982742305973[30] = 0;
   out_7588529982742305973[31] = 0;
   out_7588529982742305973[32] = 0;
   out_7588529982742305973[33] = 0;
   out_7588529982742305973[34] = 0;
   out_7588529982742305973[35] = 0;
   out_7588529982742305973[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7588529982742305973[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7588529982742305973[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7588529982742305973[39] = 0;
   out_7588529982742305973[40] = 0;
   out_7588529982742305973[41] = 0;
   out_7588529982742305973[42] = 0;
   out_7588529982742305973[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7588529982742305973[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7588529982742305973[45] = 0;
   out_7588529982742305973[46] = 0;
   out_7588529982742305973[47] = 0;
   out_7588529982742305973[48] = 0;
   out_7588529982742305973[49] = 0;
   out_7588529982742305973[50] = 0;
   out_7588529982742305973[51] = 0;
   out_7588529982742305973[52] = 0;
   out_7588529982742305973[53] = 0;
   out_7588529982742305973[54] = 0;
   out_7588529982742305973[55] = 0;
   out_7588529982742305973[56] = 0;
   out_7588529982742305973[57] = 1;
   out_7588529982742305973[58] = 0;
   out_7588529982742305973[59] = 0;
   out_7588529982742305973[60] = 0;
   out_7588529982742305973[61] = 0;
   out_7588529982742305973[62] = 0;
   out_7588529982742305973[63] = 0;
   out_7588529982742305973[64] = 0;
   out_7588529982742305973[65] = 0;
   out_7588529982742305973[66] = dt;
   out_7588529982742305973[67] = 0;
   out_7588529982742305973[68] = 0;
   out_7588529982742305973[69] = 0;
   out_7588529982742305973[70] = 0;
   out_7588529982742305973[71] = 0;
   out_7588529982742305973[72] = 0;
   out_7588529982742305973[73] = 0;
   out_7588529982742305973[74] = 0;
   out_7588529982742305973[75] = 0;
   out_7588529982742305973[76] = 1;
   out_7588529982742305973[77] = 0;
   out_7588529982742305973[78] = 0;
   out_7588529982742305973[79] = 0;
   out_7588529982742305973[80] = 0;
   out_7588529982742305973[81] = 0;
   out_7588529982742305973[82] = 0;
   out_7588529982742305973[83] = 0;
   out_7588529982742305973[84] = 0;
   out_7588529982742305973[85] = dt;
   out_7588529982742305973[86] = 0;
   out_7588529982742305973[87] = 0;
   out_7588529982742305973[88] = 0;
   out_7588529982742305973[89] = 0;
   out_7588529982742305973[90] = 0;
   out_7588529982742305973[91] = 0;
   out_7588529982742305973[92] = 0;
   out_7588529982742305973[93] = 0;
   out_7588529982742305973[94] = 0;
   out_7588529982742305973[95] = 1;
   out_7588529982742305973[96] = 0;
   out_7588529982742305973[97] = 0;
   out_7588529982742305973[98] = 0;
   out_7588529982742305973[99] = 0;
   out_7588529982742305973[100] = 0;
   out_7588529982742305973[101] = 0;
   out_7588529982742305973[102] = 0;
   out_7588529982742305973[103] = 0;
   out_7588529982742305973[104] = dt;
   out_7588529982742305973[105] = 0;
   out_7588529982742305973[106] = 0;
   out_7588529982742305973[107] = 0;
   out_7588529982742305973[108] = 0;
   out_7588529982742305973[109] = 0;
   out_7588529982742305973[110] = 0;
   out_7588529982742305973[111] = 0;
   out_7588529982742305973[112] = 0;
   out_7588529982742305973[113] = 0;
   out_7588529982742305973[114] = 1;
   out_7588529982742305973[115] = 0;
   out_7588529982742305973[116] = 0;
   out_7588529982742305973[117] = 0;
   out_7588529982742305973[118] = 0;
   out_7588529982742305973[119] = 0;
   out_7588529982742305973[120] = 0;
   out_7588529982742305973[121] = 0;
   out_7588529982742305973[122] = 0;
   out_7588529982742305973[123] = 0;
   out_7588529982742305973[124] = 0;
   out_7588529982742305973[125] = 0;
   out_7588529982742305973[126] = 0;
   out_7588529982742305973[127] = 0;
   out_7588529982742305973[128] = 0;
   out_7588529982742305973[129] = 0;
   out_7588529982742305973[130] = 0;
   out_7588529982742305973[131] = 0;
   out_7588529982742305973[132] = 0;
   out_7588529982742305973[133] = 1;
   out_7588529982742305973[134] = 0;
   out_7588529982742305973[135] = 0;
   out_7588529982742305973[136] = 0;
   out_7588529982742305973[137] = 0;
   out_7588529982742305973[138] = 0;
   out_7588529982742305973[139] = 0;
   out_7588529982742305973[140] = 0;
   out_7588529982742305973[141] = 0;
   out_7588529982742305973[142] = 0;
   out_7588529982742305973[143] = 0;
   out_7588529982742305973[144] = 0;
   out_7588529982742305973[145] = 0;
   out_7588529982742305973[146] = 0;
   out_7588529982742305973[147] = 0;
   out_7588529982742305973[148] = 0;
   out_7588529982742305973[149] = 0;
   out_7588529982742305973[150] = 0;
   out_7588529982742305973[151] = 0;
   out_7588529982742305973[152] = 1;
   out_7588529982742305973[153] = 0;
   out_7588529982742305973[154] = 0;
   out_7588529982742305973[155] = 0;
   out_7588529982742305973[156] = 0;
   out_7588529982742305973[157] = 0;
   out_7588529982742305973[158] = 0;
   out_7588529982742305973[159] = 0;
   out_7588529982742305973[160] = 0;
   out_7588529982742305973[161] = 0;
   out_7588529982742305973[162] = 0;
   out_7588529982742305973[163] = 0;
   out_7588529982742305973[164] = 0;
   out_7588529982742305973[165] = 0;
   out_7588529982742305973[166] = 0;
   out_7588529982742305973[167] = 0;
   out_7588529982742305973[168] = 0;
   out_7588529982742305973[169] = 0;
   out_7588529982742305973[170] = 0;
   out_7588529982742305973[171] = 1;
   out_7588529982742305973[172] = 0;
   out_7588529982742305973[173] = 0;
   out_7588529982742305973[174] = 0;
   out_7588529982742305973[175] = 0;
   out_7588529982742305973[176] = 0;
   out_7588529982742305973[177] = 0;
   out_7588529982742305973[178] = 0;
   out_7588529982742305973[179] = 0;
   out_7588529982742305973[180] = 0;
   out_7588529982742305973[181] = 0;
   out_7588529982742305973[182] = 0;
   out_7588529982742305973[183] = 0;
   out_7588529982742305973[184] = 0;
   out_7588529982742305973[185] = 0;
   out_7588529982742305973[186] = 0;
   out_7588529982742305973[187] = 0;
   out_7588529982742305973[188] = 0;
   out_7588529982742305973[189] = 0;
   out_7588529982742305973[190] = 1;
   out_7588529982742305973[191] = 0;
   out_7588529982742305973[192] = 0;
   out_7588529982742305973[193] = 0;
   out_7588529982742305973[194] = 0;
   out_7588529982742305973[195] = 0;
   out_7588529982742305973[196] = 0;
   out_7588529982742305973[197] = 0;
   out_7588529982742305973[198] = 0;
   out_7588529982742305973[199] = 0;
   out_7588529982742305973[200] = 0;
   out_7588529982742305973[201] = 0;
   out_7588529982742305973[202] = 0;
   out_7588529982742305973[203] = 0;
   out_7588529982742305973[204] = 0;
   out_7588529982742305973[205] = 0;
   out_7588529982742305973[206] = 0;
   out_7588529982742305973[207] = 0;
   out_7588529982742305973[208] = 0;
   out_7588529982742305973[209] = 1;
   out_7588529982742305973[210] = 0;
   out_7588529982742305973[211] = 0;
   out_7588529982742305973[212] = 0;
   out_7588529982742305973[213] = 0;
   out_7588529982742305973[214] = 0;
   out_7588529982742305973[215] = 0;
   out_7588529982742305973[216] = 0;
   out_7588529982742305973[217] = 0;
   out_7588529982742305973[218] = 0;
   out_7588529982742305973[219] = 0;
   out_7588529982742305973[220] = 0;
   out_7588529982742305973[221] = 0;
   out_7588529982742305973[222] = 0;
   out_7588529982742305973[223] = 0;
   out_7588529982742305973[224] = 0;
   out_7588529982742305973[225] = 0;
   out_7588529982742305973[226] = 0;
   out_7588529982742305973[227] = 0;
   out_7588529982742305973[228] = 1;
   out_7588529982742305973[229] = 0;
   out_7588529982742305973[230] = 0;
   out_7588529982742305973[231] = 0;
   out_7588529982742305973[232] = 0;
   out_7588529982742305973[233] = 0;
   out_7588529982742305973[234] = 0;
   out_7588529982742305973[235] = 0;
   out_7588529982742305973[236] = 0;
   out_7588529982742305973[237] = 0;
   out_7588529982742305973[238] = 0;
   out_7588529982742305973[239] = 0;
   out_7588529982742305973[240] = 0;
   out_7588529982742305973[241] = 0;
   out_7588529982742305973[242] = 0;
   out_7588529982742305973[243] = 0;
   out_7588529982742305973[244] = 0;
   out_7588529982742305973[245] = 0;
   out_7588529982742305973[246] = 0;
   out_7588529982742305973[247] = 1;
   out_7588529982742305973[248] = 0;
   out_7588529982742305973[249] = 0;
   out_7588529982742305973[250] = 0;
   out_7588529982742305973[251] = 0;
   out_7588529982742305973[252] = 0;
   out_7588529982742305973[253] = 0;
   out_7588529982742305973[254] = 0;
   out_7588529982742305973[255] = 0;
   out_7588529982742305973[256] = 0;
   out_7588529982742305973[257] = 0;
   out_7588529982742305973[258] = 0;
   out_7588529982742305973[259] = 0;
   out_7588529982742305973[260] = 0;
   out_7588529982742305973[261] = 0;
   out_7588529982742305973[262] = 0;
   out_7588529982742305973[263] = 0;
   out_7588529982742305973[264] = 0;
   out_7588529982742305973[265] = 0;
   out_7588529982742305973[266] = 1;
   out_7588529982742305973[267] = 0;
   out_7588529982742305973[268] = 0;
   out_7588529982742305973[269] = 0;
   out_7588529982742305973[270] = 0;
   out_7588529982742305973[271] = 0;
   out_7588529982742305973[272] = 0;
   out_7588529982742305973[273] = 0;
   out_7588529982742305973[274] = 0;
   out_7588529982742305973[275] = 0;
   out_7588529982742305973[276] = 0;
   out_7588529982742305973[277] = 0;
   out_7588529982742305973[278] = 0;
   out_7588529982742305973[279] = 0;
   out_7588529982742305973[280] = 0;
   out_7588529982742305973[281] = 0;
   out_7588529982742305973[282] = 0;
   out_7588529982742305973[283] = 0;
   out_7588529982742305973[284] = 0;
   out_7588529982742305973[285] = 1;
   out_7588529982742305973[286] = 0;
   out_7588529982742305973[287] = 0;
   out_7588529982742305973[288] = 0;
   out_7588529982742305973[289] = 0;
   out_7588529982742305973[290] = 0;
   out_7588529982742305973[291] = 0;
   out_7588529982742305973[292] = 0;
   out_7588529982742305973[293] = 0;
   out_7588529982742305973[294] = 0;
   out_7588529982742305973[295] = 0;
   out_7588529982742305973[296] = 0;
   out_7588529982742305973[297] = 0;
   out_7588529982742305973[298] = 0;
   out_7588529982742305973[299] = 0;
   out_7588529982742305973[300] = 0;
   out_7588529982742305973[301] = 0;
   out_7588529982742305973[302] = 0;
   out_7588529982742305973[303] = 0;
   out_7588529982742305973[304] = 1;
   out_7588529982742305973[305] = 0;
   out_7588529982742305973[306] = 0;
   out_7588529982742305973[307] = 0;
   out_7588529982742305973[308] = 0;
   out_7588529982742305973[309] = 0;
   out_7588529982742305973[310] = 0;
   out_7588529982742305973[311] = 0;
   out_7588529982742305973[312] = 0;
   out_7588529982742305973[313] = 0;
   out_7588529982742305973[314] = 0;
   out_7588529982742305973[315] = 0;
   out_7588529982742305973[316] = 0;
   out_7588529982742305973[317] = 0;
   out_7588529982742305973[318] = 0;
   out_7588529982742305973[319] = 0;
   out_7588529982742305973[320] = 0;
   out_7588529982742305973[321] = 0;
   out_7588529982742305973[322] = 0;
   out_7588529982742305973[323] = 1;
}
void h_4(double *state, double *unused, double *out_6699510873064443946) {
   out_6699510873064443946[0] = state[6] + state[9];
   out_6699510873064443946[1] = state[7] + state[10];
   out_6699510873064443946[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3505056214270275544) {
   out_3505056214270275544[0] = 0;
   out_3505056214270275544[1] = 0;
   out_3505056214270275544[2] = 0;
   out_3505056214270275544[3] = 0;
   out_3505056214270275544[4] = 0;
   out_3505056214270275544[5] = 0;
   out_3505056214270275544[6] = 1;
   out_3505056214270275544[7] = 0;
   out_3505056214270275544[8] = 0;
   out_3505056214270275544[9] = 1;
   out_3505056214270275544[10] = 0;
   out_3505056214270275544[11] = 0;
   out_3505056214270275544[12] = 0;
   out_3505056214270275544[13] = 0;
   out_3505056214270275544[14] = 0;
   out_3505056214270275544[15] = 0;
   out_3505056214270275544[16] = 0;
   out_3505056214270275544[17] = 0;
   out_3505056214270275544[18] = 0;
   out_3505056214270275544[19] = 0;
   out_3505056214270275544[20] = 0;
   out_3505056214270275544[21] = 0;
   out_3505056214270275544[22] = 0;
   out_3505056214270275544[23] = 0;
   out_3505056214270275544[24] = 0;
   out_3505056214270275544[25] = 1;
   out_3505056214270275544[26] = 0;
   out_3505056214270275544[27] = 0;
   out_3505056214270275544[28] = 1;
   out_3505056214270275544[29] = 0;
   out_3505056214270275544[30] = 0;
   out_3505056214270275544[31] = 0;
   out_3505056214270275544[32] = 0;
   out_3505056214270275544[33] = 0;
   out_3505056214270275544[34] = 0;
   out_3505056214270275544[35] = 0;
   out_3505056214270275544[36] = 0;
   out_3505056214270275544[37] = 0;
   out_3505056214270275544[38] = 0;
   out_3505056214270275544[39] = 0;
   out_3505056214270275544[40] = 0;
   out_3505056214270275544[41] = 0;
   out_3505056214270275544[42] = 0;
   out_3505056214270275544[43] = 0;
   out_3505056214270275544[44] = 1;
   out_3505056214270275544[45] = 0;
   out_3505056214270275544[46] = 0;
   out_3505056214270275544[47] = 1;
   out_3505056214270275544[48] = 0;
   out_3505056214270275544[49] = 0;
   out_3505056214270275544[50] = 0;
   out_3505056214270275544[51] = 0;
   out_3505056214270275544[52] = 0;
   out_3505056214270275544[53] = 0;
}
void h_10(double *state, double *unused, double *out_624795893851869901) {
   out_624795893851869901[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_624795893851869901[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_624795893851869901[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_703039798711493596) {
   out_703039798711493596[0] = 0;
   out_703039798711493596[1] = 9.8100000000000005*cos(state[1]);
   out_703039798711493596[2] = 0;
   out_703039798711493596[3] = 0;
   out_703039798711493596[4] = -state[8];
   out_703039798711493596[5] = state[7];
   out_703039798711493596[6] = 0;
   out_703039798711493596[7] = state[5];
   out_703039798711493596[8] = -state[4];
   out_703039798711493596[9] = 0;
   out_703039798711493596[10] = 0;
   out_703039798711493596[11] = 0;
   out_703039798711493596[12] = 1;
   out_703039798711493596[13] = 0;
   out_703039798711493596[14] = 0;
   out_703039798711493596[15] = 1;
   out_703039798711493596[16] = 0;
   out_703039798711493596[17] = 0;
   out_703039798711493596[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_703039798711493596[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_703039798711493596[20] = 0;
   out_703039798711493596[21] = state[8];
   out_703039798711493596[22] = 0;
   out_703039798711493596[23] = -state[6];
   out_703039798711493596[24] = -state[5];
   out_703039798711493596[25] = 0;
   out_703039798711493596[26] = state[3];
   out_703039798711493596[27] = 0;
   out_703039798711493596[28] = 0;
   out_703039798711493596[29] = 0;
   out_703039798711493596[30] = 0;
   out_703039798711493596[31] = 1;
   out_703039798711493596[32] = 0;
   out_703039798711493596[33] = 0;
   out_703039798711493596[34] = 1;
   out_703039798711493596[35] = 0;
   out_703039798711493596[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_703039798711493596[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_703039798711493596[38] = 0;
   out_703039798711493596[39] = -state[7];
   out_703039798711493596[40] = state[6];
   out_703039798711493596[41] = 0;
   out_703039798711493596[42] = state[4];
   out_703039798711493596[43] = -state[3];
   out_703039798711493596[44] = 0;
   out_703039798711493596[45] = 0;
   out_703039798711493596[46] = 0;
   out_703039798711493596[47] = 0;
   out_703039798711493596[48] = 0;
   out_703039798711493596[49] = 0;
   out_703039798711493596[50] = 1;
   out_703039798711493596[51] = 0;
   out_703039798711493596[52] = 0;
   out_703039798711493596[53] = 1;
}
void h_13(double *state, double *unused, double *out_3549684128180221096) {
   out_3549684128180221096[0] = state[3];
   out_3549684128180221096[1] = state[4];
   out_3549684128180221096[2] = state[5];
}
void H_13(double *state, double *unused, double *out_328699249032248480) {
   out_328699249032248480[0] = 0;
   out_328699249032248480[1] = 0;
   out_328699249032248480[2] = 0;
   out_328699249032248480[3] = 1;
   out_328699249032248480[4] = 0;
   out_328699249032248480[5] = 0;
   out_328699249032248480[6] = 0;
   out_328699249032248480[7] = 0;
   out_328699249032248480[8] = 0;
   out_328699249032248480[9] = 0;
   out_328699249032248480[10] = 0;
   out_328699249032248480[11] = 0;
   out_328699249032248480[12] = 0;
   out_328699249032248480[13] = 0;
   out_328699249032248480[14] = 0;
   out_328699249032248480[15] = 0;
   out_328699249032248480[16] = 0;
   out_328699249032248480[17] = 0;
   out_328699249032248480[18] = 0;
   out_328699249032248480[19] = 0;
   out_328699249032248480[20] = 0;
   out_328699249032248480[21] = 0;
   out_328699249032248480[22] = 1;
   out_328699249032248480[23] = 0;
   out_328699249032248480[24] = 0;
   out_328699249032248480[25] = 0;
   out_328699249032248480[26] = 0;
   out_328699249032248480[27] = 0;
   out_328699249032248480[28] = 0;
   out_328699249032248480[29] = 0;
   out_328699249032248480[30] = 0;
   out_328699249032248480[31] = 0;
   out_328699249032248480[32] = 0;
   out_328699249032248480[33] = 0;
   out_328699249032248480[34] = 0;
   out_328699249032248480[35] = 0;
   out_328699249032248480[36] = 0;
   out_328699249032248480[37] = 0;
   out_328699249032248480[38] = 0;
   out_328699249032248480[39] = 0;
   out_328699249032248480[40] = 0;
   out_328699249032248480[41] = 1;
   out_328699249032248480[42] = 0;
   out_328699249032248480[43] = 0;
   out_328699249032248480[44] = 0;
   out_328699249032248480[45] = 0;
   out_328699249032248480[46] = 0;
   out_328699249032248480[47] = 0;
   out_328699249032248480[48] = 0;
   out_328699249032248480[49] = 0;
   out_328699249032248480[50] = 0;
   out_328699249032248480[51] = 0;
   out_328699249032248480[52] = 0;
   out_328699249032248480[53] = 0;
}
void h_14(double *state, double *unused, double *out_7824739296360248187) {
   out_7824739296360248187[0] = state[6];
   out_7824739296360248187[1] = state[7];
   out_7824739296360248187[2] = state[8];
}
void H_14(double *state, double *unused, double *out_422267781974903248) {
   out_422267781974903248[0] = 0;
   out_422267781974903248[1] = 0;
   out_422267781974903248[2] = 0;
   out_422267781974903248[3] = 0;
   out_422267781974903248[4] = 0;
   out_422267781974903248[5] = 0;
   out_422267781974903248[6] = 1;
   out_422267781974903248[7] = 0;
   out_422267781974903248[8] = 0;
   out_422267781974903248[9] = 0;
   out_422267781974903248[10] = 0;
   out_422267781974903248[11] = 0;
   out_422267781974903248[12] = 0;
   out_422267781974903248[13] = 0;
   out_422267781974903248[14] = 0;
   out_422267781974903248[15] = 0;
   out_422267781974903248[16] = 0;
   out_422267781974903248[17] = 0;
   out_422267781974903248[18] = 0;
   out_422267781974903248[19] = 0;
   out_422267781974903248[20] = 0;
   out_422267781974903248[21] = 0;
   out_422267781974903248[22] = 0;
   out_422267781974903248[23] = 0;
   out_422267781974903248[24] = 0;
   out_422267781974903248[25] = 1;
   out_422267781974903248[26] = 0;
   out_422267781974903248[27] = 0;
   out_422267781974903248[28] = 0;
   out_422267781974903248[29] = 0;
   out_422267781974903248[30] = 0;
   out_422267781974903248[31] = 0;
   out_422267781974903248[32] = 0;
   out_422267781974903248[33] = 0;
   out_422267781974903248[34] = 0;
   out_422267781974903248[35] = 0;
   out_422267781974903248[36] = 0;
   out_422267781974903248[37] = 0;
   out_422267781974903248[38] = 0;
   out_422267781974903248[39] = 0;
   out_422267781974903248[40] = 0;
   out_422267781974903248[41] = 0;
   out_422267781974903248[42] = 0;
   out_422267781974903248[43] = 0;
   out_422267781974903248[44] = 1;
   out_422267781974903248[45] = 0;
   out_422267781974903248[46] = 0;
   out_422267781974903248[47] = 0;
   out_422267781974903248[48] = 0;
   out_422267781974903248[49] = 0;
   out_422267781974903248[50] = 0;
   out_422267781974903248[51] = 0;
   out_422267781974903248[52] = 0;
   out_422267781974903248[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3271959735080300269) {
  err_fun(nom_x, delta_x, out_3271959735080300269);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7212079695949744902) {
  inv_err_fun(nom_x, true_x, out_7212079695949744902);
}
void pose_H_mod_fun(double *state, double *out_5997326193381454730) {
  H_mod_fun(state, out_5997326193381454730);
}
void pose_f_fun(double *state, double dt, double *out_6861504228684851862) {
  f_fun(state,  dt, out_6861504228684851862);
}
void pose_F_fun(double *state, double dt, double *out_7588529982742305973) {
  F_fun(state,  dt, out_7588529982742305973);
}
void pose_h_4(double *state, double *unused, double *out_6699510873064443946) {
  h_4(state, unused, out_6699510873064443946);
}
void pose_H_4(double *state, double *unused, double *out_3505056214270275544) {
  H_4(state, unused, out_3505056214270275544);
}
void pose_h_10(double *state, double *unused, double *out_624795893851869901) {
  h_10(state, unused, out_624795893851869901);
}
void pose_H_10(double *state, double *unused, double *out_703039798711493596) {
  H_10(state, unused, out_703039798711493596);
}
void pose_h_13(double *state, double *unused, double *out_3549684128180221096) {
  h_13(state, unused, out_3549684128180221096);
}
void pose_H_13(double *state, double *unused, double *out_328699249032248480) {
  H_13(state, unused, out_328699249032248480);
}
void pose_h_14(double *state, double *unused, double *out_7824739296360248187) {
  h_14(state, unused, out_7824739296360248187);
}
void pose_H_14(double *state, double *unused, double *out_422267781974903248) {
  H_14(state, unused, out_422267781974903248);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
