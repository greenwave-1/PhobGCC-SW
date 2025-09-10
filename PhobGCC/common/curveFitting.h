/*
  curveFitting.h - Library for fitting curves to given
  points using Least Squares method, with Cramer's rule
  used to solve the linear equation. Max polynomial order 20.
  Created by Rowan Easter-Robinson, August 23, 2018.
  Released into the public domain.
*/

#ifndef curveFit_h
#define curveFit_h

#define MAX_ORDER 20

#ifndef CURVE_FIT_DEBUG
#define CURVE_FIT_DEBUG 0
#endif

#include <stdint.h>

/* Enum for error messages */
enum curveFitERROR{
	ORDER_AND_NCOEFFS_DO_NOT_MATCH = -1,
	ORDER_INCORRECT = -2,
	NPOINTS_INCORRECT = -3
};

void cpyArray(double *src, double*dest, int n);

void subCol(double *mat, double* sub, uint8_t coln, uint8_t n);

/*Determinant algorithm taken from https://codeforwin.org/2015/08/c-program-to-find-determinant-of-matrix.html */
int trianglize(double **m, int n);

double det(double *in, int n, uint8_t /*prnt*/);
/*End of Determinant algorithm*/

//Raise x to power
double curveFitPower(double base, int exponent);

int fitCurve (int order, int nPoints, double py[], int nCoeffs, double *coeffs);

int fitCurve (int order, int nPoints, double px[], double py[], int nCoeffs, double *coeffs);

#endif
