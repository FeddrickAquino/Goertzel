#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "goertzel_filter.h"

//Generate a noisy cosine with frequency components at 1.24 kHz, 1.26 kHz, and 10 kHz. Specify a sample rate of 32 kHz. Reset the random number generator for reproducible results.


// For the cos apart

int main(void) {
    double fs = 3200;
    int N = 32000;

    double step;

    double data1[N], data2[N], freq1, freq2;

    double freq_interest1[100], freq_interest2[100];

    Complex resultsC[500];
    int f_counts;

    freq1 = 124;
    for(int i = 0; i < N; i++){
        data1[i] = cos(2 * M_PI * freq1 * i / fs);
    }

    f_counts = 0;
    step = fs/N;
    for(int i = 0; i < N; i++){
        double curr_freq = step * i;
        if(curr_freq < 123 || curr_freq > 127){
            continue;
        }
        freq_interest1[f_counts] = curr_freq;
        resultsC[f_counts] = goertzelfilter(data1, N, fs, curr_freq);;
        f_counts++;
    }

    for(int i = 0; i < f_counts; i++){
        printf("Frequency %lf result: %lf + I * %lf, abs %lf\n", freq_interest1[i], compreal(resultsC[i]), compimag(resultsC[i]), compabs(resultsC[i]));
    }   
    
    return 0;
}