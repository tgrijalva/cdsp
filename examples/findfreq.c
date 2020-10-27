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
    float x[N];            // time series data
    float dt = 1.0 / fs;   // time step size, delta-t
    
    float f1 = 32.0;   // frequency of first sine wave in signal
    float f2 = 76.0;   // frequency of second sine wave in signal
    
    // Populate time series data with sine waves of known frequencies, f1 and f2
    for (int i = 0; i < N; i++) {
        x[i] = 7 * sin(2 * M_PI * f1 * dt * i);
        x[i] += 2 * cos(2 * M_PI * f2 * dt * i);
    }
    
    // Search time series signal for f1
    float complex z;
    z = goertzelFind(x, N, fs, f1);
    z *= normScale;
    printf("%.1f Hz content in x[n]: Magnitude: %f, Phase: %f degrees\n",
           f1, abs(z), 180 * arg(z) / M_PI);
    
    // Search for f2
    z = goertzelFind(x, N, fs, f2);
    z *= normScale;
    printf("%.1f Hz content in x[n]: Magnitude: %f, Phase: %f degrees\n",
           f2, abs(z), 180 * arg(z) / M_PI);
    
    return 0;
}
