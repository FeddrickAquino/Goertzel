#ifndef GOERTZEL_FIL
#define GOERTZEL_FIL

#include <complex.h>
#include <math.h>

#define K 132       // kth bin of interest
#define N 256       // N dft-points

#define K0 2*cos(2 * M_PI * K / N)

double complex goertzelfilter(double data[], int n){
    if(n <= 0) return 0;

    int i = 0;

    double complex xn, vn = 0, ykn = 0, wkn;
    double complex prev1 = 0, prev2 = 0;

    // First half of the computation
    do{
        xn = data[i] + I * data[i + 1];
        vn = xn + prev1 * K0 - prev2;

        prev2 = prev1;
        prev1 = vn;
        i += 2;
    }while(i < n);
    
    
    prev1 = prev2;
    // -e^(I * (-2 * M_PI * K /N)) = - (cos(2 * M_PI * K / N) - I * sin(2 * M_PI * K/ N))
    wkn = -cos(2 * M_PI * K / N) + I * sin(2 * M_PI * K/ N);

    // Second half
    ykn = vn - (wkn) * prev1;

    return ykn;
}

#endif