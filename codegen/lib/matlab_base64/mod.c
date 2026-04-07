/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mod.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "mod.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double x
 * Return Type  : double
 */
double b_mod(double x)
{
  double r;
  r = fmod(x, 3.0);
  if (r == 0.0) {
    r = 0.0;
  }
  return r;
}

/*
 * Arguments    : double x
 * Return Type  : double
 */
double c_mod(double x)
{
  double r;
  r = fmod(x, 4.0);
  if (r == 0.0) {
    r = 0.0;
  }
  return r;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
