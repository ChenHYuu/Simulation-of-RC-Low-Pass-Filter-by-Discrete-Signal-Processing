/* Problem 7 sine_wav_gen */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

void write_wav_header(FILE *file, int sample_rate, int num_samples) {
    int byte_rate = sample_rate * 2 * 2; // 2 channels, 2 bytes per sample
    int block_align = 2 * 2;
    int data_chunk_size = num_samples * 2 * 2;
    int file_size = 36 + data_chunk_size;

    // RIFF header
    fwrite("RIFF", 1, 4, file);
    fwrite(&file_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);

    // fmt subchunk
    fwrite("fmt ", 1, 4, file);
    int subchunk1_size = 16;
    short audio_format = 1;
    short num_channels = 2;
    fwrite(&subchunk1_size, 4, 1, file);
    fwrite(&audio_format, 2, 1, file);
    fwrite(&num_channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    fwrite(&block_align, 2, 1, file);
    short bits_per_sample = 16;
    fwrite(&bits_per_sample, 2, 1, file);

    // data subchunk
    fwrite("data", 1, 4, file);
    fwrite(&data_chunk_size, 4, 1, file);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <sampling_rate> <frequency> <duration> <output_file>\n", argv[0]);
        return 1;
    }

    int sample_rate = atoi(argv[1]);
    double frequency = atof(argv[2]);
    double duration = atof(argv[3]);
    const char *output_file = argv[4];

    int num_samples = (int)(sample_rate * duration);
    FILE *file = fopen(output_file, "wb");
    if (!file) {
        perror("Unable to open file for writing");
        return 1;
    }

    write_wav_header(file, sample_rate, num_samples);

    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / sample_rate;
        short left_sample = (short)(32767 * sin(2 * PI * frequency * t));   // Sine wave for left channel
        short right_sample = (short)(32767 * cos(2 * PI * frequency * t));  // Cosine wave for right channel

        fwrite(&left_sample, sizeof(short), 1, file);
        fwrite(&right_sample, sizeof(short), 1, file);
    }

    fclose(file);
    printf("WAV file '%s' generated successfully.\n", output_file);
    return 0;
}

