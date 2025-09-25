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
void err_fun(double *nom_x, double *delta_x, double *out_8215112940017755867) {
   out_8215112940017755867[0] = delta_x[0] + nom_x[0];
   out_8215112940017755867[1] = delta_x[1] + nom_x[1];
   out_8215112940017755867[2] = delta_x[2] + nom_x[2];
   out_8215112940017755867[3] = delta_x[3] + nom_x[3];
   out_8215112940017755867[4] = delta_x[4] + nom_x[4];
   out_8215112940017755867[5] = delta_x[5] + nom_x[5];
   out_8215112940017755867[6] = delta_x[6] + nom_x[6];
   out_8215112940017755867[7] = delta_x[7] + nom_x[7];
   out_8215112940017755867[8] = delta_x[8] + nom_x[8];
   out_8215112940017755867[9] = delta_x[9] + nom_x[9];
   out_8215112940017755867[10] = delta_x[10] + nom_x[10];
   out_8215112940017755867[11] = delta_x[11] + nom_x[11];
   out_8215112940017755867[12] = delta_x[12] + nom_x[12];
   out_8215112940017755867[13] = delta_x[13] + nom_x[13];
   out_8215112940017755867[14] = delta_x[14] + nom_x[14];
   out_8215112940017755867[15] = delta_x[15] + nom_x[15];
   out_8215112940017755867[16] = delta_x[16] + nom_x[16];
   out_8215112940017755867[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1173819570397538874) {
   out_1173819570397538874[0] = -nom_x[0] + true_x[0];
   out_1173819570397538874[1] = -nom_x[1] + true_x[1];
   out_1173819570397538874[2] = -nom_x[2] + true_x[2];
   out_1173819570397538874[3] = -nom_x[3] + true_x[3];
   out_1173819570397538874[4] = -nom_x[4] + true_x[4];
   out_1173819570397538874[5] = -nom_x[5] + true_x[5];
   out_1173819570397538874[6] = -nom_x[6] + true_x[6];
   out_1173819570397538874[7] = -nom_x[7] + true_x[7];
   out_1173819570397538874[8] = -nom_x[8] + true_x[8];
   out_1173819570397538874[9] = -nom_x[9] + true_x[9];
   out_1173819570397538874[10] = -nom_x[10] + true_x[10];
   out_1173819570397538874[11] = -nom_x[11] + true_x[11];
   out_1173819570397538874[12] = -nom_x[12] + true_x[12];
   out_1173819570397538874[13] = -nom_x[13] + true_x[13];
   out_1173819570397538874[14] = -nom_x[14] + true_x[14];
   out_1173819570397538874[15] = -nom_x[15] + true_x[15];
   out_1173819570397538874[16] = -nom_x[16] + true_x[16];
   out_1173819570397538874[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8295691051147185807) {
   out_8295691051147185807[0] = 1.0;
   out_8295691051147185807[1] = 0.0;
   out_8295691051147185807[2] = 0.0;
   out_8295691051147185807[3] = 0.0;
   out_8295691051147185807[4] = 0.0;
   out_8295691051147185807[5] = 0.0;
   out_8295691051147185807[6] = 0.0;
   out_8295691051147185807[7] = 0.0;
   out_8295691051147185807[8] = 0.0;
   out_8295691051147185807[9] = 0.0;
   out_8295691051147185807[10] = 0.0;
   out_8295691051147185807[11] = 0.0;
   out_8295691051147185807[12] = 0.0;
   out_8295691051147185807[13] = 0.0;
   out_8295691051147185807[14] = 0.0;
   out_8295691051147185807[15] = 0.0;
   out_8295691051147185807[16] = 0.0;
   out_8295691051147185807[17] = 0.0;
   out_8295691051147185807[18] = 0.0;
   out_8295691051147185807[19] = 1.0;
   out_8295691051147185807[20] = 0.0;
   out_8295691051147185807[21] = 0.0;
   out_8295691051147185807[22] = 0.0;
   out_8295691051147185807[23] = 0.0;
   out_8295691051147185807[24] = 0.0;
   out_8295691051147185807[25] = 0.0;
   out_8295691051147185807[26] = 0.0;
   out_8295691051147185807[27] = 0.0;
   out_8295691051147185807[28] = 0.0;
   out_8295691051147185807[29] = 0.0;
   out_8295691051147185807[30] = 0.0;
   out_8295691051147185807[31] = 0.0;
   out_8295691051147185807[32] = 0.0;
   out_8295691051147185807[33] = 0.0;
   out_8295691051147185807[34] = 0.0;
   out_8295691051147185807[35] = 0.0;
   out_8295691051147185807[36] = 0.0;
   out_8295691051147185807[37] = 0.0;
   out_8295691051147185807[38] = 1.0;
   out_8295691051147185807[39] = 0.0;
   out_8295691051147185807[40] = 0.0;
   out_8295691051147185807[41] = 0.0;
   out_8295691051147185807[42] = 0.0;
   out_8295691051147185807[43] = 0.0;
   out_8295691051147185807[44] = 0.0;
   out_8295691051147185807[45] = 0.0;
   out_8295691051147185807[46] = 0.0;
   out_8295691051147185807[47] = 0.0;
   out_8295691051147185807[48] = 0.0;
   out_8295691051147185807[49] = 0.0;
   out_8295691051147185807[50] = 0.0;
   out_8295691051147185807[51] = 0.0;
   out_8295691051147185807[52] = 0.0;
   out_8295691051147185807[53] = 0.0;
   out_8295691051147185807[54] = 0.0;
   out_8295691051147185807[55] = 0.0;
   out_8295691051147185807[56] = 0.0;
   out_8295691051147185807[57] = 1.0;
   out_8295691051147185807[58] = 0.0;
   out_8295691051147185807[59] = 0.0;
   out_8295691051147185807[60] = 0.0;
   out_8295691051147185807[61] = 0.0;
   out_8295691051147185807[62] = 0.0;
   out_8295691051147185807[63] = 0.0;
   out_8295691051147185807[64] = 0.0;
   out_8295691051147185807[65] = 0.0;
   out_8295691051147185807[66] = 0.0;
   out_8295691051147185807[67] = 0.0;
   out_8295691051147185807[68] = 0.0;
   out_8295691051147185807[69] = 0.0;
   out_8295691051147185807[70] = 0.0;
   out_8295691051147185807[71] = 0.0;
   out_8295691051147185807[72] = 0.0;
   out_8295691051147185807[73] = 0.0;
   out_8295691051147185807[74] = 0.0;
   out_8295691051147185807[75] = 0.0;
   out_8295691051147185807[76] = 1.0;
   out_8295691051147185807[77] = 0.0;
   out_8295691051147185807[78] = 0.0;
   out_8295691051147185807[79] = 0.0;
   out_8295691051147185807[80] = 0.0;
   out_8295691051147185807[81] = 0.0;
   out_8295691051147185807[82] = 0.0;
   out_8295691051147185807[83] = 0.0;
   out_8295691051147185807[84] = 0.0;
   out_8295691051147185807[85] = 0.0;
   out_8295691051147185807[86] = 0.0;
   out_8295691051147185807[87] = 0.0;
   out_8295691051147185807[88] = 0.0;
   out_8295691051147185807[89] = 0.0;
   out_8295691051147185807[90] = 0.0;
   out_8295691051147185807[91] = 0.0;
   out_8295691051147185807[92] = 0.0;
   out_8295691051147185807[93] = 0.0;
   out_8295691051147185807[94] = 0.0;
   out_8295691051147185807[95] = 1.0;
   out_8295691051147185807[96] = 0.0;
   out_8295691051147185807[97] = 0.0;
   out_8295691051147185807[98] = 0.0;
   out_8295691051147185807[99] = 0.0;
   out_8295691051147185807[100] = 0.0;
   out_8295691051147185807[101] = 0.0;
   out_8295691051147185807[102] = 0.0;
   out_8295691051147185807[103] = 0.0;
   out_8295691051147185807[104] = 0.0;
   out_8295691051147185807[105] = 0.0;
   out_8295691051147185807[106] = 0.0;
   out_8295691051147185807[107] = 0.0;
   out_8295691051147185807[108] = 0.0;
   out_8295691051147185807[109] = 0.0;
   out_8295691051147185807[110] = 0.0;
   out_8295691051147185807[111] = 0.0;
   out_8295691051147185807[112] = 0.0;
   out_8295691051147185807[113] = 0.0;
   out_8295691051147185807[114] = 1.0;
   out_8295691051147185807[115] = 0.0;
   out_8295691051147185807[116] = 0.0;
   out_8295691051147185807[117] = 0.0;
   out_8295691051147185807[118] = 0.0;
   out_8295691051147185807[119] = 0.0;
   out_8295691051147185807[120] = 0.0;
   out_8295691051147185807[121] = 0.0;
   out_8295691051147185807[122] = 0.0;
   out_8295691051147185807[123] = 0.0;
   out_8295691051147185807[124] = 0.0;
   out_8295691051147185807[125] = 0.0;
   out_8295691051147185807[126] = 0.0;
   out_8295691051147185807[127] = 0.0;
   out_8295691051147185807[128] = 0.0;
   out_8295691051147185807[129] = 0.0;
   out_8295691051147185807[130] = 0.0;
   out_8295691051147185807[131] = 0.0;
   out_8295691051147185807[132] = 0.0;
   out_8295691051147185807[133] = 1.0;
   out_8295691051147185807[134] = 0.0;
   out_8295691051147185807[135] = 0.0;
   out_8295691051147185807[136] = 0.0;
   out_8295691051147185807[137] = 0.0;
   out_8295691051147185807[138] = 0.0;
   out_8295691051147185807[139] = 0.0;
   out_8295691051147185807[140] = 0.0;
   out_8295691051147185807[141] = 0.0;
   out_8295691051147185807[142] = 0.0;
   out_8295691051147185807[143] = 0.0;
   out_8295691051147185807[144] = 0.0;
   out_8295691051147185807[145] = 0.0;
   out_8295691051147185807[146] = 0.0;
   out_8295691051147185807[147] = 0.0;
   out_8295691051147185807[148] = 0.0;
   out_8295691051147185807[149] = 0.0;
   out_8295691051147185807[150] = 0.0;
   out_8295691051147185807[151] = 0.0;
   out_8295691051147185807[152] = 1.0;
   out_8295691051147185807[153] = 0.0;
   out_8295691051147185807[154] = 0.0;
   out_8295691051147185807[155] = 0.0;
   out_8295691051147185807[156] = 0.0;
   out_8295691051147185807[157] = 0.0;
   out_8295691051147185807[158] = 0.0;
   out_8295691051147185807[159] = 0.0;
   out_8295691051147185807[160] = 0.0;
   out_8295691051147185807[161] = 0.0;
   out_8295691051147185807[162] = 0.0;
   out_8295691051147185807[163] = 0.0;
   out_8295691051147185807[164] = 0.0;
   out_8295691051147185807[165] = 0.0;
   out_8295691051147185807[166] = 0.0;
   out_8295691051147185807[167] = 0.0;
   out_8295691051147185807[168] = 0.0;
   out_8295691051147185807[169] = 0.0;
   out_8295691051147185807[170] = 0.0;
   out_8295691051147185807[171] = 1.0;
   out_8295691051147185807[172] = 0.0;
   out_8295691051147185807[173] = 0.0;
   out_8295691051147185807[174] = 0.0;
   out_8295691051147185807[175] = 0.0;
   out_8295691051147185807[176] = 0.0;
   out_8295691051147185807[177] = 0.0;
   out_8295691051147185807[178] = 0.0;
   out_8295691051147185807[179] = 0.0;
   out_8295691051147185807[180] = 0.0;
   out_8295691051147185807[181] = 0.0;
   out_8295691051147185807[182] = 0.0;
   out_8295691051147185807[183] = 0.0;
   out_8295691051147185807[184] = 0.0;
   out_8295691051147185807[185] = 0.0;
   out_8295691051147185807[186] = 0.0;
   out_8295691051147185807[187] = 0.0;
   out_8295691051147185807[188] = 0.0;
   out_8295691051147185807[189] = 0.0;
   out_8295691051147185807[190] = 1.0;
   out_8295691051147185807[191] = 0.0;
   out_8295691051147185807[192] = 0.0;
   out_8295691051147185807[193] = 0.0;
   out_8295691051147185807[194] = 0.0;
   out_8295691051147185807[195] = 0.0;
   out_8295691051147185807[196] = 0.0;
   out_8295691051147185807[197] = 0.0;
   out_8295691051147185807[198] = 0.0;
   out_8295691051147185807[199] = 0.0;
   out_8295691051147185807[200] = 0.0;
   out_8295691051147185807[201] = 0.0;
   out_8295691051147185807[202] = 0.0;
   out_8295691051147185807[203] = 0.0;
   out_8295691051147185807[204] = 0.0;
   out_8295691051147185807[205] = 0.0;
   out_8295691051147185807[206] = 0.0;
   out_8295691051147185807[207] = 0.0;
   out_8295691051147185807[208] = 0.0;
   out_8295691051147185807[209] = 1.0;
   out_8295691051147185807[210] = 0.0;
   out_8295691051147185807[211] = 0.0;
   out_8295691051147185807[212] = 0.0;
   out_8295691051147185807[213] = 0.0;
   out_8295691051147185807[214] = 0.0;
   out_8295691051147185807[215] = 0.0;
   out_8295691051147185807[216] = 0.0;
   out_8295691051147185807[217] = 0.0;
   out_8295691051147185807[218] = 0.0;
   out_8295691051147185807[219] = 0.0;
   out_8295691051147185807[220] = 0.0;
   out_8295691051147185807[221] = 0.0;
   out_8295691051147185807[222] = 0.0;
   out_8295691051147185807[223] = 0.0;
   out_8295691051147185807[224] = 0.0;
   out_8295691051147185807[225] = 0.0;
   out_8295691051147185807[226] = 0.0;
   out_8295691051147185807[227] = 0.0;
   out_8295691051147185807[228] = 1.0;
   out_8295691051147185807[229] = 0.0;
   out_8295691051147185807[230] = 0.0;
   out_8295691051147185807[231] = 0.0;
   out_8295691051147185807[232] = 0.0;
   out_8295691051147185807[233] = 0.0;
   out_8295691051147185807[234] = 0.0;
   out_8295691051147185807[235] = 0.0;
   out_8295691051147185807[236] = 0.0;
   out_8295691051147185807[237] = 0.0;
   out_8295691051147185807[238] = 0.0;
   out_8295691051147185807[239] = 0.0;
   out_8295691051147185807[240] = 0.0;
   out_8295691051147185807[241] = 0.0;
   out_8295691051147185807[242] = 0.0;
   out_8295691051147185807[243] = 0.0;
   out_8295691051147185807[244] = 0.0;
   out_8295691051147185807[245] = 0.0;
   out_8295691051147185807[246] = 0.0;
   out_8295691051147185807[247] = 1.0;
   out_8295691051147185807[248] = 0.0;
   out_8295691051147185807[249] = 0.0;
   out_8295691051147185807[250] = 0.0;
   out_8295691051147185807[251] = 0.0;
   out_8295691051147185807[252] = 0.0;
   out_8295691051147185807[253] = 0.0;
   out_8295691051147185807[254] = 0.0;
   out_8295691051147185807[255] = 0.0;
   out_8295691051147185807[256] = 0.0;
   out_8295691051147185807[257] = 0.0;
   out_8295691051147185807[258] = 0.0;
   out_8295691051147185807[259] = 0.0;
   out_8295691051147185807[260] = 0.0;
   out_8295691051147185807[261] = 0.0;
   out_8295691051147185807[262] = 0.0;
   out_8295691051147185807[263] = 0.0;
   out_8295691051147185807[264] = 0.0;
   out_8295691051147185807[265] = 0.0;
   out_8295691051147185807[266] = 1.0;
   out_8295691051147185807[267] = 0.0;
   out_8295691051147185807[268] = 0.0;
   out_8295691051147185807[269] = 0.0;
   out_8295691051147185807[270] = 0.0;
   out_8295691051147185807[271] = 0.0;
   out_8295691051147185807[272] = 0.0;
   out_8295691051147185807[273] = 0.0;
   out_8295691051147185807[274] = 0.0;
   out_8295691051147185807[275] = 0.0;
   out_8295691051147185807[276] = 0.0;
   out_8295691051147185807[277] = 0.0;
   out_8295691051147185807[278] = 0.0;
   out_8295691051147185807[279] = 0.0;
   out_8295691051147185807[280] = 0.0;
   out_8295691051147185807[281] = 0.0;
   out_8295691051147185807[282] = 0.0;
   out_8295691051147185807[283] = 0.0;
   out_8295691051147185807[284] = 0.0;
   out_8295691051147185807[285] = 1.0;
   out_8295691051147185807[286] = 0.0;
   out_8295691051147185807[287] = 0.0;
   out_8295691051147185807[288] = 0.0;
   out_8295691051147185807[289] = 0.0;
   out_8295691051147185807[290] = 0.0;
   out_8295691051147185807[291] = 0.0;
   out_8295691051147185807[292] = 0.0;
   out_8295691051147185807[293] = 0.0;
   out_8295691051147185807[294] = 0.0;
   out_8295691051147185807[295] = 0.0;
   out_8295691051147185807[296] = 0.0;
   out_8295691051147185807[297] = 0.0;
   out_8295691051147185807[298] = 0.0;
   out_8295691051147185807[299] = 0.0;
   out_8295691051147185807[300] = 0.0;
   out_8295691051147185807[301] = 0.0;
   out_8295691051147185807[302] = 0.0;
   out_8295691051147185807[303] = 0.0;
   out_8295691051147185807[304] = 1.0;
   out_8295691051147185807[305] = 0.0;
   out_8295691051147185807[306] = 0.0;
   out_8295691051147185807[307] = 0.0;
   out_8295691051147185807[308] = 0.0;
   out_8295691051147185807[309] = 0.0;
   out_8295691051147185807[310] = 0.0;
   out_8295691051147185807[311] = 0.0;
   out_8295691051147185807[312] = 0.0;
   out_8295691051147185807[313] = 0.0;
   out_8295691051147185807[314] = 0.0;
   out_8295691051147185807[315] = 0.0;
   out_8295691051147185807[316] = 0.0;
   out_8295691051147185807[317] = 0.0;
   out_8295691051147185807[318] = 0.0;
   out_8295691051147185807[319] = 0.0;
   out_8295691051147185807[320] = 0.0;
   out_8295691051147185807[321] = 0.0;
   out_8295691051147185807[322] = 0.0;
   out_8295691051147185807[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5130330965522153001) {
   out_5130330965522153001[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5130330965522153001[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5130330965522153001[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5130330965522153001[3] = dt*state[12] + state[3];
   out_5130330965522153001[4] = dt*state[13] + state[4];
   out_5130330965522153001[5] = dt*state[14] + state[5];
   out_5130330965522153001[6] = state[6];
   out_5130330965522153001[7] = state[7];
   out_5130330965522153001[8] = state[8];
   out_5130330965522153001[9] = state[9];
   out_5130330965522153001[10] = state[10];
   out_5130330965522153001[11] = state[11];
   out_5130330965522153001[12] = state[12];
   out_5130330965522153001[13] = state[13];
   out_5130330965522153001[14] = state[14];
   out_5130330965522153001[15] = state[15];
   out_5130330965522153001[16] = state[16];
   out_5130330965522153001[17] = state[17];
}
void F_fun(double *state, double dt, double *out_488534431383752290) {
   out_488534431383752290[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_488534431383752290[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_488534431383752290[2] = 0;
   out_488534431383752290[3] = 0;
   out_488534431383752290[4] = 0;
   out_488534431383752290[5] = 0;
   out_488534431383752290[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_488534431383752290[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_488534431383752290[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_488534431383752290[9] = 0;
   out_488534431383752290[10] = 0;
   out_488534431383752290[11] = 0;
   out_488534431383752290[12] = 0;
   out_488534431383752290[13] = 0;
   out_488534431383752290[14] = 0;
   out_488534431383752290[15] = 0;
   out_488534431383752290[16] = 0;
   out_488534431383752290[17] = 0;
   out_488534431383752290[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_488534431383752290[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_488534431383752290[20] = 0;
   out_488534431383752290[21] = 0;
   out_488534431383752290[22] = 0;
   out_488534431383752290[23] = 0;
   out_488534431383752290[24] = 0;
   out_488534431383752290[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_488534431383752290[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_488534431383752290[27] = 0;
   out_488534431383752290[28] = 0;
   out_488534431383752290[29] = 0;
   out_488534431383752290[30] = 0;
   out_488534431383752290[31] = 0;
   out_488534431383752290[32] = 0;
   out_488534431383752290[33] = 0;
   out_488534431383752290[34] = 0;
   out_488534431383752290[35] = 0;
   out_488534431383752290[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_488534431383752290[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_488534431383752290[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_488534431383752290[39] = 0;
   out_488534431383752290[40] = 0;
   out_488534431383752290[41] = 0;
   out_488534431383752290[42] = 0;
   out_488534431383752290[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_488534431383752290[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_488534431383752290[45] = 0;
   out_488534431383752290[46] = 0;
   out_488534431383752290[47] = 0;
   out_488534431383752290[48] = 0;
   out_488534431383752290[49] = 0;
   out_488534431383752290[50] = 0;
   out_488534431383752290[51] = 0;
   out_488534431383752290[52] = 0;
   out_488534431383752290[53] = 0;
   out_488534431383752290[54] = 0;
   out_488534431383752290[55] = 0;
   out_488534431383752290[56] = 0;
   out_488534431383752290[57] = 1;
   out_488534431383752290[58] = 0;
   out_488534431383752290[59] = 0;
   out_488534431383752290[60] = 0;
   out_488534431383752290[61] = 0;
   out_488534431383752290[62] = 0;
   out_488534431383752290[63] = 0;
   out_488534431383752290[64] = 0;
   out_488534431383752290[65] = 0;
   out_488534431383752290[66] = dt;
   out_488534431383752290[67] = 0;
   out_488534431383752290[68] = 0;
   out_488534431383752290[69] = 0;
   out_488534431383752290[70] = 0;
   out_488534431383752290[71] = 0;
   out_488534431383752290[72] = 0;
   out_488534431383752290[73] = 0;
   out_488534431383752290[74] = 0;
   out_488534431383752290[75] = 0;
   out_488534431383752290[76] = 1;
   out_488534431383752290[77] = 0;
   out_488534431383752290[78] = 0;
   out_488534431383752290[79] = 0;
   out_488534431383752290[80] = 0;
   out_488534431383752290[81] = 0;
   out_488534431383752290[82] = 0;
   out_488534431383752290[83] = 0;
   out_488534431383752290[84] = 0;
   out_488534431383752290[85] = dt;
   out_488534431383752290[86] = 0;
   out_488534431383752290[87] = 0;
   out_488534431383752290[88] = 0;
   out_488534431383752290[89] = 0;
   out_488534431383752290[90] = 0;
   out_488534431383752290[91] = 0;
   out_488534431383752290[92] = 0;
   out_488534431383752290[93] = 0;
   out_488534431383752290[94] = 0;
   out_488534431383752290[95] = 1;
   out_488534431383752290[96] = 0;
   out_488534431383752290[97] = 0;
   out_488534431383752290[98] = 0;
   out_488534431383752290[99] = 0;
   out_488534431383752290[100] = 0;
   out_488534431383752290[101] = 0;
   out_488534431383752290[102] = 0;
   out_488534431383752290[103] = 0;
   out_488534431383752290[104] = dt;
   out_488534431383752290[105] = 0;
   out_488534431383752290[106] = 0;
   out_488534431383752290[107] = 0;
   out_488534431383752290[108] = 0;
   out_488534431383752290[109] = 0;
   out_488534431383752290[110] = 0;
   out_488534431383752290[111] = 0;
   out_488534431383752290[112] = 0;
   out_488534431383752290[113] = 0;
   out_488534431383752290[114] = 1;
   out_488534431383752290[115] = 0;
   out_488534431383752290[116] = 0;
   out_488534431383752290[117] = 0;
   out_488534431383752290[118] = 0;
   out_488534431383752290[119] = 0;
   out_488534431383752290[120] = 0;
   out_488534431383752290[121] = 0;
   out_488534431383752290[122] = 0;
   out_488534431383752290[123] = 0;
   out_488534431383752290[124] = 0;
   out_488534431383752290[125] = 0;
   out_488534431383752290[126] = 0;
   out_488534431383752290[127] = 0;
   out_488534431383752290[128] = 0;
   out_488534431383752290[129] = 0;
   out_488534431383752290[130] = 0;
   out_488534431383752290[131] = 0;
   out_488534431383752290[132] = 0;
   out_488534431383752290[133] = 1;
   out_488534431383752290[134] = 0;
   out_488534431383752290[135] = 0;
   out_488534431383752290[136] = 0;
   out_488534431383752290[137] = 0;
   out_488534431383752290[138] = 0;
   out_488534431383752290[139] = 0;
   out_488534431383752290[140] = 0;
   out_488534431383752290[141] = 0;
   out_488534431383752290[142] = 0;
   out_488534431383752290[143] = 0;
   out_488534431383752290[144] = 0;
   out_488534431383752290[145] = 0;
   out_488534431383752290[146] = 0;
   out_488534431383752290[147] = 0;
   out_488534431383752290[148] = 0;
   out_488534431383752290[149] = 0;
   out_488534431383752290[150] = 0;
   out_488534431383752290[151] = 0;
   out_488534431383752290[152] = 1;
   out_488534431383752290[153] = 0;
   out_488534431383752290[154] = 0;
   out_488534431383752290[155] = 0;
   out_488534431383752290[156] = 0;
   out_488534431383752290[157] = 0;
   out_488534431383752290[158] = 0;
   out_488534431383752290[159] = 0;
   out_488534431383752290[160] = 0;
   out_488534431383752290[161] = 0;
   out_488534431383752290[162] = 0;
   out_488534431383752290[163] = 0;
   out_488534431383752290[164] = 0;
   out_488534431383752290[165] = 0;
   out_488534431383752290[166] = 0;
   out_488534431383752290[167] = 0;
   out_488534431383752290[168] = 0;
   out_488534431383752290[169] = 0;
   out_488534431383752290[170] = 0;
   out_488534431383752290[171] = 1;
   out_488534431383752290[172] = 0;
   out_488534431383752290[173] = 0;
   out_488534431383752290[174] = 0;
   out_488534431383752290[175] = 0;
   out_488534431383752290[176] = 0;
   out_488534431383752290[177] = 0;
   out_488534431383752290[178] = 0;
   out_488534431383752290[179] = 0;
   out_488534431383752290[180] = 0;
   out_488534431383752290[181] = 0;
   out_488534431383752290[182] = 0;
   out_488534431383752290[183] = 0;
   out_488534431383752290[184] = 0;
   out_488534431383752290[185] = 0;
   out_488534431383752290[186] = 0;
   out_488534431383752290[187] = 0;
   out_488534431383752290[188] = 0;
   out_488534431383752290[189] = 0;
   out_488534431383752290[190] = 1;
   out_488534431383752290[191] = 0;
   out_488534431383752290[192] = 0;
   out_488534431383752290[193] = 0;
   out_488534431383752290[194] = 0;
   out_488534431383752290[195] = 0;
   out_488534431383752290[196] = 0;
   out_488534431383752290[197] = 0;
   out_488534431383752290[198] = 0;
   out_488534431383752290[199] = 0;
   out_488534431383752290[200] = 0;
   out_488534431383752290[201] = 0;
   out_488534431383752290[202] = 0;
   out_488534431383752290[203] = 0;
   out_488534431383752290[204] = 0;
   out_488534431383752290[205] = 0;
   out_488534431383752290[206] = 0;
   out_488534431383752290[207] = 0;
   out_488534431383752290[208] = 0;
   out_488534431383752290[209] = 1;
   out_488534431383752290[210] = 0;
   out_488534431383752290[211] = 0;
   out_488534431383752290[212] = 0;
   out_488534431383752290[213] = 0;
   out_488534431383752290[214] = 0;
   out_488534431383752290[215] = 0;
   out_488534431383752290[216] = 0;
   out_488534431383752290[217] = 0;
   out_488534431383752290[218] = 0;
   out_488534431383752290[219] = 0;
   out_488534431383752290[220] = 0;
   out_488534431383752290[221] = 0;
   out_488534431383752290[222] = 0;
   out_488534431383752290[223] = 0;
   out_488534431383752290[224] = 0;
   out_488534431383752290[225] = 0;
   out_488534431383752290[226] = 0;
   out_488534431383752290[227] = 0;
   out_488534431383752290[228] = 1;
   out_488534431383752290[229] = 0;
   out_488534431383752290[230] = 0;
   out_488534431383752290[231] = 0;
   out_488534431383752290[232] = 0;
   out_488534431383752290[233] = 0;
   out_488534431383752290[234] = 0;
   out_488534431383752290[235] = 0;
   out_488534431383752290[236] = 0;
   out_488534431383752290[237] = 0;
   out_488534431383752290[238] = 0;
   out_488534431383752290[239] = 0;
   out_488534431383752290[240] = 0;
   out_488534431383752290[241] = 0;
   out_488534431383752290[242] = 0;
   out_488534431383752290[243] = 0;
   out_488534431383752290[244] = 0;
   out_488534431383752290[245] = 0;
   out_488534431383752290[246] = 0;
   out_488534431383752290[247] = 1;
   out_488534431383752290[248] = 0;
   out_488534431383752290[249] = 0;
   out_488534431383752290[250] = 0;
   out_488534431383752290[251] = 0;
   out_488534431383752290[252] = 0;
   out_488534431383752290[253] = 0;
   out_488534431383752290[254] = 0;
   out_488534431383752290[255] = 0;
   out_488534431383752290[256] = 0;
   out_488534431383752290[257] = 0;
   out_488534431383752290[258] = 0;
   out_488534431383752290[259] = 0;
   out_488534431383752290[260] = 0;
   out_488534431383752290[261] = 0;
   out_488534431383752290[262] = 0;
   out_488534431383752290[263] = 0;
   out_488534431383752290[264] = 0;
   out_488534431383752290[265] = 0;
   out_488534431383752290[266] = 1;
   out_488534431383752290[267] = 0;
   out_488534431383752290[268] = 0;
   out_488534431383752290[269] = 0;
   out_488534431383752290[270] = 0;
   out_488534431383752290[271] = 0;
   out_488534431383752290[272] = 0;
   out_488534431383752290[273] = 0;
   out_488534431383752290[274] = 0;
   out_488534431383752290[275] = 0;
   out_488534431383752290[276] = 0;
   out_488534431383752290[277] = 0;
   out_488534431383752290[278] = 0;
   out_488534431383752290[279] = 0;
   out_488534431383752290[280] = 0;
   out_488534431383752290[281] = 0;
   out_488534431383752290[282] = 0;
   out_488534431383752290[283] = 0;
   out_488534431383752290[284] = 0;
   out_488534431383752290[285] = 1;
   out_488534431383752290[286] = 0;
   out_488534431383752290[287] = 0;
   out_488534431383752290[288] = 0;
   out_488534431383752290[289] = 0;
   out_488534431383752290[290] = 0;
   out_488534431383752290[291] = 0;
   out_488534431383752290[292] = 0;
   out_488534431383752290[293] = 0;
   out_488534431383752290[294] = 0;
   out_488534431383752290[295] = 0;
   out_488534431383752290[296] = 0;
   out_488534431383752290[297] = 0;
   out_488534431383752290[298] = 0;
   out_488534431383752290[299] = 0;
   out_488534431383752290[300] = 0;
   out_488534431383752290[301] = 0;
   out_488534431383752290[302] = 0;
   out_488534431383752290[303] = 0;
   out_488534431383752290[304] = 1;
   out_488534431383752290[305] = 0;
   out_488534431383752290[306] = 0;
   out_488534431383752290[307] = 0;
   out_488534431383752290[308] = 0;
   out_488534431383752290[309] = 0;
   out_488534431383752290[310] = 0;
   out_488534431383752290[311] = 0;
   out_488534431383752290[312] = 0;
   out_488534431383752290[313] = 0;
   out_488534431383752290[314] = 0;
   out_488534431383752290[315] = 0;
   out_488534431383752290[316] = 0;
   out_488534431383752290[317] = 0;
   out_488534431383752290[318] = 0;
   out_488534431383752290[319] = 0;
   out_488534431383752290[320] = 0;
   out_488534431383752290[321] = 0;
   out_488534431383752290[322] = 0;
   out_488534431383752290[323] = 1;
}
void h_4(double *state, double *unused, double *out_8441742047814671654) {
   out_8441742047814671654[0] = state[6] + state[9];
   out_8441742047814671654[1] = state[7] + state[10];
   out_8441742047814671654[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7694699903545492360) {
   out_7694699903545492360[0] = 0;
   out_7694699903545492360[1] = 0;
   out_7694699903545492360[2] = 0;
   out_7694699903545492360[3] = 0;
   out_7694699903545492360[4] = 0;
   out_7694699903545492360[5] = 0;
   out_7694699903545492360[6] = 1;
   out_7694699903545492360[7] = 0;
   out_7694699903545492360[8] = 0;
   out_7694699903545492360[9] = 1;
   out_7694699903545492360[10] = 0;
   out_7694699903545492360[11] = 0;
   out_7694699903545492360[12] = 0;
   out_7694699903545492360[13] = 0;
   out_7694699903545492360[14] = 0;
   out_7694699903545492360[15] = 0;
   out_7694699903545492360[16] = 0;
   out_7694699903545492360[17] = 0;
   out_7694699903545492360[18] = 0;
   out_7694699903545492360[19] = 0;
   out_7694699903545492360[20] = 0;
   out_7694699903545492360[21] = 0;
   out_7694699903545492360[22] = 0;
   out_7694699903545492360[23] = 0;
   out_7694699903545492360[24] = 0;
   out_7694699903545492360[25] = 1;
   out_7694699903545492360[26] = 0;
   out_7694699903545492360[27] = 0;
   out_7694699903545492360[28] = 1;
   out_7694699903545492360[29] = 0;
   out_7694699903545492360[30] = 0;
   out_7694699903545492360[31] = 0;
   out_7694699903545492360[32] = 0;
   out_7694699903545492360[33] = 0;
   out_7694699903545492360[34] = 0;
   out_7694699903545492360[35] = 0;
   out_7694699903545492360[36] = 0;
   out_7694699903545492360[37] = 0;
   out_7694699903545492360[38] = 0;
   out_7694699903545492360[39] = 0;
   out_7694699903545492360[40] = 0;
   out_7694699903545492360[41] = 0;
   out_7694699903545492360[42] = 0;
   out_7694699903545492360[43] = 0;
   out_7694699903545492360[44] = 1;
   out_7694699903545492360[45] = 0;
   out_7694699903545492360[46] = 0;
   out_7694699903545492360[47] = 1;
   out_7694699903545492360[48] = 0;
   out_7694699903545492360[49] = 0;
   out_7694699903545492360[50] = 0;
   out_7694699903545492360[51] = 0;
   out_7694699903545492360[52] = 0;
   out_7694699903545492360[53] = 0;
}
void h_10(double *state, double *unused, double *out_1124287673941347069) {
   out_1124287673941347069[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1124287673941347069[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1124287673941347069[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8452541670693679658) {
   out_8452541670693679658[0] = 0;
   out_8452541670693679658[1] = 9.8100000000000005*cos(state[1]);
   out_8452541670693679658[2] = 0;
   out_8452541670693679658[3] = 0;
   out_8452541670693679658[4] = -state[8];
   out_8452541670693679658[5] = state[7];
   out_8452541670693679658[6] = 0;
   out_8452541670693679658[7] = state[5];
   out_8452541670693679658[8] = -state[4];
   out_8452541670693679658[9] = 0;
   out_8452541670693679658[10] = 0;
   out_8452541670693679658[11] = 0;
   out_8452541670693679658[12] = 1;
   out_8452541670693679658[13] = 0;
   out_8452541670693679658[14] = 0;
   out_8452541670693679658[15] = 1;
   out_8452541670693679658[16] = 0;
   out_8452541670693679658[17] = 0;
   out_8452541670693679658[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8452541670693679658[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8452541670693679658[20] = 0;
   out_8452541670693679658[21] = state[8];
   out_8452541670693679658[22] = 0;
   out_8452541670693679658[23] = -state[6];
   out_8452541670693679658[24] = -state[5];
   out_8452541670693679658[25] = 0;
   out_8452541670693679658[26] = state[3];
   out_8452541670693679658[27] = 0;
   out_8452541670693679658[28] = 0;
   out_8452541670693679658[29] = 0;
   out_8452541670693679658[30] = 0;
   out_8452541670693679658[31] = 1;
   out_8452541670693679658[32] = 0;
   out_8452541670693679658[33] = 0;
   out_8452541670693679658[34] = 1;
   out_8452541670693679658[35] = 0;
   out_8452541670693679658[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8452541670693679658[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8452541670693679658[38] = 0;
   out_8452541670693679658[39] = -state[7];
   out_8452541670693679658[40] = state[6];
   out_8452541670693679658[41] = 0;
   out_8452541670693679658[42] = state[4];
   out_8452541670693679658[43] = -state[3];
   out_8452541670693679658[44] = 0;
   out_8452541670693679658[45] = 0;
   out_8452541670693679658[46] = 0;
   out_8452541670693679658[47] = 0;
   out_8452541670693679658[48] = 0;
   out_8452541670693679658[49] = 0;
   out_8452541670693679658[50] = 1;
   out_8452541670693679658[51] = 0;
   out_8452541670693679658[52] = 0;
   out_8452541670693679658[53] = 1;
}
void h_13(double *state, double *unused, double *out_157612946214320216) {
   out_157612946214320216[0] = state[3];
   out_157612946214320216[1] = state[4];
   out_157612946214320216[2] = state[5];
}
void H_13(double *state, double *unused, double *out_84068695228791431) {
   out_84068695228791431[0] = 0;
   out_84068695228791431[1] = 0;
   out_84068695228791431[2] = 0;
   out_84068695228791431[3] = 1;
   out_84068695228791431[4] = 0;
   out_84068695228791431[5] = 0;
   out_84068695228791431[6] = 0;
   out_84068695228791431[7] = 0;
   out_84068695228791431[8] = 0;
   out_84068695228791431[9] = 0;
   out_84068695228791431[10] = 0;
   out_84068695228791431[11] = 0;
   out_84068695228791431[12] = 0;
   out_84068695228791431[13] = 0;
   out_84068695228791431[14] = 0;
   out_84068695228791431[15] = 0;
   out_84068695228791431[16] = 0;
   out_84068695228791431[17] = 0;
   out_84068695228791431[18] = 0;
   out_84068695228791431[19] = 0;
   out_84068695228791431[20] = 0;
   out_84068695228791431[21] = 0;
   out_84068695228791431[22] = 1;
   out_84068695228791431[23] = 0;
   out_84068695228791431[24] = 0;
   out_84068695228791431[25] = 0;
   out_84068695228791431[26] = 0;
   out_84068695228791431[27] = 0;
   out_84068695228791431[28] = 0;
   out_84068695228791431[29] = 0;
   out_84068695228791431[30] = 0;
   out_84068695228791431[31] = 0;
   out_84068695228791431[32] = 0;
   out_84068695228791431[33] = 0;
   out_84068695228791431[34] = 0;
   out_84068695228791431[35] = 0;
   out_84068695228791431[36] = 0;
   out_84068695228791431[37] = 0;
   out_84068695228791431[38] = 0;
   out_84068695228791431[39] = 0;
   out_84068695228791431[40] = 0;
   out_84068695228791431[41] = 1;
   out_84068695228791431[42] = 0;
   out_84068695228791431[43] = 0;
   out_84068695228791431[44] = 0;
   out_84068695228791431[45] = 0;
   out_84068695228791431[46] = 0;
   out_84068695228791431[47] = 0;
   out_84068695228791431[48] = 0;
   out_84068695228791431[49] = 0;
   out_84068695228791431[50] = 0;
   out_84068695228791431[51] = 0;
   out_84068695228791431[52] = 0;
   out_84068695228791431[53] = 0;
}
void h_14(double *state, double *unused, double *out_5323712927848765653) {
   out_5323712927848765653[0] = state[6];
   out_5323712927848765653[1] = state[7];
   out_5323712927848765653[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3731459047206007831) {
   out_3731459047206007831[0] = 0;
   out_3731459047206007831[1] = 0;
   out_3731459047206007831[2] = 0;
   out_3731459047206007831[3] = 0;
   out_3731459047206007831[4] = 0;
   out_3731459047206007831[5] = 0;
   out_3731459047206007831[6] = 1;
   out_3731459047206007831[7] = 0;
   out_3731459047206007831[8] = 0;
   out_3731459047206007831[9] = 0;
   out_3731459047206007831[10] = 0;
   out_3731459047206007831[11] = 0;
   out_3731459047206007831[12] = 0;
   out_3731459047206007831[13] = 0;
   out_3731459047206007831[14] = 0;
   out_3731459047206007831[15] = 0;
   out_3731459047206007831[16] = 0;
   out_3731459047206007831[17] = 0;
   out_3731459047206007831[18] = 0;
   out_3731459047206007831[19] = 0;
   out_3731459047206007831[20] = 0;
   out_3731459047206007831[21] = 0;
   out_3731459047206007831[22] = 0;
   out_3731459047206007831[23] = 0;
   out_3731459047206007831[24] = 0;
   out_3731459047206007831[25] = 1;
   out_3731459047206007831[26] = 0;
   out_3731459047206007831[27] = 0;
   out_3731459047206007831[28] = 0;
   out_3731459047206007831[29] = 0;
   out_3731459047206007831[30] = 0;
   out_3731459047206007831[31] = 0;
   out_3731459047206007831[32] = 0;
   out_3731459047206007831[33] = 0;
   out_3731459047206007831[34] = 0;
   out_3731459047206007831[35] = 0;
   out_3731459047206007831[36] = 0;
   out_3731459047206007831[37] = 0;
   out_3731459047206007831[38] = 0;
   out_3731459047206007831[39] = 0;
   out_3731459047206007831[40] = 0;
   out_3731459047206007831[41] = 0;
   out_3731459047206007831[42] = 0;
   out_3731459047206007831[43] = 0;
   out_3731459047206007831[44] = 1;
   out_3731459047206007831[45] = 0;
   out_3731459047206007831[46] = 0;
   out_3731459047206007831[47] = 0;
   out_3731459047206007831[48] = 0;
   out_3731459047206007831[49] = 0;
   out_3731459047206007831[50] = 0;
   out_3731459047206007831[51] = 0;
   out_3731459047206007831[52] = 0;
   out_3731459047206007831[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8215112940017755867) {
  err_fun(nom_x, delta_x, out_8215112940017755867);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1173819570397538874) {
  inv_err_fun(nom_x, true_x, out_1173819570397538874);
}
void pose_H_mod_fun(double *state, double *out_8295691051147185807) {
  H_mod_fun(state, out_8295691051147185807);
}
void pose_f_fun(double *state, double dt, double *out_5130330965522153001) {
  f_fun(state,  dt, out_5130330965522153001);
}
void pose_F_fun(double *state, double dt, double *out_488534431383752290) {
  F_fun(state,  dt, out_488534431383752290);
}
void pose_h_4(double *state, double *unused, double *out_8441742047814671654) {
  h_4(state, unused, out_8441742047814671654);
}
void pose_H_4(double *state, double *unused, double *out_7694699903545492360) {
  H_4(state, unused, out_7694699903545492360);
}
void pose_h_10(double *state, double *unused, double *out_1124287673941347069) {
  h_10(state, unused, out_1124287673941347069);
}
void pose_H_10(double *state, double *unused, double *out_8452541670693679658) {
  H_10(state, unused, out_8452541670693679658);
}
void pose_h_13(double *state, double *unused, double *out_157612946214320216) {
  h_13(state, unused, out_157612946214320216);
}
void pose_H_13(double *state, double *unused, double *out_84068695228791431) {
  H_13(state, unused, out_84068695228791431);
}
void pose_h_14(double *state, double *unused, double *out_5323712927848765653) {
  h_14(state, unused, out_5323712927848765653);
}
void pose_H_14(double *state, double *unused, double *out_3731459047206007831) {
  H_14(state, unused, out_3731459047206007831);
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
