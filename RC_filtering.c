#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define PI 3.141592653589793

typedef struct {
    char riff[4];
    int overall_size;
    char wave[4];
    char fmt_chunk_marker[4];
    int length_of_fmt;
    short format_type;
    short channels;
    int sample_rate;
    int byterate;
    short block_align;
    short bits_per_sample;
    char data_chunk_header[4];
    int data_size;
} WAVHeader;

void read_wav_header(FILE *file, WAVHeader *header) {
    fread(header, sizeof(WAVHeader), 1, file);
}

void write_wav_header(FILE *file, WAVHeader *header) {
    fwrite(header, sizeof(WAVHeader), 1, file);
}

short apply_rc_filter(short input, double *prev_output, double alpha, double beta) {
    double output = alpha * (*prev_output) + beta * input;
    *prev_output = output;
    return (short)output;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    FILE *in_fp = fopen(input_file, "rb");
    if (!in_fp) {
        perror("Unable to open input file");
        return 1;
    }

    FILE *out_fp = fopen(output_file, "wb");
    if (!out_fp) {
        perror("Unable to open output file");
        fclose(in_fp);
        return 1;
    }

    WAVHeader header;
    read_wav_header(in_fp, &header);
    write_wav_header(out_fp, &header);

    int sample_rate = header.sample_rate;
    double RC = 1.0 / (2 * PI * 400); // 假設 RC 的值
    double dt = 1.0 / sample_rate;
    double alpha = RC / (RC + dt);      // 計算 alpha = RC / (RC + τ)
    double beta = dt / (RC + dt);       // 計算 beta = τ / (τ + RC)

    short buffer[BUFFER_SIZE];
    double prev_output_left = 0;
    double prev_output_right = 0;

    size_t samples_read;
    while ((samples_read = fread(buffer, sizeof(short), BUFFER_SIZE, in_fp)) > 0) {
        for (size_t i = 0; i < samples_read; i += 2) {
            buffer[i] = apply_rc_filter(buffer[i], &prev_output_left, alpha, beta);   // 左聲道濾波
            if (header.channels > 1) { // 若為立體聲，處理右聲道
                buffer[i + 1] = apply_rc_filter(buffer[i + 1], &prev_output_right, alpha, beta); // 右聲道濾波
            }
        }
        fwrite(buffer, sizeof(short), samples_read, out_fp);
    }

    fclose(in_fp);
    fclose(out_fp);
    printf("Filtered WAV file '%s' generated successfully.\n", output_file);
    return 0;
}
