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
void err_fun(double *nom_x, double *delta_x, double *out_5992451308463414616) {
   out_5992451308463414616[0] = delta_x[0] + nom_x[0];
   out_5992451308463414616[1] = delta_x[1] + nom_x[1];
   out_5992451308463414616[2] = delta_x[2] + nom_x[2];
   out_5992451308463414616[3] = delta_x[3] + nom_x[3];
   out_5992451308463414616[4] = delta_x[4] + nom_x[4];
   out_5992451308463414616[5] = delta_x[5] + nom_x[5];
   out_5992451308463414616[6] = delta_x[6] + nom_x[6];
   out_5992451308463414616[7] = delta_x[7] + nom_x[7];
   out_5992451308463414616[8] = delta_x[8] + nom_x[8];
   out_5992451308463414616[9] = delta_x[9] + nom_x[9];
   out_5992451308463414616[10] = delta_x[10] + nom_x[10];
   out_5992451308463414616[11] = delta_x[11] + nom_x[11];
   out_5992451308463414616[12] = delta_x[12] + nom_x[12];
   out_5992451308463414616[13] = delta_x[13] + nom_x[13];
   out_5992451308463414616[14] = delta_x[14] + nom_x[14];
   out_5992451308463414616[15] = delta_x[15] + nom_x[15];
   out_5992451308463414616[16] = delta_x[16] + nom_x[16];
   out_5992451308463414616[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7389899634648651549) {
   out_7389899634648651549[0] = -nom_x[0] + true_x[0];
   out_7389899634648651549[1] = -nom_x[1] + true_x[1];
   out_7389899634648651549[2] = -nom_x[2] + true_x[2];
   out_7389899634648651549[3] = -nom_x[3] + true_x[3];
   out_7389899634648651549[4] = -nom_x[4] + true_x[4];
   out_7389899634648651549[5] = -nom_x[5] + true_x[5];
   out_7389899634648651549[6] = -nom_x[6] + true_x[6];
   out_7389899634648651549[7] = -nom_x[7] + true_x[7];
   out_7389899634648651549[8] = -nom_x[8] + true_x[8];
   out_7389899634648651549[9] = -nom_x[9] + true_x[9];
   out_7389899634648651549[10] = -nom_x[10] + true_x[10];
   out_7389899634648651549[11] = -nom_x[11] + true_x[11];
   out_7389899634648651549[12] = -nom_x[12] + true_x[12];
   out_7389899634648651549[13] = -nom_x[13] + true_x[13];
   out_7389899634648651549[14] = -nom_x[14] + true_x[14];
   out_7389899634648651549[15] = -nom_x[15] + true_x[15];
   out_7389899634648651549[16] = -nom_x[16] + true_x[16];
   out_7389899634648651549[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3435766699566864488) {
   out_3435766699566864488[0] = 1.0;
   out_3435766699566864488[1] = 0.0;
   out_3435766699566864488[2] = 0.0;
   out_3435766699566864488[3] = 0.0;
   out_3435766699566864488[4] = 0.0;
   out_3435766699566864488[5] = 0.0;
   out_3435766699566864488[6] = 0.0;
   out_3435766699566864488[7] = 0.0;
   out_3435766699566864488[8] = 0.0;
   out_3435766699566864488[9] = 0.0;
   out_3435766699566864488[10] = 0.0;
   out_3435766699566864488[11] = 0.0;
   out_3435766699566864488[12] = 0.0;
   out_3435766699566864488[13] = 0.0;
   out_3435766699566864488[14] = 0.0;
   out_3435766699566864488[15] = 0.0;
   out_3435766699566864488[16] = 0.0;
   out_3435766699566864488[17] = 0.0;
   out_3435766699566864488[18] = 0.0;
   out_3435766699566864488[19] = 1.0;
   out_3435766699566864488[20] = 0.0;
   out_3435766699566864488[21] = 0.0;
   out_3435766699566864488[22] = 0.0;
   out_3435766699566864488[23] = 0.0;
   out_3435766699566864488[24] = 0.0;
   out_3435766699566864488[25] = 0.0;
   out_3435766699566864488[26] = 0.0;
   out_3435766699566864488[27] = 0.0;
   out_3435766699566864488[28] = 0.0;
   out_3435766699566864488[29] = 0.0;
   out_3435766699566864488[30] = 0.0;
   out_3435766699566864488[31] = 0.0;
   out_3435766699566864488[32] = 0.0;
   out_3435766699566864488[33] = 0.0;
   out_3435766699566864488[34] = 0.0;
   out_3435766699566864488[35] = 0.0;
   out_3435766699566864488[36] = 0.0;
   out_3435766699566864488[37] = 0.0;
   out_3435766699566864488[38] = 1.0;
   out_3435766699566864488[39] = 0.0;
   out_3435766699566864488[40] = 0.0;
   out_3435766699566864488[41] = 0.0;
   out_3435766699566864488[42] = 0.0;
   out_3435766699566864488[43] = 0.0;
   out_3435766699566864488[44] = 0.0;
   out_3435766699566864488[45] = 0.0;
   out_3435766699566864488[46] = 0.0;
   out_3435766699566864488[47] = 0.0;
   out_3435766699566864488[48] = 0.0;
   out_3435766699566864488[49] = 0.0;
   out_3435766699566864488[50] = 0.0;
   out_3435766699566864488[51] = 0.0;
   out_3435766699566864488[52] = 0.0;
   out_3435766699566864488[53] = 0.0;
   out_3435766699566864488[54] = 0.0;
   out_3435766699566864488[55] = 0.0;
   out_3435766699566864488[56] = 0.0;
   out_3435766699566864488[57] = 1.0;
   out_3435766699566864488[58] = 0.0;
   out_3435766699566864488[59] = 0.0;
   out_3435766699566864488[60] = 0.0;
   out_3435766699566864488[61] = 0.0;
   out_3435766699566864488[62] = 0.0;
   out_3435766699566864488[63] = 0.0;
   out_3435766699566864488[64] = 0.0;
   out_3435766699566864488[65] = 0.0;
   out_3435766699566864488[66] = 0.0;
   out_3435766699566864488[67] = 0.0;
   out_3435766699566864488[68] = 0.0;
   out_3435766699566864488[69] = 0.0;
   out_3435766699566864488[70] = 0.0;
   out_3435766699566864488[71] = 0.0;
   out_3435766699566864488[72] = 0.0;
   out_3435766699566864488[73] = 0.0;
   out_3435766699566864488[74] = 0.0;
   out_3435766699566864488[75] = 0.0;
   out_3435766699566864488[76] = 1.0;
   out_3435766699566864488[77] = 0.0;
   out_3435766699566864488[78] = 0.0;
   out_3435766699566864488[79] = 0.0;
   out_3435766699566864488[80] = 0.0;
   out_3435766699566864488[81] = 0.0;
   out_3435766699566864488[82] = 0.0;
   out_3435766699566864488[83] = 0.0;
   out_3435766699566864488[84] = 0.0;
   out_3435766699566864488[85] = 0.0;
   out_3435766699566864488[86] = 0.0;
   out_3435766699566864488[87] = 0.0;
   out_3435766699566864488[88] = 0.0;
   out_3435766699566864488[89] = 0.0;
   out_3435766699566864488[90] = 0.0;
   out_3435766699566864488[91] = 0.0;
   out_3435766699566864488[92] = 0.0;
   out_3435766699566864488[93] = 0.0;
   out_3435766699566864488[94] = 0.0;
   out_3435766699566864488[95] = 1.0;
   out_3435766699566864488[96] = 0.0;
   out_3435766699566864488[97] = 0.0;
   out_3435766699566864488[98] = 0.0;
   out_3435766699566864488[99] = 0.0;
   out_3435766699566864488[100] = 0.0;
   out_3435766699566864488[101] = 0.0;
   out_3435766699566864488[102] = 0.0;
   out_3435766699566864488[103] = 0.0;
   out_3435766699566864488[104] = 0.0;
   out_3435766699566864488[105] = 0.0;
   out_3435766699566864488[106] = 0.0;
   out_3435766699566864488[107] = 0.0;
   out_3435766699566864488[108] = 0.0;
   out_3435766699566864488[109] = 0.0;
   out_3435766699566864488[110] = 0.0;
   out_3435766699566864488[111] = 0.0;
   out_3435766699566864488[112] = 0.0;
   out_3435766699566864488[113] = 0.0;
   out_3435766699566864488[114] = 1.0;
   out_3435766699566864488[115] = 0.0;
   out_3435766699566864488[116] = 0.0;
   out_3435766699566864488[117] = 0.0;
   out_3435766699566864488[118] = 0.0;
   out_3435766699566864488[119] = 0.0;
   out_3435766699566864488[120] = 0.0;
   out_3435766699566864488[121] = 0.0;
   out_3435766699566864488[122] = 0.0;
   out_3435766699566864488[123] = 0.0;
   out_3435766699566864488[124] = 0.0;
   out_3435766699566864488[125] = 0.0;
   out_3435766699566864488[126] = 0.0;
   out_3435766699566864488[127] = 0.0;
   out_3435766699566864488[128] = 0.0;
   out_3435766699566864488[129] = 0.0;
   out_3435766699566864488[130] = 0.0;
   out_3435766699566864488[131] = 0.0;
   out_3435766699566864488[132] = 0.0;
   out_3435766699566864488[133] = 1.0;
   out_3435766699566864488[134] = 0.0;
   out_3435766699566864488[135] = 0.0;
   out_3435766699566864488[136] = 0.0;
   out_3435766699566864488[137] = 0.0;
   out_3435766699566864488[138] = 0.0;
   out_3435766699566864488[139] = 0.0;
   out_3435766699566864488[140] = 0.0;
   out_3435766699566864488[141] = 0.0;
   out_3435766699566864488[142] = 0.0;
   out_3435766699566864488[143] = 0.0;
   out_3435766699566864488[144] = 0.0;
   out_3435766699566864488[145] = 0.0;
   out_3435766699566864488[146] = 0.0;
   out_3435766699566864488[147] = 0.0;
   out_3435766699566864488[148] = 0.0;
   out_3435766699566864488[149] = 0.0;
   out_3435766699566864488[150] = 0.0;
   out_3435766699566864488[151] = 0.0;
   out_3435766699566864488[152] = 1.0;
   out_3435766699566864488[153] = 0.0;
   out_3435766699566864488[154] = 0.0;
   out_3435766699566864488[155] = 0.0;
   out_3435766699566864488[156] = 0.0;
   out_3435766699566864488[157] = 0.0;
   out_3435766699566864488[158] = 0.0;
   out_3435766699566864488[159] = 0.0;
   out_3435766699566864488[160] = 0.0;
   out_3435766699566864488[161] = 0.0;
   out_3435766699566864488[162] = 0.0;
   out_3435766699566864488[163] = 0.0;
   out_3435766699566864488[164] = 0.0;
   out_3435766699566864488[165] = 0.0;
   out_3435766699566864488[166] = 0.0;
   out_3435766699566864488[167] = 0.0;
   out_3435766699566864488[168] = 0.0;
   out_3435766699566864488[169] = 0.0;
   out_3435766699566864488[170] = 0.0;
   out_3435766699566864488[171] = 1.0;
   out_3435766699566864488[172] = 0.0;
   out_3435766699566864488[173] = 0.0;
   out_3435766699566864488[174] = 0.0;
   out_3435766699566864488[175] = 0.0;
   out_3435766699566864488[176] = 0.0;
   out_3435766699566864488[177] = 0.0;
   out_3435766699566864488[178] = 0.0;
   out_3435766699566864488[179] = 0.0;
   out_3435766699566864488[180] = 0.0;
   out_3435766699566864488[181] = 0.0;
   out_3435766699566864488[182] = 0.0;
   out_3435766699566864488[183] = 0.0;
   out_3435766699566864488[184] = 0.0;
   out_3435766699566864488[185] = 0.0;
   out_3435766699566864488[186] = 0.0;
   out_3435766699566864488[187] = 0.0;
   out_3435766699566864488[188] = 0.0;
   out_3435766699566864488[189] = 0.0;
   out_3435766699566864488[190] = 1.0;
   out_3435766699566864488[191] = 0.0;
   out_3435766699566864488[192] = 0.0;
   out_3435766699566864488[193] = 0.0;
   out_3435766699566864488[194] = 0.0;
   out_3435766699566864488[195] = 0.0;
   out_3435766699566864488[196] = 0.0;
   out_3435766699566864488[197] = 0.0;
   out_3435766699566864488[198] = 0.0;
   out_3435766699566864488[199] = 0.0;
   out_3435766699566864488[200] = 0.0;
   out_3435766699566864488[201] = 0.0;
   out_3435766699566864488[202] = 0.0;
   out_3435766699566864488[203] = 0.0;
   out_3435766699566864488[204] = 0.0;
   out_3435766699566864488[205] = 0.0;
   out_3435766699566864488[206] = 0.0;
   out_3435766699566864488[207] = 0.0;
   out_3435766699566864488[208] = 0.0;
   out_3435766699566864488[209] = 1.0;
   out_3435766699566864488[210] = 0.0;
   out_3435766699566864488[211] = 0.0;
   out_3435766699566864488[212] = 0.0;
   out_3435766699566864488[213] = 0.0;
   out_3435766699566864488[214] = 0.0;
   out_3435766699566864488[215] = 0.0;
   out_3435766699566864488[216] = 0.0;
   out_3435766699566864488[217] = 0.0;
   out_3435766699566864488[218] = 0.0;
   out_3435766699566864488[219] = 0.0;
   out_3435766699566864488[220] = 0.0;
   out_3435766699566864488[221] = 0.0;
   out_3435766699566864488[222] = 0.0;
   out_3435766699566864488[223] = 0.0;
   out_3435766699566864488[224] = 0.0;
   out_3435766699566864488[225] = 0.0;
   out_3435766699566864488[226] = 0.0;
   out_3435766699566864488[227] = 0.0;
   out_3435766699566864488[228] = 1.0;
   out_3435766699566864488[229] = 0.0;
   out_3435766699566864488[230] = 0.0;
   out_3435766699566864488[231] = 0.0;
   out_3435766699566864488[232] = 0.0;
   out_3435766699566864488[233] = 0.0;
   out_3435766699566864488[234] = 0.0;
   out_3435766699566864488[235] = 0.0;
   out_3435766699566864488[236] = 0.0;
   out_3435766699566864488[237] = 0.0;
   out_3435766699566864488[238] = 0.0;
   out_3435766699566864488[239] = 0.0;
   out_3435766699566864488[240] = 0.0;
   out_3435766699566864488[241] = 0.0;
   out_3435766699566864488[242] = 0.0;
   out_3435766699566864488[243] = 0.0;
   out_3435766699566864488[244] = 0.0;
   out_3435766699566864488[245] = 0.0;
   out_3435766699566864488[246] = 0.0;
   out_3435766699566864488[247] = 1.0;
   out_3435766699566864488[248] = 0.0;
   out_3435766699566864488[249] = 0.0;
   out_3435766699566864488[250] = 0.0;
   out_3435766699566864488[251] = 0.0;
   out_3435766699566864488[252] = 0.0;
   out_3435766699566864488[253] = 0.0;
   out_3435766699566864488[254] = 0.0;
   out_3435766699566864488[255] = 0.0;
   out_3435766699566864488[256] = 0.0;
   out_3435766699566864488[257] = 0.0;
   out_3435766699566864488[258] = 0.0;
   out_3435766699566864488[259] = 0.0;
   out_3435766699566864488[260] = 0.0;
   out_3435766699566864488[261] = 0.0;
   out_3435766699566864488[262] = 0.0;
   out_3435766699566864488[263] = 0.0;
   out_3435766699566864488[264] = 0.0;
   out_3435766699566864488[265] = 0.0;
   out_3435766699566864488[266] = 1.0;
   out_3435766699566864488[267] = 0.0;
   out_3435766699566864488[268] = 0.0;
   out_3435766699566864488[269] = 0.0;
   out_3435766699566864488[270] = 0.0;
   out_3435766699566864488[271] = 0.0;
   out_3435766699566864488[272] = 0.0;
   out_3435766699566864488[273] = 0.0;
   out_3435766699566864488[274] = 0.0;
   out_3435766699566864488[275] = 0.0;
   out_3435766699566864488[276] = 0.0;
   out_3435766699566864488[277] = 0.0;
   out_3435766699566864488[278] = 0.0;
   out_3435766699566864488[279] = 0.0;
   out_3435766699566864488[280] = 0.0;
   out_3435766699566864488[281] = 0.0;
   out_3435766699566864488[282] = 0.0;
   out_3435766699566864488[283] = 0.0;
   out_3435766699566864488[284] = 0.0;
   out_3435766699566864488[285] = 1.0;
   out_3435766699566864488[286] = 0.0;
   out_3435766699566864488[287] = 0.0;
   out_3435766699566864488[288] = 0.0;
   out_3435766699566864488[289] = 0.0;
   out_3435766699566864488[290] = 0.0;
   out_3435766699566864488[291] = 0.0;
   out_3435766699566864488[292] = 0.0;
   out_3435766699566864488[293] = 0.0;
   out_3435766699566864488[294] = 0.0;
   out_3435766699566864488[295] = 0.0;
   out_3435766699566864488[296] = 0.0;
   out_3435766699566864488[297] = 0.0;
   out_3435766699566864488[298] = 0.0;
   out_3435766699566864488[299] = 0.0;
   out_3435766699566864488[300] = 0.0;
   out_3435766699566864488[301] = 0.0;
   out_3435766699566864488[302] = 0.0;
   out_3435766699566864488[303] = 0.0;
   out_3435766699566864488[304] = 1.0;
   out_3435766699566864488[305] = 0.0;
   out_3435766699566864488[306] = 0.0;
   out_3435766699566864488[307] = 0.0;
   out_3435766699566864488[308] = 0.0;
   out_3435766699566864488[309] = 0.0;
   out_3435766699566864488[310] = 0.0;
   out_3435766699566864488[311] = 0.0;
   out_3435766699566864488[312] = 0.0;
   out_3435766699566864488[313] = 0.0;
   out_3435766699566864488[314] = 0.0;
   out_3435766699566864488[315] = 0.0;
   out_3435766699566864488[316] = 0.0;
   out_3435766699566864488[317] = 0.0;
   out_3435766699566864488[318] = 0.0;
   out_3435766699566864488[319] = 0.0;
   out_3435766699566864488[320] = 0.0;
   out_3435766699566864488[321] = 0.0;
   out_3435766699566864488[322] = 0.0;
   out_3435766699566864488[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8749009569559483773) {
   out_8749009569559483773[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8749009569559483773[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8749009569559483773[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8749009569559483773[3] = dt*state[12] + state[3];
   out_8749009569559483773[4] = dt*state[13] + state[4];
   out_8749009569559483773[5] = dt*state[14] + state[5];
   out_8749009569559483773[6] = state[6];
   out_8749009569559483773[7] = state[7];
   out_8749009569559483773[8] = state[8];
   out_8749009569559483773[9] = state[9];
   out_8749009569559483773[10] = state[10];
   out_8749009569559483773[11] = state[11];
   out_8749009569559483773[12] = state[12];
   out_8749009569559483773[13] = state[13];
   out_8749009569559483773[14] = state[14];
   out_8749009569559483773[15] = state[15];
   out_8749009569559483773[16] = state[16];
   out_8749009569559483773[17] = state[17];
}
void F_fun(double *state, double dt, double *out_52750658265818918) {
   out_52750658265818918[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_52750658265818918[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_52750658265818918[2] = 0;
   out_52750658265818918[3] = 0;
   out_52750658265818918[4] = 0;
   out_52750658265818918[5] = 0;
   out_52750658265818918[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_52750658265818918[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_52750658265818918[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_52750658265818918[9] = 0;
   out_52750658265818918[10] = 0;
   out_52750658265818918[11] = 0;
   out_52750658265818918[12] = 0;
   out_52750658265818918[13] = 0;
   out_52750658265818918[14] = 0;
   out_52750658265818918[15] = 0;
   out_52750658265818918[16] = 0;
   out_52750658265818918[17] = 0;
   out_52750658265818918[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_52750658265818918[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_52750658265818918[20] = 0;
   out_52750658265818918[21] = 0;
   out_52750658265818918[22] = 0;
   out_52750658265818918[23] = 0;
   out_52750658265818918[24] = 0;
   out_52750658265818918[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_52750658265818918[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_52750658265818918[27] = 0;
   out_52750658265818918[28] = 0;
   out_52750658265818918[29] = 0;
   out_52750658265818918[30] = 0;
   out_52750658265818918[31] = 0;
   out_52750658265818918[32] = 0;
   out_52750658265818918[33] = 0;
   out_52750658265818918[34] = 0;
   out_52750658265818918[35] = 0;
   out_52750658265818918[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_52750658265818918[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_52750658265818918[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_52750658265818918[39] = 0;
   out_52750658265818918[40] = 0;
   out_52750658265818918[41] = 0;
   out_52750658265818918[42] = 0;
   out_52750658265818918[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_52750658265818918[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_52750658265818918[45] = 0;
   out_52750658265818918[46] = 0;
   out_52750658265818918[47] = 0;
   out_52750658265818918[48] = 0;
   out_52750658265818918[49] = 0;
   out_52750658265818918[50] = 0;
   out_52750658265818918[51] = 0;
   out_52750658265818918[52] = 0;
   out_52750658265818918[53] = 0;
   out_52750658265818918[54] = 0;
   out_52750658265818918[55] = 0;
   out_52750658265818918[56] = 0;
   out_52750658265818918[57] = 1;
   out_52750658265818918[58] = 0;
   out_52750658265818918[59] = 0;
   out_52750658265818918[60] = 0;
   out_52750658265818918[61] = 0;
   out_52750658265818918[62] = 0;
   out_52750658265818918[63] = 0;
   out_52750658265818918[64] = 0;
   out_52750658265818918[65] = 0;
   out_52750658265818918[66] = dt;
   out_52750658265818918[67] = 0;
   out_52750658265818918[68] = 0;
   out_52750658265818918[69] = 0;
   out_52750658265818918[70] = 0;
   out_52750658265818918[71] = 0;
   out_52750658265818918[72] = 0;
   out_52750658265818918[73] = 0;
   out_52750658265818918[74] = 0;
   out_52750658265818918[75] = 0;
   out_52750658265818918[76] = 1;
   out_52750658265818918[77] = 0;
   out_52750658265818918[78] = 0;
   out_52750658265818918[79] = 0;
   out_52750658265818918[80] = 0;
   out_52750658265818918[81] = 0;
   out_52750658265818918[82] = 0;
   out_52750658265818918[83] = 0;
   out_52750658265818918[84] = 0;
   out_52750658265818918[85] = dt;
   out_52750658265818918[86] = 0;
   out_52750658265818918[87] = 0;
   out_52750658265818918[88] = 0;
   out_52750658265818918[89] = 0;
   out_52750658265818918[90] = 0;
   out_52750658265818918[91] = 0;
   out_52750658265818918[92] = 0;
   out_52750658265818918[93] = 0;
   out_52750658265818918[94] = 0;
   out_52750658265818918[95] = 1;
   out_52750658265818918[96] = 0;
   out_52750658265818918[97] = 0;
   out_52750658265818918[98] = 0;
   out_52750658265818918[99] = 0;
   out_52750658265818918[100] = 0;
   out_52750658265818918[101] = 0;
   out_52750658265818918[102] = 0;
   out_52750658265818918[103] = 0;
   out_52750658265818918[104] = dt;
   out_52750658265818918[105] = 0;
   out_52750658265818918[106] = 0;
   out_52750658265818918[107] = 0;
   out_52750658265818918[108] = 0;
   out_52750658265818918[109] = 0;
   out_52750658265818918[110] = 0;
   out_52750658265818918[111] = 0;
   out_52750658265818918[112] = 0;
   out_52750658265818918[113] = 0;
   out_52750658265818918[114] = 1;
   out_52750658265818918[115] = 0;
   out_52750658265818918[116] = 0;
   out_52750658265818918[117] = 0;
   out_52750658265818918[118] = 0;
   out_52750658265818918[119] = 0;
   out_52750658265818918[120] = 0;
   out_52750658265818918[121] = 0;
   out_52750658265818918[122] = 0;
   out_52750658265818918[123] = 0;
   out_52750658265818918[124] = 0;
   out_52750658265818918[125] = 0;
   out_52750658265818918[126] = 0;
   out_52750658265818918[127] = 0;
   out_52750658265818918[128] = 0;
   out_52750658265818918[129] = 0;
   out_52750658265818918[130] = 0;
   out_52750658265818918[131] = 0;
   out_52750658265818918[132] = 0;
   out_52750658265818918[133] = 1;
   out_52750658265818918[134] = 0;
   out_52750658265818918[135] = 0;
   out_52750658265818918[136] = 0;
   out_52750658265818918[137] = 0;
   out_52750658265818918[138] = 0;
   out_52750658265818918[139] = 0;
   out_52750658265818918[140] = 0;
   out_52750658265818918[141] = 0;
   out_52750658265818918[142] = 0;
   out_52750658265818918[143] = 0;
   out_52750658265818918[144] = 0;
   out_52750658265818918[145] = 0;
   out_52750658265818918[146] = 0;
   out_52750658265818918[147] = 0;
   out_52750658265818918[148] = 0;
   out_52750658265818918[149] = 0;
   out_52750658265818918[150] = 0;
   out_52750658265818918[151] = 0;
   out_52750658265818918[152] = 1;
   out_52750658265818918[153] = 0;
   out_52750658265818918[154] = 0;
   out_52750658265818918[155] = 0;
   out_52750658265818918[156] = 0;
   out_52750658265818918[157] = 0;
   out_52750658265818918[158] = 0;
   out_52750658265818918[159] = 0;
   out_52750658265818918[160] = 0;
   out_52750658265818918[161] = 0;
   out_52750658265818918[162] = 0;
   out_52750658265818918[163] = 0;
   out_52750658265818918[164] = 0;
   out_52750658265818918[165] = 0;
   out_52750658265818918[166] = 0;
   out_52750658265818918[167] = 0;
   out_52750658265818918[168] = 0;
   out_52750658265818918[169] = 0;
   out_52750658265818918[170] = 0;
   out_52750658265818918[171] = 1;
   out_52750658265818918[172] = 0;
   out_52750658265818918[173] = 0;
   out_52750658265818918[174] = 0;
   out_52750658265818918[175] = 0;
   out_52750658265818918[176] = 0;
   out_52750658265818918[177] = 0;
   out_52750658265818918[178] = 0;
   out_52750658265818918[179] = 0;
   out_52750658265818918[180] = 0;
   out_52750658265818918[181] = 0;
   out_52750658265818918[182] = 0;
   out_52750658265818918[183] = 0;
   out_52750658265818918[184] = 0;
   out_52750658265818918[185] = 0;
   out_52750658265818918[186] = 0;
   out_52750658265818918[187] = 0;
   out_52750658265818918[188] = 0;
   out_52750658265818918[189] = 0;
   out_52750658265818918[190] = 1;
   out_52750658265818918[191] = 0;
   out_52750658265818918[192] = 0;
   out_52750658265818918[193] = 0;
   out_52750658265818918[194] = 0;
   out_52750658265818918[195] = 0;
   out_52750658265818918[196] = 0;
   out_52750658265818918[197] = 0;
   out_52750658265818918[198] = 0;
   out_52750658265818918[199] = 0;
   out_52750658265818918[200] = 0;
   out_52750658265818918[201] = 0;
   out_52750658265818918[202] = 0;
   out_52750658265818918[203] = 0;
   out_52750658265818918[204] = 0;
   out_52750658265818918[205] = 0;
   out_52750658265818918[206] = 0;
   out_52750658265818918[207] = 0;
   out_52750658265818918[208] = 0;
   out_52750658265818918[209] = 1;
   out_52750658265818918[210] = 0;
   out_52750658265818918[211] = 0;
   out_52750658265818918[212] = 0;
   out_52750658265818918[213] = 0;
   out_52750658265818918[214] = 0;
   out_52750658265818918[215] = 0;
   out_52750658265818918[216] = 0;
   out_52750658265818918[217] = 0;
   out_52750658265818918[218] = 0;
   out_52750658265818918[219] = 0;
   out_52750658265818918[220] = 0;
   out_52750658265818918[221] = 0;
   out_52750658265818918[222] = 0;
   out_52750658265818918[223] = 0;
   out_52750658265818918[224] = 0;
   out_52750658265818918[225] = 0;
   out_52750658265818918[226] = 0;
   out_52750658265818918[227] = 0;
   out_52750658265818918[228] = 1;
   out_52750658265818918[229] = 0;
   out_52750658265818918[230] = 0;
   out_52750658265818918[231] = 0;
   out_52750658265818918[232] = 0;
   out_52750658265818918[233] = 0;
   out_52750658265818918[234] = 0;
   out_52750658265818918[235] = 0;
   out_52750658265818918[236] = 0;
   out_52750658265818918[237] = 0;
   out_52750658265818918[238] = 0;
   out_52750658265818918[239] = 0;
   out_52750658265818918[240] = 0;
   out_52750658265818918[241] = 0;
   out_52750658265818918[242] = 0;
   out_52750658265818918[243] = 0;
   out_52750658265818918[244] = 0;
   out_52750658265818918[245] = 0;
   out_52750658265818918[246] = 0;
   out_52750658265818918[247] = 1;
   out_52750658265818918[248] = 0;
   out_52750658265818918[249] = 0;
   out_52750658265818918[250] = 0;
   out_52750658265818918[251] = 0;
   out_52750658265818918[252] = 0;
   out_52750658265818918[253] = 0;
   out_52750658265818918[254] = 0;
   out_52750658265818918[255] = 0;
   out_52750658265818918[256] = 0;
   out_52750658265818918[257] = 0;
   out_52750658265818918[258] = 0;
   out_52750658265818918[259] = 0;
   out_52750658265818918[260] = 0;
   out_52750658265818918[261] = 0;
   out_52750658265818918[262] = 0;
   out_52750658265818918[263] = 0;
   out_52750658265818918[264] = 0;
   out_52750658265818918[265] = 0;
   out_52750658265818918[266] = 1;
   out_52750658265818918[267] = 0;
   out_52750658265818918[268] = 0;
   out_52750658265818918[269] = 0;
   out_52750658265818918[270] = 0;
   out_52750658265818918[271] = 0;
   out_52750658265818918[272] = 0;
   out_52750658265818918[273] = 0;
   out_52750658265818918[274] = 0;
   out_52750658265818918[275] = 0;
   out_52750658265818918[276] = 0;
   out_52750658265818918[277] = 0;
   out_52750658265818918[278] = 0;
   out_52750658265818918[279] = 0;
   out_52750658265818918[280] = 0;
   out_52750658265818918[281] = 0;
   out_52750658265818918[282] = 0;
   out_52750658265818918[283] = 0;
   out_52750658265818918[284] = 0;
   out_52750658265818918[285] = 1;
   out_52750658265818918[286] = 0;
   out_52750658265818918[287] = 0;
   out_52750658265818918[288] = 0;
   out_52750658265818918[289] = 0;
   out_52750658265818918[290] = 0;
   out_52750658265818918[291] = 0;
   out_52750658265818918[292] = 0;
   out_52750658265818918[293] = 0;
   out_52750658265818918[294] = 0;
   out_52750658265818918[295] = 0;
   out_52750658265818918[296] = 0;
   out_52750658265818918[297] = 0;
   out_52750658265818918[298] = 0;
   out_52750658265818918[299] = 0;
   out_52750658265818918[300] = 0;
   out_52750658265818918[301] = 0;
   out_52750658265818918[302] = 0;
   out_52750658265818918[303] = 0;
   out_52750658265818918[304] = 1;
   out_52750658265818918[305] = 0;
   out_52750658265818918[306] = 0;
   out_52750658265818918[307] = 0;
   out_52750658265818918[308] = 0;
   out_52750658265818918[309] = 0;
   out_52750658265818918[310] = 0;
   out_52750658265818918[311] = 0;
   out_52750658265818918[312] = 0;
   out_52750658265818918[313] = 0;
   out_52750658265818918[314] = 0;
   out_52750658265818918[315] = 0;
   out_52750658265818918[316] = 0;
   out_52750658265818918[317] = 0;
   out_52750658265818918[318] = 0;
   out_52750658265818918[319] = 0;
   out_52750658265818918[320] = 0;
   out_52750658265818918[321] = 0;
   out_52750658265818918[322] = 0;
   out_52750658265818918[323] = 1;
}
void h_4(double *state, double *unused, double *out_5958124488714996433) {
   out_5958124488714996433[0] = state[6] + state[9];
   out_5958124488714996433[1] = state[7] + state[10];
   out_5958124488714996433[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2412315107185094233) {
   out_2412315107185094233[0] = 0;
   out_2412315107185094233[1] = 0;
   out_2412315107185094233[2] = 0;
   out_2412315107185094233[3] = 0;
   out_2412315107185094233[4] = 0;
   out_2412315107185094233[5] = 0;
   out_2412315107185094233[6] = 1;
   out_2412315107185094233[7] = 0;
   out_2412315107185094233[8] = 0;
   out_2412315107185094233[9] = 1;
   out_2412315107185094233[10] = 0;
   out_2412315107185094233[11] = 0;
   out_2412315107185094233[12] = 0;
   out_2412315107185094233[13] = 0;
   out_2412315107185094233[14] = 0;
   out_2412315107185094233[15] = 0;
   out_2412315107185094233[16] = 0;
   out_2412315107185094233[17] = 0;
   out_2412315107185094233[18] = 0;
   out_2412315107185094233[19] = 0;
   out_2412315107185094233[20] = 0;
   out_2412315107185094233[21] = 0;
   out_2412315107185094233[22] = 0;
   out_2412315107185094233[23] = 0;
   out_2412315107185094233[24] = 0;
   out_2412315107185094233[25] = 1;
   out_2412315107185094233[26] = 0;
   out_2412315107185094233[27] = 0;
   out_2412315107185094233[28] = 1;
   out_2412315107185094233[29] = 0;
   out_2412315107185094233[30] = 0;
   out_2412315107185094233[31] = 0;
   out_2412315107185094233[32] = 0;
   out_2412315107185094233[33] = 0;
   out_2412315107185094233[34] = 0;
   out_2412315107185094233[35] = 0;
   out_2412315107185094233[36] = 0;
   out_2412315107185094233[37] = 0;
   out_2412315107185094233[38] = 0;
   out_2412315107185094233[39] = 0;
   out_2412315107185094233[40] = 0;
   out_2412315107185094233[41] = 0;
   out_2412315107185094233[42] = 0;
   out_2412315107185094233[43] = 0;
   out_2412315107185094233[44] = 1;
   out_2412315107185094233[45] = 0;
   out_2412315107185094233[46] = 0;
   out_2412315107185094233[47] = 1;
   out_2412315107185094233[48] = 0;
   out_2412315107185094233[49] = 0;
   out_2412315107185094233[50] = 0;
   out_2412315107185094233[51] = 0;
   out_2412315107185094233[52] = 0;
   out_2412315107185094233[53] = 0;
}
void h_10(double *state, double *unused, double *out_1722102185314223216) {
   out_1722102185314223216[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1722102185314223216[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1722102185314223216[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_9091090751848045599) {
   out_9091090751848045599[0] = 0;
   out_9091090751848045599[1] = 9.8100000000000005*cos(state[1]);
   out_9091090751848045599[2] = 0;
   out_9091090751848045599[3] = 0;
   out_9091090751848045599[4] = -state[8];
   out_9091090751848045599[5] = state[7];
   out_9091090751848045599[6] = 0;
   out_9091090751848045599[7] = state[5];
   out_9091090751848045599[8] = -state[4];
   out_9091090751848045599[9] = 0;
   out_9091090751848045599[10] = 0;
   out_9091090751848045599[11] = 0;
   out_9091090751848045599[12] = 1;
   out_9091090751848045599[13] = 0;
   out_9091090751848045599[14] = 0;
   out_9091090751848045599[15] = 1;
   out_9091090751848045599[16] = 0;
   out_9091090751848045599[17] = 0;
   out_9091090751848045599[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_9091090751848045599[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_9091090751848045599[20] = 0;
   out_9091090751848045599[21] = state[8];
   out_9091090751848045599[22] = 0;
   out_9091090751848045599[23] = -state[6];
   out_9091090751848045599[24] = -state[5];
   out_9091090751848045599[25] = 0;
   out_9091090751848045599[26] = state[3];
   out_9091090751848045599[27] = 0;
   out_9091090751848045599[28] = 0;
   out_9091090751848045599[29] = 0;
   out_9091090751848045599[30] = 0;
   out_9091090751848045599[31] = 1;
   out_9091090751848045599[32] = 0;
   out_9091090751848045599[33] = 0;
   out_9091090751848045599[34] = 1;
   out_9091090751848045599[35] = 0;
   out_9091090751848045599[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_9091090751848045599[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_9091090751848045599[38] = 0;
   out_9091090751848045599[39] = -state[7];
   out_9091090751848045599[40] = state[6];
   out_9091090751848045599[41] = 0;
   out_9091090751848045599[42] = state[4];
   out_9091090751848045599[43] = -state[3];
   out_9091090751848045599[44] = 0;
   out_9091090751848045599[45] = 0;
   out_9091090751848045599[46] = 0;
   out_9091090751848045599[47] = 0;
   out_9091090751848045599[48] = 0;
   out_9091090751848045599[49] = 0;
   out_9091090751848045599[50] = 1;
   out_9091090751848045599[51] = 0;
   out_9091090751848045599[52] = 0;
   out_9091090751848045599[53] = 1;
}
void h_13(double *state, double *unused, double *out_6609880627909947861) {
   out_6609880627909947861[0] = state[3];
   out_6609880627909947861[1] = state[4];
   out_6609880627909947861[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5198316101131606696) {
   out_5198316101131606696[0] = 0;
   out_5198316101131606696[1] = 0;
   out_5198316101131606696[2] = 0;
   out_5198316101131606696[3] = 1;
   out_5198316101131606696[4] = 0;
   out_5198316101131606696[5] = 0;
   out_5198316101131606696[6] = 0;
   out_5198316101131606696[7] = 0;
   out_5198316101131606696[8] = 0;
   out_5198316101131606696[9] = 0;
   out_5198316101131606696[10] = 0;
   out_5198316101131606696[11] = 0;
   out_5198316101131606696[12] = 0;
   out_5198316101131606696[13] = 0;
   out_5198316101131606696[14] = 0;
   out_5198316101131606696[15] = 0;
   out_5198316101131606696[16] = 0;
   out_5198316101131606696[17] = 0;
   out_5198316101131606696[18] = 0;
   out_5198316101131606696[19] = 0;
   out_5198316101131606696[20] = 0;
   out_5198316101131606696[21] = 0;
   out_5198316101131606696[22] = 1;
   out_5198316101131606696[23] = 0;
   out_5198316101131606696[24] = 0;
   out_5198316101131606696[25] = 0;
   out_5198316101131606696[26] = 0;
   out_5198316101131606696[27] = 0;
   out_5198316101131606696[28] = 0;
   out_5198316101131606696[29] = 0;
   out_5198316101131606696[30] = 0;
   out_5198316101131606696[31] = 0;
   out_5198316101131606696[32] = 0;
   out_5198316101131606696[33] = 0;
   out_5198316101131606696[34] = 0;
   out_5198316101131606696[35] = 0;
   out_5198316101131606696[36] = 0;
   out_5198316101131606696[37] = 0;
   out_5198316101131606696[38] = 0;
   out_5198316101131606696[39] = 0;
   out_5198316101131606696[40] = 0;
   out_5198316101131606696[41] = 1;
   out_5198316101131606696[42] = 0;
   out_5198316101131606696[43] = 0;
   out_5198316101131606696[44] = 0;
   out_5198316101131606696[45] = 0;
   out_5198316101131606696[46] = 0;
   out_5198316101131606696[47] = 0;
   out_5198316101131606696[48] = 0;
   out_5198316101131606696[49] = 0;
   out_5198316101131606696[50] = 0;
   out_5198316101131606696[51] = 0;
   out_5198316101131606696[52] = 0;
   out_5198316101131606696[53] = 0;
}
void h_14(double *state, double *unused, double *out_925595179133717464) {
   out_925595179133717464[0] = state[6];
   out_925595179133717464[1] = state[7];
   out_925595179133717464[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1550925749154390296) {
   out_1550925749154390296[0] = 0;
   out_1550925749154390296[1] = 0;
   out_1550925749154390296[2] = 0;
   out_1550925749154390296[3] = 0;
   out_1550925749154390296[4] = 0;
   out_1550925749154390296[5] = 0;
   out_1550925749154390296[6] = 1;
   out_1550925749154390296[7] = 0;
   out_1550925749154390296[8] = 0;
   out_1550925749154390296[9] = 0;
   out_1550925749154390296[10] = 0;
   out_1550925749154390296[11] = 0;
   out_1550925749154390296[12] = 0;
   out_1550925749154390296[13] = 0;
   out_1550925749154390296[14] = 0;
   out_1550925749154390296[15] = 0;
   out_1550925749154390296[16] = 0;
   out_1550925749154390296[17] = 0;
   out_1550925749154390296[18] = 0;
   out_1550925749154390296[19] = 0;
   out_1550925749154390296[20] = 0;
   out_1550925749154390296[21] = 0;
   out_1550925749154390296[22] = 0;
   out_1550925749154390296[23] = 0;
   out_1550925749154390296[24] = 0;
   out_1550925749154390296[25] = 1;
   out_1550925749154390296[26] = 0;
   out_1550925749154390296[27] = 0;
   out_1550925749154390296[28] = 0;
   out_1550925749154390296[29] = 0;
   out_1550925749154390296[30] = 0;
   out_1550925749154390296[31] = 0;
   out_1550925749154390296[32] = 0;
   out_1550925749154390296[33] = 0;
   out_1550925749154390296[34] = 0;
   out_1550925749154390296[35] = 0;
   out_1550925749154390296[36] = 0;
   out_1550925749154390296[37] = 0;
   out_1550925749154390296[38] = 0;
   out_1550925749154390296[39] = 0;
   out_1550925749154390296[40] = 0;
   out_1550925749154390296[41] = 0;
   out_1550925749154390296[42] = 0;
   out_1550925749154390296[43] = 0;
   out_1550925749154390296[44] = 1;
   out_1550925749154390296[45] = 0;
   out_1550925749154390296[46] = 0;
   out_1550925749154390296[47] = 0;
   out_1550925749154390296[48] = 0;
   out_1550925749154390296[49] = 0;
   out_1550925749154390296[50] = 0;
   out_1550925749154390296[51] = 0;
   out_1550925749154390296[52] = 0;
   out_1550925749154390296[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5992451308463414616) {
  err_fun(nom_x, delta_x, out_5992451308463414616);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7389899634648651549) {
  inv_err_fun(nom_x, true_x, out_7389899634648651549);
}
void pose_H_mod_fun(double *state, double *out_3435766699566864488) {
  H_mod_fun(state, out_3435766699566864488);
}
void pose_f_fun(double *state, double dt, double *out_8749009569559483773) {
  f_fun(state,  dt, out_8749009569559483773);
}
void pose_F_fun(double *state, double dt, double *out_52750658265818918) {
  F_fun(state,  dt, out_52750658265818918);
}
void pose_h_4(double *state, double *unused, double *out_5958124488714996433) {
  h_4(state, unused, out_5958124488714996433);
}
void pose_H_4(double *state, double *unused, double *out_2412315107185094233) {
  H_4(state, unused, out_2412315107185094233);
}
void pose_h_10(double *state, double *unused, double *out_1722102185314223216) {
  h_10(state, unused, out_1722102185314223216);
}
void pose_H_10(double *state, double *unused, double *out_9091090751848045599) {
  H_10(state, unused, out_9091090751848045599);
}
void pose_h_13(double *state, double *unused, double *out_6609880627909947861) {
  h_13(state, unused, out_6609880627909947861);
}
void pose_H_13(double *state, double *unused, double *out_5198316101131606696) {
  H_13(state, unused, out_5198316101131606696);
}
void pose_h_14(double *state, double *unused, double *out_925595179133717464) {
  h_14(state, unused, out_925595179133717464);
}
void pose_H_14(double *state, double *unused, double *out_1550925749154390296) {
  H_14(state, unused, out_1550925749154390296);
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
