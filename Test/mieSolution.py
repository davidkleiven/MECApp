import numpy as np
from scipy import special as spec
from matplotlib import pyplot as plt

def hankel2Spherical( n, z ):
    return spec.spherical_jn(n, z) - 1j*spec.spherical_yn(n,z)

def hankel2SphericalDeriv( n, z ):
    return spec.spherical_jn(n, z, derivative=True) - 1j*spec.spherical_yn(n,z, derivative=True)

def coeff_n( n, kR, eps, mu, aOrb ):
    refrIndx = np.sqrt(eps*mu)
    
    if ( aOrb == 'a' ):
        matprop = eps
    else:
        matprop = mu
    num1 = matprop*spec.spherical_jn(n, refrIndx*kR)*( spec.spherical_jn(n,kR) + kR*spec.spherical_jn(n,kR,derivative=True) )
    num2 = spec.spherical_jn(n, kR)*( spec.spherical_jn(n, refrIndx*kR) + refrIndx*kR*spec.spherical_jn(n,refrIndx*kR,derivative=True) )
    denum1 = matprop*spec.jn(n,refrIndx*kR)*( hankel2Spherical(n, kR) + kR*hankel2SphericalDeriv(n,kR) )
    denum2 = hankel2Spherical(n,kR)*(spec.spherical_jn(n,refrIndx*kR) + refrIndx*kR*spec.spherical_jn(n,refrIndx*kR,derivative=True) )

    return (num1-num2)/(denum1 - denum2)

def scatteringCrossSection(Nterms, eps, mu, kR):
    crossSection = 0.0
    for i in range(1,Nterms):
        a_n = coeff_n(i,kR, eps, mu, 'a')
        b_n = coeff_n(i,kR, eps, mu, 'b')
        crossSection += (2*i+1)*(np.abs(a_n)**2 + np.abs(b_n)**2)
    return 2.0*np.pi*crossSection/kr**2

def radarCrossSection(Nterms, eps, mu, kR):
    crossSection = 0.0
    for i in range(1,Nterms):
        a_n = coeff_n(i,kR, eps, mu, 'a')
        b_n = coeff_n(i,kR, eps, mu, 'b')
        crossSection += (2*i+1)*(a_n - b_n)*(-1.0)**i
    return np.pi*np.abs(crossSection)**2 /(kR**2)

def main():
    kr = np.logspace(-1, 2, 1000)
    sigma = radarCrossSection(20, 2.2-1j*7.0,1.1, kr)
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    ax.plot( kr, sigma ) 
    ax.set_yscale('log')
    ax.set_xscale('log')
    plt.show()

if __name__ == "__main__":
    main()
    
