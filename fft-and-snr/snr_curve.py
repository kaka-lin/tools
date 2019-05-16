"""Signal-to-noise ratio (SNR)
    
SNR = P_signal / P_noise     # power of signal
    = (A_signal / A_noise)^2 # amplitude
    = sum(x^2) / sum(n^2)
SNR_dB = 10 * log(SNR)
=> SNR = 10 ^ (SNR_dB / 10)
"""

import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    r = np.linspace(0.000001, 20) 
    
    # np.log -> ln (The natural logarithm log is the inverse of the exponential function)
    snr = 10 * np.log10(r)
    plt.plot(r, snr) 
    plt.grid() 
    plt.xlabel("$10*log_{10}\\frac{\sum{x^2}}{\sum{n^2}}$") 
    plt.ylabel("SNR") 
    plt.title("The ratio-snr curve") 
    plt.tight_layout()

    plt.show()