/* Problem 7 sine_wav_gen */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

void write_wav_header(FILE *file, int sample_rate, int num_samples) {
    int byte_rate = sample_rate * 2 * 2;        // 計算每秒的byte數（取樣率 * 聲道數 * 每樣本位元數 / 8）
    int block_align = 2 * 2;                    // 計算每一樣本的byte數（聲道數 * 每樣本位元數 / 8）
    int data_chunk_size = num_samples * 2 * 2;  // 計算音訊資料的byte大小（樣本數 * 聲道數 * 每樣本位元數 / 8）
    int file_size = 36 + data_chunk_size;       // 計算 RIFF 檔案大小（固定值 36 + 音訊資料區塊大小）

    fwrite("RIFF", 1, 4, file);                 // "RIFF"
    fwrite(&file_size, 4, 1, file);             // Chunk size = 36 + 音訊資料大小
    fwrite("WAVE", 1, 4, file);                 // "WAVE"

    fwrite("fmt ", 1, 4, file);                 // "fmt "
    int subchunk1_size = 16;                    // PCM = 16
    short audio_format = 1;                     // PCM = 1
    short num_channels = 2;                     // 雙聲道
    fwrite(&subchunk1_size, 4, 1, file);        // Subchunk1 size = 16
    fwrite(&audio_format, 2, 1, file);          // Audio format = 1
    fwrite(&num_channels, 2, 1, file);          // Number of channels = 2
    fwrite(&sample_rate, 4, 1, file);           // Sample rate
    fwrite(&byte_rate, 4, 1, file);             // Byte rate, 每秒 byte 數
    fwrite(&block_align, 2, 1, file);           // Block align, 每一樣本的 byte 數
    short bits_per_sample = 16;                 // 16 bits, 每個樣本位元數
    fwrite(&bits_per_sample, 2, 1, file);       // Bits per sample

    fwrite("data", 1, 4, file);                 // "data"
    fwrite(&data_chunk_size, 4, 1, file);       // 音訊資料大小
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <sampling_rate> <frequency> <duration> <output_file.wav>\n", argv[0]);
        return 1;
    }

    int sample_rate = atoi(argv[1]);
    double frequency = atoi(argv[2]);
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
        short left_sample = (short)(32767 * sin(2 * PI * frequency * t));   
        short right_sample = (short)(32767 * cos(2 * PI * frequency * t));  
        
     // fwrite(要寫入的資料, {多少}byte, 幾個, 寫入檔案)
        fwrite(&left_sample, sizeof(short), 1, file);
        fwrite(&right_sample, sizeof(short), 1, file);
    }

    fclose(file);
    printf("WAV file '%s' generated successfully.\n", output_file);
    return 0;
}

