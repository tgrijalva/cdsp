//
//  goertzel.c
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

// NOTE: This file can be compiled as C or C++.
#include "dsp.h"

// From the Goertzel Filter definition:
// y[n] = e^(j*w0*n) * sum( x[k] * e^(-j*w0*k) ) from k=0 to n.
// When computing DFT coefficients, we apply several restrictions.
// (1) The filter runs up to n=N, where N is the number of terms in DFT input.
// (2) The frequencies chosen for analysis are restricted to
// w0 = 2*pi*k/N, where k belongs to {0,1,2,...,N-1}.
// Using the above restrictions and observing that
// e^(j*2*pi*k) = 1, yields the following expression:
// y[N] = sum( x[n] * e^(-j*2*pi*k*n/N) ) from n=0 to N.
// The formula is broken down into an intermediate IIR filter
// from n=0 to N-1, and an additional step where n=N.
// For details see: https://en.wikipedia.org/wiki/Goertzel_algorithm
// The implemataion is normalized to compute Fourier Transform Coefficients X[k],
// without regard for the sampling frequency, fs.
double_complex goertzel(double *x, int N, int k) {
    double w;                       // Omega(k) = w0 * k, where w0 = 2*PI*fs/N (DFT bin width)
    double sinW, cosW, twoCosW;     // Complex Exponentials Variables
    double s0, s1, s2;              // IIR State Variables
    
    // Compute Coefficients
    w = (2.0 * M_PI * k) / N;
    sinW = sin(w);
    cosW = cos(w);
    twoCosW = 2.0 * cosW;
    
    // Initialize State Variables
    s0 = 0.0;
    s1 = 0.0;
    s2 = 0.0;
    
    // IIR Filter for intermediate states (from n=0 to N-1)
    // s[n] = x[n] + (2*cos(w) * s[n-1]) - s[n-2]
    for (int n = 0; n < N; n++) {
        s0 = x[n] + (twoCosW * s1) - s2;
        s2 = s1;
        s1 = s0;
    }
    
    // Compute final step where n = N
    // s[N] = 2 * cos(w) * s[N-1] - s[N-2]
    // y[N] = s[N] - e^(-j*2*pi*k/N) * s[N-1]
    // Combine algebraically to yeild:
    // y[N] = e^(j*2*pi*k/N) * s[N-1] - s[N-2]
    // y[N] = [cos(w) + j*sin(w)] * s[N-1] - s[N-2]
    // y[N] = Real{ cos(w) * s[N-1] - s[N-2] } + Imag{ sin(w) * s[N-1] }
    return double_complex(cosW * s1 - s2, sinW * s1);
}

// Same as goertzel() but with floats
float_complex goertzelf(float *x, int N, int k) {
    float w;
    float sinW, cosW, twoCosW;
    float s0, s1, s2;
    
    w = (2.0 * M_PI * k) / N;
    sinW = sinf(w);
    cosW = cosf(w);
    twoCosW = 2.0 * cosW;
    
    s0 = 0.0;
    s1 = 0.0;
    s2 = 0.0;
    
    for (int n = 0; n < N; n++) {
        s0 = x[n] + (twoCosW * s1) - s2;
        s2 = s1;
        s1 = s0;
    }
    
    return float_complex(cosW * s1 - s2, sinW * s1);
}

double_complex goertzelFind(double *x, int N, double fs, double ft) {
    // Target frequenct cannot be above Nyquest frequency
    if (ft > (fs / 2)) {
        return 0;
    }
    
    // Calculate k (DFT bin) for given target frequency
    int k = 0.5 + N * ft / fs;
    
    return goertzel(x, N, k);
}

float_complex goertzelFindf(float *x, int N, float fs, float ft) {
    // Target frequenct cannot be above Nyquest frequency
    if (ft > (fs / 2)) {
        return 0;
    }
    
    // Calculate k (DFT bin) for given target frequency
    int k = 0.5 + N * ft / fs;
    
    return goertzelf(x, N, k);
}
