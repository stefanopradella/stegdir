/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: base64Decode.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "base64Decode.h"
#include "matlab_base64_data.h"
#include "matlab_base64_emxutil.h"
#include "matlab_base64_initialize.h"
#include "matlab_base64_types.h"
#include "mod.h"
#include "repelem.h"
#include "validator_check_size.h"
#include "omp.h"
#include <math.h>
#include <string.h>

/* Variable Definitions */
static unsigned char base64DecodeTable[122];

/* Function Declarations */
static double rt_roundd(double u);

/* Function Definitions */
/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

/*
 * Arguments    : const emxArray_uint8_T *inputData
 *                boolean_T urlmode
 *                emxArray_uint8_T *decodedData
 * Return Type  : void
 */
void base64Decode(const emxArray_uint8_T *inputData, boolean_T urlmode,
                  emxArray_uint8_T *decodedData)
{
  emxArray_uint8_T *b_decodedData;
  emxArray_uint8_T *decodedBytes;
  double tmp_data[4];
  double paddingLength;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int i3;
  int loop_ub;
  int nBlocks;
  unsigned char c_varargin_1;
  unsigned char d_varargin_1;
  unsigned char e_varargin_1;
  unsigned char f_varargin_1;
  unsigned char g_varargin_1;
  unsigned char varargin_2;
  unsigned char *decodedBytes_data;
  unsigned char *decodedData_data;
  if (!isInitialized_matlab_base64) {
    matlab_base64_initialize();
  }
  emxInit_uint8_T(&decodedBytes, 2);
  validator_check_size(inputData, decodedBytes);
  decodedBytes_data = decodedBytes->data;
  /*  Make the variable persistent for efficiency */
  nBlocks = (int)ceil((double)decodedBytes->size[1] / 4.0);
  /*  Handle padding. The value of '=' is expressed as a number to allow */
  /*  code generation */
  if (urlmode) {
    int tmp_size[2];
    int c_loop_ub;
    paddingLength = c_mod(4.0 - c_mod(decodedBytes->size[1]));
    repelem(paddingLength, tmp_data, tmp_size);
    b_loop_ub = decodedBytes->size[1];
    c_loop_ub = tmp_size[1];
    loop_ub = decodedBytes->size[0] * decodedBytes->size[1];
    decodedBytes->size[1] += tmp_size[1];
    emxEnsureCapacity_uint8_T(decodedBytes, loop_ub);
    decodedBytes_data = decodedBytes->data;
    for (i = 0; i < c_loop_ub; i++) {
      decodedBytes_data[b_loop_ub + i] = (unsigned char)rt_roundd(tmp_data[i]);
    }
  } else {
    paddingLength = (decodedBytes_data[decodedBytes->size[1] - 2] == 61) +
                    (decodedBytes_data[decodedBytes->size[1] - 1] == 61);
  }
  loop_ub = decodedBytes->size[0] * decodedBytes->size[1];
  decodedBytes->size[0] = 1;
  emxEnsureCapacity_uint8_T(decodedBytes, loop_ub);
  decodedBytes_data = decodedBytes->data;
  loop_ub = decodedBytes->size[1];
  for (i = 0; i < loop_ub; i++) {
    decodedBytes_data[i] = base64DecodeTable[decodedBytes_data[i] - 1];
  }
  /*  4 rows, N columns */
  /*  Vectorized shift-or */
  emxInit_uint8_T(&b_decodedData, 2);
  loop_ub = b_decodedData->size[0] * b_decodedData->size[1];
  b_decodedData->size[0] = 3;
  b_decodedData->size[1] = nBlocks;
  emxEnsureCapacity_uint8_T(b_decodedData, loop_ub);
  decodedData_data = b_decodedData->data;
  loop_ub = 3 * nBlocks;
  for (i = 0; i < loop_ub; i++) {
    decodedData_data[i] = 0U;
  }
  loop_ub = (nBlocks < 1600);
  if (loop_ub) {
    unsigned char b_varargin_1;
    unsigned char varargin_1;
    for (i1 = 0; i1 < nBlocks; i1++) {
      varargin_1 = decodedBytes_data[4 * i1];
      b_varargin_1 = decodedBytes_data[4 * i1 + 1];
      decodedData_data[3 * i1] =
          (unsigned char)((unsigned char)(varargin_1 << 2) |
                          (unsigned char)(b_varargin_1 >> 4));
    }
    for (i2 = 0; i2 < nBlocks; i2++) {
      varargin_1 = decodedBytes_data[4 * i2 + 1];
      b_varargin_1 = decodedBytes_data[4 * i2 + 2];
      decodedData_data[3 * i2 + 1] =
          (unsigned char)((unsigned char)(varargin_1 << 4) |
                          (unsigned char)(b_varargin_1 >> 2));
    }
    for (i3 = 0; i3 < nBlocks; i3++) {
      varargin_1 = decodedBytes_data[4 * i3 + 2];
      b_varargin_1 = decodedBytes_data[4 * i3 + 3];
      decodedData_data[3 * i3 + 2] =
          (unsigned char)((unsigned char)(varargin_1 << 6) | b_varargin_1);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        c_varargin_1, d_varargin_1)

    for (i1 = 0; i1 < nBlocks; i1++) {
      c_varargin_1 = decodedBytes_data[4 * i1];
      d_varargin_1 = decodedBytes_data[4 * i1 + 1];
      decodedData_data[3 * i1] =
          (unsigned char)((unsigned char)(c_varargin_1 << 2) |
                          (unsigned char)(d_varargin_1 >> 4));
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        e_varargin_1, f_varargin_1)

    for (i2 = 0; i2 < nBlocks; i2++) {
      e_varargin_1 = decodedBytes_data[4 * i2 + 1];
      f_varargin_1 = decodedBytes_data[4 * i2 + 2];
      decodedData_data[3 * i2 + 1] =
          (unsigned char)((unsigned char)(e_varargin_1 << 4) |
                          (unsigned char)(f_varargin_1 >> 2));
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        g_varargin_1, varargin_2)

    for (i3 = 0; i3 < nBlocks; i3++) {
      g_varargin_1 = decodedBytes_data[4 * i3 + 2];
      varargin_2 = decodedBytes_data[4 * i3 + 3];
      decodedData_data[3 * i3 + 2] =
          (unsigned char)((unsigned char)(g_varargin_1 << 6) | varargin_2);
    }
  }
  emxFree_uint8_T(&decodedBytes);
  loop_ub = decodedData->size[0] * decodedData->size[1];
  decodedData->size[0] = 1;
  b_loop_ub = 3 * b_decodedData->size[1];
  decodedData->size[1] = b_loop_ub;
  emxEnsureCapacity_uint8_T(decodedData, loop_ub);
  decodedBytes_data = decodedData->data;
  for (i = 0; i < b_loop_ub; i++) {
    decodedBytes_data[i] = decodedData_data[i];
  }
  emxFree_uint8_T(&b_decodedData);
  /*  Remove padding */
  paddingLength = (double)b_loop_ub - paddingLength;
  loop_ub = decodedData->size[0] * decodedData->size[1];
  if (paddingLength < 1.0) {
    decodedData->size[1] = 0;
  } else {
    decodedData->size[1] = (int)paddingLength;
  }
  emxEnsureCapacity_uint8_T(decodedData, loop_ub);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void base64Decode_init(void)
{
  int i;
  memset(&base64DecodeTable[0], 0, 122U * sizeof(unsigned char));
  /*  Standard Base64 */
  for (i = 0; i < 26; i++) {
    base64DecodeTable[i + 64] = (unsigned char)i;
    base64DecodeTable[i + 96] = (unsigned char)((unsigned int)i + 26U);
  }
  for (i = 0; i < 10; i++) {
    base64DecodeTable[i + 47] = (unsigned char)((unsigned int)i + 52U);
  }
  base64DecodeTable[42] = 62U;
  base64DecodeTable[46] = 63U;
  /* Base64URL characters */
  base64DecodeTable[44] = 62U;
  base64DecodeTable[94] = 63U;
}

/*
 * File trailer for base64Decode.c
 *
 * [EOF]
 */
