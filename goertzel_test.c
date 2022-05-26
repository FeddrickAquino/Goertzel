#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "goertzel_filter.h"


int main(void) {
  int Fs = 8000;
  int N = 205;
  
  double data[N];

  int freqs[7] = {697, 770, 852, 941, 1209, 1336, 1477};

  int ks[7];

  double results[7] = {0};
  double complex resultsC[7] = {0};

  for(int i = 0; i < N; i++){
    data[i] = sin(2 * M_PI * 697 * (i * 1.0)/Fs) + sin(2 * M_PI * 1209 * (i * 1.0)/Fs);
    // printf("%lf\n", data[i]);
  }

  for(int i = 0; i < 7; i++){
    ks[i] = round(freqs[i] * (N * 1.0)/Fs) + 1;
    // printf("%d\n", ks[i]);
  }

  for(int i = 0; i< 7; i++){
    resultsC[i] = goertzelfilter(data, N, ks[i], Fs);
    results[i] = cabs(resultsC[i]);
  }

  for(int i = 0; i < 7; i++){
    
    printf("Frequency %d result: %lf + I * %lf, abs %lf\n", freqs[i], creal(resultsC[i]), cimag(resultsC[i]), results[i]);
  }

  return 0;
}