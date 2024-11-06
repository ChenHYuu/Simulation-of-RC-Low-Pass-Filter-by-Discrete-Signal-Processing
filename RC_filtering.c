/* Problem 7 RC_filtering */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void apply_rc_filter(int16_t *data, int num_samples, float rc, float tau) {
    float alpha = rc / (rc + tau);
    int16_t y_prev = data[0];

    for (int i = 1; i < num_samples; i++) {
        data[i] = (int16_t)(alpha * y_prev + (1 - alpha) * data[i]);
        y_prev = data[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s in_fn out_fn\n", argv[0]);
        return 1;
    }

    const char *in_fn = argv[1];
    const char *out_fn = argv[2];

    FILE *input = fopen(in_fn, "rb");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    int sample_rate;
    fseek(input, 24, SEEK_SET);
    fread(&sample_rate, sizeof(int), 1, input);
    fseek(input, 44, SEEK_SET);

    FILE *output = fopen(out_fn, "wb");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    // Copy header
    fseek(input, 0, SEEK_SET);
    for (int i = 0; i < 44; i++) fputc(fgetc(input), output);

    // Set RC filter parameter
    float rc = 1.0 / (2 * M_PI * 3000); 
    float tau = 1.0 / sample_rate;

    int16_t sample[2];
    int num_samples = 0;
    while (fread(sample, sizeof(int16_t), 2, input) == 2) {
        apply_rc_filter(&sample[0], 1, rc, tau); // Apply filter to left channel
        apply_rc_filter(&sample[1], 1, rc, tau); // Apply filter to right channel

        fwrite(sample, sizeof(int16_t), 2, output);
        num_samples++;
    }

    fclose(input);
    fclose(output);
    return 0;
}


