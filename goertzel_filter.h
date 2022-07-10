#ifndef GOERTZEL_FIL
#define GOERTZEL_FIL


typedef double DATA_TYPE;

typedef struct complx {
    DATA_TYPE real;
    DATA_TYPE imag;
} Complex;


Complex goertzelfilter(double data[], double N, double fs, double freq_target);

Complex goertzelfilterC(double data[], double N, double Nfft, double fs, double freq_target);

DATA_TYPE compreal(Complex c);

DATA_TYPE compimag(Complex c);

DATA_TYPE compabs(Complex c);

#endif