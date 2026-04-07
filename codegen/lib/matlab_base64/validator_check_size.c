/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: validator_check_size.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "validator_check_size.h"
#include "matlab_base64_emxutil.h"
#include "matlab_base64_types.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_uint8_T *in
 *                emxArray_uint8_T *out
 * Return Type  : void
 */
void validator_check_size(const emxArray_uint8_T *in, emxArray_uint8_T *out)
{
  int i1;
  int inVectorLength;
  const unsigned char *in_data;
  unsigned char *out_data;
  in_data = in->data;
  inVectorLength = 1;
  if (in->size[0] != 1) {
    inVectorLength = in->size[0];
  }
  if (in->size[0] == 0) {
    int i;
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_uint8_T(out, i);
    out_data = out->data;
    for (i1 = 0; i1 < inVectorLength; i1++) {
      out_data[i1] = in_data[i1];
    }
  } else {
    int i;
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_uint8_T(out, i);
    out_data = out->data;
    for (i1 = 0; i1 < inVectorLength; i1++) {
      out_data[i1] = in_data[i1];
    }
  }
}

/*
 * File trailer for validator_check_size.c
 *
 * [EOF]
 */
