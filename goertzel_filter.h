#ifndef GOERTZEL_FIL
#define GOERTZEL_FIL

#include <complex.h>

// #define K 132       // kth bin of interest
// #define N 256       // N dft-points

double complex goertzelfilter(double data[], double N, int k, double fs);

#endif