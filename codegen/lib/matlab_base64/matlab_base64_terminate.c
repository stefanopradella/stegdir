/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: matlab_base64_terminate.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "matlab_base64_terminate.h"
#include "matlab_base64_data.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void matlab_base64_terminate(void)
{
  omp_destroy_nest_lock(&matlab_base64_nestLockGlobal);
  isInitialized_matlab_base64 = false;
}

/*
 * File trailer for matlab_base64_terminate.c
 *
 * [EOF]
 */
