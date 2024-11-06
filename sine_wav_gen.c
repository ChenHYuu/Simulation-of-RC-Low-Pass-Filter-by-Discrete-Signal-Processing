/* Problem 7 sine_wav_gen */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define TWO_PI 6.28318530717958647692

void write_wav_header(FILE *file, int sample_rate, int num_samples) {
    int num_channels = 2;
    int byte_rate = sample_rate * num_channels * sizeof(int16_t);
    int block_align = num_channels * sizeof(int16_t);
    int data_size = num_samples * num_channels * sizeof(int16_t);

    fwrite("RIFF", 1, 4, file);
    int32_t chunk_size = 36 + data_size;
    fwrite(&chunk_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);
    fwrite("fmt ", 1, 4, file);

    int32_t subchunk1_size = 16;
    int16_t audio_format = 1;
    int16_t num_channels_s = num_channels;
    int32_t sample_rate_s = sample_rate;
    fwrite(&subchunk1_size, 4, 1, file);
    fwrite(&audio_format, 2, 1, file);
    fwrite(&num_channels_s, 2, 1, file);
    fwrite(&sample_rate_s, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    fwrite(&block_align, 2, 1, file);
    fwrite(&(int16_t){16}, 2, 1, file);

    fwrite("data", 1, 4, file);
    fwrite(&data_size, 4, 1, file);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s fs f L out_fn\n", argv[0]);
        return 1;
    }

    int sample_rate = atoi(argv[1]);
    double frequency = atof(argv[2]);
    double duration = atof(argv[3]);
    const char *out_fn = argv[4];

    int num_samples = (int)(duration * sample_rate);

    FILE *file = fopen(out_fn, "wb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    write_wav_header(file, sample_rate, num_samples);

    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / sample_rate;
        int16_t sample_left = (int16_t)(32767 * sin(TWO_PI * frequency * t));
        int16_t sample_right = (int16_t)(32767 * cos(TWO_PI * frequency * t));
        fwrite(&sample_left, sizeof(int16_t), 1, file);
        fwrite(&sample_right, sizeof(int16_t), 1, file);
    }

    fclose(file);
    return 0;
}
