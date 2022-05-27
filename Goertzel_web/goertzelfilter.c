#include "goertzelfilter.h"

#include <math.h>

GoertzelFilter goertzelSetup( double normalizedfreq )
{
  double w = 2 * M_PI * normalizedfreq;
  double wr, wi;

  GoertzelFilter g;

  wr = cos(w);
  wi = sin(w);
  g.coeff = 2 * wr;
  g.cosine = wr;
  g.sine = wi;

  return g;
}

double complex goertzelFilterC(double *samples, int nsamples, GoertzelFilter *g )
{
  double sprev = 0.0;
  double sprev2 = 0.0;
  double s, imag, real;
  int n;

  for (n=0; n<nsamples; n++ ) {
    s = samples[n] + g->coeff * sprev - sprev2;
    sprev2 = sprev;
    sprev = s;
  }

  real = sprev*g->cosine - sprev2;
  imag = -sprev*g->sine;

  return real + I*imag;
}