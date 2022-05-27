
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "goertzel_filter.h"

#define K0(K, N) 2*cos(2 * M_PI * K / N)

/*
 * Arguments
 * data -> Sampled values from the signal
 * N-> number of element in the array data[]
 * k -> the bin corresponding to the coefficient we are looking for
 * fs -> Sample frequency
 */

//k = Freq_of_interest / (Fs/N_sample)

double complex goertzelfilter(double data[], double N, int k, double fs){
    if(N <= 0) return 0;

    int i = 0;

    double complex xn, vn = 0 + I * 0, ykn = 0 + I * 0, wkn;
    double complex prev1 = 0 + I * 0, prev2 = 0 + I * 0;

    // First half of the computation
    do{
        xn = data[i];
        vn = xn + prev1 * K0(k, N) - prev2;

        prev2 = prev1;
        prev1 = vn;
        i++;
    }while(i < N);
    
    
    prev1 = prev2;
    // -e^(I * (-2 * M_PI * K /N)) = - (cos(2 * M_PI * K / N) - I * sin(2 * M_PI * K/ N))
    wkn = cos(2 * M_PI * (k  * 1.0)/ N) - I * sin(2 * M_PI * (k  * 1.0)/ N);

    // Second half
    ykn = (vn - wkn * prev1) * (cos(2 * M_PI * k) - I * sin(2 * M_PI * k));

    return ykn;
}