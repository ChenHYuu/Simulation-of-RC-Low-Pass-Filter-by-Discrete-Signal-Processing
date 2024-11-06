# Problem 7 plot_waveform #

import os
import wave
import numpy as np
import matplotlib.pyplot as plt

# Directory to save waveform images
output_dir = "waveform_images"
os.makedirs(output_dir, exist_ok=True)  # Create the directory if it doesn't exist

def plot_waveform(file_path):
    # Open the .wav file
    with wave.open(file_path, "rb") as wav_file:
        # Extract parameters
        n_channels, sampwidth, framerate, n_frames, comptype, compname = wav_file.getparams()
        # Read frames and convert to numpy array
        frames = wav_file.readframes(n_frames)
        waveform = np.frombuffer(frames, dtype=np.int16)
        
        # Reshape for stereo files
        if n_channels == 2:
            waveform = waveform.reshape(-1, 2)
        
        # Time axis for plotting
        time_axis = np.linspace(0, n_frames / framerate, num=n_frames)

        # Plot waveform
        plt.figure(figsize=(12, 4))
        if n_channels == 2:
            plt.plot(time_axis, waveform[:, 0], label="Left Channel")
            plt.plot(time_axis, waveform[:, 1], label="Right Channel")
            plt.legend()
        else:
            plt.plot(time_axis, waveform, label="Mono Channel")
        
        plt.xlabel("Time [s]")
        plt.ylabel("Amplitude")
        plt.title(f"Waveform of {os.path.basename(file_path)}")
        
        # Save the plot
        output_path = os.path.join(output_dir, f"{os.path.splitext(os.path.basename(file_path))[0]}.png")
        plt.savefig(output_path)
        plt.close()
        print(f"Waveform saved to: {output_path}")

# Example usage: list all .wav files in the current directory and plot each
for file_name in os.listdir("."):
    if file_name.endswith(".wav"):
        plot_waveform(file_name)
