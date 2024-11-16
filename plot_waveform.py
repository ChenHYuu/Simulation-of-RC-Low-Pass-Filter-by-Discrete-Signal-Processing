import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.fft import fft, fftfreq

def plot_wav_comparison(wav1, wav2, target_frequency):
    # 讀取兩個 WAV 檔案
    sample_rate1, data1 = wavfile.read(wav1)
    sample_rate2, data2 = wavfile.read(wav2)

    left_channel1 = data1[:, 0]
    right_channel1 = data1[:, 1]

    left_channel2 = data2[:, 0]
    right_channel2 = data2[:, 1]
    
    # 創建資料夾保存圖片
    output_folder = "output_images"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    
    # 計算振幅和相位
    yf_left1 = fft(left_channel1)
    yf_left2 = fft(left_channel2)
    xf1 = fftfreq(len(left_channel1), 1 / sample_rate1)
    xf2 = fftfreq(len(left_channel2), 1 / sample_rate2)

    amplitude_left1 = np.abs(yf_left1[:len(yf_left1) // 2])
    amplitude_left2 = np.abs(yf_left2[:len(yf_left2) // 2])
    phase_left1 = np.angle(yf_left1[:len(yf_left1) // 2])
    phase_left2 = np.angle(yf_left2[:len(yf_left2) // 2])

    yf_right1 = fft(right_channel1)
    amplitude_right1 = np.abs(yf_right1[:len(yf_right1) // 2])
    # phase_right1 = np.angle(yf_right1[:len(yf_right1) // 2])

    yf_right2 = fft(right_channel2)
    amplitude_right2 = np.abs(yf_right2[:len(yf_right2) // 2])
    # phase_right2 = np.angle(yf_right2[:len(yf_right2) // 2])

    # 時間軸資料
    time1 = np.linspace(0, len(left_channel1) / sample_rate1, num=len(left_channel1))
    time2 = np.linspace(0, len(left_channel2) / sample_rate2, num=len(left_channel2))

    idx1 = np.argmin(np.abs(xf1 - target_frequency))
    idx2 = np.argmin(np.abs(xf2 - target_frequency))

    # 提取目標頻率的相位值
    phase1 = phase_left1[idx1]
    phase2 = phase_left2[idx2]

    # 計算相位差和延遲
    phase_diff = phase2 - phase1
    delay = phase_diff / (2 * np.pi * target_frequency)

    # 顯示結果
    # print(f"Frequency: {target_frequency} Hz")
    # print(f"Phase 1: {phase1:.4f} radians, Phase 2: {phase2:.4f} radians")
    # print(f"Phase Difference: {phase_diff:.4f} radians")
    # print(f"Delay: {delay:.6f} seconds")

    # 開始繪製比較圖
    plt.figure(figsize=(15, 20))

    # 時域波形比較
    plt.subplot(5, 2, 1)
    plt.plot(time1, left_channel1, color='blue', label=f"{wav1} Left Channel")
    plt.plot(time2, left_channel2, color='red', label=f"{wav2} Left Channel")
    plt.title("Left Channel - Time Domain Comparison")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")
    plt.legend()

    plt.subplot(5, 2, 2)
    plt.plot(time1, right_channel1, color='green', label=f"{wav1} Right Channel")
    plt.plot(time2, right_channel2, color='orange', label=f"{wav2} Right Channel")
    plt.title("Right Channel - Time Domain Comparison")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")
    plt.legend()

    # 振幅比較
    plt.subplot(5, 2, 3)
    plt.plot(xf1[:len(amplitude_left1)], amplitude_left1, color='blue', label=f"{wav1} Left Channel")
    plt.plot(xf2[:len(amplitude_left2)], amplitude_left2, color='red', label=f"{wav2} Left Channel")
    plt.title("Left Channel - Amplitude Comparison")
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Amplitude")
    plt.legend()

    plt.subplot(5, 2, 4)
    plt.plot(xf1[:len(amplitude_right1)], amplitude_right1, color='green', label=f"{wav1} Right Channel")
    plt.plot(xf2[:len(amplitude_right2)], amplitude_right2, color='orange', label=f"{wav2} Right Channel")
    plt.title("Right Channel - Amplitude Comparison")
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Amplitude")
    plt.legend()

    text = (
        f"Frequency: {target_frequency} Hz\n"
        f"Phase 1: {phase1:.4f} radians\n"
        f"Phase 2: {phase2:.4f} radians\n"
        f"Phase Difference: {phase_diff:.4f} radians\n"
        f"Delay: {delay:.6f} seconds\n"
    )
    plt.figtext(0.5, 0.5, text, ha="left", va="bottom", fontsize=12, color="black", wrap=True)

    # 儲存圖像為 PNG 檔案
    output_file = os.path.join(output_folder, "16000_3000.png")
    plt.tight_layout()
    plt.savefig(output_file)
    print(f"Comparison plot saved as {output_file}")
    plt.show()

if __name__ == "__main__":
    wav1 = "in_fn_16000_3000.wav"  # 第一個音訊檔案名稱
    wav2 = "out_fn_16000_3000.wav"   # 第二個音訊檔案名稱
    target_frequency = 3000  # 目標頻率
    plot_wav_comparison(wav1, wav2, target_frequency)
