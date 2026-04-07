/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: repelem.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "repelem.h"

/* Function Definitions */
/*
 * Arguments    : double varargin_2
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void repelem(double varargin_2, double y_data[], int y_size[2])
{
  int i;
  int k;
  y_size[0] = 1;
  i = (int)varargin_2;
  y_size[1] = (int)varargin_2;
  if ((int)varargin_2 > 0) {
    y_data[0] = 61.0;
    for (k = 2; k <= i; k++) {
      y_data[k - 1] = 61.0;
    }
  }
}

/*
 * File trailer for repelem.c
 *
 * [EOF]
 */
