/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: base64Encode.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "base64Encode.h"
#include "matlab_base64_data.h"
#include "matlab_base64_emxutil.h"
#include "matlab_base64_initialize.h"
#include "matlab_base64_types.h"
#include "mod.h"
#include "validator_check_size.h"
#include "omp.h"
#include <math.h>
#include <string.h>

/* Variable Definitions */
static boolean_T base64AlphabetTable_not_empty;

static boolean_T lastURLmode_not_empty;

/* Function Definitions */
/*
 * Arguments    : const emxArray_uint8_T *inputData
 *                boolean_T urlmode
 *                emxArray_char_T *encodedData
 * Return Type  : void
 */
void base64Encode(const emxArray_uint8_T *inputData, boolean_T urlmode,
                  emxArray_char_T *encodedData)
{
  static const char cv[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                              'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                              'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  static const char cv1[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  static const char cv2[10] = {'0', '1', '2', '3', '4',
                               '5', '6', '7', '8', '9'};
  static char base64AlphabetTable[64];
  static boolean_T lastURLmode;
  emxArray_uint8_T *b_inputData;
  emxArray_uint8_T *inputBytes;
  emxArray_uint8_T *r;
  double paddingLength;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int loop_ub;
  int nBlocks;
  unsigned char b_varargin_1;
  unsigned char d_varargin_1;
  unsigned char e_varargin_1;
  unsigned char f_varargin_1;
  unsigned char g_varargin_1;
  unsigned char h_varargin_1;
  char *encodedData_data;
  unsigned char *inputBytes_data;
  unsigned char *r1;
  if (!isInitialized_matlab_base64) {
    matlab_base64_initialize();
  }
  emxInit_uint8_T(&b_inputData, 2);
  validator_check_size(inputData, b_inputData);
  inputBytes_data = b_inputData->data;
  /*  Make the variable persistent for efficiency. */
  /*  At each function call check urlmode and eventually change the table */
  /*  calling the function. The condition check is odd because persistent  */
  /*  variables must be populated before using them in the cindition of an */
  /*  if statemens. */
  if (!lastURLmode_not_empty) {
    lastURLmode = urlmode;
    lastURLmode_not_empty = true;
  }
  if (!base64AlphabetTable_not_empty) {
    memset(&base64AlphabetTable[0], 0, 64U * sizeof(char));
    /*  Standard Base64 */
    for (i = 0; i < 26; i++) {
      base64AlphabetTable[i] = cv[i];
      base64AlphabetTable[i + 26] = cv1[i];
    }
    for (i = 0; i < 10; i++) {
      base64AlphabetTable[i + 52] = cv2[i];
    }
    if (urlmode) {
      /* Base64URL characters */
      base64AlphabetTable[62] = '-';
      base64AlphabetTable[63] = '_';
    } else {
      base64AlphabetTable[62] = '+';
      base64AlphabetTable[63] = '/';
    }
    base64AlphabetTable_not_empty = true;
  }
  if (urlmode != lastURLmode) {
    memset(&base64AlphabetTable[0], 0, 64U * sizeof(char));
    /*  Standard Base64 */
    for (i = 0; i < 26; i++) {
      base64AlphabetTable[i] = cv[i];
      base64AlphabetTable[i + 26] = cv1[i];
    }
    for (i = 0; i < 10; i++) {
      base64AlphabetTable[i + 52] = cv2[i];
    }
    if (urlmode) {
      /* Base64URL characters */
      base64AlphabetTable[62] = '-';
      base64AlphabetTable[63] = '_';
    } else {
      base64AlphabetTable[62] = '+';
      base64AlphabetTable[63] = '/';
    }
    lastURLmode = urlmode;
  }
  paddingLength = b_mod(3.0 - b_mod(b_inputData->size[1]));
  nBlocks = (int)ceil((double)b_inputData->size[1] / 3.0);
  emxInit_uint8_T(&r, 1);
  loop_ub = r->size[0];
  r->size[0] = b_inputData->size[1] + (int)paddingLength;
  emxEnsureCapacity_uint8_T(r, loop_ub);
  r1 = r->data;
  loop_ub = b_inputData->size[1];
  for (i = 0; i < loop_ub; i++) {
    r1[i] = inputBytes_data[i];
  }
  loop_ub = (int)paddingLength;
  for (i = 0; i < loop_ub; i++) {
    r1[i + b_inputData->size[1]] = 0U;
  }
  emxFree_uint8_T(&b_inputData);
  emxInit_uint8_T(&inputBytes, 2);
  loop_ub = inputBytes->size[0] * inputBytes->size[1];
  inputBytes->size[0] = 4;
  inputBytes->size[1] = nBlocks;
  emxEnsureCapacity_uint8_T(inputBytes, loop_ub);
  inputBytes_data = inputBytes->data;
  b_loop_ub = nBlocks << 2;
  for (i = 0; i < b_loop_ub; i++) {
    inputBytes_data[i] = 0U;
  }
  loop_ub = (nBlocks < 1600);
  if (loop_ub) {
    unsigned char c_varargin_1;
    unsigned char varargin_1;
    for (i1 = 0; i1 < nBlocks; i1++) {
      varargin_1 = r1[3 * i1];
      inputBytes_data[4 * i1] = (unsigned char)(varargin_1 >> 2);
    }
    for (i2 = 0; i2 < nBlocks; i2++) {
      varargin_1 = r1[3 * i2];
      c_varargin_1 = r1[3 * i2 + 1];
      inputBytes_data[4 * i2 + 1] =
          (unsigned char)((unsigned char)((unsigned char)(varargin_1 & 3)
                                          << 4) |
                          (unsigned char)(c_varargin_1 >> 4));
    }
    for (i3 = 0; i3 < nBlocks; i3++) {
      varargin_1 = r1[3 * i3 + 1];
      c_varargin_1 = r1[3 * i3 + 2];
      inputBytes_data[4 * i3 + 2] =
          (unsigned char)((unsigned char)((unsigned char)(varargin_1 & 15)
                                          << 2) |
                          (unsigned char)(c_varargin_1 >> 6));
    }
    for (i4 = 0; i4 < nBlocks; i4++) {
      varargin_1 = r1[3 * i4 + 2];
      inputBytes_data[4 * i4 + 3] = (unsigned char)(varargin_1 & 63);
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        b_varargin_1)

    for (i1 = 0; i1 < nBlocks; i1++) {
      b_varargin_1 = r1[3 * i1];
      inputBytes_data[4 * i1] = (unsigned char)(b_varargin_1 >> 2);
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        d_varargin_1, e_varargin_1)

    for (i2 = 0; i2 < nBlocks; i2++) {
      d_varargin_1 = r1[3 * i2];
      e_varargin_1 = r1[3 * i2 + 1];
      inputBytes_data[4 * i2 + 1] =
          (unsigned char)((unsigned char)((unsigned char)(d_varargin_1 & 3)
                                          << 4) |
                          (unsigned char)(e_varargin_1 >> 4));
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        f_varargin_1, g_varargin_1)

    for (i3 = 0; i3 < nBlocks; i3++) {
      f_varargin_1 = r1[3 * i3 + 1];
      g_varargin_1 = r1[3 * i3 + 2];
      inputBytes_data[4 * i3 + 2] =
          (unsigned char)((unsigned char)((unsigned char)(f_varargin_1 & 15)
                                          << 2) |
                          (unsigned char)(g_varargin_1 >> 6));
    }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        h_varargin_1)

    for (i4 = 0; i4 < nBlocks; i4++) {
      h_varargin_1 = r1[3 * i4 + 2];
      inputBytes_data[4 * i4 + 3] = (unsigned char)(h_varargin_1 & 63);
    }
  }
  emxFree_uint8_T(&r);
  loop_ub = encodedData->size[0] * encodedData->size[1];
  encodedData->size[0] = 1;
  encodedData->size[1] = b_loop_ub;
  emxEnsureCapacity_char_T(encodedData, loop_ub);
  encodedData_data = encodedData->data;
  for (i = 0; i < b_loop_ub; i++) {
    encodedData_data[i] =
        base64AlphabetTable[(unsigned char)(inputBytes_data[i] + 1) - 1];
  }
  emxFree_uint8_T(&inputBytes);
  if (paddingLength > 0.0) {
    if (urlmode) {
      paddingLength = (double)b_loop_ub - paddingLength;
      loop_ub = encodedData->size[0] * encodedData->size[1];
      if (paddingLength < 1.0) {
        encodedData->size[1] = 0;
      } else {
        encodedData->size[1] = (int)paddingLength;
      }
      emxEnsureCapacity_char_T(encodedData, loop_ub);
    } else {
      paddingLength = ((double)b_loop_ub - paddingLength) + 1.0;
      if (paddingLength > b_loop_ub) {
        nBlocks = 0;
        b_loop_ub = 0;
      } else {
        nBlocks = (int)paddingLength - 1;
      }
      loop_ub = b_loop_ub - nBlocks;
      for (i = 0; i < loop_ub; i++) {
        encodedData_data[nBlocks + i] = '=';
      }
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void base64Encode_init(void)
{
  lastURLmode_not_empty = false;
  base64AlphabetTable_not_empty = false;
}

/*
 * File trailer for base64Encode.c
 *
 * [EOF]
 */
