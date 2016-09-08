#ifndef FAR_FIELD_H
#define FAR_FIELD_H
#include "point.h"
#include "facet.h"
#include <complex>

class FarField
{
public:
  FarField(){};
  void computePoynting( const Vec3<double> &E_inc, const Vec3<double> &H_inc );
  void setObservationDirection( const Vec3<double> &observationPoint );
protected:
  Vec3<double> incPoyntingUnit;
  Vec3<double> observationDirection;

  // These two refers to Meana et al: High Frequency Techniques: the Physical Optics Approximation and the Modified Equivalanet Current Appr.
  double a, b;
  std::complex<double> surfaceIntegralValue;
  
  void computeIntegralCoefficients( const Facet &facet, double wavenumber );
  void surfaceIntegral( const Facet &facet, double wavenumber);

  // Flags for verifying call order for debugging
  bool hasComputedPoynting{false};
  bool observationDirectionIsSet{false};
  bool runUnitTest{false}; // For running unittests
};
  
#endif
