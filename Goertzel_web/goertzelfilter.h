/* goertzelfilter.h
*/

#ifndef GOERTZELFILTER_H_
#define GOERTZELFILTER_H_

#include <complex.h>

typedef struct goertzelfilterstruct {
  double coeff ;
  double sine ;
  double cosine ;
} GoertzelFilter;

GoertzelFilter goertzelSetup( double normalizedfreq );

double complex goertzelFilterC( double *sample, int nsamples, GoertzelFilter *g );

#endif