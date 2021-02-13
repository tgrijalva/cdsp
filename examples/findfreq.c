//
//  findfreq.c
//  cdsp
//
//  Copyright (c) 2020 Timothy Grijalva
//
//  Search a time series signal for a target frequency
//

#include <stdio.h>
#include <string.h>

#include "dsp.h"

const int fs = 1000;                // Sample frequency
const int N = 100;                  // Nuber of Samples in data, x[n]
const int f0 = fs / N;              // base frequency (DFT bin width)
const int maxk = N/2 + 1;           // max value of k without aliasing. (Nyquist)
const double normScale = 2.0 / N;   // DFT normalization scale value

int main(int argc, const char * argv[]) {
    
    // Generate a time series data signal
    // with known frequency content.
    const int numFreqs = 2;
    double freqs[numFreqs] = { 33.33, 200 };    // frequencis in signal
    double mags[numFreqs] = { 2.0, 1.0 };       // magnitudes of freqs
    
    // Populate time series data with sine waves of known frequencies
    static double x[N];           // time series data
    const double dt = 1.0 / fs;   // time step size, delta-t
    for (int sampleIndex = 0; sampleIndex < N; sampleIndex++) {
        x[sampleIndex] = 0;
        double t = dt * sampleIndex;
        for (int i = 0; i < numFreqs; i++) {
            x[sampleIndex] += mags[i] * sin(2 * M_PI * freqs[i] * t);
        }
    }
    
    // Search for a frequency
    double complex z;
    double ft = freqs[0]; // target frequency
    z = goertzelFind(x, N, fs, ft) * normScale;
    
    // Print results
    printf("frequency(Hz), Magnitude, Phase\n");
    printf("%.2lf, %lf, %lf\n", ft, abs(z), 180 * arg(z) / M_PI);
    
    // [Debug] Print out DFT coefficients
//    double kFreq;
//    const double kStep = 1.0; // 0.0 < k <= 1.0
//    for (double k = 0; k <= (N/2)+1; k+=kStep) {
//        kFreq = k * f0;
//        z = goertzel(x, N, k);
//        z *= normScale;
//        printf("%.2lf, %lf, %lf\n", kFreq, abs(z), 180 * arg(z) / M_PI);
//    }
    
    return 0;
}
