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
void err_fun(double *nom_x, double *delta_x, double *out_6360695334706395645) {
   out_6360695334706395645[0] = delta_x[0] + nom_x[0];
   out_6360695334706395645[1] = delta_x[1] + nom_x[1];
   out_6360695334706395645[2] = delta_x[2] + nom_x[2];
   out_6360695334706395645[3] = delta_x[3] + nom_x[3];
   out_6360695334706395645[4] = delta_x[4] + nom_x[4];
   out_6360695334706395645[5] = delta_x[5] + nom_x[5];
   out_6360695334706395645[6] = delta_x[6] + nom_x[6];
   out_6360695334706395645[7] = delta_x[7] + nom_x[7];
   out_6360695334706395645[8] = delta_x[8] + nom_x[8];
   out_6360695334706395645[9] = delta_x[9] + nom_x[9];
   out_6360695334706395645[10] = delta_x[10] + nom_x[10];
   out_6360695334706395645[11] = delta_x[11] + nom_x[11];
   out_6360695334706395645[12] = delta_x[12] + nom_x[12];
   out_6360695334706395645[13] = delta_x[13] + nom_x[13];
   out_6360695334706395645[14] = delta_x[14] + nom_x[14];
   out_6360695334706395645[15] = delta_x[15] + nom_x[15];
   out_6360695334706395645[16] = delta_x[16] + nom_x[16];
   out_6360695334706395645[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3498794849105875793) {
   out_3498794849105875793[0] = -nom_x[0] + true_x[0];
   out_3498794849105875793[1] = -nom_x[1] + true_x[1];
   out_3498794849105875793[2] = -nom_x[2] + true_x[2];
   out_3498794849105875793[3] = -nom_x[3] + true_x[3];
   out_3498794849105875793[4] = -nom_x[4] + true_x[4];
   out_3498794849105875793[5] = -nom_x[5] + true_x[5];
   out_3498794849105875793[6] = -nom_x[6] + true_x[6];
   out_3498794849105875793[7] = -nom_x[7] + true_x[7];
   out_3498794849105875793[8] = -nom_x[8] + true_x[8];
   out_3498794849105875793[9] = -nom_x[9] + true_x[9];
   out_3498794849105875793[10] = -nom_x[10] + true_x[10];
   out_3498794849105875793[11] = -nom_x[11] + true_x[11];
   out_3498794849105875793[12] = -nom_x[12] + true_x[12];
   out_3498794849105875793[13] = -nom_x[13] + true_x[13];
   out_3498794849105875793[14] = -nom_x[14] + true_x[14];
   out_3498794849105875793[15] = -nom_x[15] + true_x[15];
   out_3498794849105875793[16] = -nom_x[16] + true_x[16];
   out_3498794849105875793[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9153131841173163388) {
   out_9153131841173163388[0] = 1.0;
   out_9153131841173163388[1] = 0.0;
   out_9153131841173163388[2] = 0.0;
   out_9153131841173163388[3] = 0.0;
   out_9153131841173163388[4] = 0.0;
   out_9153131841173163388[5] = 0.0;
   out_9153131841173163388[6] = 0.0;
   out_9153131841173163388[7] = 0.0;
   out_9153131841173163388[8] = 0.0;
   out_9153131841173163388[9] = 0.0;
   out_9153131841173163388[10] = 0.0;
   out_9153131841173163388[11] = 0.0;
   out_9153131841173163388[12] = 0.0;
   out_9153131841173163388[13] = 0.0;
   out_9153131841173163388[14] = 0.0;
   out_9153131841173163388[15] = 0.0;
   out_9153131841173163388[16] = 0.0;
   out_9153131841173163388[17] = 0.0;
   out_9153131841173163388[18] = 0.0;
   out_9153131841173163388[19] = 1.0;
   out_9153131841173163388[20] = 0.0;
   out_9153131841173163388[21] = 0.0;
   out_9153131841173163388[22] = 0.0;
   out_9153131841173163388[23] = 0.0;
   out_9153131841173163388[24] = 0.0;
   out_9153131841173163388[25] = 0.0;
   out_9153131841173163388[26] = 0.0;
   out_9153131841173163388[27] = 0.0;
   out_9153131841173163388[28] = 0.0;
   out_9153131841173163388[29] = 0.0;
   out_9153131841173163388[30] = 0.0;
   out_9153131841173163388[31] = 0.0;
   out_9153131841173163388[32] = 0.0;
   out_9153131841173163388[33] = 0.0;
   out_9153131841173163388[34] = 0.0;
   out_9153131841173163388[35] = 0.0;
   out_9153131841173163388[36] = 0.0;
   out_9153131841173163388[37] = 0.0;
   out_9153131841173163388[38] = 1.0;
   out_9153131841173163388[39] = 0.0;
   out_9153131841173163388[40] = 0.0;
   out_9153131841173163388[41] = 0.0;
   out_9153131841173163388[42] = 0.0;
   out_9153131841173163388[43] = 0.0;
   out_9153131841173163388[44] = 0.0;
   out_9153131841173163388[45] = 0.0;
   out_9153131841173163388[46] = 0.0;
   out_9153131841173163388[47] = 0.0;
   out_9153131841173163388[48] = 0.0;
   out_9153131841173163388[49] = 0.0;
   out_9153131841173163388[50] = 0.0;
   out_9153131841173163388[51] = 0.0;
   out_9153131841173163388[52] = 0.0;
   out_9153131841173163388[53] = 0.0;
   out_9153131841173163388[54] = 0.0;
   out_9153131841173163388[55] = 0.0;
   out_9153131841173163388[56] = 0.0;
   out_9153131841173163388[57] = 1.0;
   out_9153131841173163388[58] = 0.0;
   out_9153131841173163388[59] = 0.0;
   out_9153131841173163388[60] = 0.0;
   out_9153131841173163388[61] = 0.0;
   out_9153131841173163388[62] = 0.0;
   out_9153131841173163388[63] = 0.0;
   out_9153131841173163388[64] = 0.0;
   out_9153131841173163388[65] = 0.0;
   out_9153131841173163388[66] = 0.0;
   out_9153131841173163388[67] = 0.0;
   out_9153131841173163388[68] = 0.0;
   out_9153131841173163388[69] = 0.0;
   out_9153131841173163388[70] = 0.0;
   out_9153131841173163388[71] = 0.0;
   out_9153131841173163388[72] = 0.0;
   out_9153131841173163388[73] = 0.0;
   out_9153131841173163388[74] = 0.0;
   out_9153131841173163388[75] = 0.0;
   out_9153131841173163388[76] = 1.0;
   out_9153131841173163388[77] = 0.0;
   out_9153131841173163388[78] = 0.0;
   out_9153131841173163388[79] = 0.0;
   out_9153131841173163388[80] = 0.0;
   out_9153131841173163388[81] = 0.0;
   out_9153131841173163388[82] = 0.0;
   out_9153131841173163388[83] = 0.0;
   out_9153131841173163388[84] = 0.0;
   out_9153131841173163388[85] = 0.0;
   out_9153131841173163388[86] = 0.0;
   out_9153131841173163388[87] = 0.0;
   out_9153131841173163388[88] = 0.0;
   out_9153131841173163388[89] = 0.0;
   out_9153131841173163388[90] = 0.0;
   out_9153131841173163388[91] = 0.0;
   out_9153131841173163388[92] = 0.0;
   out_9153131841173163388[93] = 0.0;
   out_9153131841173163388[94] = 0.0;
   out_9153131841173163388[95] = 1.0;
   out_9153131841173163388[96] = 0.0;
   out_9153131841173163388[97] = 0.0;
   out_9153131841173163388[98] = 0.0;
   out_9153131841173163388[99] = 0.0;
   out_9153131841173163388[100] = 0.0;
   out_9153131841173163388[101] = 0.0;
   out_9153131841173163388[102] = 0.0;
   out_9153131841173163388[103] = 0.0;
   out_9153131841173163388[104] = 0.0;
   out_9153131841173163388[105] = 0.0;
   out_9153131841173163388[106] = 0.0;
   out_9153131841173163388[107] = 0.0;
   out_9153131841173163388[108] = 0.0;
   out_9153131841173163388[109] = 0.0;
   out_9153131841173163388[110] = 0.0;
   out_9153131841173163388[111] = 0.0;
   out_9153131841173163388[112] = 0.0;
   out_9153131841173163388[113] = 0.0;
   out_9153131841173163388[114] = 1.0;
   out_9153131841173163388[115] = 0.0;
   out_9153131841173163388[116] = 0.0;
   out_9153131841173163388[117] = 0.0;
   out_9153131841173163388[118] = 0.0;
   out_9153131841173163388[119] = 0.0;
   out_9153131841173163388[120] = 0.0;
   out_9153131841173163388[121] = 0.0;
   out_9153131841173163388[122] = 0.0;
   out_9153131841173163388[123] = 0.0;
   out_9153131841173163388[124] = 0.0;
   out_9153131841173163388[125] = 0.0;
   out_9153131841173163388[126] = 0.0;
   out_9153131841173163388[127] = 0.0;
   out_9153131841173163388[128] = 0.0;
   out_9153131841173163388[129] = 0.0;
   out_9153131841173163388[130] = 0.0;
   out_9153131841173163388[131] = 0.0;
   out_9153131841173163388[132] = 0.0;
   out_9153131841173163388[133] = 1.0;
   out_9153131841173163388[134] = 0.0;
   out_9153131841173163388[135] = 0.0;
   out_9153131841173163388[136] = 0.0;
   out_9153131841173163388[137] = 0.0;
   out_9153131841173163388[138] = 0.0;
   out_9153131841173163388[139] = 0.0;
   out_9153131841173163388[140] = 0.0;
   out_9153131841173163388[141] = 0.0;
   out_9153131841173163388[142] = 0.0;
   out_9153131841173163388[143] = 0.0;
   out_9153131841173163388[144] = 0.0;
   out_9153131841173163388[145] = 0.0;
   out_9153131841173163388[146] = 0.0;
   out_9153131841173163388[147] = 0.0;
   out_9153131841173163388[148] = 0.0;
   out_9153131841173163388[149] = 0.0;
   out_9153131841173163388[150] = 0.0;
   out_9153131841173163388[151] = 0.0;
   out_9153131841173163388[152] = 1.0;
   out_9153131841173163388[153] = 0.0;
   out_9153131841173163388[154] = 0.0;
   out_9153131841173163388[155] = 0.0;
   out_9153131841173163388[156] = 0.0;
   out_9153131841173163388[157] = 0.0;
   out_9153131841173163388[158] = 0.0;
   out_9153131841173163388[159] = 0.0;
   out_9153131841173163388[160] = 0.0;
   out_9153131841173163388[161] = 0.0;
   out_9153131841173163388[162] = 0.0;
   out_9153131841173163388[163] = 0.0;
   out_9153131841173163388[164] = 0.0;
   out_9153131841173163388[165] = 0.0;
   out_9153131841173163388[166] = 0.0;
   out_9153131841173163388[167] = 0.0;
   out_9153131841173163388[168] = 0.0;
   out_9153131841173163388[169] = 0.0;
   out_9153131841173163388[170] = 0.0;
   out_9153131841173163388[171] = 1.0;
   out_9153131841173163388[172] = 0.0;
   out_9153131841173163388[173] = 0.0;
   out_9153131841173163388[174] = 0.0;
   out_9153131841173163388[175] = 0.0;
   out_9153131841173163388[176] = 0.0;
   out_9153131841173163388[177] = 0.0;
   out_9153131841173163388[178] = 0.0;
   out_9153131841173163388[179] = 0.0;
   out_9153131841173163388[180] = 0.0;
   out_9153131841173163388[181] = 0.0;
   out_9153131841173163388[182] = 0.0;
   out_9153131841173163388[183] = 0.0;
   out_9153131841173163388[184] = 0.0;
   out_9153131841173163388[185] = 0.0;
   out_9153131841173163388[186] = 0.0;
   out_9153131841173163388[187] = 0.0;
   out_9153131841173163388[188] = 0.0;
   out_9153131841173163388[189] = 0.0;
   out_9153131841173163388[190] = 1.0;
   out_9153131841173163388[191] = 0.0;
   out_9153131841173163388[192] = 0.0;
   out_9153131841173163388[193] = 0.0;
   out_9153131841173163388[194] = 0.0;
   out_9153131841173163388[195] = 0.0;
   out_9153131841173163388[196] = 0.0;
   out_9153131841173163388[197] = 0.0;
   out_9153131841173163388[198] = 0.0;
   out_9153131841173163388[199] = 0.0;
   out_9153131841173163388[200] = 0.0;
   out_9153131841173163388[201] = 0.0;
   out_9153131841173163388[202] = 0.0;
   out_9153131841173163388[203] = 0.0;
   out_9153131841173163388[204] = 0.0;
   out_9153131841173163388[205] = 0.0;
   out_9153131841173163388[206] = 0.0;
   out_9153131841173163388[207] = 0.0;
   out_9153131841173163388[208] = 0.0;
   out_9153131841173163388[209] = 1.0;
   out_9153131841173163388[210] = 0.0;
   out_9153131841173163388[211] = 0.0;
   out_9153131841173163388[212] = 0.0;
   out_9153131841173163388[213] = 0.0;
   out_9153131841173163388[214] = 0.0;
   out_9153131841173163388[215] = 0.0;
   out_9153131841173163388[216] = 0.0;
   out_9153131841173163388[217] = 0.0;
   out_9153131841173163388[218] = 0.0;
   out_9153131841173163388[219] = 0.0;
   out_9153131841173163388[220] = 0.0;
   out_9153131841173163388[221] = 0.0;
   out_9153131841173163388[222] = 0.0;
   out_9153131841173163388[223] = 0.0;
   out_9153131841173163388[224] = 0.0;
   out_9153131841173163388[225] = 0.0;
   out_9153131841173163388[226] = 0.0;
   out_9153131841173163388[227] = 0.0;
   out_9153131841173163388[228] = 1.0;
   out_9153131841173163388[229] = 0.0;
   out_9153131841173163388[230] = 0.0;
   out_9153131841173163388[231] = 0.0;
   out_9153131841173163388[232] = 0.0;
   out_9153131841173163388[233] = 0.0;
   out_9153131841173163388[234] = 0.0;
   out_9153131841173163388[235] = 0.0;
   out_9153131841173163388[236] = 0.0;
   out_9153131841173163388[237] = 0.0;
   out_9153131841173163388[238] = 0.0;
   out_9153131841173163388[239] = 0.0;
   out_9153131841173163388[240] = 0.0;
   out_9153131841173163388[241] = 0.0;
   out_9153131841173163388[242] = 0.0;
   out_9153131841173163388[243] = 0.0;
   out_9153131841173163388[244] = 0.0;
   out_9153131841173163388[245] = 0.0;
   out_9153131841173163388[246] = 0.0;
   out_9153131841173163388[247] = 1.0;
   out_9153131841173163388[248] = 0.0;
   out_9153131841173163388[249] = 0.0;
   out_9153131841173163388[250] = 0.0;
   out_9153131841173163388[251] = 0.0;
   out_9153131841173163388[252] = 0.0;
   out_9153131841173163388[253] = 0.0;
   out_9153131841173163388[254] = 0.0;
   out_9153131841173163388[255] = 0.0;
   out_9153131841173163388[256] = 0.0;
   out_9153131841173163388[257] = 0.0;
   out_9153131841173163388[258] = 0.0;
   out_9153131841173163388[259] = 0.0;
   out_9153131841173163388[260] = 0.0;
   out_9153131841173163388[261] = 0.0;
   out_9153131841173163388[262] = 0.0;
   out_9153131841173163388[263] = 0.0;
   out_9153131841173163388[264] = 0.0;
   out_9153131841173163388[265] = 0.0;
   out_9153131841173163388[266] = 1.0;
   out_9153131841173163388[267] = 0.0;
   out_9153131841173163388[268] = 0.0;
   out_9153131841173163388[269] = 0.0;
   out_9153131841173163388[270] = 0.0;
   out_9153131841173163388[271] = 0.0;
   out_9153131841173163388[272] = 0.0;
   out_9153131841173163388[273] = 0.0;
   out_9153131841173163388[274] = 0.0;
   out_9153131841173163388[275] = 0.0;
   out_9153131841173163388[276] = 0.0;
   out_9153131841173163388[277] = 0.0;
   out_9153131841173163388[278] = 0.0;
   out_9153131841173163388[279] = 0.0;
   out_9153131841173163388[280] = 0.0;
   out_9153131841173163388[281] = 0.0;
   out_9153131841173163388[282] = 0.0;
   out_9153131841173163388[283] = 0.0;
   out_9153131841173163388[284] = 0.0;
   out_9153131841173163388[285] = 1.0;
   out_9153131841173163388[286] = 0.0;
   out_9153131841173163388[287] = 0.0;
   out_9153131841173163388[288] = 0.0;
   out_9153131841173163388[289] = 0.0;
   out_9153131841173163388[290] = 0.0;
   out_9153131841173163388[291] = 0.0;
   out_9153131841173163388[292] = 0.0;
   out_9153131841173163388[293] = 0.0;
   out_9153131841173163388[294] = 0.0;
   out_9153131841173163388[295] = 0.0;
   out_9153131841173163388[296] = 0.0;
   out_9153131841173163388[297] = 0.0;
   out_9153131841173163388[298] = 0.0;
   out_9153131841173163388[299] = 0.0;
   out_9153131841173163388[300] = 0.0;
   out_9153131841173163388[301] = 0.0;
   out_9153131841173163388[302] = 0.0;
   out_9153131841173163388[303] = 0.0;
   out_9153131841173163388[304] = 1.0;
   out_9153131841173163388[305] = 0.0;
   out_9153131841173163388[306] = 0.0;
   out_9153131841173163388[307] = 0.0;
   out_9153131841173163388[308] = 0.0;
   out_9153131841173163388[309] = 0.0;
   out_9153131841173163388[310] = 0.0;
   out_9153131841173163388[311] = 0.0;
   out_9153131841173163388[312] = 0.0;
   out_9153131841173163388[313] = 0.0;
   out_9153131841173163388[314] = 0.0;
   out_9153131841173163388[315] = 0.0;
   out_9153131841173163388[316] = 0.0;
   out_9153131841173163388[317] = 0.0;
   out_9153131841173163388[318] = 0.0;
   out_9153131841173163388[319] = 0.0;
   out_9153131841173163388[320] = 0.0;
   out_9153131841173163388[321] = 0.0;
   out_9153131841173163388[322] = 0.0;
   out_9153131841173163388[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5731900164957455748) {
   out_5731900164957455748[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5731900164957455748[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5731900164957455748[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5731900164957455748[3] = dt*state[12] + state[3];
   out_5731900164957455748[4] = dt*state[13] + state[4];
   out_5731900164957455748[5] = dt*state[14] + state[5];
   out_5731900164957455748[6] = state[6];
   out_5731900164957455748[7] = state[7];
   out_5731900164957455748[8] = state[8];
   out_5731900164957455748[9] = state[9];
   out_5731900164957455748[10] = state[10];
   out_5731900164957455748[11] = state[11];
   out_5731900164957455748[12] = state[12];
   out_5731900164957455748[13] = state[13];
   out_5731900164957455748[14] = state[14];
   out_5731900164957455748[15] = state[15];
   out_5731900164957455748[16] = state[16];
   out_5731900164957455748[17] = state[17];
}
void F_fun(double *state, double dt, double *out_552344081412747464) {
   out_552344081412747464[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_552344081412747464[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_552344081412747464[2] = 0;
   out_552344081412747464[3] = 0;
   out_552344081412747464[4] = 0;
   out_552344081412747464[5] = 0;
   out_552344081412747464[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_552344081412747464[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_552344081412747464[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_552344081412747464[9] = 0;
   out_552344081412747464[10] = 0;
   out_552344081412747464[11] = 0;
   out_552344081412747464[12] = 0;
   out_552344081412747464[13] = 0;
   out_552344081412747464[14] = 0;
   out_552344081412747464[15] = 0;
   out_552344081412747464[16] = 0;
   out_552344081412747464[17] = 0;
   out_552344081412747464[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_552344081412747464[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_552344081412747464[20] = 0;
   out_552344081412747464[21] = 0;
   out_552344081412747464[22] = 0;
   out_552344081412747464[23] = 0;
   out_552344081412747464[24] = 0;
   out_552344081412747464[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_552344081412747464[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_552344081412747464[27] = 0;
   out_552344081412747464[28] = 0;
   out_552344081412747464[29] = 0;
   out_552344081412747464[30] = 0;
   out_552344081412747464[31] = 0;
   out_552344081412747464[32] = 0;
   out_552344081412747464[33] = 0;
   out_552344081412747464[34] = 0;
   out_552344081412747464[35] = 0;
   out_552344081412747464[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_552344081412747464[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_552344081412747464[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_552344081412747464[39] = 0;
   out_552344081412747464[40] = 0;
   out_552344081412747464[41] = 0;
   out_552344081412747464[42] = 0;
   out_552344081412747464[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_552344081412747464[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_552344081412747464[45] = 0;
   out_552344081412747464[46] = 0;
   out_552344081412747464[47] = 0;
   out_552344081412747464[48] = 0;
   out_552344081412747464[49] = 0;
   out_552344081412747464[50] = 0;
   out_552344081412747464[51] = 0;
   out_552344081412747464[52] = 0;
   out_552344081412747464[53] = 0;
   out_552344081412747464[54] = 0;
   out_552344081412747464[55] = 0;
   out_552344081412747464[56] = 0;
   out_552344081412747464[57] = 1;
   out_552344081412747464[58] = 0;
   out_552344081412747464[59] = 0;
   out_552344081412747464[60] = 0;
   out_552344081412747464[61] = 0;
   out_552344081412747464[62] = 0;
   out_552344081412747464[63] = 0;
   out_552344081412747464[64] = 0;
   out_552344081412747464[65] = 0;
   out_552344081412747464[66] = dt;
   out_552344081412747464[67] = 0;
   out_552344081412747464[68] = 0;
   out_552344081412747464[69] = 0;
   out_552344081412747464[70] = 0;
   out_552344081412747464[71] = 0;
   out_552344081412747464[72] = 0;
   out_552344081412747464[73] = 0;
   out_552344081412747464[74] = 0;
   out_552344081412747464[75] = 0;
   out_552344081412747464[76] = 1;
   out_552344081412747464[77] = 0;
   out_552344081412747464[78] = 0;
   out_552344081412747464[79] = 0;
   out_552344081412747464[80] = 0;
   out_552344081412747464[81] = 0;
   out_552344081412747464[82] = 0;
   out_552344081412747464[83] = 0;
   out_552344081412747464[84] = 0;
   out_552344081412747464[85] = dt;
   out_552344081412747464[86] = 0;
   out_552344081412747464[87] = 0;
   out_552344081412747464[88] = 0;
   out_552344081412747464[89] = 0;
   out_552344081412747464[90] = 0;
   out_552344081412747464[91] = 0;
   out_552344081412747464[92] = 0;
   out_552344081412747464[93] = 0;
   out_552344081412747464[94] = 0;
   out_552344081412747464[95] = 1;
   out_552344081412747464[96] = 0;
   out_552344081412747464[97] = 0;
   out_552344081412747464[98] = 0;
   out_552344081412747464[99] = 0;
   out_552344081412747464[100] = 0;
   out_552344081412747464[101] = 0;
   out_552344081412747464[102] = 0;
   out_552344081412747464[103] = 0;
   out_552344081412747464[104] = dt;
   out_552344081412747464[105] = 0;
   out_552344081412747464[106] = 0;
   out_552344081412747464[107] = 0;
   out_552344081412747464[108] = 0;
   out_552344081412747464[109] = 0;
   out_552344081412747464[110] = 0;
   out_552344081412747464[111] = 0;
   out_552344081412747464[112] = 0;
   out_552344081412747464[113] = 0;
   out_552344081412747464[114] = 1;
   out_552344081412747464[115] = 0;
   out_552344081412747464[116] = 0;
   out_552344081412747464[117] = 0;
   out_552344081412747464[118] = 0;
   out_552344081412747464[119] = 0;
   out_552344081412747464[120] = 0;
   out_552344081412747464[121] = 0;
   out_552344081412747464[122] = 0;
   out_552344081412747464[123] = 0;
   out_552344081412747464[124] = 0;
   out_552344081412747464[125] = 0;
   out_552344081412747464[126] = 0;
   out_552344081412747464[127] = 0;
   out_552344081412747464[128] = 0;
   out_552344081412747464[129] = 0;
   out_552344081412747464[130] = 0;
   out_552344081412747464[131] = 0;
   out_552344081412747464[132] = 0;
   out_552344081412747464[133] = 1;
   out_552344081412747464[134] = 0;
   out_552344081412747464[135] = 0;
   out_552344081412747464[136] = 0;
   out_552344081412747464[137] = 0;
   out_552344081412747464[138] = 0;
   out_552344081412747464[139] = 0;
   out_552344081412747464[140] = 0;
   out_552344081412747464[141] = 0;
   out_552344081412747464[142] = 0;
   out_552344081412747464[143] = 0;
   out_552344081412747464[144] = 0;
   out_552344081412747464[145] = 0;
   out_552344081412747464[146] = 0;
   out_552344081412747464[147] = 0;
   out_552344081412747464[148] = 0;
   out_552344081412747464[149] = 0;
   out_552344081412747464[150] = 0;
   out_552344081412747464[151] = 0;
   out_552344081412747464[152] = 1;
   out_552344081412747464[153] = 0;
   out_552344081412747464[154] = 0;
   out_552344081412747464[155] = 0;
   out_552344081412747464[156] = 0;
   out_552344081412747464[157] = 0;
   out_552344081412747464[158] = 0;
   out_552344081412747464[159] = 0;
   out_552344081412747464[160] = 0;
   out_552344081412747464[161] = 0;
   out_552344081412747464[162] = 0;
   out_552344081412747464[163] = 0;
   out_552344081412747464[164] = 0;
   out_552344081412747464[165] = 0;
   out_552344081412747464[166] = 0;
   out_552344081412747464[167] = 0;
   out_552344081412747464[168] = 0;
   out_552344081412747464[169] = 0;
   out_552344081412747464[170] = 0;
   out_552344081412747464[171] = 1;
   out_552344081412747464[172] = 0;
   out_552344081412747464[173] = 0;
   out_552344081412747464[174] = 0;
   out_552344081412747464[175] = 0;
   out_552344081412747464[176] = 0;
   out_552344081412747464[177] = 0;
   out_552344081412747464[178] = 0;
   out_552344081412747464[179] = 0;
   out_552344081412747464[180] = 0;
   out_552344081412747464[181] = 0;
   out_552344081412747464[182] = 0;
   out_552344081412747464[183] = 0;
   out_552344081412747464[184] = 0;
   out_552344081412747464[185] = 0;
   out_552344081412747464[186] = 0;
   out_552344081412747464[187] = 0;
   out_552344081412747464[188] = 0;
   out_552344081412747464[189] = 0;
   out_552344081412747464[190] = 1;
   out_552344081412747464[191] = 0;
   out_552344081412747464[192] = 0;
   out_552344081412747464[193] = 0;
   out_552344081412747464[194] = 0;
   out_552344081412747464[195] = 0;
   out_552344081412747464[196] = 0;
   out_552344081412747464[197] = 0;
   out_552344081412747464[198] = 0;
   out_552344081412747464[199] = 0;
   out_552344081412747464[200] = 0;
   out_552344081412747464[201] = 0;
   out_552344081412747464[202] = 0;
   out_552344081412747464[203] = 0;
   out_552344081412747464[204] = 0;
   out_552344081412747464[205] = 0;
   out_552344081412747464[206] = 0;
   out_552344081412747464[207] = 0;
   out_552344081412747464[208] = 0;
   out_552344081412747464[209] = 1;
   out_552344081412747464[210] = 0;
   out_552344081412747464[211] = 0;
   out_552344081412747464[212] = 0;
   out_552344081412747464[213] = 0;
   out_552344081412747464[214] = 0;
   out_552344081412747464[215] = 0;
   out_552344081412747464[216] = 0;
   out_552344081412747464[217] = 0;
   out_552344081412747464[218] = 0;
   out_552344081412747464[219] = 0;
   out_552344081412747464[220] = 0;
   out_552344081412747464[221] = 0;
   out_552344081412747464[222] = 0;
   out_552344081412747464[223] = 0;
   out_552344081412747464[224] = 0;
   out_552344081412747464[225] = 0;
   out_552344081412747464[226] = 0;
   out_552344081412747464[227] = 0;
   out_552344081412747464[228] = 1;
   out_552344081412747464[229] = 0;
   out_552344081412747464[230] = 0;
   out_552344081412747464[231] = 0;
   out_552344081412747464[232] = 0;
   out_552344081412747464[233] = 0;
   out_552344081412747464[234] = 0;
   out_552344081412747464[235] = 0;
   out_552344081412747464[236] = 0;
   out_552344081412747464[237] = 0;
   out_552344081412747464[238] = 0;
   out_552344081412747464[239] = 0;
   out_552344081412747464[240] = 0;
   out_552344081412747464[241] = 0;
   out_552344081412747464[242] = 0;
   out_552344081412747464[243] = 0;
   out_552344081412747464[244] = 0;
   out_552344081412747464[245] = 0;
   out_552344081412747464[246] = 0;
   out_552344081412747464[247] = 1;
   out_552344081412747464[248] = 0;
   out_552344081412747464[249] = 0;
   out_552344081412747464[250] = 0;
   out_552344081412747464[251] = 0;
   out_552344081412747464[252] = 0;
   out_552344081412747464[253] = 0;
   out_552344081412747464[254] = 0;
   out_552344081412747464[255] = 0;
   out_552344081412747464[256] = 0;
   out_552344081412747464[257] = 0;
   out_552344081412747464[258] = 0;
   out_552344081412747464[259] = 0;
   out_552344081412747464[260] = 0;
   out_552344081412747464[261] = 0;
   out_552344081412747464[262] = 0;
   out_552344081412747464[263] = 0;
   out_552344081412747464[264] = 0;
   out_552344081412747464[265] = 0;
   out_552344081412747464[266] = 1;
   out_552344081412747464[267] = 0;
   out_552344081412747464[268] = 0;
   out_552344081412747464[269] = 0;
   out_552344081412747464[270] = 0;
   out_552344081412747464[271] = 0;
   out_552344081412747464[272] = 0;
   out_552344081412747464[273] = 0;
   out_552344081412747464[274] = 0;
   out_552344081412747464[275] = 0;
   out_552344081412747464[276] = 0;
   out_552344081412747464[277] = 0;
   out_552344081412747464[278] = 0;
   out_552344081412747464[279] = 0;
   out_552344081412747464[280] = 0;
   out_552344081412747464[281] = 0;
   out_552344081412747464[282] = 0;
   out_552344081412747464[283] = 0;
   out_552344081412747464[284] = 0;
   out_552344081412747464[285] = 1;
   out_552344081412747464[286] = 0;
   out_552344081412747464[287] = 0;
   out_552344081412747464[288] = 0;
   out_552344081412747464[289] = 0;
   out_552344081412747464[290] = 0;
   out_552344081412747464[291] = 0;
   out_552344081412747464[292] = 0;
   out_552344081412747464[293] = 0;
   out_552344081412747464[294] = 0;
   out_552344081412747464[295] = 0;
   out_552344081412747464[296] = 0;
   out_552344081412747464[297] = 0;
   out_552344081412747464[298] = 0;
   out_552344081412747464[299] = 0;
   out_552344081412747464[300] = 0;
   out_552344081412747464[301] = 0;
   out_552344081412747464[302] = 0;
   out_552344081412747464[303] = 0;
   out_552344081412747464[304] = 1;
   out_552344081412747464[305] = 0;
   out_552344081412747464[306] = 0;
   out_552344081412747464[307] = 0;
   out_552344081412747464[308] = 0;
   out_552344081412747464[309] = 0;
   out_552344081412747464[310] = 0;
   out_552344081412747464[311] = 0;
   out_552344081412747464[312] = 0;
   out_552344081412747464[313] = 0;
   out_552344081412747464[314] = 0;
   out_552344081412747464[315] = 0;
   out_552344081412747464[316] = 0;
   out_552344081412747464[317] = 0;
   out_552344081412747464[318] = 0;
   out_552344081412747464[319] = 0;
   out_552344081412747464[320] = 0;
   out_552344081412747464[321] = 0;
   out_552344081412747464[322] = 0;
   out_552344081412747464[323] = 1;
}
void h_4(double *state, double *unused, double *out_2352995918424077902) {
   out_2352995918424077902[0] = state[6] + state[9];
   out_2352995918424077902[1] = state[7] + state[10];
   out_2352995918424077902[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6019390153745438975) {
   out_6019390153745438975[0] = 0;
   out_6019390153745438975[1] = 0;
   out_6019390153745438975[2] = 0;
   out_6019390153745438975[3] = 0;
   out_6019390153745438975[4] = 0;
   out_6019390153745438975[5] = 0;
   out_6019390153745438975[6] = 1;
   out_6019390153745438975[7] = 0;
   out_6019390153745438975[8] = 0;
   out_6019390153745438975[9] = 1;
   out_6019390153745438975[10] = 0;
   out_6019390153745438975[11] = 0;
   out_6019390153745438975[12] = 0;
   out_6019390153745438975[13] = 0;
   out_6019390153745438975[14] = 0;
   out_6019390153745438975[15] = 0;
   out_6019390153745438975[16] = 0;
   out_6019390153745438975[17] = 0;
   out_6019390153745438975[18] = 0;
   out_6019390153745438975[19] = 0;
   out_6019390153745438975[20] = 0;
   out_6019390153745438975[21] = 0;
   out_6019390153745438975[22] = 0;
   out_6019390153745438975[23] = 0;
   out_6019390153745438975[24] = 0;
   out_6019390153745438975[25] = 1;
   out_6019390153745438975[26] = 0;
   out_6019390153745438975[27] = 0;
   out_6019390153745438975[28] = 1;
   out_6019390153745438975[29] = 0;
   out_6019390153745438975[30] = 0;
   out_6019390153745438975[31] = 0;
   out_6019390153745438975[32] = 0;
   out_6019390153745438975[33] = 0;
   out_6019390153745438975[34] = 0;
   out_6019390153745438975[35] = 0;
   out_6019390153745438975[36] = 0;
   out_6019390153745438975[37] = 0;
   out_6019390153745438975[38] = 0;
   out_6019390153745438975[39] = 0;
   out_6019390153745438975[40] = 0;
   out_6019390153745438975[41] = 0;
   out_6019390153745438975[42] = 0;
   out_6019390153745438975[43] = 0;
   out_6019390153745438975[44] = 1;
   out_6019390153745438975[45] = 0;
   out_6019390153745438975[46] = 0;
   out_6019390153745438975[47] = 1;
   out_6019390153745438975[48] = 0;
   out_6019390153745438975[49] = 0;
   out_6019390153745438975[50] = 0;
   out_6019390153745438975[51] = 0;
   out_6019390153745438975[52] = 0;
   out_6019390153745438975[53] = 0;
}
void h_10(double *state, double *unused, double *out_577009537073488637) {
   out_577009537073488637[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_577009537073488637[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_577009537073488637[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1175900786030612795) {
   out_1175900786030612795[0] = 0;
   out_1175900786030612795[1] = 9.8100000000000005*cos(state[1]);
   out_1175900786030612795[2] = 0;
   out_1175900786030612795[3] = 0;
   out_1175900786030612795[4] = -state[8];
   out_1175900786030612795[5] = state[7];
   out_1175900786030612795[6] = 0;
   out_1175900786030612795[7] = state[5];
   out_1175900786030612795[8] = -state[4];
   out_1175900786030612795[9] = 0;
   out_1175900786030612795[10] = 0;
   out_1175900786030612795[11] = 0;
   out_1175900786030612795[12] = 1;
   out_1175900786030612795[13] = 0;
   out_1175900786030612795[14] = 0;
   out_1175900786030612795[15] = 1;
   out_1175900786030612795[16] = 0;
   out_1175900786030612795[17] = 0;
   out_1175900786030612795[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1175900786030612795[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1175900786030612795[20] = 0;
   out_1175900786030612795[21] = state[8];
   out_1175900786030612795[22] = 0;
   out_1175900786030612795[23] = -state[6];
   out_1175900786030612795[24] = -state[5];
   out_1175900786030612795[25] = 0;
   out_1175900786030612795[26] = state[3];
   out_1175900786030612795[27] = 0;
   out_1175900786030612795[28] = 0;
   out_1175900786030612795[29] = 0;
   out_1175900786030612795[30] = 0;
   out_1175900786030612795[31] = 1;
   out_1175900786030612795[32] = 0;
   out_1175900786030612795[33] = 0;
   out_1175900786030612795[34] = 1;
   out_1175900786030612795[35] = 0;
   out_1175900786030612795[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1175900786030612795[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1175900786030612795[38] = 0;
   out_1175900786030612795[39] = -state[7];
   out_1175900786030612795[40] = state[6];
   out_1175900786030612795[41] = 0;
   out_1175900786030612795[42] = state[4];
   out_1175900786030612795[43] = -state[3];
   out_1175900786030612795[44] = 0;
   out_1175900786030612795[45] = 0;
   out_1175900786030612795[46] = 0;
   out_1175900786030612795[47] = 0;
   out_1175900786030612795[48] = 0;
   out_1175900786030612795[49] = 0;
   out_1175900786030612795[50] = 1;
   out_1175900786030612795[51] = 0;
   out_1175900786030612795[52] = 0;
   out_1175900786030612795[53] = 1;
}
void h_13(double *state, double *unused, double *out_4589151815082178536) {
   out_4589151815082178536[0] = state[3];
   out_4589151815082178536[1] = state[4];
   out_4589151815082178536[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4816722711647411712) {
   out_4816722711647411712[0] = 0;
   out_4816722711647411712[1] = 0;
   out_4816722711647411712[2] = 0;
   out_4816722711647411712[3] = 1;
   out_4816722711647411712[4] = 0;
   out_4816722711647411712[5] = 0;
   out_4816722711647411712[6] = 0;
   out_4816722711647411712[7] = 0;
   out_4816722711647411712[8] = 0;
   out_4816722711647411712[9] = 0;
   out_4816722711647411712[10] = 0;
   out_4816722711647411712[11] = 0;
   out_4816722711647411712[12] = 0;
   out_4816722711647411712[13] = 0;
   out_4816722711647411712[14] = 0;
   out_4816722711647411712[15] = 0;
   out_4816722711647411712[16] = 0;
   out_4816722711647411712[17] = 0;
   out_4816722711647411712[18] = 0;
   out_4816722711647411712[19] = 0;
   out_4816722711647411712[20] = 0;
   out_4816722711647411712[21] = 0;
   out_4816722711647411712[22] = 1;
   out_4816722711647411712[23] = 0;
   out_4816722711647411712[24] = 0;
   out_4816722711647411712[25] = 0;
   out_4816722711647411712[26] = 0;
   out_4816722711647411712[27] = 0;
   out_4816722711647411712[28] = 0;
   out_4816722711647411712[29] = 0;
   out_4816722711647411712[30] = 0;
   out_4816722711647411712[31] = 0;
   out_4816722711647411712[32] = 0;
   out_4816722711647411712[33] = 0;
   out_4816722711647411712[34] = 0;
   out_4816722711647411712[35] = 0;
   out_4816722711647411712[36] = 0;
   out_4816722711647411712[37] = 0;
   out_4816722711647411712[38] = 0;
   out_4816722711647411712[39] = 0;
   out_4816722711647411712[40] = 0;
   out_4816722711647411712[41] = 1;
   out_4816722711647411712[42] = 0;
   out_4816722711647411712[43] = 0;
   out_4816722711647411712[44] = 0;
   out_4816722711647411712[45] = 0;
   out_4816722711647411712[46] = 0;
   out_4816722711647411712[47] = 0;
   out_4816722711647411712[48] = 0;
   out_4816722711647411712[49] = 0;
   out_4816722711647411712[50] = 0;
   out_4816722711647411712[51] = 0;
   out_4816722711647411712[52] = 0;
   out_4816722711647411712[53] = 0;
}
void h_14(double *state, double *unused, double *out_4921164340780417902) {
   out_4921164340780417902[0] = state[6];
   out_4921164340780417902[1] = state[7];
   out_4921164340780417902[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8464113063624628112) {
   out_8464113063624628112[0] = 0;
   out_8464113063624628112[1] = 0;
   out_8464113063624628112[2] = 0;
   out_8464113063624628112[3] = 0;
   out_8464113063624628112[4] = 0;
   out_8464113063624628112[5] = 0;
   out_8464113063624628112[6] = 1;
   out_8464113063624628112[7] = 0;
   out_8464113063624628112[8] = 0;
   out_8464113063624628112[9] = 0;
   out_8464113063624628112[10] = 0;
   out_8464113063624628112[11] = 0;
   out_8464113063624628112[12] = 0;
   out_8464113063624628112[13] = 0;
   out_8464113063624628112[14] = 0;
   out_8464113063624628112[15] = 0;
   out_8464113063624628112[16] = 0;
   out_8464113063624628112[17] = 0;
   out_8464113063624628112[18] = 0;
   out_8464113063624628112[19] = 0;
   out_8464113063624628112[20] = 0;
   out_8464113063624628112[21] = 0;
   out_8464113063624628112[22] = 0;
   out_8464113063624628112[23] = 0;
   out_8464113063624628112[24] = 0;
   out_8464113063624628112[25] = 1;
   out_8464113063624628112[26] = 0;
   out_8464113063624628112[27] = 0;
   out_8464113063624628112[28] = 0;
   out_8464113063624628112[29] = 0;
   out_8464113063624628112[30] = 0;
   out_8464113063624628112[31] = 0;
   out_8464113063624628112[32] = 0;
   out_8464113063624628112[33] = 0;
   out_8464113063624628112[34] = 0;
   out_8464113063624628112[35] = 0;
   out_8464113063624628112[36] = 0;
   out_8464113063624628112[37] = 0;
   out_8464113063624628112[38] = 0;
   out_8464113063624628112[39] = 0;
   out_8464113063624628112[40] = 0;
   out_8464113063624628112[41] = 0;
   out_8464113063624628112[42] = 0;
   out_8464113063624628112[43] = 0;
   out_8464113063624628112[44] = 1;
   out_8464113063624628112[45] = 0;
   out_8464113063624628112[46] = 0;
   out_8464113063624628112[47] = 0;
   out_8464113063624628112[48] = 0;
   out_8464113063624628112[49] = 0;
   out_8464113063624628112[50] = 0;
   out_8464113063624628112[51] = 0;
   out_8464113063624628112[52] = 0;
   out_8464113063624628112[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6360695334706395645) {
  err_fun(nom_x, delta_x, out_6360695334706395645);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3498794849105875793) {
  inv_err_fun(nom_x, true_x, out_3498794849105875793);
}
void pose_H_mod_fun(double *state, double *out_9153131841173163388) {
  H_mod_fun(state, out_9153131841173163388);
}
void pose_f_fun(double *state, double dt, double *out_5731900164957455748) {
  f_fun(state,  dt, out_5731900164957455748);
}
void pose_F_fun(double *state, double dt, double *out_552344081412747464) {
  F_fun(state,  dt, out_552344081412747464);
}
void pose_h_4(double *state, double *unused, double *out_2352995918424077902) {
  h_4(state, unused, out_2352995918424077902);
}
void pose_H_4(double *state, double *unused, double *out_6019390153745438975) {
  H_4(state, unused, out_6019390153745438975);
}
void pose_h_10(double *state, double *unused, double *out_577009537073488637) {
  h_10(state, unused, out_577009537073488637);
}
void pose_H_10(double *state, double *unused, double *out_1175900786030612795) {
  H_10(state, unused, out_1175900786030612795);
}
void pose_h_13(double *state, double *unused, double *out_4589151815082178536) {
  h_13(state, unused, out_4589151815082178536);
}
void pose_H_13(double *state, double *unused, double *out_4816722711647411712) {
  H_13(state, unused, out_4816722711647411712);
}
void pose_h_14(double *state, double *unused, double *out_4921164340780417902) {
  h_14(state, unused, out_4921164340780417902);
}
void pose_H_14(double *state, double *unused, double *out_8464113063624628112) {
  H_14(state, unused, out_8464113063624628112);
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
