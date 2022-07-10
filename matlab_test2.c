#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "goertzel_filter.h"

//Generate a noisy cosine with frequency components at 1.24 kHz, 1.26 kHz, and 10 kHz. Specify a sample rate of 32 kHz. Reset the random number generator for reproducible results.

int main(void) {
  double Fs = 32000;
  int N = 94721;
  double nHalf;

  int num_of_interest;
  
  double data[N];
  double freqs_of_interest[(N+1)/2];


  for(int i = 0; i < N; i++){
    data[i] = cos(2 * M_PI * 1240 * i/Fs) + cos(2 * M_PI * 1260 * i/Fs) + cos(2 * M_PI * 10000 * i/Fs);
    // printf("%lf\n", data[i]);
  }

  nHalf = (N + 1.0) / 2.0;
  num_of_interest = 0;
  for(int i = 0; i < (N+1)/2; i++){
    double curr_freq = (Fs/2.0)/nHalf * i;
    if(1200 < curr_freq && curr_freq < 1300){
      freqs_of_interest[num_of_interest] = curr_freq;
      num_of_interest++;
    }
  }

  double results[num_of_interest];
  Complex resultsC[num_of_interest];

  for(int i = 0; i < num_of_interest; i++){
    resultsC[i] = goertzelfilter(data, (double)N, Fs, freqs_of_interest[i]);
    results[i] = compabs(resultsC[i]);
  }

  for(int i = 0; i < num_of_interest; i++){
    
    printf("Frequency %lf6 result: %lf + I * %lf, abs %lf\n", freqs_of_interest[i], compreal(resultsC[i]), compimag(resultsC[i]), results[i]);
  }

  return 0;
}