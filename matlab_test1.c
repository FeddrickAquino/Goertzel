#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "goertzel_filter.h"


int main(void) {
  double Fs = 8000;
  int N = 205;
  
  double data[N];

  int freqs[7] = {697, 770, 852, 941, 1209, 1336, 1477};

  double results[7] = {0};
  Complex resultsC[7] = {0};

  for(int i = 0; i < N; i++){
    data[i] = sin(2 * M_PI * 697 * (i * 1.0)/Fs) + sin(2 * M_PI * 1209 * (i * 1.0)/Fs);
    // printf("%lf\n", data[i]);
  }

  for(int i = 0; i< 7; i++){
    resultsC[i] = goertzelfilter(data, (double)N, Fs, freqs[i]);
    results[i] = compabs(resultsC[i]);
  }

  for(int i = 0; i < 7; i++){
    
    printf("Frequency %d result: %lf + I * %lf, abs %lf\n", freqs[i], compreal(resultsC[i]), compimag(resultsC[i]), results[i]);
  }

  return 0;
}