//
//  dsp.h
//  cdsp
//
//  Created by Timothy Grijalva on 8/1/20.
//  Copyright © 2020 Timothy Grijalva. All rights reserved.
//

#ifndef dsp_h
#define dsp_h

#include <complex.h>

// Fourier
double complex goertzel(double *x, int N, int k);
float complex goertzelf(float *x, int N, int k);
double complex goertzelFind(double *x, int N, double fs, double ft);
float complex goertzelFindf(float *x, int N, float fs, float ft);

#endif /* dsp_h */
