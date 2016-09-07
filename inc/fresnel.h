#ifndef FRESNEL_H
#define FRESNEL_H
#include "materialProp.h"
#include "regionBoundary.h"
#include "point.h"
#include <complex>

class Fresnel
{
  public:
    Fresnel();
    std::complex<double> reflectionTE( const Vec3<double> &normalVec, const Vec3<double> &waveVector ) const;
    std::complex<double> reflectionTM( const Vec3<double> &normalVec,  const Vec3<double> &waveVector ) const;
    void setMaterial( const Material &mat, RegionBoundary::Domain_t domain );

    // TODO: Verify that there are no sign issues in this function
    Vec3< std::complex<double> > totalField( const Vec3<double> &E_inc, const Vec3<double>& normalVec, const Vec3<double> &waveVector ) const;
  private:
    // Pointers to material. Designed to be pointers to properties in the RegionBoundary class
    const Material *incident;
    const Material *scattered;
}; 
    
#endif
