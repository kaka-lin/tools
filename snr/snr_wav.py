"""Signal-to-noise ratio (SNR)
    
SNR = P_signal / P_noise     # power of signal
    = (A_signal / A_noise)^2 # root mean square amplitude.
    = sum(x^2) / sum(n^2)
SNR_dB = 10 * log(SNR)
=> SNR = 10 ^ (SNR_dB / 10)
"""

import sys
import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft, ifft
from scipy.io import wavfile as wav

def rms(data):
    return np.sqrt(np.mean(np.square(data), axis=-1))

def snr(sig, noise):
    return 20 * np.log10(sig / noise)

if __name__ == "__main__":
    fs1, signal_data = wav.read("audio/signal.wav")
    fs2, signoise_data = wav.read("audio/signal_with_noise.wav")
    
    if fs1 == fs2:
        fs = fs1
    else:
        print("Error!\n")
        sys.exit()
    
    if len(signal_data) == len(signoise_data):
        N = len(signal_data)
    else:
        print("Error!\n")
        sys.exit()
    
    Ts = 1.0 / fs
    t = N / fs
    sig_amplitude = np.max(signal_data)
    signoise_amplitude = np.max(signoise_data)

    # duration
    x = np.arange(0, t, Ts)

    # data
    sig_y = signal_data / sig_amplitude
    signoise_y = signoise_data / signoise_amplitude

    # noise
    noise = signoise_y - sig_y
    recover_sig = signoise_y - noise
    recover_signoise = noise + recover_sig

    '''
    with wave.open("recovery.wav", "wb") as wav:
        wav.setparams((2, 2, fs, 0, 'NONE', 'not compressed'))

        datas = recover_signoise * signoise_amplitude
        datas = datas.astype(np.short)
             
        for data in datas:
            wav.writeframes(data[0].tostring())
            wav.writeframes(data[1].tostring())
            
    with wave.open("noise.wav", "wb") as wav:
        wav.setparams((2, 2, fs, 0, 'NONE', 'not compressed'))

        datas = noise * signoise_amplitude
        datas = datas.astype(np.short)

        for data in datas:
            wav.writeframes(data[0].tostring())
            wav.writeframes(data[1].tostring())
    '''

    # Using amplitude to calculate SNR
    signoise_yl = signoise_y[:, 0]
    sig_yl = sig_y[:, 0]
    noise_l = noise[:, 0]
    recover_sig_l = recover_sig[:, 0]
    recover_signoise_l = recover_signoise[:, 0]

    rms_sig = rms(sig_yl)
    rms_noise = rms(noise_l)
    snr_amplitude = snr(rms_sig, rms_noise)

    # Using FFT to calculate SNR
    yfft = fft(sig_yl)
    xpower = np.sum(np.abs(yfft ** 2)) / (len(yfft) ** 2)
    nfft = fft(noise_l)
    npower = np.sum(np.abs(nfft ** 2)) / (len(nfft) ** 2)

    snr_fft = 10 * np.log10(xpower / npower)

    print("SNR_amplitude: {}dB\nSNR_fft: {}dB".format(round(snr_amplitude, 2), round(snr_fft, 2)))

    plt.figure() 
    plt.subplot(3,1,1)
    plt.plot(x[:4410], signoise_yl[:4410], 'k')
    plt.title("The original signal that with noise") 
    plt.subplot(3,1,2)
    plt.plot(x[:4410], noise_l[:4410], 'b')
    plt.plot(x[:4410], recover_sig_l[:4410], 'b')
    plt.title("The signal without noise & The noise signal") 
    plt.subplot(3,1,3)
    plt.plot(x[:4410], recover_signoise_l[:4410], 'r')
    plt.title("The signal of recovery") 
    
    plt.tight_layout() 
    plt.show()
