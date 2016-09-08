#include "farField.h"
#include <cmath>
#include <cassert>
#include <iostream>
#define INTEGRAL_COEFF_ZERO 1E-12
#define DEBUG_FAR_FIELD

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
  obsPoint = observationPoint;
  obsPointIsSet = true;
}

void FarField::computeIntegralCoefficients( const Facet &facet, double wavenumber )
{
  assert( hasComputedPoynting );
  assert( obsPointIsSet );
  const unsigned int *nodes = facet.getNodes();

  // See Meana et al. for these vector definitions
  Vec3<double> v12 = Facet::nodesCrd[nodes[1]] - Facet::nodesCrd[nodes[0]];
  Vec3<double> v13 = Facet::nodesCrd[nodes[2]] - Facet::nodesCrd[nodes[0]];
  Vec3<double> observationDirection = obsPoint/obsPoint.abs();

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
    
void FarField::auxillaryFields( const Facet &facet, double wavenumber )
{
  surfaceIntegral( facet, wavenumber );
  Vec3<double> unitVecCentroidToObs = obsPoint - facet.getCentroid();
  unitVecCentroidToObs /= unitVecCentroidToObs.abs();
  Vec3< complex<double> > unitVecCentroidToObsComplex;

  // Copy coordinates
  unitVecCentroidToObsComplex.setX( unitVecCentroidToObs.getX() );
  unitVecCentroidToObsComplex.setY( unitVecCentroidToObs.getY() );
  unitVecCentroidToObsComplex.setZ( unitVecCentroidToObs.getZ() );
  
  // Compute auxillary H-field 
  complex<double> phasePart = exp( IM_UNIT*wavenumber*unitVecCentroidToObs.dot(obsPoint) )*surfaceIntegralValue;
  auxillaryHfield = unitVecCentroidToObsComplex.cross(facet.getEquivalentCurrent().electric);
  auxillaryHfield *= phasePart;

  auxillaryEfield = unitVecCentroidToObsComplex.cross(facet.getEquivalentCurrent().magnetic);
  auxillaryEfield *= phasePart;
}

void FarField::computeScatteredFields( const Facet &facet, double wavenumber )
{
  auxillaryFields( facet, wavenumber );
  double R = obsPoint.abs();
  double wavelength = 2.0*PI/wavenumber;
  complex<double> incImpedance = 1.0; // Should be read from the material
  Vec3<double> obsUnit = obsPoint/R;

  // Complex version of obsUnit to be able to multiply with a complex vector
  Vec3< complex<double> > obsUnitCmplx;
  obsUnitCmplx.setX( obsUnit.getX() ); 
  obsUnitCmplx.setY( obsUnit.getY() ); 
  obsUnitCmplx.setZ( obsUnit.getZ() ); 
  
  scatteredEfield =  auxillaryEfield - auxillaryHfield.cross(obsUnitCmplx)*incImpedance;
  scatteredEfield *= IM_UNIT*exp(-IM_UNIT*wavenumber*R)/(2.0*wavelength*R);

  scatteredHfield = auxillaryHfield - obsUnitCmplx.cross(auxillaryEfield)/incImpedance;
  scatteredHfield *= -IM_UNIT*exp(-IM_UNIT*wavenumber*R)/(2.0*wavelength*R);
}

double FarField::radiatedPower()
{
  scatteredHfield.conj();
  double power = 0.5*scatteredEfield.cross( scatteredHfield ).abs();
  scatteredHfield.conj(); // Undo complex conjugateion
  return abs(power);
}
