import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.fft import fft, fftfreq

def plot_wav_comparison(wav1, wav2, target_frequency):
    # 讀取wav in/out
    sample_rate1, data1 = wavfile.read(wav1)
    sample_rate2, data2 = wavfile.read(wav2)

    # 讀wac in/out 的左右channel
    left_channel1 = data1[:, 0]
    right_channel1 = data1[:, 1]
    left_channel2 = data2[:, 0]
    right_channel2 = data2[:, 1]

    # 計算最大值(正規化用)
    global_max = max(
        np.max(np.abs(left_channel1)),
        np.max(np.abs(right_channel1)),
        np.max(np.abs(left_channel2)),
        np.max(np.abs(right_channel2))
    )

    # 正規畫波形 [-1, 1]
    left_channel1 = left_channel1 / global_max
    right_channel1 = right_channel1 / global_max
    left_channel2 = left_channel2 / global_max
    right_channel2 = right_channel2 / global_max

    # 計算 FFT
    yf_left1 = fft(left_channel1)
    yf_left2 = fft(left_channel2)
    xf1 = fftfreq(len(left_channel1), 1 / sample_rate1)
    xf2 = fftfreq(len(left_channel2), 1 / sample_rate2)

    # 計算目標頻率(100, 400, 3000)的震幅相位
    idx1 = np.argmin(np.abs(xf1 - target_frequency))
    idx2 = np.argmin(np.abs(xf2 - target_frequency))
    amplitude1 = np.abs(yf_left1[idx1])
    amplitude2 = np.abs(yf_left2[idx2])
    phase1 = np.angle(yf_left1[idx1])
    phase2 = np.angle(yf_left2[idx2])

    # 計算 相位差 & delay
    phase_diff = phase2 - phase1
    delay = phase_diff / (2 * np.pi * target_frequency)

    # 資料夾
    output_folder = "output_images"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 畫圖
    plt.figure(figsize=(15, 10))

    # 左聲道 比較in/out
    plt.subplot(2, 1, 1)
    plt.plot(np.linspace(0, len(left_channel1) / sample_rate1, num=len(left_channel1)), left_channel1, color='blue', label=f"{wav1} Left Channel")
    plt.plot(np.linspace(0, len(left_channel2) / sample_rate2, num=len(left_channel2)), left_channel2, color='red', label=f"{wav2} Left Channel")
    plt.title("Left Channel - Time Domain Comparison (Normalized)")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude [-1, 1]")
    plt.legend()

    # 右聲道 比較in/out
    plt.subplot(2, 1, 2)
    plt.plot(np.linspace(0, len(right_channel1) / sample_rate1, num=len(right_channel1)), right_channel1, color='green', label=f"{wav1} Right Channel")
    plt.plot(np.linspace(0, len(right_channel2) / sample_rate2, num=len(right_channel2)), right_channel2, color='orange', label=f"{wav2} Right Channel")
    plt.title("Right Channel - Time Domain Comparison (Normalized)")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude [-1, 1]")
    plt.legend()

    # print出震幅相位
    result_text = (
        f"Frequency: {target_frequency} Hz\n"
        f"Amplitude in: {amplitude1:.4f}\n"
        f"Amplitude out: {amplitude2:.4f}\n"
        f"Amp out/Amp in: {amplitude2/amplitude1:.4f}\n"
        "\n"
        f"Phase in: {phase1:.4f} radians\n"
        f"Phase out: {phase2:.4f} radians\n"
        f"Phase Difference: {phase_diff:.4f} radians\n"
        f"Delay: {delay:.6f} seconds\n"
    )
    plt.figtext(0.5, -0.1, result_text, ha="center", va="top", fontsize=12, color="black", wrap=True)

    # 保存圖片
    output_file = os.path.join(output_folder, "16000_3000.png")
    plt.tight_layout()
    plt.savefig(output_file, bbox_inches="tight")
    print(f"Summary saved as {output_file}")
    plt.show()

if __name__ == "__main__":
    wav1 = "in_fn_16000_3000.wav"  # in
    wav2 = "out_fn_16000_3000.wav"  # out
    target_frequency = 3000  # 目標頻率
    plot_wav_comparison(wav1, wav2, target_frequency)
