# 編譯
CC = gcc
CFLAGS = -Wall -O2 -lm

# 目標檔案
SINE_GEN = sine_wav_gen
RC_FILTER = RC_filtering

# 要得 fs, f, T 的參數
SAMPLING_RATES = 4000 8000 16000
FREQUENCIES = 100 400 3000
DURATION = 0.1

all: $(SINE_GEN) $(RC_FILTER) generate_wavs filter_wavs

# 編譯 sine_wav_gen.c
$(SINE_GEN): sine_wav_gen.c
	$(CC) $(CFLAGS) -o $@ $<

# 編譯 RC_filtering.c
$(RC_FILTER): RC_filtering.c
	$(CC) $(CFLAGS) -o $@ $<

# 產生wav
generate_wavs: $(SINE_GEN)
	@echo Generating input WAV files...
	@for %%S in ($(SAMPLING_RATES)) do ( \
		for %%F in ($(FREQUENCIES)) do ( \
			$(SINE_GEN) %%S %%F $(DURATION) in_fn_%%S_%%F.wav \
		) \
	)

# 濾波所有的wav
filter_wavs: $(RC_FILTER)
	@echo Applying RC filtering...
	@for %%S in ($(SAMPLING_RATES)) do ( \
		for %%F in ($(FREQUENCIES)) do ( \
			$(RC_FILTER) in_fn_%%S_%%F.wav out_fn_%%S_%%F.wav \
		) \
	)

# 清理目標文件
clean:
	@echo Cleaning up...
	del /q $(SINE_GEN) $(RC_FILTER)
	del /q in_fn_*.wav out_fn_*.wav
