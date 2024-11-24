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

short apply_rc_filter(short input, double *prev_output, int sample_rate) {
    double RC = 1.0 / (2 * PI * 400);
    double tau = 1.0 / sample_rate;
    double output = RC / (RC + tau) * (*prev_output) + tau / (RC + tau) * input;
    *prev_output = output;
    return (short)output;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file.wav> <output_file.wav>\n", argv[0]);
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
    int total_samples = header.data_size / (header.bits_per_sample / 8); // 計算總樣本數

    short *buffer = malloc(header.data_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error.\n");
        fclose(in_fp);
        fclose(out_fp);
        return 1;
    }

    if (fread(buffer, header.data_size, 1, in_fp) != 1) {
        fprintf(stderr, "Error reading WAV data.\n");
        free(buffer);
        fclose(in_fp);
        fclose(out_fp);
        return 1;
    }

    double prev_output_left = 0;    // 用來保存左聲道的前一個輸出 y[n-1]
    double prev_output_right = 0;   // 用來保存右聲道的前一個輸出 y[n-1]

    for (int i = 0; i < total_samples; i += 2) {
        buffer[i] = apply_rc_filter(buffer[i], &prev_output_left, sample_rate);    // 左聲道處理
        buffer[i + 1] = apply_rc_filter(buffer[i + 1], &prev_output_right, sample_rate); // 右聲道處理
    }

    fwrite(buffer, header.data_size, 1, out_fp);

    free(buffer);
    fclose(in_fp);
    fclose(out_fp);
    printf("Filtered WAV file '%s' generated successfully.\n", output_file);
    return 0;
}
