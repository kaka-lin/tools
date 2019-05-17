"""Signal-to-noise ratio (SNR)
    
SNR = P_signal / P_noise     # power of signal
    = (A_signal / A_noise)^2 # amplitude
    = sum(x^2) / sum(n^2)
SNR_dB = 10 * log(SNR)
=> SNR = 10 ^ (SNR_dB / 10)
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile as wav

# Add white Gaussian noise to signal
def awgn(x, snr): 
    # SNR = 10 ^ (SNR_dB / 10)
    snr = 10 ** (snr / 10.0)
    xpower = np.abs(np.sum(x ** 2) / len(x))
    npower = np.abs(xpower / snr)

    # np.random.randn():
    #   Return a sample (or samples) from the “standard normal” distribution
    n = np.random.randn(len(x)) * np.sqrt(npower)
    return x+n, n

if __name__ == "__main__":
    # sampling and signal information
    fs, data = wav.read("audio/gen.wav")
    Ts = 1.0 / fs
    N = len(data)
    t = N / fs
    amplitude = np.max(data)

    # avoid overflow -> normalization (-1, 1)
    y = data / amplitude
    
    # channel data
    yl = y[:, 0]
    yr = y[:, 1]

    # use left channel
    x = np.arange(0, t, Ts)
    yn, n = awgn(yl, 6)

    plt.figure() 
    plt.subplot(221) 
    plt.plot(x[:441], yl[:441], 'k')
    plt.title("The original signal") 
    plt.subplot(222) 
    plt.plot(x[:441], yl[:441], 'k')
    plt.plot(x[:441], yn[:441], 'r')
    plt.title("The original sinal with Gauss White Noise") 
    plt.subplot(223) 
    plt.hist(n, bins=100, density=True) 
    plt.title("Gauss Noise Distribution") 
    plt.subplot(224) 
    plt.psd(n)
    plt.title("PSD")
    plt.tight_layout() 
    #plt.savefig("img/snr_wav.png", dpi=600)

    plt.show()
