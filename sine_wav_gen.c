/* Problem 7 sine_wav_gen */

#include <stdio.h>
#include <math.h>
#include <memory.h>
#define PI 3.14159265359

/* This program generates a PCM file of 1 second 440Hz pure sin wave*/
int main(void)
{
    double fs = 16000;// sampling frequency 16kHz
    double T = 1/fs;// sampling period 1/16k
    double L = 1.0;// length of sin wave in an unit of second
    double f = 440;// frequency of sin wave (Hz)
    double A = 10000;// amplitude of sin wave
    short *x;// array of the sin wave (2 byte for each sample)
    double tmp;// temp variable
    size_t N = (size_t)(L * fs);// length of sin wave (sample)
    size_t n;// sample index
    FILE *fp;// a file pointet to save waveform
    char fn[1024] = {"sin440Hz.pcm"};
    x = (short *) malloc(sizeof(short) * N);
    for( n = 0; n < N; n ++ ) {
        tmp = A * sin(2 * PI * f * n * T); // generate sin wave for each sample
        x[n] = (short)floor(tmp + 0.5);// quantization
    }
    fp = fopen(fn, "wb");// open a file pointer to save a binary file
    if( !fp ) {// chech if the file is opened sucessfully
        fprintf(stderr, "Cannot save %s\n", fn);
        exit(1);// stop and exit this program if error
    }
    fwrite( x, sizeof(short), N, fp);// write the waveform to the file
    fclose(fp);
    return 0;
}