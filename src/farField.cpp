#include "farField.h"
#include <cmath>
#include <cassert>
#define INTEGRAL_COEFF_ZERO 1E-12

using namespace std;
const double PI = acos(-1.0);
const complex<double> IM_UNIT(0.0,1.0);

void FarField::computePoynting( const Vec3<double> &E_inc, const Vec3<double> &H_inc )
{
  incPoyntingUnit = E_inc.cross(H_inc);
  incPoyntingUnit /= incPoyntingUnit.abs();
  hasComputedPoynting = true;
}

void FarField::setObservationDirection( const Vec3<double> &observationPoint )
{
  observationDirection = observationPoint/observationPoint.abs();
  observationDirectionIsSet = true;
}

void FarField::computeIntegralCoefficients( const Facet &facet, double wavenumber )
{
  assert( hasComputedPoynting );
  assert( observationDirectionIsSet );
  const unsigned int *nodes = facet.getNodes();

  // See Meana et al. for these vector definitions
  Vec3<double> v12 = Facet::nodesCrd[nodes[1]] - Facet::nodesCrd[nodes[0]];
  Vec3<double> v13 = Facet::nodesCrd[nodes[2]] - Facet::nodesCrd[nodes[0]];

  a = v12.dot(observationDirection - incPoyntingUnit)*wavenumber; 
  b =  v13.dot(observationDirection - incPoyntingUnit)*wavenumber;
}
   
void FarField::surfaceIntegral( const Facet &facet, double wavenumber )
{
  if ( !runUnitTest )
  {
    computeIntegralCoefficients( facet, wavenumber );
  }

  if (( abs(a) < INTEGRAL_COEFF_ZERO ) && ( abs(b) < INTEGRAL_COEFF_ZERO ))
  {
    surfaceIntegralValue =  facet.area();
  }
  else if ( abs(b-a) < INTEGRAL_COEFF_ZERO )
  {
    complex<double> numerator = exp(IM_UNIT*a)*(1.0-IM_UNIT*a)-1.0;
    surfaceIntegralValue = 2.0*facet.area()*exp(-2.0*IM_UNIT*a/3.0)*numerator/pow(a,2);
  }
  else if ( abs(b) < INTEGRAL_COEFF_ZERO )
  {
    complex<double> numerator = 1.0+IM_UNIT*a - exp(IM_UNIT*a);
    surfaceIntegralValue = 2.0*facet.area()*exp(-IM_UNIT*a/3.0)*numerator/pow(a,2);
  }
  else if ( abs(a) < INTEGRAL_COEFF_ZERO )
  {
    complex<double> numerator = 1.0+IM_UNIT*b - exp(IM_UNIT*b);
    surfaceIntegralValue = 2.0*facet.area()*exp(-IM_UNIT*b/3.0)*numerator/pow(b,2);
  }
  else
  {
    complex<double> numerator = a*exp(IM_UNIT*b) - b*exp(IM_UNIT*a) + b - a;
    surfaceIntegralValue = 2.0*facet.area()*exp(-IM_UNIT*(a+b)/3.0)*numerator/(a*b*(a-b));
  }
}
    
    
