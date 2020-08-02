//
//  goertzel.c
//  cdsp
//
//  Created by Timothy Grijalva on 8/1/20.
//  Copyright © 2020 Timothy Grijalva. All rights reserved.
//

#include "dsp.h"

#include <complex.h>
#include <math.h>

#undef I
#define J _Complex_I

// From the Goertzel definition:
// Y[N] = sum( x[n] * e^(-j*2*pi*k*n/N) ) from n = 0 to N
// the forulat is broken down into an intermediat IIR filter
// from n=0 to N-1, and then a final step is calculated
// where n=N. For details see:
// https://en.wikipedia.org/wiki/Goertzel_algorithm
// The implemataion is normalized to compute Fourier Transform Coefficients W[k],
// without regard for the sampling frequency, fs.
double complex goertzel(double *x, int N, int k) {
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
    // using modified formula for y[N]
    // y[N] = e^(j*2*pi*k/N) * s[N-1] - s[N-2]
    // y[N] = [cos(w) + j*sin(w)] * s[N-1] - s[N-2]
    // y[N] = Real{ cos(w) * s[N-1] - s[N-2] } + Imag{ sin(w) * s[N-1] }
    return (cosW * s1 - s2) + (sinW * s1) * J;
}

// Same as goertzel() but with floats
float complex goertzelf(float *x, int N, int k) {
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
    
    return (cosW * s1 - s2) + (sinW * s1) * J;
}

double complex goertzelFind(double *x, int N, double fs, double ft) {
    // Target frequenct cannot be above Nyquest frequency
    if (ft > (fs / 2)) {
        return 0;
    }
    
    // Calculate k (DFT bin) for given target frequency
    int k = 0.5 + N * ft / fs;
    
    return goertzel(x, N, k);
}

float complex goertzelFindf(float *x, int N, float fs, float ft) {
    // Target frequenct cannot be above Nyquest frequency
    if (ft > (fs / 2)) {
        return 0;
    }
    
    // Calculate k (DFT bin) for given target frequency
    int k = 0.5 + N * ft / fs;
    
    return goertzelf(x, N, k);
}
