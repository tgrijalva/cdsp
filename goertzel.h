//
//  goertzel.h
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

#ifndef goertzel_h
#define goertzel_h

#include "complex_compat.h"

/**
 Computes the k-th Discrete Fourier Transform (DFT) coefficient, X[k],
 of the time series data x[n]
 
 Normalization:
 By default the output value, X[k], is unnormalized,  and should be
 consistent with the output of Matlab/Octave's FFT functions.
 The output can be normalized using the scale factor (N/2).
 EX: normalized X[k] = X[k] / (N/2).
 
 @param x Time series data
 @param N Number of data in \a x
 @param k Index of desired Fourier coefficient. Valid for k=0 to (N/2)+1.
 @return Unnormalized complex Discrete Fourier Transform coefficient X[k]
 */
double_complex goertzel(double *x, int N, int k);

/**
 See \a goertzel definition
 */
float_complex goertzelf(float *x, int N, int k);


/**
 Computes the value of the Discrete Time Fourier Transform (DTFT)
 of the time series data, x[n], at the frequency described by
 k times the bin-width, fs/N.
 
 Normalization:
 By default the output value, X[k], is unnormalized,  and should be
 consistent with the output of Matlab/Octave's FFT functions.
 The output can be normalized using the scale factor (N/2).
 EX: normalized X[k] = X[k] / (N/2).
 
 @param x Time series data
 @param N Number of data in \a x
 @param k Frequency normalized DTFT index. Valid for k=0 to (N/2)+1.
 @return Unnormalized complex Discrete Time Fourier Transform value at k
 */
double_complex goertzelGen(double *x, int N, double k);

/**
 See \a goertzelGen definition
 */
float_complex goertzelGenf(float *x, int N, float k);

/**
 Compute the complex frequency content for a target frequency
 within a time series dataset
 
 See goertzelGen's note on normalization.
 
 @param x Time series data
 @param N Number of data in \a x
 @param fs Sampling frequency of \a x
 @param ft Target frequency
 @return Unnormalized complex Fourier coefficient nearest to target frequency
 */
double_complex goertzelFind(double *x, int N, double fs, double ft);

/**
 See \a goertzelFind definition
 */
float_complex goertzelFindf(float *x, int N, float fs, float ft);

#endif /* goertzel_h */
