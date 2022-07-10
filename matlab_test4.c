#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "goertzel_filter.h"

//Generate a noisy cosine with frequency components at 1.24 kHz, 1.26 kHz, and 10 kHz. Specify a sample rate of 32 kHz. Reset the random number generator for reproducible results.

int main(void) {

//     fs = 50;
// t = 0:1/fs:10-1/fs;
// N = length(t);
// xn = chirp(t,15,t(end),20)+randn(1,N)/100;

// f0 = 17.36;
// k = N*f0/fs;

// ykn = filter([1 -exp(-2j*pi*k/N)],[1 -2*cos(2*pi*k/N) 1],[xn 0]);
    double Fs = 50;
    int N = 10 * Fs;
    double data[500] = {1.000000, -0.309616, -0.807534, 0.812334, 0.299421, -0.999876, 0.330491, 0.790502, -0.832038, -0.260136, 0.998019, -0.380501, -0.752479, 0.866864, 0.189607, -0.989984, 0.457633, 0.689305, -0.911313, -0.086772, 0.968458, -0.557858, -0.595399, 0.956723, -0.048458, -0.923578, 0.674106, 0.464895, -0.990938, 0.213656, 0.843720, -0.795107, -0.293408, 0.998359, -0.401938, -0.717052, 0.904451, 0.080499, -0.960836, 0.599942, 0.534125, -0.980400, 0.167307, 0.859875, -0.786242, -0.291602, 0.997148, -0.433397, -0.680590, 0.931115, -0.003148, -0.928332, 0.688849, 0.417444, -0.998794, 0.327519, 0.753308, -0.892573, -0.081126, 0.953364, -0.640910, -0.466009, 0.995662, -0.295214, -0.768825, 0.886242, 0.084891, -0.951445, 0.653389, 0.442453, -0.998395, 0.339389, 0.731378, -0.915160, -0.008184, 0.921146, -0.723602, -0.344123, 0.998174, -0.455953, -0.631194, 0.964416, -0.148657, -0.843382, 0.834127, 0.162960, -0.966870, 0.629728, 0.448653, -0.999214, 0.377588, 0.685648, -0.947292, 0.104320, 0.859554, -0.824631, -0.166065, 0.964082, -0.648610, -0.414009, 0.999921, -0.437931, -0.625316, 0.973136, -0.210579, -0.791273, 0.893423, 0.017627, -0.908176, 0.772436, 0.233904, -0.976504, 0.622364, 0.428853, -0.999904, 0.454832, 0.596410, -0.984170, 0.280140, 0.733521, -0.936298, 0.106824, 0.839641, -0.863708, -0.058517, 0.916172, -0.773634, -0.211195, 0.965899, -0.672710, -0.348257, 0.992474, -0.566709, -0.468236, 0.999987, -0.460430, -0.570851, 0.992627, -0.357682, -0.656719, 0.974425, -0.261352, -0.727070, 0.949092, -0.173510, -0.783511, 0.919916, -0.095550, -0.827823, 0.889717, -0.028327, -0.861798, 0.860838, 0.027698, -0.887116, 0.835167, 0.072338, -0.905255, 0.814166, 0.105572, -0.917429, 0.798909, 0.127457, -0.924541, 0.790116, 0.138065, -0.927158, 0.788183, 0.137441, -0.925497, 0.793194, 0.125583, -0.919422, 0.804927, 0.102441, -0.908439, 0.822846, 0.067942, -0.891720, 0.846078, 0.022033, -0.868116, 0.873379, -0.035249, -0.836205, 0.903104, -0.103694, -0.794342, 0.933166, -0.182803, -0.740753, 0.961011, -0.271668, -0.673641, 0.983607, -0.368827, -0.591345, 0.997470, -0.472125, -0.492530, 0.998732, -0.578580, -0.376422, 0.983264, -0.684272, -0.243076, 0.946888, -0.784293, -0.093670, 0.885658, -0.872765, 0.069198, 0.796251, -0.942974, 0.241243, 0.676428, -0.987639, 0.416300, 0.525582, -0.999356, 0.586256, 0.345305, -0.971219, 0.741176, 0.139935, -0.897626, 0.869675, -0.083009, -0.775227, 0.959606, -0.312607, -0.603964, 0.999084, -0.534657, -0.388057, 0.977841, -0.732236, -0.136817, 0.888853, -0.886825, 0.134946, 0.730088, -0.980026, 0.407120, 0.506166, -0.995836, 0.655293, 0.229617, -0.923337, 0.852722, -0.078616, -0.759485, 0.973281, -0.389797, -0.511586, 0.995242, -0.669442, -0.198871, 0.905523, -0.880936, 0.147412, 0.703760, -0.990596, 0.485941, 0.405394, -0.973713, 0.769630, 0.042798, -0.820694, 0.952217, -0.336427, -0.542084, 0.996549, -0.674571, -0.171030, 0.883309, -0.912347, 0.238187, 0.618414, -0.999998, 0.616433, 0.236964, -0.909227, 0.890864, -0.198254, -0.643323, 0.999683, -0.604967, -0.242465, 0.907912, -0.896234, 0.218573, 0.620391, -0.999913, 0.641876, 0.187752, -0.878842, 0.926448, -0.298220, -0.546310, 0.993586, -0.721426, -0.071082, 0.811600, -0.968771, 0.432262, 0.412289, -0.962391, 0.828529, -0.108076, -0.687936, 0.998568, -0.607470, -0.208733, 0.878241, -0.935188, 0.342349, 0.487041, -0.979012, 0.795870, -0.066058, -0.708219, 0.997689, -0.606970, -0.195785, 0.864974, -0.948894, 0.393273, 0.426007, -0.958894, 0.850412, -0.175370, -0.615441, 0.997559, -0.720117, -0.031474, 0.761529, -0.991844, 0.573949, 0.217344, -0.866550, 0.953743, -0.424868, -0.377005, 0.935855, -0.894833, 0.282556, 0.508879, -0.976368, 0.825343, -0.153636, -0.613951, 0.995425, -0.753722, 0.042169, 0.694759, -0.999980, 0.686564, 0.049716, -0.754549, 0.996118, -0.628749, -0.121210, 0.796631, -0.988795, 0.583703, 0.172270, -0.823918, 0.981740, -0.553671, -0.203188, 0.838613, -0.977444, 0.539967, 0.214271, -0.842026, 0.977177, -0.543142, -0.205653, 0.834474, -0.981015, 0.563072, 0.177229, -0.815261, 0.987836, -0.598934, -0.128705, 0.782728, -0.995304, 0.649089, 0.059774, -0.734376, 0.999845, -0.710881, 0.029586, 0.667101, -0.996653, 0.780371, -0.138688, -0.577552, 0.979775, -0.852064, 0.265603, 0.462664, -0.942343, 0.918677, -0.406545, -0.320371, 0.877034, -0.971069, 0.555243, 0.150524, -0.776816, 0.998431, -0.702417, 0.044056, 0.636065, -0.988889, 0.835513, -0.256487, -0.452026, 0.930655, -0.938925, 0.474898, 0.226553, -0.813801, 0.994931, -0.681973, 0.032103, 0.632658, -0.985587, 0.855343, -0.307819, -0.388637, 0.895674, -0.969237, 0.576009, 0.093043, -0.716613, 0.997732, -0.804553, 0.230843, 0.450903, -0.919669, 0.956906, -0.547364, -0.116209, 0.724905, -0.997774, 0.810863, -0.252225, -0.420874, 0.901203, -0.971667, 0.602457, 0.037766, -0.660036, 0.985905, -0.871533, 0.369997, 0.294612, -0.828176, 0.996755, -0.728365, 0.142428, 0.504537, -0.931802, 0.955987, -0.568782, -0.061659, 0.664752, -0.983946, 0.885366, -0.412862, -0.232680, 0.779583, -0.999822, 0.803430, -0.274090, -0.367656, 0.856969, -0.993937, 0.724471, -0.160475, -0.467679, 0.905790, -0.978495, 0.658616, -0.076105, -0.535720, 0.934068, -0.962732, 0.612459, -0.022663, -0.574979, 0.947896, -0.952792, 0.589821, -0.000630, -0.587785};
    double f = 17.36;

    double results;
    Complex resultsC;

    resultsC = goertzelfilter(data, (double)N, Fs, f);
    results = compabs(resultsC);

    
    printf("Frequency %lf result: %lf + I * %lf, abs %lf\n", f, compreal(resultsC), compimag(resultsC), results);

    return 0;
}