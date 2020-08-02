//
//  dsp.h
//  cdsp
//
//  Copyright (c) 2020 Timothy Grijalva
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#ifndef dsp_h
#define dsp_h

#include <complex.h>

// Fourier
/**
 Computes the the k-th Fourier coefficient, X[k],
 for the time series data x[n]
 
 By default the output value, X[k], is unnormalized.
 This is done for consistancy with Matlab/Octave's FFT functions.
 The output can be normalized using the scale factor \a (N/2).
 EX: normalizedX[k] = X[k] / (N/2).

 @param x Time series data with length 2^n
 @param N Number of data in \a x
 @param k Index of desired Fourier coefficient
 @return Unnormalized complex Fourier coefficient X[k]
 */
double complex goertzel(double *x, int N, int k);

/**
 See \a goertzel definition
 */
float complex goertzelf(float *x, int N, int k);

/**
 Compute the complex frequency content for a target frequency
 within a time series dataset
 
 By default the output value, X[k], is unnormalized.
 This is done for consistancy with Matlab/Octave's FFT functions.
 The output can be normalized using the scale factor \a (N/2).
 EX: normalizedX[k] = X[k] / (N/2).
 
 @param x Time series data with length 2^n
 @param N Number of data in \a x
 @param fs Sampling frequency of \a x
 @param ft Target frequency
 @return Unnormalized complex Fourier coefficient nearest to target frequency
 */
double complex goertzelFind(double *x, int N, double fs, double ft);

/**
 See \a goertzelFind definition
 */
float complex goertzelFindf(float *x, int N, float fs, float ft);

#endif /* dsp_h */
