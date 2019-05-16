import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile as wav

if __name__ == "__main__":
    fs, data = wav.read("audio/gen.wav")
    Ts = 1.0 / fs
    N = len(data)
    t = N / fs
    left_data = data[:, 0]
    right_data = data[:, 1]
    x = np.arange(0, t, Ts)

    fft_left = fft(left_data)
    yw = np.abs(fft_left[0:int(N//2)]) / N
    xw = np.linspace(0.0, 1.0/(2.0*Ts), N//2)
    
    plt.subplot(211)
    plt.plot(x[:441], left_data[:441], 'k')
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")
    plt.grid()
    plt.tight_layout()

    plt.subplot(212)
    plt.plot(xw, yw, 'r')
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("magnitude")
    plt.grid()
    plt.tight_layout()

    plt.show()
