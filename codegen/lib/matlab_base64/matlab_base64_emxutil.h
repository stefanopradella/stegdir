/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: matlab_base64_emxutil.h
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

#ifndef MATLAB_BASE64_EMXUTIL_H
#define MATLAB_BASE64_EMXUTIL_H

/* Include Files */
#include "matlab_base64_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int oldNumel);

extern void emxFree_char_T(emxArray_char_T **pEmxArray);

extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);

extern void emxInit_char_T(emxArray_char_T **pEmxArray, int numDimensions);

extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for matlab_base64_emxutil.h
 *
 * [EOF]
 */
