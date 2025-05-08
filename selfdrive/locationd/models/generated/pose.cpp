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
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7661590215377839666) {
   out_7661590215377839666[0] = delta_x[0] + nom_x[0];
   out_7661590215377839666[1] = delta_x[1] + nom_x[1];
   out_7661590215377839666[2] = delta_x[2] + nom_x[2];
   out_7661590215377839666[3] = delta_x[3] + nom_x[3];
   out_7661590215377839666[4] = delta_x[4] + nom_x[4];
   out_7661590215377839666[5] = delta_x[5] + nom_x[5];
   out_7661590215377839666[6] = delta_x[6] + nom_x[6];
   out_7661590215377839666[7] = delta_x[7] + nom_x[7];
   out_7661590215377839666[8] = delta_x[8] + nom_x[8];
   out_7661590215377839666[9] = delta_x[9] + nom_x[9];
   out_7661590215377839666[10] = delta_x[10] + nom_x[10];
   out_7661590215377839666[11] = delta_x[11] + nom_x[11];
   out_7661590215377839666[12] = delta_x[12] + nom_x[12];
   out_7661590215377839666[13] = delta_x[13] + nom_x[13];
   out_7661590215377839666[14] = delta_x[14] + nom_x[14];
   out_7661590215377839666[15] = delta_x[15] + nom_x[15];
   out_7661590215377839666[16] = delta_x[16] + nom_x[16];
   out_7661590215377839666[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_867942321893475263) {
   out_867942321893475263[0] = -nom_x[0] + true_x[0];
   out_867942321893475263[1] = -nom_x[1] + true_x[1];
   out_867942321893475263[2] = -nom_x[2] + true_x[2];
   out_867942321893475263[3] = -nom_x[3] + true_x[3];
   out_867942321893475263[4] = -nom_x[4] + true_x[4];
   out_867942321893475263[5] = -nom_x[5] + true_x[5];
   out_867942321893475263[6] = -nom_x[6] + true_x[6];
   out_867942321893475263[7] = -nom_x[7] + true_x[7];
   out_867942321893475263[8] = -nom_x[8] + true_x[8];
   out_867942321893475263[9] = -nom_x[9] + true_x[9];
   out_867942321893475263[10] = -nom_x[10] + true_x[10];
   out_867942321893475263[11] = -nom_x[11] + true_x[11];
   out_867942321893475263[12] = -nom_x[12] + true_x[12];
   out_867942321893475263[13] = -nom_x[13] + true_x[13];
   out_867942321893475263[14] = -nom_x[14] + true_x[14];
   out_867942321893475263[15] = -nom_x[15] + true_x[15];
   out_867942321893475263[16] = -nom_x[16] + true_x[16];
   out_867942321893475263[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3310708289553390566) {
   out_3310708289553390566[0] = 1.0;
   out_3310708289553390566[1] = 0.0;
   out_3310708289553390566[2] = 0.0;
   out_3310708289553390566[3] = 0.0;
   out_3310708289553390566[4] = 0.0;
   out_3310708289553390566[5] = 0.0;
   out_3310708289553390566[6] = 0.0;
   out_3310708289553390566[7] = 0.0;
   out_3310708289553390566[8] = 0.0;
   out_3310708289553390566[9] = 0.0;
   out_3310708289553390566[10] = 0.0;
   out_3310708289553390566[11] = 0.0;
   out_3310708289553390566[12] = 0.0;
   out_3310708289553390566[13] = 0.0;
   out_3310708289553390566[14] = 0.0;
   out_3310708289553390566[15] = 0.0;
   out_3310708289553390566[16] = 0.0;
   out_3310708289553390566[17] = 0.0;
   out_3310708289553390566[18] = 0.0;
   out_3310708289553390566[19] = 1.0;
   out_3310708289553390566[20] = 0.0;
   out_3310708289553390566[21] = 0.0;
   out_3310708289553390566[22] = 0.0;
   out_3310708289553390566[23] = 0.0;
   out_3310708289553390566[24] = 0.0;
   out_3310708289553390566[25] = 0.0;
   out_3310708289553390566[26] = 0.0;
   out_3310708289553390566[27] = 0.0;
   out_3310708289553390566[28] = 0.0;
   out_3310708289553390566[29] = 0.0;
   out_3310708289553390566[30] = 0.0;
   out_3310708289553390566[31] = 0.0;
   out_3310708289553390566[32] = 0.0;
   out_3310708289553390566[33] = 0.0;
   out_3310708289553390566[34] = 0.0;
   out_3310708289553390566[35] = 0.0;
   out_3310708289553390566[36] = 0.0;
   out_3310708289553390566[37] = 0.0;
   out_3310708289553390566[38] = 1.0;
   out_3310708289553390566[39] = 0.0;
   out_3310708289553390566[40] = 0.0;
   out_3310708289553390566[41] = 0.0;
   out_3310708289553390566[42] = 0.0;
   out_3310708289553390566[43] = 0.0;
   out_3310708289553390566[44] = 0.0;
   out_3310708289553390566[45] = 0.0;
   out_3310708289553390566[46] = 0.0;
   out_3310708289553390566[47] = 0.0;
   out_3310708289553390566[48] = 0.0;
   out_3310708289553390566[49] = 0.0;
   out_3310708289553390566[50] = 0.0;
   out_3310708289553390566[51] = 0.0;
   out_3310708289553390566[52] = 0.0;
   out_3310708289553390566[53] = 0.0;
   out_3310708289553390566[54] = 0.0;
   out_3310708289553390566[55] = 0.0;
   out_3310708289553390566[56] = 0.0;
   out_3310708289553390566[57] = 1.0;
   out_3310708289553390566[58] = 0.0;
   out_3310708289553390566[59] = 0.0;
   out_3310708289553390566[60] = 0.0;
   out_3310708289553390566[61] = 0.0;
   out_3310708289553390566[62] = 0.0;
   out_3310708289553390566[63] = 0.0;
   out_3310708289553390566[64] = 0.0;
   out_3310708289553390566[65] = 0.0;
   out_3310708289553390566[66] = 0.0;
   out_3310708289553390566[67] = 0.0;
   out_3310708289553390566[68] = 0.0;
   out_3310708289553390566[69] = 0.0;
   out_3310708289553390566[70] = 0.0;
   out_3310708289553390566[71] = 0.0;
   out_3310708289553390566[72] = 0.0;
   out_3310708289553390566[73] = 0.0;
   out_3310708289553390566[74] = 0.0;
   out_3310708289553390566[75] = 0.0;
   out_3310708289553390566[76] = 1.0;
   out_3310708289553390566[77] = 0.0;
   out_3310708289553390566[78] = 0.0;
   out_3310708289553390566[79] = 0.0;
   out_3310708289553390566[80] = 0.0;
   out_3310708289553390566[81] = 0.0;
   out_3310708289553390566[82] = 0.0;
   out_3310708289553390566[83] = 0.0;
   out_3310708289553390566[84] = 0.0;
   out_3310708289553390566[85] = 0.0;
   out_3310708289553390566[86] = 0.0;
   out_3310708289553390566[87] = 0.0;
   out_3310708289553390566[88] = 0.0;
   out_3310708289553390566[89] = 0.0;
   out_3310708289553390566[90] = 0.0;
   out_3310708289553390566[91] = 0.0;
   out_3310708289553390566[92] = 0.0;
   out_3310708289553390566[93] = 0.0;
   out_3310708289553390566[94] = 0.0;
   out_3310708289553390566[95] = 1.0;
   out_3310708289553390566[96] = 0.0;
   out_3310708289553390566[97] = 0.0;
   out_3310708289553390566[98] = 0.0;
   out_3310708289553390566[99] = 0.0;
   out_3310708289553390566[100] = 0.0;
   out_3310708289553390566[101] = 0.0;
   out_3310708289553390566[102] = 0.0;
   out_3310708289553390566[103] = 0.0;
   out_3310708289553390566[104] = 0.0;
   out_3310708289553390566[105] = 0.0;
   out_3310708289553390566[106] = 0.0;
   out_3310708289553390566[107] = 0.0;
   out_3310708289553390566[108] = 0.0;
   out_3310708289553390566[109] = 0.0;
   out_3310708289553390566[110] = 0.0;
   out_3310708289553390566[111] = 0.0;
   out_3310708289553390566[112] = 0.0;
   out_3310708289553390566[113] = 0.0;
   out_3310708289553390566[114] = 1.0;
   out_3310708289553390566[115] = 0.0;
   out_3310708289553390566[116] = 0.0;
   out_3310708289553390566[117] = 0.0;
   out_3310708289553390566[118] = 0.0;
   out_3310708289553390566[119] = 0.0;
   out_3310708289553390566[120] = 0.0;
   out_3310708289553390566[121] = 0.0;
   out_3310708289553390566[122] = 0.0;
   out_3310708289553390566[123] = 0.0;
   out_3310708289553390566[124] = 0.0;
   out_3310708289553390566[125] = 0.0;
   out_3310708289553390566[126] = 0.0;
   out_3310708289553390566[127] = 0.0;
   out_3310708289553390566[128] = 0.0;
   out_3310708289553390566[129] = 0.0;
   out_3310708289553390566[130] = 0.0;
   out_3310708289553390566[131] = 0.0;
   out_3310708289553390566[132] = 0.0;
   out_3310708289553390566[133] = 1.0;
   out_3310708289553390566[134] = 0.0;
   out_3310708289553390566[135] = 0.0;
   out_3310708289553390566[136] = 0.0;
   out_3310708289553390566[137] = 0.0;
   out_3310708289553390566[138] = 0.0;
   out_3310708289553390566[139] = 0.0;
   out_3310708289553390566[140] = 0.0;
   out_3310708289553390566[141] = 0.0;
   out_3310708289553390566[142] = 0.0;
   out_3310708289553390566[143] = 0.0;
   out_3310708289553390566[144] = 0.0;
   out_3310708289553390566[145] = 0.0;
   out_3310708289553390566[146] = 0.0;
   out_3310708289553390566[147] = 0.0;
   out_3310708289553390566[148] = 0.0;
   out_3310708289553390566[149] = 0.0;
   out_3310708289553390566[150] = 0.0;
   out_3310708289553390566[151] = 0.0;
   out_3310708289553390566[152] = 1.0;
   out_3310708289553390566[153] = 0.0;
   out_3310708289553390566[154] = 0.0;
   out_3310708289553390566[155] = 0.0;
   out_3310708289553390566[156] = 0.0;
   out_3310708289553390566[157] = 0.0;
   out_3310708289553390566[158] = 0.0;
   out_3310708289553390566[159] = 0.0;
   out_3310708289553390566[160] = 0.0;
   out_3310708289553390566[161] = 0.0;
   out_3310708289553390566[162] = 0.0;
   out_3310708289553390566[163] = 0.0;
   out_3310708289553390566[164] = 0.0;
   out_3310708289553390566[165] = 0.0;
   out_3310708289553390566[166] = 0.0;
   out_3310708289553390566[167] = 0.0;
   out_3310708289553390566[168] = 0.0;
   out_3310708289553390566[169] = 0.0;
   out_3310708289553390566[170] = 0.0;
   out_3310708289553390566[171] = 1.0;
   out_3310708289553390566[172] = 0.0;
   out_3310708289553390566[173] = 0.0;
   out_3310708289553390566[174] = 0.0;
   out_3310708289553390566[175] = 0.0;
   out_3310708289553390566[176] = 0.0;
   out_3310708289553390566[177] = 0.0;
   out_3310708289553390566[178] = 0.0;
   out_3310708289553390566[179] = 0.0;
   out_3310708289553390566[180] = 0.0;
   out_3310708289553390566[181] = 0.0;
   out_3310708289553390566[182] = 0.0;
   out_3310708289553390566[183] = 0.0;
   out_3310708289553390566[184] = 0.0;
   out_3310708289553390566[185] = 0.0;
   out_3310708289553390566[186] = 0.0;
   out_3310708289553390566[187] = 0.0;
   out_3310708289553390566[188] = 0.0;
   out_3310708289553390566[189] = 0.0;
   out_3310708289553390566[190] = 1.0;
   out_3310708289553390566[191] = 0.0;
   out_3310708289553390566[192] = 0.0;
   out_3310708289553390566[193] = 0.0;
   out_3310708289553390566[194] = 0.0;
   out_3310708289553390566[195] = 0.0;
   out_3310708289553390566[196] = 0.0;
   out_3310708289553390566[197] = 0.0;
   out_3310708289553390566[198] = 0.0;
   out_3310708289553390566[199] = 0.0;
   out_3310708289553390566[200] = 0.0;
   out_3310708289553390566[201] = 0.0;
   out_3310708289553390566[202] = 0.0;
   out_3310708289553390566[203] = 0.0;
   out_3310708289553390566[204] = 0.0;
   out_3310708289553390566[205] = 0.0;
   out_3310708289553390566[206] = 0.0;
   out_3310708289553390566[207] = 0.0;
   out_3310708289553390566[208] = 0.0;
   out_3310708289553390566[209] = 1.0;
   out_3310708289553390566[210] = 0.0;
   out_3310708289553390566[211] = 0.0;
   out_3310708289553390566[212] = 0.0;
   out_3310708289553390566[213] = 0.0;
   out_3310708289553390566[214] = 0.0;
   out_3310708289553390566[215] = 0.0;
   out_3310708289553390566[216] = 0.0;
   out_3310708289553390566[217] = 0.0;
   out_3310708289553390566[218] = 0.0;
   out_3310708289553390566[219] = 0.0;
   out_3310708289553390566[220] = 0.0;
   out_3310708289553390566[221] = 0.0;
   out_3310708289553390566[222] = 0.0;
   out_3310708289553390566[223] = 0.0;
   out_3310708289553390566[224] = 0.0;
   out_3310708289553390566[225] = 0.0;
   out_3310708289553390566[226] = 0.0;
   out_3310708289553390566[227] = 0.0;
   out_3310708289553390566[228] = 1.0;
   out_3310708289553390566[229] = 0.0;
   out_3310708289553390566[230] = 0.0;
   out_3310708289553390566[231] = 0.0;
   out_3310708289553390566[232] = 0.0;
   out_3310708289553390566[233] = 0.0;
   out_3310708289553390566[234] = 0.0;
   out_3310708289553390566[235] = 0.0;
   out_3310708289553390566[236] = 0.0;
   out_3310708289553390566[237] = 0.0;
   out_3310708289553390566[238] = 0.0;
   out_3310708289553390566[239] = 0.0;
   out_3310708289553390566[240] = 0.0;
   out_3310708289553390566[241] = 0.0;
   out_3310708289553390566[242] = 0.0;
   out_3310708289553390566[243] = 0.0;
   out_3310708289553390566[244] = 0.0;
   out_3310708289553390566[245] = 0.0;
   out_3310708289553390566[246] = 0.0;
   out_3310708289553390566[247] = 1.0;
   out_3310708289553390566[248] = 0.0;
   out_3310708289553390566[249] = 0.0;
   out_3310708289553390566[250] = 0.0;
   out_3310708289553390566[251] = 0.0;
   out_3310708289553390566[252] = 0.0;
   out_3310708289553390566[253] = 0.0;
   out_3310708289553390566[254] = 0.0;
   out_3310708289553390566[255] = 0.0;
   out_3310708289553390566[256] = 0.0;
   out_3310708289553390566[257] = 0.0;
   out_3310708289553390566[258] = 0.0;
   out_3310708289553390566[259] = 0.0;
   out_3310708289553390566[260] = 0.0;
   out_3310708289553390566[261] = 0.0;
   out_3310708289553390566[262] = 0.0;
   out_3310708289553390566[263] = 0.0;
   out_3310708289553390566[264] = 0.0;
   out_3310708289553390566[265] = 0.0;
   out_3310708289553390566[266] = 1.0;
   out_3310708289553390566[267] = 0.0;
   out_3310708289553390566[268] = 0.0;
   out_3310708289553390566[269] = 0.0;
   out_3310708289553390566[270] = 0.0;
   out_3310708289553390566[271] = 0.0;
   out_3310708289553390566[272] = 0.0;
   out_3310708289553390566[273] = 0.0;
   out_3310708289553390566[274] = 0.0;
   out_3310708289553390566[275] = 0.0;
   out_3310708289553390566[276] = 0.0;
   out_3310708289553390566[277] = 0.0;
   out_3310708289553390566[278] = 0.0;
   out_3310708289553390566[279] = 0.0;
   out_3310708289553390566[280] = 0.0;
   out_3310708289553390566[281] = 0.0;
   out_3310708289553390566[282] = 0.0;
   out_3310708289553390566[283] = 0.0;
   out_3310708289553390566[284] = 0.0;
   out_3310708289553390566[285] = 1.0;
   out_3310708289553390566[286] = 0.0;
   out_3310708289553390566[287] = 0.0;
   out_3310708289553390566[288] = 0.0;
   out_3310708289553390566[289] = 0.0;
   out_3310708289553390566[290] = 0.0;
   out_3310708289553390566[291] = 0.0;
   out_3310708289553390566[292] = 0.0;
   out_3310708289553390566[293] = 0.0;
   out_3310708289553390566[294] = 0.0;
   out_3310708289553390566[295] = 0.0;
   out_3310708289553390566[296] = 0.0;
   out_3310708289553390566[297] = 0.0;
   out_3310708289553390566[298] = 0.0;
   out_3310708289553390566[299] = 0.0;
   out_3310708289553390566[300] = 0.0;
   out_3310708289553390566[301] = 0.0;
   out_3310708289553390566[302] = 0.0;
   out_3310708289553390566[303] = 0.0;
   out_3310708289553390566[304] = 1.0;
   out_3310708289553390566[305] = 0.0;
   out_3310708289553390566[306] = 0.0;
   out_3310708289553390566[307] = 0.0;
   out_3310708289553390566[308] = 0.0;
   out_3310708289553390566[309] = 0.0;
   out_3310708289553390566[310] = 0.0;
   out_3310708289553390566[311] = 0.0;
   out_3310708289553390566[312] = 0.0;
   out_3310708289553390566[313] = 0.0;
   out_3310708289553390566[314] = 0.0;
   out_3310708289553390566[315] = 0.0;
   out_3310708289553390566[316] = 0.0;
   out_3310708289553390566[317] = 0.0;
   out_3310708289553390566[318] = 0.0;
   out_3310708289553390566[319] = 0.0;
   out_3310708289553390566[320] = 0.0;
   out_3310708289553390566[321] = 0.0;
   out_3310708289553390566[322] = 0.0;
   out_3310708289553390566[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8818314056008048446) {
   out_8818314056008048446[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8818314056008048446[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8818314056008048446[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8818314056008048446[3] = dt*state[12] + state[3];
   out_8818314056008048446[4] = dt*state[13] + state[4];
   out_8818314056008048446[5] = dt*state[14] + state[5];
   out_8818314056008048446[6] = state[6];
   out_8818314056008048446[7] = state[7];
   out_8818314056008048446[8] = state[8];
   out_8818314056008048446[9] = state[9];
   out_8818314056008048446[10] = state[10];
   out_8818314056008048446[11] = state[11];
   out_8818314056008048446[12] = state[12];
   out_8818314056008048446[13] = state[13];
   out_8818314056008048446[14] = state[14];
   out_8818314056008048446[15] = state[15];
   out_8818314056008048446[16] = state[16];
   out_8818314056008048446[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2885434936790366260) {
   out_2885434936790366260[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2885434936790366260[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2885434936790366260[2] = 0;
   out_2885434936790366260[3] = 0;
   out_2885434936790366260[4] = 0;
   out_2885434936790366260[5] = 0;
   out_2885434936790366260[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2885434936790366260[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2885434936790366260[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2885434936790366260[9] = 0;
   out_2885434936790366260[10] = 0;
   out_2885434936790366260[11] = 0;
   out_2885434936790366260[12] = 0;
   out_2885434936790366260[13] = 0;
   out_2885434936790366260[14] = 0;
   out_2885434936790366260[15] = 0;
   out_2885434936790366260[16] = 0;
   out_2885434936790366260[17] = 0;
   out_2885434936790366260[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2885434936790366260[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2885434936790366260[20] = 0;
   out_2885434936790366260[21] = 0;
   out_2885434936790366260[22] = 0;
   out_2885434936790366260[23] = 0;
   out_2885434936790366260[24] = 0;
   out_2885434936790366260[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2885434936790366260[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2885434936790366260[27] = 0;
   out_2885434936790366260[28] = 0;
   out_2885434936790366260[29] = 0;
   out_2885434936790366260[30] = 0;
   out_2885434936790366260[31] = 0;
   out_2885434936790366260[32] = 0;
   out_2885434936790366260[33] = 0;
   out_2885434936790366260[34] = 0;
   out_2885434936790366260[35] = 0;
   out_2885434936790366260[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2885434936790366260[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2885434936790366260[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2885434936790366260[39] = 0;
   out_2885434936790366260[40] = 0;
   out_2885434936790366260[41] = 0;
   out_2885434936790366260[42] = 0;
   out_2885434936790366260[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2885434936790366260[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2885434936790366260[45] = 0;
   out_2885434936790366260[46] = 0;
   out_2885434936790366260[47] = 0;
   out_2885434936790366260[48] = 0;
   out_2885434936790366260[49] = 0;
   out_2885434936790366260[50] = 0;
   out_2885434936790366260[51] = 0;
   out_2885434936790366260[52] = 0;
   out_2885434936790366260[53] = 0;
   out_2885434936790366260[54] = 0;
   out_2885434936790366260[55] = 0;
   out_2885434936790366260[56] = 0;
   out_2885434936790366260[57] = 1;
   out_2885434936790366260[58] = 0;
   out_2885434936790366260[59] = 0;
   out_2885434936790366260[60] = 0;
   out_2885434936790366260[61] = 0;
   out_2885434936790366260[62] = 0;
   out_2885434936790366260[63] = 0;
   out_2885434936790366260[64] = 0;
   out_2885434936790366260[65] = 0;
   out_2885434936790366260[66] = dt;
   out_2885434936790366260[67] = 0;
   out_2885434936790366260[68] = 0;
   out_2885434936790366260[69] = 0;
   out_2885434936790366260[70] = 0;
   out_2885434936790366260[71] = 0;
   out_2885434936790366260[72] = 0;
   out_2885434936790366260[73] = 0;
   out_2885434936790366260[74] = 0;
   out_2885434936790366260[75] = 0;
   out_2885434936790366260[76] = 1;
   out_2885434936790366260[77] = 0;
   out_2885434936790366260[78] = 0;
   out_2885434936790366260[79] = 0;
   out_2885434936790366260[80] = 0;
   out_2885434936790366260[81] = 0;
   out_2885434936790366260[82] = 0;
   out_2885434936790366260[83] = 0;
   out_2885434936790366260[84] = 0;
   out_2885434936790366260[85] = dt;
   out_2885434936790366260[86] = 0;
   out_2885434936790366260[87] = 0;
   out_2885434936790366260[88] = 0;
   out_2885434936790366260[89] = 0;
   out_2885434936790366260[90] = 0;
   out_2885434936790366260[91] = 0;
   out_2885434936790366260[92] = 0;
   out_2885434936790366260[93] = 0;
   out_2885434936790366260[94] = 0;
   out_2885434936790366260[95] = 1;
   out_2885434936790366260[96] = 0;
   out_2885434936790366260[97] = 0;
   out_2885434936790366260[98] = 0;
   out_2885434936790366260[99] = 0;
   out_2885434936790366260[100] = 0;
   out_2885434936790366260[101] = 0;
   out_2885434936790366260[102] = 0;
   out_2885434936790366260[103] = 0;
   out_2885434936790366260[104] = dt;
   out_2885434936790366260[105] = 0;
   out_2885434936790366260[106] = 0;
   out_2885434936790366260[107] = 0;
   out_2885434936790366260[108] = 0;
   out_2885434936790366260[109] = 0;
   out_2885434936790366260[110] = 0;
   out_2885434936790366260[111] = 0;
   out_2885434936790366260[112] = 0;
   out_2885434936790366260[113] = 0;
   out_2885434936790366260[114] = 1;
   out_2885434936790366260[115] = 0;
   out_2885434936790366260[116] = 0;
   out_2885434936790366260[117] = 0;
   out_2885434936790366260[118] = 0;
   out_2885434936790366260[119] = 0;
   out_2885434936790366260[120] = 0;
   out_2885434936790366260[121] = 0;
   out_2885434936790366260[122] = 0;
   out_2885434936790366260[123] = 0;
   out_2885434936790366260[124] = 0;
   out_2885434936790366260[125] = 0;
   out_2885434936790366260[126] = 0;
   out_2885434936790366260[127] = 0;
   out_2885434936790366260[128] = 0;
   out_2885434936790366260[129] = 0;
   out_2885434936790366260[130] = 0;
   out_2885434936790366260[131] = 0;
   out_2885434936790366260[132] = 0;
   out_2885434936790366260[133] = 1;
   out_2885434936790366260[134] = 0;
   out_2885434936790366260[135] = 0;
   out_2885434936790366260[136] = 0;
   out_2885434936790366260[137] = 0;
   out_2885434936790366260[138] = 0;
   out_2885434936790366260[139] = 0;
   out_2885434936790366260[140] = 0;
   out_2885434936790366260[141] = 0;
   out_2885434936790366260[142] = 0;
   out_2885434936790366260[143] = 0;
   out_2885434936790366260[144] = 0;
   out_2885434936790366260[145] = 0;
   out_2885434936790366260[146] = 0;
   out_2885434936790366260[147] = 0;
   out_2885434936790366260[148] = 0;
   out_2885434936790366260[149] = 0;
   out_2885434936790366260[150] = 0;
   out_2885434936790366260[151] = 0;
   out_2885434936790366260[152] = 1;
   out_2885434936790366260[153] = 0;
   out_2885434936790366260[154] = 0;
   out_2885434936790366260[155] = 0;
   out_2885434936790366260[156] = 0;
   out_2885434936790366260[157] = 0;
   out_2885434936790366260[158] = 0;
   out_2885434936790366260[159] = 0;
   out_2885434936790366260[160] = 0;
   out_2885434936790366260[161] = 0;
   out_2885434936790366260[162] = 0;
   out_2885434936790366260[163] = 0;
   out_2885434936790366260[164] = 0;
   out_2885434936790366260[165] = 0;
   out_2885434936790366260[166] = 0;
   out_2885434936790366260[167] = 0;
   out_2885434936790366260[168] = 0;
   out_2885434936790366260[169] = 0;
   out_2885434936790366260[170] = 0;
   out_2885434936790366260[171] = 1;
   out_2885434936790366260[172] = 0;
   out_2885434936790366260[173] = 0;
   out_2885434936790366260[174] = 0;
   out_2885434936790366260[175] = 0;
   out_2885434936790366260[176] = 0;
   out_2885434936790366260[177] = 0;
   out_2885434936790366260[178] = 0;
   out_2885434936790366260[179] = 0;
   out_2885434936790366260[180] = 0;
   out_2885434936790366260[181] = 0;
   out_2885434936790366260[182] = 0;
   out_2885434936790366260[183] = 0;
   out_2885434936790366260[184] = 0;
   out_2885434936790366260[185] = 0;
   out_2885434936790366260[186] = 0;
   out_2885434936790366260[187] = 0;
   out_2885434936790366260[188] = 0;
   out_2885434936790366260[189] = 0;
   out_2885434936790366260[190] = 1;
   out_2885434936790366260[191] = 0;
   out_2885434936790366260[192] = 0;
   out_2885434936790366260[193] = 0;
   out_2885434936790366260[194] = 0;
   out_2885434936790366260[195] = 0;
   out_2885434936790366260[196] = 0;
   out_2885434936790366260[197] = 0;
   out_2885434936790366260[198] = 0;
   out_2885434936790366260[199] = 0;
   out_2885434936790366260[200] = 0;
   out_2885434936790366260[201] = 0;
   out_2885434936790366260[202] = 0;
   out_2885434936790366260[203] = 0;
   out_2885434936790366260[204] = 0;
   out_2885434936790366260[205] = 0;
   out_2885434936790366260[206] = 0;
   out_2885434936790366260[207] = 0;
   out_2885434936790366260[208] = 0;
   out_2885434936790366260[209] = 1;
   out_2885434936790366260[210] = 0;
   out_2885434936790366260[211] = 0;
   out_2885434936790366260[212] = 0;
   out_2885434936790366260[213] = 0;
   out_2885434936790366260[214] = 0;
   out_2885434936790366260[215] = 0;
   out_2885434936790366260[216] = 0;
   out_2885434936790366260[217] = 0;
   out_2885434936790366260[218] = 0;
   out_2885434936790366260[219] = 0;
   out_2885434936790366260[220] = 0;
   out_2885434936790366260[221] = 0;
   out_2885434936790366260[222] = 0;
   out_2885434936790366260[223] = 0;
   out_2885434936790366260[224] = 0;
   out_2885434936790366260[225] = 0;
   out_2885434936790366260[226] = 0;
   out_2885434936790366260[227] = 0;
   out_2885434936790366260[228] = 1;
   out_2885434936790366260[229] = 0;
   out_2885434936790366260[230] = 0;
   out_2885434936790366260[231] = 0;
   out_2885434936790366260[232] = 0;
   out_2885434936790366260[233] = 0;
   out_2885434936790366260[234] = 0;
   out_2885434936790366260[235] = 0;
   out_2885434936790366260[236] = 0;
   out_2885434936790366260[237] = 0;
   out_2885434936790366260[238] = 0;
   out_2885434936790366260[239] = 0;
   out_2885434936790366260[240] = 0;
   out_2885434936790366260[241] = 0;
   out_2885434936790366260[242] = 0;
   out_2885434936790366260[243] = 0;
   out_2885434936790366260[244] = 0;
   out_2885434936790366260[245] = 0;
   out_2885434936790366260[246] = 0;
   out_2885434936790366260[247] = 1;
   out_2885434936790366260[248] = 0;
   out_2885434936790366260[249] = 0;
   out_2885434936790366260[250] = 0;
   out_2885434936790366260[251] = 0;
   out_2885434936790366260[252] = 0;
   out_2885434936790366260[253] = 0;
   out_2885434936790366260[254] = 0;
   out_2885434936790366260[255] = 0;
   out_2885434936790366260[256] = 0;
   out_2885434936790366260[257] = 0;
   out_2885434936790366260[258] = 0;
   out_2885434936790366260[259] = 0;
   out_2885434936790366260[260] = 0;
   out_2885434936790366260[261] = 0;
   out_2885434936790366260[262] = 0;
   out_2885434936790366260[263] = 0;
   out_2885434936790366260[264] = 0;
   out_2885434936790366260[265] = 0;
   out_2885434936790366260[266] = 1;
   out_2885434936790366260[267] = 0;
   out_2885434936790366260[268] = 0;
   out_2885434936790366260[269] = 0;
   out_2885434936790366260[270] = 0;
   out_2885434936790366260[271] = 0;
   out_2885434936790366260[272] = 0;
   out_2885434936790366260[273] = 0;
   out_2885434936790366260[274] = 0;
   out_2885434936790366260[275] = 0;
   out_2885434936790366260[276] = 0;
   out_2885434936790366260[277] = 0;
   out_2885434936790366260[278] = 0;
   out_2885434936790366260[279] = 0;
   out_2885434936790366260[280] = 0;
   out_2885434936790366260[281] = 0;
   out_2885434936790366260[282] = 0;
   out_2885434936790366260[283] = 0;
   out_2885434936790366260[284] = 0;
   out_2885434936790366260[285] = 1;
   out_2885434936790366260[286] = 0;
   out_2885434936790366260[287] = 0;
   out_2885434936790366260[288] = 0;
   out_2885434936790366260[289] = 0;
   out_2885434936790366260[290] = 0;
   out_2885434936790366260[291] = 0;
   out_2885434936790366260[292] = 0;
   out_2885434936790366260[293] = 0;
   out_2885434936790366260[294] = 0;
   out_2885434936790366260[295] = 0;
   out_2885434936790366260[296] = 0;
   out_2885434936790366260[297] = 0;
   out_2885434936790366260[298] = 0;
   out_2885434936790366260[299] = 0;
   out_2885434936790366260[300] = 0;
   out_2885434936790366260[301] = 0;
   out_2885434936790366260[302] = 0;
   out_2885434936790366260[303] = 0;
   out_2885434936790366260[304] = 1;
   out_2885434936790366260[305] = 0;
   out_2885434936790366260[306] = 0;
   out_2885434936790366260[307] = 0;
   out_2885434936790366260[308] = 0;
   out_2885434936790366260[309] = 0;
   out_2885434936790366260[310] = 0;
   out_2885434936790366260[311] = 0;
   out_2885434936790366260[312] = 0;
   out_2885434936790366260[313] = 0;
   out_2885434936790366260[314] = 0;
   out_2885434936790366260[315] = 0;
   out_2885434936790366260[316] = 0;
   out_2885434936790366260[317] = 0;
   out_2885434936790366260[318] = 0;
   out_2885434936790366260[319] = 0;
   out_2885434936790366260[320] = 0;
   out_2885434936790366260[321] = 0;
   out_2885434936790366260[322] = 0;
   out_2885434936790366260[323] = 1;
}
void h_4(double *state, double *unused, double *out_7861660616364934295) {
   out_7861660616364934295[0] = state[6] + state[9];
   out_7861660616364934295[1] = state[7] + state[10];
   out_7861660616364934295[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2112760807670492462) {
   out_2112760807670492462[0] = 0;
   out_2112760807670492462[1] = 0;
   out_2112760807670492462[2] = 0;
   out_2112760807670492462[3] = 0;
   out_2112760807670492462[4] = 0;
   out_2112760807670492462[5] = 0;
   out_2112760807670492462[6] = 1;
   out_2112760807670492462[7] = 0;
   out_2112760807670492462[8] = 0;
   out_2112760807670492462[9] = 1;
   out_2112760807670492462[10] = 0;
   out_2112760807670492462[11] = 0;
   out_2112760807670492462[12] = 0;
   out_2112760807670492462[13] = 0;
   out_2112760807670492462[14] = 0;
   out_2112760807670492462[15] = 0;
   out_2112760807670492462[16] = 0;
   out_2112760807670492462[17] = 0;
   out_2112760807670492462[18] = 0;
   out_2112760807670492462[19] = 0;
   out_2112760807670492462[20] = 0;
   out_2112760807670492462[21] = 0;
   out_2112760807670492462[22] = 0;
   out_2112760807670492462[23] = 0;
   out_2112760807670492462[24] = 0;
   out_2112760807670492462[25] = 1;
   out_2112760807670492462[26] = 0;
   out_2112760807670492462[27] = 0;
   out_2112760807670492462[28] = 1;
   out_2112760807670492462[29] = 0;
   out_2112760807670492462[30] = 0;
   out_2112760807670492462[31] = 0;
   out_2112760807670492462[32] = 0;
   out_2112760807670492462[33] = 0;
   out_2112760807670492462[34] = 0;
   out_2112760807670492462[35] = 0;
   out_2112760807670492462[36] = 0;
   out_2112760807670492462[37] = 0;
   out_2112760807670492462[38] = 0;
   out_2112760807670492462[39] = 0;
   out_2112760807670492462[40] = 0;
   out_2112760807670492462[41] = 0;
   out_2112760807670492462[42] = 0;
   out_2112760807670492462[43] = 0;
   out_2112760807670492462[44] = 1;
   out_2112760807670492462[45] = 0;
   out_2112760807670492462[46] = 0;
   out_2112760807670492462[47] = 1;
   out_2112760807670492462[48] = 0;
   out_2112760807670492462[49] = 0;
   out_2112760807670492462[50] = 0;
   out_2112760807670492462[51] = 0;
   out_2112760807670492462[52] = 0;
   out_2112760807670492462[53] = 0;
}
void h_10(double *state, double *unused, double *out_896930610882370113) {
   out_896930610882370113[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_896930610882370113[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_896930610882370113[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_107142426047667165) {
   out_107142426047667165[0] = 0;
   out_107142426047667165[1] = 9.8100000000000005*cos(state[1]);
   out_107142426047667165[2] = 0;
   out_107142426047667165[3] = 0;
   out_107142426047667165[4] = -state[8];
   out_107142426047667165[5] = state[7];
   out_107142426047667165[6] = 0;
   out_107142426047667165[7] = state[5];
   out_107142426047667165[8] = -state[4];
   out_107142426047667165[9] = 0;
   out_107142426047667165[10] = 0;
   out_107142426047667165[11] = 0;
   out_107142426047667165[12] = 1;
   out_107142426047667165[13] = 0;
   out_107142426047667165[14] = 0;
   out_107142426047667165[15] = 1;
   out_107142426047667165[16] = 0;
   out_107142426047667165[17] = 0;
   out_107142426047667165[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_107142426047667165[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_107142426047667165[20] = 0;
   out_107142426047667165[21] = state[8];
   out_107142426047667165[22] = 0;
   out_107142426047667165[23] = -state[6];
   out_107142426047667165[24] = -state[5];
   out_107142426047667165[25] = 0;
   out_107142426047667165[26] = state[3];
   out_107142426047667165[27] = 0;
   out_107142426047667165[28] = 0;
   out_107142426047667165[29] = 0;
   out_107142426047667165[30] = 0;
   out_107142426047667165[31] = 1;
   out_107142426047667165[32] = 0;
   out_107142426047667165[33] = 0;
   out_107142426047667165[34] = 1;
   out_107142426047667165[35] = 0;
   out_107142426047667165[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_107142426047667165[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_107142426047667165[38] = 0;
   out_107142426047667165[39] = -state[7];
   out_107142426047667165[40] = state[6];
   out_107142426047667165[41] = 0;
   out_107142426047667165[42] = state[4];
   out_107142426047667165[43] = -state[3];
   out_107142426047667165[44] = 0;
   out_107142426047667165[45] = 0;
   out_107142426047667165[46] = 0;
   out_107142426047667165[47] = 0;
   out_107142426047667165[48] = 0;
   out_107142426047667165[49] = 0;
   out_107142426047667165[50] = 1;
   out_107142426047667165[51] = 0;
   out_107142426047667165[52] = 0;
   out_107142426047667165[53] = 1;
}
void h_13(double *state, double *unused, double *out_6097667701153012788) {
   out_6097667701153012788[0] = state[3];
   out_6097667701153012788[1] = state[4];
   out_6097667701153012788[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1099513017661840339) {
   out_1099513017661840339[0] = 0;
   out_1099513017661840339[1] = 0;
   out_1099513017661840339[2] = 0;
   out_1099513017661840339[3] = 1;
   out_1099513017661840339[4] = 0;
   out_1099513017661840339[5] = 0;
   out_1099513017661840339[6] = 0;
   out_1099513017661840339[7] = 0;
   out_1099513017661840339[8] = 0;
   out_1099513017661840339[9] = 0;
   out_1099513017661840339[10] = 0;
   out_1099513017661840339[11] = 0;
   out_1099513017661840339[12] = 0;
   out_1099513017661840339[13] = 0;
   out_1099513017661840339[14] = 0;
   out_1099513017661840339[15] = 0;
   out_1099513017661840339[16] = 0;
   out_1099513017661840339[17] = 0;
   out_1099513017661840339[18] = 0;
   out_1099513017661840339[19] = 0;
   out_1099513017661840339[20] = 0;
   out_1099513017661840339[21] = 0;
   out_1099513017661840339[22] = 1;
   out_1099513017661840339[23] = 0;
   out_1099513017661840339[24] = 0;
   out_1099513017661840339[25] = 0;
   out_1099513017661840339[26] = 0;
   out_1099513017661840339[27] = 0;
   out_1099513017661840339[28] = 0;
   out_1099513017661840339[29] = 0;
   out_1099513017661840339[30] = 0;
   out_1099513017661840339[31] = 0;
   out_1099513017661840339[32] = 0;
   out_1099513017661840339[33] = 0;
   out_1099513017661840339[34] = 0;
   out_1099513017661840339[35] = 0;
   out_1099513017661840339[36] = 0;
   out_1099513017661840339[37] = 0;
   out_1099513017661840339[38] = 0;
   out_1099513017661840339[39] = 0;
   out_1099513017661840339[40] = 0;
   out_1099513017661840339[41] = 1;
   out_1099513017661840339[42] = 0;
   out_1099513017661840339[43] = 0;
   out_1099513017661840339[44] = 0;
   out_1099513017661840339[45] = 0;
   out_1099513017661840339[46] = 0;
   out_1099513017661840339[47] = 0;
   out_1099513017661840339[48] = 0;
   out_1099513017661840339[49] = 0;
   out_1099513017661840339[50] = 0;
   out_1099513017661840339[51] = 0;
   out_1099513017661840339[52] = 0;
   out_1099513017661840339[53] = 0;
}
void h_14(double *state, double *unused, double *out_7028840117111836812) {
   out_7028840117111836812[0] = state[6];
   out_7028840117111836812[1] = state[7];
   out_7028840117111836812[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5195549239965864758) {
   out_5195549239965864758[0] = 0;
   out_5195549239965864758[1] = 0;
   out_5195549239965864758[2] = 0;
   out_5195549239965864758[3] = 0;
   out_5195549239965864758[4] = 0;
   out_5195549239965864758[5] = 0;
   out_5195549239965864758[6] = 1;
   out_5195549239965864758[7] = 0;
   out_5195549239965864758[8] = 0;
   out_5195549239965864758[9] = 0;
   out_5195549239965864758[10] = 0;
   out_5195549239965864758[11] = 0;
   out_5195549239965864758[12] = 0;
   out_5195549239965864758[13] = 0;
   out_5195549239965864758[14] = 0;
   out_5195549239965864758[15] = 0;
   out_5195549239965864758[16] = 0;
   out_5195549239965864758[17] = 0;
   out_5195549239965864758[18] = 0;
   out_5195549239965864758[19] = 0;
   out_5195549239965864758[20] = 0;
   out_5195549239965864758[21] = 0;
   out_5195549239965864758[22] = 0;
   out_5195549239965864758[23] = 0;
   out_5195549239965864758[24] = 0;
   out_5195549239965864758[25] = 1;
   out_5195549239965864758[26] = 0;
   out_5195549239965864758[27] = 0;
   out_5195549239965864758[28] = 0;
   out_5195549239965864758[29] = 0;
   out_5195549239965864758[30] = 0;
   out_5195549239965864758[31] = 0;
   out_5195549239965864758[32] = 0;
   out_5195549239965864758[33] = 0;
   out_5195549239965864758[34] = 0;
   out_5195549239965864758[35] = 0;
   out_5195549239965864758[36] = 0;
   out_5195549239965864758[37] = 0;
   out_5195549239965864758[38] = 0;
   out_5195549239965864758[39] = 0;
   out_5195549239965864758[40] = 0;
   out_5195549239965864758[41] = 0;
   out_5195549239965864758[42] = 0;
   out_5195549239965864758[43] = 0;
   out_5195549239965864758[44] = 1;
   out_5195549239965864758[45] = 0;
   out_5195549239965864758[46] = 0;
   out_5195549239965864758[47] = 0;
   out_5195549239965864758[48] = 0;
   out_5195549239965864758[49] = 0;
   out_5195549239965864758[50] = 0;
   out_5195549239965864758[51] = 0;
   out_5195549239965864758[52] = 0;
   out_5195549239965864758[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7661590215377839666) {
  err_fun(nom_x, delta_x, out_7661590215377839666);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_867942321893475263) {
  inv_err_fun(nom_x, true_x, out_867942321893475263);
}
void pose_H_mod_fun(double *state, double *out_3310708289553390566) {
  H_mod_fun(state, out_3310708289553390566);
}
void pose_f_fun(double *state, double dt, double *out_8818314056008048446) {
  f_fun(state,  dt, out_8818314056008048446);
}
void pose_F_fun(double *state, double dt, double *out_2885434936790366260) {
  F_fun(state,  dt, out_2885434936790366260);
}
void pose_h_4(double *state, double *unused, double *out_7861660616364934295) {
  h_4(state, unused, out_7861660616364934295);
}
void pose_H_4(double *state, double *unused, double *out_2112760807670492462) {
  H_4(state, unused, out_2112760807670492462);
}
void pose_h_10(double *state, double *unused, double *out_896930610882370113) {
  h_10(state, unused, out_896930610882370113);
}
void pose_H_10(double *state, double *unused, double *out_107142426047667165) {
  H_10(state, unused, out_107142426047667165);
}
void pose_h_13(double *state, double *unused, double *out_6097667701153012788) {
  h_13(state, unused, out_6097667701153012788);
}
void pose_H_13(double *state, double *unused, double *out_1099513017661840339) {
  H_13(state, unused, out_1099513017661840339);
}
void pose_h_14(double *state, double *unused, double *out_7028840117111836812) {
  h_14(state, unused, out_7028840117111836812);
}
void pose_H_14(double *state, double *unused, double *out_5195549239965864758) {
  H_14(state, unused, out_5195549239965864758);
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
