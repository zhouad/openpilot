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
void err_fun(double *nom_x, double *delta_x, double *out_6950291583245326091) {
   out_6950291583245326091[0] = delta_x[0] + nom_x[0];
   out_6950291583245326091[1] = delta_x[1] + nom_x[1];
   out_6950291583245326091[2] = delta_x[2] + nom_x[2];
   out_6950291583245326091[3] = delta_x[3] + nom_x[3];
   out_6950291583245326091[4] = delta_x[4] + nom_x[4];
   out_6950291583245326091[5] = delta_x[5] + nom_x[5];
   out_6950291583245326091[6] = delta_x[6] + nom_x[6];
   out_6950291583245326091[7] = delta_x[7] + nom_x[7];
   out_6950291583245326091[8] = delta_x[8] + nom_x[8];
   out_6950291583245326091[9] = delta_x[9] + nom_x[9];
   out_6950291583245326091[10] = delta_x[10] + nom_x[10];
   out_6950291583245326091[11] = delta_x[11] + nom_x[11];
   out_6950291583245326091[12] = delta_x[12] + nom_x[12];
   out_6950291583245326091[13] = delta_x[13] + nom_x[13];
   out_6950291583245326091[14] = delta_x[14] + nom_x[14];
   out_6950291583245326091[15] = delta_x[15] + nom_x[15];
   out_6950291583245326091[16] = delta_x[16] + nom_x[16];
   out_6950291583245326091[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7864587791361010025) {
   out_7864587791361010025[0] = -nom_x[0] + true_x[0];
   out_7864587791361010025[1] = -nom_x[1] + true_x[1];
   out_7864587791361010025[2] = -nom_x[2] + true_x[2];
   out_7864587791361010025[3] = -nom_x[3] + true_x[3];
   out_7864587791361010025[4] = -nom_x[4] + true_x[4];
   out_7864587791361010025[5] = -nom_x[5] + true_x[5];
   out_7864587791361010025[6] = -nom_x[6] + true_x[6];
   out_7864587791361010025[7] = -nom_x[7] + true_x[7];
   out_7864587791361010025[8] = -nom_x[8] + true_x[8];
   out_7864587791361010025[9] = -nom_x[9] + true_x[9];
   out_7864587791361010025[10] = -nom_x[10] + true_x[10];
   out_7864587791361010025[11] = -nom_x[11] + true_x[11];
   out_7864587791361010025[12] = -nom_x[12] + true_x[12];
   out_7864587791361010025[13] = -nom_x[13] + true_x[13];
   out_7864587791361010025[14] = -nom_x[14] + true_x[14];
   out_7864587791361010025[15] = -nom_x[15] + true_x[15];
   out_7864587791361010025[16] = -nom_x[16] + true_x[16];
   out_7864587791361010025[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5486619309331330377) {
   out_5486619309331330377[0] = 1.0;
   out_5486619309331330377[1] = 0.0;
   out_5486619309331330377[2] = 0.0;
   out_5486619309331330377[3] = 0.0;
   out_5486619309331330377[4] = 0.0;
   out_5486619309331330377[5] = 0.0;
   out_5486619309331330377[6] = 0.0;
   out_5486619309331330377[7] = 0.0;
   out_5486619309331330377[8] = 0.0;
   out_5486619309331330377[9] = 0.0;
   out_5486619309331330377[10] = 0.0;
   out_5486619309331330377[11] = 0.0;
   out_5486619309331330377[12] = 0.0;
   out_5486619309331330377[13] = 0.0;
   out_5486619309331330377[14] = 0.0;
   out_5486619309331330377[15] = 0.0;
   out_5486619309331330377[16] = 0.0;
   out_5486619309331330377[17] = 0.0;
   out_5486619309331330377[18] = 0.0;
   out_5486619309331330377[19] = 1.0;
   out_5486619309331330377[20] = 0.0;
   out_5486619309331330377[21] = 0.0;
   out_5486619309331330377[22] = 0.0;
   out_5486619309331330377[23] = 0.0;
   out_5486619309331330377[24] = 0.0;
   out_5486619309331330377[25] = 0.0;
   out_5486619309331330377[26] = 0.0;
   out_5486619309331330377[27] = 0.0;
   out_5486619309331330377[28] = 0.0;
   out_5486619309331330377[29] = 0.0;
   out_5486619309331330377[30] = 0.0;
   out_5486619309331330377[31] = 0.0;
   out_5486619309331330377[32] = 0.0;
   out_5486619309331330377[33] = 0.0;
   out_5486619309331330377[34] = 0.0;
   out_5486619309331330377[35] = 0.0;
   out_5486619309331330377[36] = 0.0;
   out_5486619309331330377[37] = 0.0;
   out_5486619309331330377[38] = 1.0;
   out_5486619309331330377[39] = 0.0;
   out_5486619309331330377[40] = 0.0;
   out_5486619309331330377[41] = 0.0;
   out_5486619309331330377[42] = 0.0;
   out_5486619309331330377[43] = 0.0;
   out_5486619309331330377[44] = 0.0;
   out_5486619309331330377[45] = 0.0;
   out_5486619309331330377[46] = 0.0;
   out_5486619309331330377[47] = 0.0;
   out_5486619309331330377[48] = 0.0;
   out_5486619309331330377[49] = 0.0;
   out_5486619309331330377[50] = 0.0;
   out_5486619309331330377[51] = 0.0;
   out_5486619309331330377[52] = 0.0;
   out_5486619309331330377[53] = 0.0;
   out_5486619309331330377[54] = 0.0;
   out_5486619309331330377[55] = 0.0;
   out_5486619309331330377[56] = 0.0;
   out_5486619309331330377[57] = 1.0;
   out_5486619309331330377[58] = 0.0;
   out_5486619309331330377[59] = 0.0;
   out_5486619309331330377[60] = 0.0;
   out_5486619309331330377[61] = 0.0;
   out_5486619309331330377[62] = 0.0;
   out_5486619309331330377[63] = 0.0;
   out_5486619309331330377[64] = 0.0;
   out_5486619309331330377[65] = 0.0;
   out_5486619309331330377[66] = 0.0;
   out_5486619309331330377[67] = 0.0;
   out_5486619309331330377[68] = 0.0;
   out_5486619309331330377[69] = 0.0;
   out_5486619309331330377[70] = 0.0;
   out_5486619309331330377[71] = 0.0;
   out_5486619309331330377[72] = 0.0;
   out_5486619309331330377[73] = 0.0;
   out_5486619309331330377[74] = 0.0;
   out_5486619309331330377[75] = 0.0;
   out_5486619309331330377[76] = 1.0;
   out_5486619309331330377[77] = 0.0;
   out_5486619309331330377[78] = 0.0;
   out_5486619309331330377[79] = 0.0;
   out_5486619309331330377[80] = 0.0;
   out_5486619309331330377[81] = 0.0;
   out_5486619309331330377[82] = 0.0;
   out_5486619309331330377[83] = 0.0;
   out_5486619309331330377[84] = 0.0;
   out_5486619309331330377[85] = 0.0;
   out_5486619309331330377[86] = 0.0;
   out_5486619309331330377[87] = 0.0;
   out_5486619309331330377[88] = 0.0;
   out_5486619309331330377[89] = 0.0;
   out_5486619309331330377[90] = 0.0;
   out_5486619309331330377[91] = 0.0;
   out_5486619309331330377[92] = 0.0;
   out_5486619309331330377[93] = 0.0;
   out_5486619309331330377[94] = 0.0;
   out_5486619309331330377[95] = 1.0;
   out_5486619309331330377[96] = 0.0;
   out_5486619309331330377[97] = 0.0;
   out_5486619309331330377[98] = 0.0;
   out_5486619309331330377[99] = 0.0;
   out_5486619309331330377[100] = 0.0;
   out_5486619309331330377[101] = 0.0;
   out_5486619309331330377[102] = 0.0;
   out_5486619309331330377[103] = 0.0;
   out_5486619309331330377[104] = 0.0;
   out_5486619309331330377[105] = 0.0;
   out_5486619309331330377[106] = 0.0;
   out_5486619309331330377[107] = 0.0;
   out_5486619309331330377[108] = 0.0;
   out_5486619309331330377[109] = 0.0;
   out_5486619309331330377[110] = 0.0;
   out_5486619309331330377[111] = 0.0;
   out_5486619309331330377[112] = 0.0;
   out_5486619309331330377[113] = 0.0;
   out_5486619309331330377[114] = 1.0;
   out_5486619309331330377[115] = 0.0;
   out_5486619309331330377[116] = 0.0;
   out_5486619309331330377[117] = 0.0;
   out_5486619309331330377[118] = 0.0;
   out_5486619309331330377[119] = 0.0;
   out_5486619309331330377[120] = 0.0;
   out_5486619309331330377[121] = 0.0;
   out_5486619309331330377[122] = 0.0;
   out_5486619309331330377[123] = 0.0;
   out_5486619309331330377[124] = 0.0;
   out_5486619309331330377[125] = 0.0;
   out_5486619309331330377[126] = 0.0;
   out_5486619309331330377[127] = 0.0;
   out_5486619309331330377[128] = 0.0;
   out_5486619309331330377[129] = 0.0;
   out_5486619309331330377[130] = 0.0;
   out_5486619309331330377[131] = 0.0;
   out_5486619309331330377[132] = 0.0;
   out_5486619309331330377[133] = 1.0;
   out_5486619309331330377[134] = 0.0;
   out_5486619309331330377[135] = 0.0;
   out_5486619309331330377[136] = 0.0;
   out_5486619309331330377[137] = 0.0;
   out_5486619309331330377[138] = 0.0;
   out_5486619309331330377[139] = 0.0;
   out_5486619309331330377[140] = 0.0;
   out_5486619309331330377[141] = 0.0;
   out_5486619309331330377[142] = 0.0;
   out_5486619309331330377[143] = 0.0;
   out_5486619309331330377[144] = 0.0;
   out_5486619309331330377[145] = 0.0;
   out_5486619309331330377[146] = 0.0;
   out_5486619309331330377[147] = 0.0;
   out_5486619309331330377[148] = 0.0;
   out_5486619309331330377[149] = 0.0;
   out_5486619309331330377[150] = 0.0;
   out_5486619309331330377[151] = 0.0;
   out_5486619309331330377[152] = 1.0;
   out_5486619309331330377[153] = 0.0;
   out_5486619309331330377[154] = 0.0;
   out_5486619309331330377[155] = 0.0;
   out_5486619309331330377[156] = 0.0;
   out_5486619309331330377[157] = 0.0;
   out_5486619309331330377[158] = 0.0;
   out_5486619309331330377[159] = 0.0;
   out_5486619309331330377[160] = 0.0;
   out_5486619309331330377[161] = 0.0;
   out_5486619309331330377[162] = 0.0;
   out_5486619309331330377[163] = 0.0;
   out_5486619309331330377[164] = 0.0;
   out_5486619309331330377[165] = 0.0;
   out_5486619309331330377[166] = 0.0;
   out_5486619309331330377[167] = 0.0;
   out_5486619309331330377[168] = 0.0;
   out_5486619309331330377[169] = 0.0;
   out_5486619309331330377[170] = 0.0;
   out_5486619309331330377[171] = 1.0;
   out_5486619309331330377[172] = 0.0;
   out_5486619309331330377[173] = 0.0;
   out_5486619309331330377[174] = 0.0;
   out_5486619309331330377[175] = 0.0;
   out_5486619309331330377[176] = 0.0;
   out_5486619309331330377[177] = 0.0;
   out_5486619309331330377[178] = 0.0;
   out_5486619309331330377[179] = 0.0;
   out_5486619309331330377[180] = 0.0;
   out_5486619309331330377[181] = 0.0;
   out_5486619309331330377[182] = 0.0;
   out_5486619309331330377[183] = 0.0;
   out_5486619309331330377[184] = 0.0;
   out_5486619309331330377[185] = 0.0;
   out_5486619309331330377[186] = 0.0;
   out_5486619309331330377[187] = 0.0;
   out_5486619309331330377[188] = 0.0;
   out_5486619309331330377[189] = 0.0;
   out_5486619309331330377[190] = 1.0;
   out_5486619309331330377[191] = 0.0;
   out_5486619309331330377[192] = 0.0;
   out_5486619309331330377[193] = 0.0;
   out_5486619309331330377[194] = 0.0;
   out_5486619309331330377[195] = 0.0;
   out_5486619309331330377[196] = 0.0;
   out_5486619309331330377[197] = 0.0;
   out_5486619309331330377[198] = 0.0;
   out_5486619309331330377[199] = 0.0;
   out_5486619309331330377[200] = 0.0;
   out_5486619309331330377[201] = 0.0;
   out_5486619309331330377[202] = 0.0;
   out_5486619309331330377[203] = 0.0;
   out_5486619309331330377[204] = 0.0;
   out_5486619309331330377[205] = 0.0;
   out_5486619309331330377[206] = 0.0;
   out_5486619309331330377[207] = 0.0;
   out_5486619309331330377[208] = 0.0;
   out_5486619309331330377[209] = 1.0;
   out_5486619309331330377[210] = 0.0;
   out_5486619309331330377[211] = 0.0;
   out_5486619309331330377[212] = 0.0;
   out_5486619309331330377[213] = 0.0;
   out_5486619309331330377[214] = 0.0;
   out_5486619309331330377[215] = 0.0;
   out_5486619309331330377[216] = 0.0;
   out_5486619309331330377[217] = 0.0;
   out_5486619309331330377[218] = 0.0;
   out_5486619309331330377[219] = 0.0;
   out_5486619309331330377[220] = 0.0;
   out_5486619309331330377[221] = 0.0;
   out_5486619309331330377[222] = 0.0;
   out_5486619309331330377[223] = 0.0;
   out_5486619309331330377[224] = 0.0;
   out_5486619309331330377[225] = 0.0;
   out_5486619309331330377[226] = 0.0;
   out_5486619309331330377[227] = 0.0;
   out_5486619309331330377[228] = 1.0;
   out_5486619309331330377[229] = 0.0;
   out_5486619309331330377[230] = 0.0;
   out_5486619309331330377[231] = 0.0;
   out_5486619309331330377[232] = 0.0;
   out_5486619309331330377[233] = 0.0;
   out_5486619309331330377[234] = 0.0;
   out_5486619309331330377[235] = 0.0;
   out_5486619309331330377[236] = 0.0;
   out_5486619309331330377[237] = 0.0;
   out_5486619309331330377[238] = 0.0;
   out_5486619309331330377[239] = 0.0;
   out_5486619309331330377[240] = 0.0;
   out_5486619309331330377[241] = 0.0;
   out_5486619309331330377[242] = 0.0;
   out_5486619309331330377[243] = 0.0;
   out_5486619309331330377[244] = 0.0;
   out_5486619309331330377[245] = 0.0;
   out_5486619309331330377[246] = 0.0;
   out_5486619309331330377[247] = 1.0;
   out_5486619309331330377[248] = 0.0;
   out_5486619309331330377[249] = 0.0;
   out_5486619309331330377[250] = 0.0;
   out_5486619309331330377[251] = 0.0;
   out_5486619309331330377[252] = 0.0;
   out_5486619309331330377[253] = 0.0;
   out_5486619309331330377[254] = 0.0;
   out_5486619309331330377[255] = 0.0;
   out_5486619309331330377[256] = 0.0;
   out_5486619309331330377[257] = 0.0;
   out_5486619309331330377[258] = 0.0;
   out_5486619309331330377[259] = 0.0;
   out_5486619309331330377[260] = 0.0;
   out_5486619309331330377[261] = 0.0;
   out_5486619309331330377[262] = 0.0;
   out_5486619309331330377[263] = 0.0;
   out_5486619309331330377[264] = 0.0;
   out_5486619309331330377[265] = 0.0;
   out_5486619309331330377[266] = 1.0;
   out_5486619309331330377[267] = 0.0;
   out_5486619309331330377[268] = 0.0;
   out_5486619309331330377[269] = 0.0;
   out_5486619309331330377[270] = 0.0;
   out_5486619309331330377[271] = 0.0;
   out_5486619309331330377[272] = 0.0;
   out_5486619309331330377[273] = 0.0;
   out_5486619309331330377[274] = 0.0;
   out_5486619309331330377[275] = 0.0;
   out_5486619309331330377[276] = 0.0;
   out_5486619309331330377[277] = 0.0;
   out_5486619309331330377[278] = 0.0;
   out_5486619309331330377[279] = 0.0;
   out_5486619309331330377[280] = 0.0;
   out_5486619309331330377[281] = 0.0;
   out_5486619309331330377[282] = 0.0;
   out_5486619309331330377[283] = 0.0;
   out_5486619309331330377[284] = 0.0;
   out_5486619309331330377[285] = 1.0;
   out_5486619309331330377[286] = 0.0;
   out_5486619309331330377[287] = 0.0;
   out_5486619309331330377[288] = 0.0;
   out_5486619309331330377[289] = 0.0;
   out_5486619309331330377[290] = 0.0;
   out_5486619309331330377[291] = 0.0;
   out_5486619309331330377[292] = 0.0;
   out_5486619309331330377[293] = 0.0;
   out_5486619309331330377[294] = 0.0;
   out_5486619309331330377[295] = 0.0;
   out_5486619309331330377[296] = 0.0;
   out_5486619309331330377[297] = 0.0;
   out_5486619309331330377[298] = 0.0;
   out_5486619309331330377[299] = 0.0;
   out_5486619309331330377[300] = 0.0;
   out_5486619309331330377[301] = 0.0;
   out_5486619309331330377[302] = 0.0;
   out_5486619309331330377[303] = 0.0;
   out_5486619309331330377[304] = 1.0;
   out_5486619309331330377[305] = 0.0;
   out_5486619309331330377[306] = 0.0;
   out_5486619309331330377[307] = 0.0;
   out_5486619309331330377[308] = 0.0;
   out_5486619309331330377[309] = 0.0;
   out_5486619309331330377[310] = 0.0;
   out_5486619309331330377[311] = 0.0;
   out_5486619309331330377[312] = 0.0;
   out_5486619309331330377[313] = 0.0;
   out_5486619309331330377[314] = 0.0;
   out_5486619309331330377[315] = 0.0;
   out_5486619309331330377[316] = 0.0;
   out_5486619309331330377[317] = 0.0;
   out_5486619309331330377[318] = 0.0;
   out_5486619309331330377[319] = 0.0;
   out_5486619309331330377[320] = 0.0;
   out_5486619309331330377[321] = 0.0;
   out_5486619309331330377[322] = 0.0;
   out_5486619309331330377[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1235871428435988271) {
   out_1235871428435988271[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1235871428435988271[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1235871428435988271[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1235871428435988271[3] = dt*state[12] + state[3];
   out_1235871428435988271[4] = dt*state[13] + state[4];
   out_1235871428435988271[5] = dt*state[14] + state[5];
   out_1235871428435988271[6] = state[6];
   out_1235871428435988271[7] = state[7];
   out_1235871428435988271[8] = state[8];
   out_1235871428435988271[9] = state[9];
   out_1235871428435988271[10] = state[10];
   out_1235871428435988271[11] = state[11];
   out_1235871428435988271[12] = state[12];
   out_1235871428435988271[13] = state[13];
   out_1235871428435988271[14] = state[14];
   out_1235871428435988271[15] = state[15];
   out_1235871428435988271[16] = state[16];
   out_1235871428435988271[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6226252063534521061) {
   out_6226252063534521061[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6226252063534521061[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6226252063534521061[2] = 0;
   out_6226252063534521061[3] = 0;
   out_6226252063534521061[4] = 0;
   out_6226252063534521061[5] = 0;
   out_6226252063534521061[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6226252063534521061[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6226252063534521061[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6226252063534521061[9] = 0;
   out_6226252063534521061[10] = 0;
   out_6226252063534521061[11] = 0;
   out_6226252063534521061[12] = 0;
   out_6226252063534521061[13] = 0;
   out_6226252063534521061[14] = 0;
   out_6226252063534521061[15] = 0;
   out_6226252063534521061[16] = 0;
   out_6226252063534521061[17] = 0;
   out_6226252063534521061[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6226252063534521061[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6226252063534521061[20] = 0;
   out_6226252063534521061[21] = 0;
   out_6226252063534521061[22] = 0;
   out_6226252063534521061[23] = 0;
   out_6226252063534521061[24] = 0;
   out_6226252063534521061[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6226252063534521061[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6226252063534521061[27] = 0;
   out_6226252063534521061[28] = 0;
   out_6226252063534521061[29] = 0;
   out_6226252063534521061[30] = 0;
   out_6226252063534521061[31] = 0;
   out_6226252063534521061[32] = 0;
   out_6226252063534521061[33] = 0;
   out_6226252063534521061[34] = 0;
   out_6226252063534521061[35] = 0;
   out_6226252063534521061[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6226252063534521061[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6226252063534521061[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6226252063534521061[39] = 0;
   out_6226252063534521061[40] = 0;
   out_6226252063534521061[41] = 0;
   out_6226252063534521061[42] = 0;
   out_6226252063534521061[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6226252063534521061[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6226252063534521061[45] = 0;
   out_6226252063534521061[46] = 0;
   out_6226252063534521061[47] = 0;
   out_6226252063534521061[48] = 0;
   out_6226252063534521061[49] = 0;
   out_6226252063534521061[50] = 0;
   out_6226252063534521061[51] = 0;
   out_6226252063534521061[52] = 0;
   out_6226252063534521061[53] = 0;
   out_6226252063534521061[54] = 0;
   out_6226252063534521061[55] = 0;
   out_6226252063534521061[56] = 0;
   out_6226252063534521061[57] = 1;
   out_6226252063534521061[58] = 0;
   out_6226252063534521061[59] = 0;
   out_6226252063534521061[60] = 0;
   out_6226252063534521061[61] = 0;
   out_6226252063534521061[62] = 0;
   out_6226252063534521061[63] = 0;
   out_6226252063534521061[64] = 0;
   out_6226252063534521061[65] = 0;
   out_6226252063534521061[66] = dt;
   out_6226252063534521061[67] = 0;
   out_6226252063534521061[68] = 0;
   out_6226252063534521061[69] = 0;
   out_6226252063534521061[70] = 0;
   out_6226252063534521061[71] = 0;
   out_6226252063534521061[72] = 0;
   out_6226252063534521061[73] = 0;
   out_6226252063534521061[74] = 0;
   out_6226252063534521061[75] = 0;
   out_6226252063534521061[76] = 1;
   out_6226252063534521061[77] = 0;
   out_6226252063534521061[78] = 0;
   out_6226252063534521061[79] = 0;
   out_6226252063534521061[80] = 0;
   out_6226252063534521061[81] = 0;
   out_6226252063534521061[82] = 0;
   out_6226252063534521061[83] = 0;
   out_6226252063534521061[84] = 0;
   out_6226252063534521061[85] = dt;
   out_6226252063534521061[86] = 0;
   out_6226252063534521061[87] = 0;
   out_6226252063534521061[88] = 0;
   out_6226252063534521061[89] = 0;
   out_6226252063534521061[90] = 0;
   out_6226252063534521061[91] = 0;
   out_6226252063534521061[92] = 0;
   out_6226252063534521061[93] = 0;
   out_6226252063534521061[94] = 0;
   out_6226252063534521061[95] = 1;
   out_6226252063534521061[96] = 0;
   out_6226252063534521061[97] = 0;
   out_6226252063534521061[98] = 0;
   out_6226252063534521061[99] = 0;
   out_6226252063534521061[100] = 0;
   out_6226252063534521061[101] = 0;
   out_6226252063534521061[102] = 0;
   out_6226252063534521061[103] = 0;
   out_6226252063534521061[104] = dt;
   out_6226252063534521061[105] = 0;
   out_6226252063534521061[106] = 0;
   out_6226252063534521061[107] = 0;
   out_6226252063534521061[108] = 0;
   out_6226252063534521061[109] = 0;
   out_6226252063534521061[110] = 0;
   out_6226252063534521061[111] = 0;
   out_6226252063534521061[112] = 0;
   out_6226252063534521061[113] = 0;
   out_6226252063534521061[114] = 1;
   out_6226252063534521061[115] = 0;
   out_6226252063534521061[116] = 0;
   out_6226252063534521061[117] = 0;
   out_6226252063534521061[118] = 0;
   out_6226252063534521061[119] = 0;
   out_6226252063534521061[120] = 0;
   out_6226252063534521061[121] = 0;
   out_6226252063534521061[122] = 0;
   out_6226252063534521061[123] = 0;
   out_6226252063534521061[124] = 0;
   out_6226252063534521061[125] = 0;
   out_6226252063534521061[126] = 0;
   out_6226252063534521061[127] = 0;
   out_6226252063534521061[128] = 0;
   out_6226252063534521061[129] = 0;
   out_6226252063534521061[130] = 0;
   out_6226252063534521061[131] = 0;
   out_6226252063534521061[132] = 0;
   out_6226252063534521061[133] = 1;
   out_6226252063534521061[134] = 0;
   out_6226252063534521061[135] = 0;
   out_6226252063534521061[136] = 0;
   out_6226252063534521061[137] = 0;
   out_6226252063534521061[138] = 0;
   out_6226252063534521061[139] = 0;
   out_6226252063534521061[140] = 0;
   out_6226252063534521061[141] = 0;
   out_6226252063534521061[142] = 0;
   out_6226252063534521061[143] = 0;
   out_6226252063534521061[144] = 0;
   out_6226252063534521061[145] = 0;
   out_6226252063534521061[146] = 0;
   out_6226252063534521061[147] = 0;
   out_6226252063534521061[148] = 0;
   out_6226252063534521061[149] = 0;
   out_6226252063534521061[150] = 0;
   out_6226252063534521061[151] = 0;
   out_6226252063534521061[152] = 1;
   out_6226252063534521061[153] = 0;
   out_6226252063534521061[154] = 0;
   out_6226252063534521061[155] = 0;
   out_6226252063534521061[156] = 0;
   out_6226252063534521061[157] = 0;
   out_6226252063534521061[158] = 0;
   out_6226252063534521061[159] = 0;
   out_6226252063534521061[160] = 0;
   out_6226252063534521061[161] = 0;
   out_6226252063534521061[162] = 0;
   out_6226252063534521061[163] = 0;
   out_6226252063534521061[164] = 0;
   out_6226252063534521061[165] = 0;
   out_6226252063534521061[166] = 0;
   out_6226252063534521061[167] = 0;
   out_6226252063534521061[168] = 0;
   out_6226252063534521061[169] = 0;
   out_6226252063534521061[170] = 0;
   out_6226252063534521061[171] = 1;
   out_6226252063534521061[172] = 0;
   out_6226252063534521061[173] = 0;
   out_6226252063534521061[174] = 0;
   out_6226252063534521061[175] = 0;
   out_6226252063534521061[176] = 0;
   out_6226252063534521061[177] = 0;
   out_6226252063534521061[178] = 0;
   out_6226252063534521061[179] = 0;
   out_6226252063534521061[180] = 0;
   out_6226252063534521061[181] = 0;
   out_6226252063534521061[182] = 0;
   out_6226252063534521061[183] = 0;
   out_6226252063534521061[184] = 0;
   out_6226252063534521061[185] = 0;
   out_6226252063534521061[186] = 0;
   out_6226252063534521061[187] = 0;
   out_6226252063534521061[188] = 0;
   out_6226252063534521061[189] = 0;
   out_6226252063534521061[190] = 1;
   out_6226252063534521061[191] = 0;
   out_6226252063534521061[192] = 0;
   out_6226252063534521061[193] = 0;
   out_6226252063534521061[194] = 0;
   out_6226252063534521061[195] = 0;
   out_6226252063534521061[196] = 0;
   out_6226252063534521061[197] = 0;
   out_6226252063534521061[198] = 0;
   out_6226252063534521061[199] = 0;
   out_6226252063534521061[200] = 0;
   out_6226252063534521061[201] = 0;
   out_6226252063534521061[202] = 0;
   out_6226252063534521061[203] = 0;
   out_6226252063534521061[204] = 0;
   out_6226252063534521061[205] = 0;
   out_6226252063534521061[206] = 0;
   out_6226252063534521061[207] = 0;
   out_6226252063534521061[208] = 0;
   out_6226252063534521061[209] = 1;
   out_6226252063534521061[210] = 0;
   out_6226252063534521061[211] = 0;
   out_6226252063534521061[212] = 0;
   out_6226252063534521061[213] = 0;
   out_6226252063534521061[214] = 0;
   out_6226252063534521061[215] = 0;
   out_6226252063534521061[216] = 0;
   out_6226252063534521061[217] = 0;
   out_6226252063534521061[218] = 0;
   out_6226252063534521061[219] = 0;
   out_6226252063534521061[220] = 0;
   out_6226252063534521061[221] = 0;
   out_6226252063534521061[222] = 0;
   out_6226252063534521061[223] = 0;
   out_6226252063534521061[224] = 0;
   out_6226252063534521061[225] = 0;
   out_6226252063534521061[226] = 0;
   out_6226252063534521061[227] = 0;
   out_6226252063534521061[228] = 1;
   out_6226252063534521061[229] = 0;
   out_6226252063534521061[230] = 0;
   out_6226252063534521061[231] = 0;
   out_6226252063534521061[232] = 0;
   out_6226252063534521061[233] = 0;
   out_6226252063534521061[234] = 0;
   out_6226252063534521061[235] = 0;
   out_6226252063534521061[236] = 0;
   out_6226252063534521061[237] = 0;
   out_6226252063534521061[238] = 0;
   out_6226252063534521061[239] = 0;
   out_6226252063534521061[240] = 0;
   out_6226252063534521061[241] = 0;
   out_6226252063534521061[242] = 0;
   out_6226252063534521061[243] = 0;
   out_6226252063534521061[244] = 0;
   out_6226252063534521061[245] = 0;
   out_6226252063534521061[246] = 0;
   out_6226252063534521061[247] = 1;
   out_6226252063534521061[248] = 0;
   out_6226252063534521061[249] = 0;
   out_6226252063534521061[250] = 0;
   out_6226252063534521061[251] = 0;
   out_6226252063534521061[252] = 0;
   out_6226252063534521061[253] = 0;
   out_6226252063534521061[254] = 0;
   out_6226252063534521061[255] = 0;
   out_6226252063534521061[256] = 0;
   out_6226252063534521061[257] = 0;
   out_6226252063534521061[258] = 0;
   out_6226252063534521061[259] = 0;
   out_6226252063534521061[260] = 0;
   out_6226252063534521061[261] = 0;
   out_6226252063534521061[262] = 0;
   out_6226252063534521061[263] = 0;
   out_6226252063534521061[264] = 0;
   out_6226252063534521061[265] = 0;
   out_6226252063534521061[266] = 1;
   out_6226252063534521061[267] = 0;
   out_6226252063534521061[268] = 0;
   out_6226252063534521061[269] = 0;
   out_6226252063534521061[270] = 0;
   out_6226252063534521061[271] = 0;
   out_6226252063534521061[272] = 0;
   out_6226252063534521061[273] = 0;
   out_6226252063534521061[274] = 0;
   out_6226252063534521061[275] = 0;
   out_6226252063534521061[276] = 0;
   out_6226252063534521061[277] = 0;
   out_6226252063534521061[278] = 0;
   out_6226252063534521061[279] = 0;
   out_6226252063534521061[280] = 0;
   out_6226252063534521061[281] = 0;
   out_6226252063534521061[282] = 0;
   out_6226252063534521061[283] = 0;
   out_6226252063534521061[284] = 0;
   out_6226252063534521061[285] = 1;
   out_6226252063534521061[286] = 0;
   out_6226252063534521061[287] = 0;
   out_6226252063534521061[288] = 0;
   out_6226252063534521061[289] = 0;
   out_6226252063534521061[290] = 0;
   out_6226252063534521061[291] = 0;
   out_6226252063534521061[292] = 0;
   out_6226252063534521061[293] = 0;
   out_6226252063534521061[294] = 0;
   out_6226252063534521061[295] = 0;
   out_6226252063534521061[296] = 0;
   out_6226252063534521061[297] = 0;
   out_6226252063534521061[298] = 0;
   out_6226252063534521061[299] = 0;
   out_6226252063534521061[300] = 0;
   out_6226252063534521061[301] = 0;
   out_6226252063534521061[302] = 0;
   out_6226252063534521061[303] = 0;
   out_6226252063534521061[304] = 1;
   out_6226252063534521061[305] = 0;
   out_6226252063534521061[306] = 0;
   out_6226252063534521061[307] = 0;
   out_6226252063534521061[308] = 0;
   out_6226252063534521061[309] = 0;
   out_6226252063534521061[310] = 0;
   out_6226252063534521061[311] = 0;
   out_6226252063534521061[312] = 0;
   out_6226252063534521061[313] = 0;
   out_6226252063534521061[314] = 0;
   out_6226252063534521061[315] = 0;
   out_6226252063534521061[316] = 0;
   out_6226252063534521061[317] = 0;
   out_6226252063534521061[318] = 0;
   out_6226252063534521061[319] = 0;
   out_6226252063534521061[320] = 0;
   out_6226252063534521061[321] = 0;
   out_6226252063534521061[322] = 0;
   out_6226252063534521061[323] = 1;
}
void h_4(double *state, double *unused, double *out_3900248353984202260) {
   out_3900248353984202260[0] = state[6] + state[9];
   out_3900248353984202260[1] = state[7] + state[10];
   out_3900248353984202260[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4732458307276617770) {
   out_4732458307276617770[0] = 0;
   out_4732458307276617770[1] = 0;
   out_4732458307276617770[2] = 0;
   out_4732458307276617770[3] = 0;
   out_4732458307276617770[4] = 0;
   out_4732458307276617770[5] = 0;
   out_4732458307276617770[6] = 1;
   out_4732458307276617770[7] = 0;
   out_4732458307276617770[8] = 0;
   out_4732458307276617770[9] = 1;
   out_4732458307276617770[10] = 0;
   out_4732458307276617770[11] = 0;
   out_4732458307276617770[12] = 0;
   out_4732458307276617770[13] = 0;
   out_4732458307276617770[14] = 0;
   out_4732458307276617770[15] = 0;
   out_4732458307276617770[16] = 0;
   out_4732458307276617770[17] = 0;
   out_4732458307276617770[18] = 0;
   out_4732458307276617770[19] = 0;
   out_4732458307276617770[20] = 0;
   out_4732458307276617770[21] = 0;
   out_4732458307276617770[22] = 0;
   out_4732458307276617770[23] = 0;
   out_4732458307276617770[24] = 0;
   out_4732458307276617770[25] = 1;
   out_4732458307276617770[26] = 0;
   out_4732458307276617770[27] = 0;
   out_4732458307276617770[28] = 1;
   out_4732458307276617770[29] = 0;
   out_4732458307276617770[30] = 0;
   out_4732458307276617770[31] = 0;
   out_4732458307276617770[32] = 0;
   out_4732458307276617770[33] = 0;
   out_4732458307276617770[34] = 0;
   out_4732458307276617770[35] = 0;
   out_4732458307276617770[36] = 0;
   out_4732458307276617770[37] = 0;
   out_4732458307276617770[38] = 0;
   out_4732458307276617770[39] = 0;
   out_4732458307276617770[40] = 0;
   out_4732458307276617770[41] = 0;
   out_4732458307276617770[42] = 0;
   out_4732458307276617770[43] = 0;
   out_4732458307276617770[44] = 1;
   out_4732458307276617770[45] = 0;
   out_4732458307276617770[46] = 0;
   out_4732458307276617770[47] = 1;
   out_4732458307276617770[48] = 0;
   out_4732458307276617770[49] = 0;
   out_4732458307276617770[50] = 0;
   out_4732458307276617770[51] = 0;
   out_4732458307276617770[52] = 0;
   out_4732458307276617770[53] = 0;
}
void h_10(double *state, double *unused, double *out_5710312720723321812) {
   out_5710312720723321812[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5710312720723321812[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5710312720723321812[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1994324288274465262) {
   out_1994324288274465262[0] = 0;
   out_1994324288274465262[1] = 9.8100000000000005*cos(state[1]);
   out_1994324288274465262[2] = 0;
   out_1994324288274465262[3] = 0;
   out_1994324288274465262[4] = -state[8];
   out_1994324288274465262[5] = state[7];
   out_1994324288274465262[6] = 0;
   out_1994324288274465262[7] = state[5];
   out_1994324288274465262[8] = -state[4];
   out_1994324288274465262[9] = 0;
   out_1994324288274465262[10] = 0;
   out_1994324288274465262[11] = 0;
   out_1994324288274465262[12] = 1;
   out_1994324288274465262[13] = 0;
   out_1994324288274465262[14] = 0;
   out_1994324288274465262[15] = 1;
   out_1994324288274465262[16] = 0;
   out_1994324288274465262[17] = 0;
   out_1994324288274465262[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1994324288274465262[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1994324288274465262[20] = 0;
   out_1994324288274465262[21] = state[8];
   out_1994324288274465262[22] = 0;
   out_1994324288274465262[23] = -state[6];
   out_1994324288274465262[24] = -state[5];
   out_1994324288274465262[25] = 0;
   out_1994324288274465262[26] = state[3];
   out_1994324288274465262[27] = 0;
   out_1994324288274465262[28] = 0;
   out_1994324288274465262[29] = 0;
   out_1994324288274465262[30] = 0;
   out_1994324288274465262[31] = 1;
   out_1994324288274465262[32] = 0;
   out_1994324288274465262[33] = 0;
   out_1994324288274465262[34] = 1;
   out_1994324288274465262[35] = 0;
   out_1994324288274465262[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1994324288274465262[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1994324288274465262[38] = 0;
   out_1994324288274465262[39] = -state[7];
   out_1994324288274465262[40] = state[6];
   out_1994324288274465262[41] = 0;
   out_1994324288274465262[42] = state[4];
   out_1994324288274465262[43] = -state[3];
   out_1994324288274465262[44] = 0;
   out_1994324288274465262[45] = 0;
   out_1994324288274465262[46] = 0;
   out_1994324288274465262[47] = 0;
   out_1994324288274465262[48] = 0;
   out_1994324288274465262[49] = 0;
   out_1994324288274465262[50] = 1;
   out_1994324288274465262[51] = 0;
   out_1994324288274465262[52] = 0;
   out_1994324288274465262[53] = 1;
}
void h_13(double *state, double *unused, double *out_6587030294683941770) {
   out_6587030294683941770[0] = state[3];
   out_6587030294683941770[1] = state[4];
   out_6587030294683941770[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1520184481944284969) {
   out_1520184481944284969[0] = 0;
   out_1520184481944284969[1] = 0;
   out_1520184481944284969[2] = 0;
   out_1520184481944284969[3] = 1;
   out_1520184481944284969[4] = 0;
   out_1520184481944284969[5] = 0;
   out_1520184481944284969[6] = 0;
   out_1520184481944284969[7] = 0;
   out_1520184481944284969[8] = 0;
   out_1520184481944284969[9] = 0;
   out_1520184481944284969[10] = 0;
   out_1520184481944284969[11] = 0;
   out_1520184481944284969[12] = 0;
   out_1520184481944284969[13] = 0;
   out_1520184481944284969[14] = 0;
   out_1520184481944284969[15] = 0;
   out_1520184481944284969[16] = 0;
   out_1520184481944284969[17] = 0;
   out_1520184481944284969[18] = 0;
   out_1520184481944284969[19] = 0;
   out_1520184481944284969[20] = 0;
   out_1520184481944284969[21] = 0;
   out_1520184481944284969[22] = 1;
   out_1520184481944284969[23] = 0;
   out_1520184481944284969[24] = 0;
   out_1520184481944284969[25] = 0;
   out_1520184481944284969[26] = 0;
   out_1520184481944284969[27] = 0;
   out_1520184481944284969[28] = 0;
   out_1520184481944284969[29] = 0;
   out_1520184481944284969[30] = 0;
   out_1520184481944284969[31] = 0;
   out_1520184481944284969[32] = 0;
   out_1520184481944284969[33] = 0;
   out_1520184481944284969[34] = 0;
   out_1520184481944284969[35] = 0;
   out_1520184481944284969[36] = 0;
   out_1520184481944284969[37] = 0;
   out_1520184481944284969[38] = 0;
   out_1520184481944284969[39] = 0;
   out_1520184481944284969[40] = 0;
   out_1520184481944284969[41] = 1;
   out_1520184481944284969[42] = 0;
   out_1520184481944284969[43] = 0;
   out_1520184481944284969[44] = 0;
   out_1520184481944284969[45] = 0;
   out_1520184481944284969[46] = 0;
   out_1520184481944284969[47] = 0;
   out_1520184481944284969[48] = 0;
   out_1520184481944284969[49] = 0;
   out_1520184481944284969[50] = 0;
   out_1520184481944284969[51] = 0;
   out_1520184481944284969[52] = 0;
   out_1520184481944284969[53] = 0;
}
void h_14(double *state, double *unused, double *out_5256678746065369612) {
   out_5256678746065369612[0] = state[6];
   out_5256678746065369612[1] = state[7];
   out_5256678746065369612[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7815246739571990066) {
   out_7815246739571990066[0] = 0;
   out_7815246739571990066[1] = 0;
   out_7815246739571990066[2] = 0;
   out_7815246739571990066[3] = 0;
   out_7815246739571990066[4] = 0;
   out_7815246739571990066[5] = 0;
   out_7815246739571990066[6] = 1;
   out_7815246739571990066[7] = 0;
   out_7815246739571990066[8] = 0;
   out_7815246739571990066[9] = 0;
   out_7815246739571990066[10] = 0;
   out_7815246739571990066[11] = 0;
   out_7815246739571990066[12] = 0;
   out_7815246739571990066[13] = 0;
   out_7815246739571990066[14] = 0;
   out_7815246739571990066[15] = 0;
   out_7815246739571990066[16] = 0;
   out_7815246739571990066[17] = 0;
   out_7815246739571990066[18] = 0;
   out_7815246739571990066[19] = 0;
   out_7815246739571990066[20] = 0;
   out_7815246739571990066[21] = 0;
   out_7815246739571990066[22] = 0;
   out_7815246739571990066[23] = 0;
   out_7815246739571990066[24] = 0;
   out_7815246739571990066[25] = 1;
   out_7815246739571990066[26] = 0;
   out_7815246739571990066[27] = 0;
   out_7815246739571990066[28] = 0;
   out_7815246739571990066[29] = 0;
   out_7815246739571990066[30] = 0;
   out_7815246739571990066[31] = 0;
   out_7815246739571990066[32] = 0;
   out_7815246739571990066[33] = 0;
   out_7815246739571990066[34] = 0;
   out_7815246739571990066[35] = 0;
   out_7815246739571990066[36] = 0;
   out_7815246739571990066[37] = 0;
   out_7815246739571990066[38] = 0;
   out_7815246739571990066[39] = 0;
   out_7815246739571990066[40] = 0;
   out_7815246739571990066[41] = 0;
   out_7815246739571990066[42] = 0;
   out_7815246739571990066[43] = 0;
   out_7815246739571990066[44] = 1;
   out_7815246739571990066[45] = 0;
   out_7815246739571990066[46] = 0;
   out_7815246739571990066[47] = 0;
   out_7815246739571990066[48] = 0;
   out_7815246739571990066[49] = 0;
   out_7815246739571990066[50] = 0;
   out_7815246739571990066[51] = 0;
   out_7815246739571990066[52] = 0;
   out_7815246739571990066[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6950291583245326091) {
  err_fun(nom_x, delta_x, out_6950291583245326091);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7864587791361010025) {
  inv_err_fun(nom_x, true_x, out_7864587791361010025);
}
void pose_H_mod_fun(double *state, double *out_5486619309331330377) {
  H_mod_fun(state, out_5486619309331330377);
}
void pose_f_fun(double *state, double dt, double *out_1235871428435988271) {
  f_fun(state,  dt, out_1235871428435988271);
}
void pose_F_fun(double *state, double dt, double *out_6226252063534521061) {
  F_fun(state,  dt, out_6226252063534521061);
}
void pose_h_4(double *state, double *unused, double *out_3900248353984202260) {
  h_4(state, unused, out_3900248353984202260);
}
void pose_H_4(double *state, double *unused, double *out_4732458307276617770) {
  H_4(state, unused, out_4732458307276617770);
}
void pose_h_10(double *state, double *unused, double *out_5710312720723321812) {
  h_10(state, unused, out_5710312720723321812);
}
void pose_H_10(double *state, double *unused, double *out_1994324288274465262) {
  H_10(state, unused, out_1994324288274465262);
}
void pose_h_13(double *state, double *unused, double *out_6587030294683941770) {
  h_13(state, unused, out_6587030294683941770);
}
void pose_H_13(double *state, double *unused, double *out_1520184481944284969) {
  H_13(state, unused, out_1520184481944284969);
}
void pose_h_14(double *state, double *unused, double *out_5256678746065369612) {
  h_14(state, unused, out_5256678746065369612);
}
void pose_H_14(double *state, double *unused, double *out_7815246739571990066) {
  H_14(state, unused, out_7815246739571990066);
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
