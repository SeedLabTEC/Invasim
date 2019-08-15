#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    //asm volatile("ecall");
    unsigned MAXSIZE;
    unsigned MAXWAVES;
    unsigned i, j;
    float *RealIn;
    float *ImagIn;
    float *RealOut;
    float *ImagOut;
    float *coeff;
    float *amp;
    int invfft = 0;

    // if (argc<3)
    // {
    // 	printf("Usage: fft <waves> <length> -i\n");
    // 	printf("-i performs an inverse fft\n");
    // 	printf("make <waves> random sinusoids");
    // 	printf("<length> is the number of samples\n");
    // 	exit(-1);
    // }
    // else if (argc==4)
    // 	invfft = !strncmp(argv[3],"-i",2);
    MAXSIZE  = 16;
    MAXWAVES = 4;

    srand(1);
    RealIn  = (float *)malloc(sizeof(float) * MAXSIZE);
    ImagIn  = (float *)malloc(sizeof(float) * MAXSIZE);
    RealOut = (float *)malloc(sizeof(float) * MAXSIZE);
    ImagOut = (float *)malloc(sizeof(float) * MAXSIZE);
    coeff   = (float *)malloc(sizeof(float) * MAXWAVES);
    amp     = (float *)malloc(sizeof(float) * MAXWAVES);

    /* Makes MAXWAVES waves of random amplitude and period */
    for (i = 0; i < MAXWAVES; i++) {
        coeff[i] = rand() % 1000;
        amp[i]   = rand() % 1000;
    }

    for (i = 0; i < MAXSIZE; i++) {
        /*   RealIn[i]=rand();*/
        RealIn[i] = 0;
        for (j = 0; j < MAXWAVES; j++) {
            /* randomly select sin or cos */
            if (rand() % 2) {
                RealIn[i] += coeff[j] * cos(amp[j] * i);
            } else {
                RealIn[i] += coeff[j] * sin(amp[j] * i);
            }
            ImagIn[i] = 0;
        }
    }

    /* regular*/
    fft_float(MAXSIZE, invfft, RealIn, ImagIn, RealOut, ImagOut);

    printf("RealOut:\n");
    for (i = 0; i < MAXSIZE; i++)
        printf("%f \n", RealOut[i]);

    printf("ImagOut:\n");
    for (i = 0; i < MAXSIZE; i++)
        printf("%f \n", ImagOut[i]);

    free(RealIn);
    free(ImagIn);
    free(RealOut);
    free(ImagOut);
    free(coeff);
    free(amp);
    exit(0);
}
