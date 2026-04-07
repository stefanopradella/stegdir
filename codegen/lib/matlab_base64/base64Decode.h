/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: base64Decode.h
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

#ifndef BASE64DECODE_H
#define BASE64DECODE_H

/* Include Files */
#include "matlab_base64_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void base64Decode(const emxArray_uint8_T *inputData, boolean_T urlmode,
                         emxArray_uint8_T *decodedData);

void base64Decode_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for base64Decode.h
 *
 * [EOF]
 */
