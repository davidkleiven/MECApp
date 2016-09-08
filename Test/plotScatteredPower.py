import numpy as np
from matplotlib import pyplot as plt

def main():
    fname = "data/scatteredPower.csv"
    wavelength, power = np.loadtxt( fname, delimiter=",", unpack=True )
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    ax.plot( wavelength, power )
    ax.set_yscale('log')
    plt.show()

if __name__ == "__main__":
    main()
