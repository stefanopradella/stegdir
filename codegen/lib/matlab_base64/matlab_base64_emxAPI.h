/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: matlab_base64_emxAPI.h
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

#ifndef MATLAB_BASE64_EMXAPI_H
#define MATLAB_BASE64_EMXAPI_H

/* Include Files */
#include "matlab_base64_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern emxArray_char_T *emxCreateND_char_T(int numDimensions, const int *size);

extern emxArray_uint8_T *emxCreateND_uint8_T(int numDimensions,
                                             const int *size);

extern emxArray_char_T *emxCreateWrapperND_char_T(char *data, int numDimensions,
                                                  const int *size);

extern emxArray_uint8_T *emxCreateWrapperND_uint8_T(unsigned char *data,
                                                    int numDimensions,
                                                    const int *size);

extern emxArray_char_T *emxCreateWrapper_char_T(char *data, int rows, int cols);

extern emxArray_uint8_T *emxCreateWrapper_uint8_T(unsigned char *data, int rows,
                                                  int cols);

extern emxArray_char_T *emxCreate_char_T(int rows, int cols);

extern emxArray_uint8_T *emxCreate_uint8_T(int rows, int cols);

extern void emxDestroyArray_char_T(emxArray_char_T *emxArray);

extern void emxDestroyArray_uint8_T(emxArray_uint8_T *emxArray);

extern void emxInitArray_char_T(emxArray_char_T **pEmxArray, int numDimensions);

extern void emxInitArray_uint8_T(emxArray_uint8_T **pEmxArray,
                                 int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for matlab_base64_emxAPI.h
 *
 * [EOF]
 */
