/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: matlab_base64_emxAPI.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 07-Apr-2026 21:59:24
 */

/* Include Files */
#include "matlab_base64_emxAPI.h"
#include "matlab_base64_emxutil.h"
#include "matlab_base64_types.h"
#include <stdlib.h>

/* Function Definitions */
/*
 * Arguments    : int numDimensions
 *                const int *size
 * Return Type  : emxArray_char_T *
 */
emxArray_char_T *emxCreateND_char_T(int numDimensions, const int *size)
{
  emxArray_char_T *emx;
  int i;
  int numEl;
  emxInit_char_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = (char *)malloc((unsigned int)numEl * sizeof(char));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                const int *size
 * Return Type  : emxArray_uint8_T *
 */
emxArray_uint8_T *emxCreateND_uint8_T(int numDimensions, const int *size)
{
  emxArray_uint8_T *emx;
  int i;
  int numEl;
  emxInit_uint8_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data =
      (unsigned char *)malloc((unsigned int)numEl * sizeof(unsigned char));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : char *data
 *                int numDimensions
 *                const int *size
 * Return Type  : emxArray_char_T *
 */
emxArray_char_T *emxCreateWrapperND_char_T(char *data, int numDimensions,
                                           const int *size)
{
  emxArray_char_T *emx;
  int i;
  int numEl;
  emxInit_char_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : unsigned char *data
 *                int numDimensions
 *                const int *size
 * Return Type  : emxArray_uint8_T *
 */
emxArray_uint8_T *emxCreateWrapperND_uint8_T(unsigned char *data,
                                             int numDimensions, const int *size)
{
  emxArray_uint8_T *emx;
  int i;
  int numEl;
  emxInit_uint8_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : char *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_char_T *
 */
emxArray_char_T *emxCreateWrapper_char_T(char *data, int rows, int cols)
{
  emxArray_char_T *emx;
  emxInit_char_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : unsigned char *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_uint8_T *
 */
emxArray_uint8_T *emxCreateWrapper_uint8_T(unsigned char *data, int rows,
                                           int cols)
{
  emxArray_uint8_T *emx;
  emxInit_uint8_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_char_T *
 */
emxArray_char_T *emxCreate_char_T(int rows, int cols)
{
  emxArray_char_T *emx;
  emxInit_char_T(&emx, 2);
  emx->size[0] = rows;
  rows *= cols;
  emx->size[1] = cols;
  emx->data = (char *)malloc((unsigned int)rows * sizeof(char));
  emx->numDimensions = 2;
  emx->allocatedSize = rows;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_uint8_T *
 */
emxArray_uint8_T *emxCreate_uint8_T(int rows, int cols)
{
  emxArray_uint8_T *emx;
  emxInit_uint8_T(&emx, 2);
  emx->size[0] = rows;
  rows *= cols;
  emx->size[1] = cols;
  emx->data =
      (unsigned char *)malloc((unsigned int)rows * sizeof(unsigned char));
  emx->numDimensions = 2;
  emx->allocatedSize = rows;
  return emx;
}

/*
 * Arguments    : emxArray_char_T *emxArray
 * Return Type  : void
 */
void emxDestroyArray_char_T(emxArray_char_T *emxArray)
{
  emxFree_char_T(&emxArray);
}

/*
 * Arguments    : emxArray_uint8_T *emxArray
 * Return Type  : void
 */
void emxDestroyArray_uint8_T(emxArray_uint8_T *emxArray)
{
  emxFree_uint8_T(&emxArray);
}

/*
 * Arguments    : emxArray_char_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_char_T(emxArray_char_T **pEmxArray, int numDimensions)
{
  emxInit_char_T(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_uint8_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions)
{
  emxInit_uint8_T(pEmxArray, numDimensions);
}

/*
 * File trailer for matlab_base64_emxAPI.c
 *
 * [EOF]
 */
