import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.fft import fft, fftfreq

def plot_wav(input_file):
    # 讀取 WAV 檔案
    sample_rate, data = wavfile.read(input_file)
    
    # 檢查是否為立體聲
    if len(data.shape) == 2:
        left_channel = data[:, 0]
        right_channel = data[:, 1]
    else:
        left_channel = data
        right_channel = None  # 單聲道沒有右聲道

    # 創建資料夾以保存圖片
    output_folder = "output_images"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    
    # 時域圖
    time = np.linspace(0, len(left_channel) / sample_rate, num=len(left_channel))

    plt.figure(figsize=(12, 10))

    # 左聲道時域圖
    plt.subplot(4, 1, 1)
    plt.plot(time, left_channel, color='blue')
    plt.title("Left Channel - Time Domain")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")

    # 右聲道時域圖（如果有右聲道）
    if right_channel is not None:
        plt.subplot(4, 1, 2)
        plt.plot(time, right_channel, color='green')
        plt.title("Right Channel - Time Domain")
        plt.xlabel("Time [s]")
        plt.ylabel("Amplitude")
    
    # 左聲道頻域圖
    yf_left = fft(left_channel)
    xf = fftfreq(len(left_channel), 1 / sample_rate)
    plt.subplot(4, 1, 3)
    plt.plot(xf[:len(xf) // 2], np.abs(yf_left[:len(yf_left) // 2]), color='red')
    plt.title("Left Channel - Frequency Domain")
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Magnitude")

    # 右聲道頻域圖（如果有右聲道）
    if right_channel is not None:
        yf_right = fft(right_channel)
        plt.subplot(4, 1, 4)
        plt.plot(xf[:len(xf) // 2], np.abs(yf_right[:len(yf_right) // 2]), color='orange')
        plt.title("Right Channel - Frequency Domain")
        plt.xlabel("Frequency [Hz]")
        plt.ylabel("Magnitude")

    # 儲存圖像為 PNG 檔案
    output_file = os.path.join(output_folder, input_file.replace(".wav", "_stereo_plot.png"))
    plt.tight_layout()
    plt.savefig(output_file)
    print(f"Plot saved as {output_file}")
    plt.show()

if __name__ == "__main__":
    input_file = "ffn.wav"  # 修改成您實際的音訊檔名稱
    plot_wav(input_file)
