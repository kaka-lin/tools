"""Signal-to-noise ratio (SNR)
    
SNR = P_signal / P_noise     # power of signal
    = (A_signal / A_noise)^2 # amplitude
    = sum(x^2) / sum(n^2)
SNR_dB = 10 * log(SNR)
=> SNR = 10 ^ (SNR_dB / 10)
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft, ifft
from scipy.io import wavfile as wav

# Add white Gaussian noise to signal
def awgn(x, snr): 
    # SNR = 10 ^ (SNR_dB / 10)
    snr = 10 ** (snr / 10.0)
    # A_sig ^ 2 = (x1^2 + x2^2 + ... + xn^2) / n
    xpower = np.sum(np.abs(x ** 2)) / len(x)
    npower = np.abs(xpower / snr)

    # np.random.randn():
    #   Return a sample (or samples) from the “standard normal” distribution
    n = np.random.randn(len(x)) * np.sqrt(npower)
    return x+n, n

if __name__ == "__main__":
    # sampling and signal information
    fs, data = wav.read("audio/test1.wav")
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

    """ Parseval's theorem
    
    np.sum(np.abs(sig)**2) == np.sum(np.abs(np.fft.fft(sig))**2)/sig.size

    power = np.sum(np.abs(sig)**2)/sig.size
          = np.sum(np.abs(np.fft.fft(sig))**2)/(sig.size**2)
    """
    # By Parseval's theorem, 
    # we can calculate the power of a signal through X[k] that is the FFT of x[n].
    yfft = fft(yl)
    ynfft = fft(yn)
    xpower = np.sum(np.abs(yfft ** 2)) / (len(yfft) ** 2)

    noise = yn - yl
    nfft = fft(noise)
    npower = np.sum(np.abs(nfft ** 2)) / (len(nfft) ** 2)

    # SNR 
    snr = xpower / npower
    snr_dB = 10 * np.log10(snr)
    print("SNR: {}dB".format(round(snr_dB, 2)))

    plt.figure() 
    plt.plot(x[:441], yl[:441], 'k')
    plt.plot(x[:441], yn[:441], 'r')
    plt.title("The original sinal with Gauss White Noise") 
    
    plt.tight_layout() 
    plt.show()
