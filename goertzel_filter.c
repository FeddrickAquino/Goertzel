#include "goertzel_filter.h"

#include <math.h>
#include <stdio.h>


static Complex compadd(Complex a, Complex b){
    return (Complex){a.real + b.real, a.imag + b.imag};
}

static Complex compsub(Complex a, Complex b){
    return (Complex){a.real - b.real, a.imag - b.imag};
}

static Complex compmult(Complex a, Complex b){
    return (Complex) {(a.real * b.real) - (a.imag * b.imag), 
                    (a.real * b.imag) + (b.real * a.imag)};
}

DATA_TYPE compreal(Complex c){
    return c.real;
}

DATA_TYPE compimag(Complex c){
    return c.imag;
}

DATA_TYPE compabs(Complex c){
    return sqrt(pow(c.real, 2) + pow(c.imag, 2));
}

Complex goertzelfilterC(double data[], double N, double Nfft, double fs, double freq_target){ 
    double kDouble, k, omega, sine, cosine, coeff, realN;

    realN = N/2;
    Complex q0, q1, q2, result, neg_wKn, matlabFactor;

    kDouble = (((realN) * freq_target) / fs);
    k = (int) (kDouble + 0.5);

    omega = (2.0 * M_PI * k)/(realN);
    sine = sin(omega);
    cosine = cos(omega);
    coeff = 2.0 * cosine;

    q0 = q1 = q2 = (Complex) {0, 0};

    for(int i = 0; i < (int) realN; i++){

        // q0 = q1 * coeff - q2 + data
        Complex q1_coeff = compmult(q1, (Complex) {coeff, 0});
        Complex curr_data = (Complex) {data[i*2], data[(i*2) + 1]};
        q0 = compadd(curr_data, compsub(q1_coeff, q2));

        q2 = q1;
        q1 = q0;

    }

    // result = q1 * -wKn
    neg_wKn = (Complex) {-cosine, sine};
    result = compmult(neg_wKn, q1);

    // result = result + (q1 * coeff)
    result = compadd(result, compmult(q1, (Complex){coeff, 0}));

    // result = result - q2
    result = compsub(result, q2);

    // result = result * exp(-2 * pi * k)
    matlabFactor = (Complex) {cos(2 * M_PI * k), -sin(2 * M_PI * k)};

    result = compmult(result, matlabFactor);

    return result;
}

Complex goertzelfilter(double data[], double N, double fs, double freq_target)
{
    double dataC[(int)N * 2];
    for(int i = 0; i < N; i++){
        dataC[i*2] = data[i];
        dataC[(i*2) + 1] = 0;
    }

    return goertzelfilterC(dataC, N*2, 255, fs, freq_target);

    // int     i;
    // double  k, omega,sine,cosine,coeff,q0,q1,q2,magnitude;
    // double real,imag, res_real,res_imag;
    // double  yFactorReal, yFactorImag;
    // double kDouble;

    
    // kDouble =  ((N * freq_target) / fs);
    // k = (int)(kDouble + 0.5);

    // omega = (2.0 * M_PI * kDouble)/N;
    // sine = sin(omega);
    // cosine = cos(omega);
    // coeff = 2.0 * cosine;
    // q0=0;
    // q1=0;
    // q2=0;


    // // printf("cosine %lf sine %lf coeff %lf\n", cosine, sine, coeff);

    // for(i=0; i<N; i++)
    // {
    //     // q0 = coeff * q1 - q2 + data[i];
        
    //     // Matlab version
    //     q0 = coeff * q1 - q2 + data[i];
    //     q2 = q1;
    //     q1 = q0;
    // }

    // //printf("prev1 %lf prev2 %lf\n", q1, q2);
    // real = (q1 * coeff - q2) + (q1 * -cosine);
    // imag = (q1 * sine);

    // //printf("Result before factor = real %lf imag %lf\n", real, imag);

    // yFactorReal = cos(2.0 * M_PI * kDouble);
    // yFactorImag = -sin(2.0 * M_PI * kDouble);

    // // From matlab diagram
    // res_real = (yFactorReal * real) - (yFactorImag * imag);
    // res_imag = (imag * yFactorReal) + (real * yFactorImag);
    // double complex result = res_real + I * res_imag;
    // return result;
}

