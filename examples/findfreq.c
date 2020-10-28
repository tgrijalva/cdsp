//
//  findfreq.c
//  cdsp
//
//  Copyright (c) 2020 Timothy Grijalva
//
//  Search a time series signal for a target frequency
//


#include <stdio.h>

#include "dsp.h"

const int fs = 1024;                // Sample frequency
const int N = 256;                  // Nuber of Samples in data, x[n]
const int f0 = fs / N;              // base frequency (DFT bin width)
const int maxk = N/2 + 1;           // max value of k without aliasing. (Nyquist)
const double normScale = 2.0 / N;   // DFT normalization scale value

int main(int argc, const char * argv[]) {
    
    // Generate a time series data signal
    // with known frequency content.
    double x[N];            // time series data
    double dt = 1.0 / fs;   // time step size, delta-t
    
    double f1 = 32.0;   // frequency of first sine wave in signal
    double m1 = 1.0;
    double f2 = 76.0;   // frequency of second sine wave in signal
    double m2 = 1.0;
    
    // Populate time series data with sine waves of known frequencies, f1 and f2
    double t;
    for (int i = 0; i < N; i++) {
        t = dt * i;
        x[i] = m1 * sin(2 * M_PI * f1 * t);
        x[i] += m2 * sin(2 * M_PI * f2 * t);
    }
    
    double complex z;
    double binWidth = fs / N;
    double kFreq;
    printf("frequency(Hz), Magnitude, Phase\n");
    for (double k = 0; k <= (N/2)+1; k+=0.5) {
        kFreq = k * binWidth;
        z = goertzel(x, N, k);
        z *= normScale;
        printf("%.2lf, %lf, %lf\n", kFreq, abs(z), 180 * arg(z) / M_PI);
    }
    
    return 0;
}
