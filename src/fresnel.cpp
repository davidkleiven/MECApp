#include "fresnel.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
//#define FRESNEL_DEBUG

using namespace std;

Fresnel::Fresnel():incident(NULL), scattered(NULL){};
void Fresnel::setMaterial( const Material &mat, RegionBoundary::Domain_t domain )
{
  switch ( domain )
  {
    case RegionBoundary::Domain_t::INCIDENT:
      incident = &mat;
      break;
    case RegionBoundary::Domain_t::SCATTERED:
      scattered = &mat;
      break;
  }
}
complex<double> Fresnel::reflectionTE( const Vec3<double>& normalVec, const Vec3<double> &waveVector ) const
{
  if ( incident == NULL )
  {
    throw (invalid_argument("No incident material set..."));
  }
  if ( scattered == NULL )
  {
    throw (invalid_argument("No scattered material set..."));
  }

  double k = waveVector.abs();
  double kNormalInc = abs(waveVector.dot(normalVec))/normalVec.abs();
  Vec3<double> kParallel = waveVector.cross(normalVec)/normalVec.abs();

  complex<double> n_inc = sqrt( incident->eps*incident->mu );
  complex<double> n_scat = sqrt( scattered->eps*scattered->mu );
  complex<double> kNormalScat = sqrt( k*k - pow(n_inc*kParallel.abs()/n_scat, 2) );
  
  complex<double> numerator = sqrt(incident->eps/incident->mu)*kNormalInc - sqrt(scattered->eps/scattered->mu)*kNormalScat;
  complex<double> denum = sqrt(incident->eps/incident->mu)*kNormalInc + sqrt(scattered->eps/scattered->mu)*kNormalScat;
  return numerator/denum; 
}

complex<double> Fresnel::reflectionTM( const Vec3<double>& normalVec, const Vec3<double> &waveVector ) const
{
  if ( incident == NULL )
  {
    throw (invalid_argument("No incident material set..."));
  }
  if ( scattered == NULL )
  {
    throw (invalid_argument("No scattered material set..."));
  }

  double k = waveVector.abs();
  double kNormalInc = abs(waveVector.dot(normalVec))/normalVec.abs();
  Vec3<double> kParallel = waveVector.cross(normalVec)/normalVec.abs();

  complex<double> n_inc = sqrt( incident->eps*incident->mu );
  complex<double> n_scat = sqrt( scattered->eps*scattered->mu );
  complex<double> kNormalScat = sqrt( k*k - pow(n_inc*kParallel.abs()/n_scat, 2) );
  
  complex<double> numerator = sqrt(scattered->eps/scattered->mu)*kNormalInc - sqrt(incident->eps/incident->mu)*kNormalScat;
  complex<double> denum = sqrt(scattered->eps/scattered->mu)*kNormalInc + sqrt(incident->eps/incident->mu)*kNormalScat;
  return numerator/denum; 
} 

Vec3< complex<double> > Fresnel::totalField( const Vec3<double> &E_inc, const Vec3<double> &normalVec, const Vec3<double> &waveVector ) const
{
  double sign = waveVector.dot(normalVec) > 0.0 ? -1.0:1.0; // Normal vector should be pointing in opposite direction of k
  complex<double> r_TE = reflectionTE( normalVec, waveVector );
  complex<double> r_TM = reflectionTM( normalVec, waveVector );
  Vec3<double> outOfScatteringPlane = normalVec.cross(waveVector);
  outOfScatteringPlane *= sign;
  outOfScatteringPlane /= outOfScatteringPlane.abs();
  double E_TE = E_inc.dot(outOfScatteringPlane);
  
  Vec3<double> TM_unit = outOfScatteringPlane.cross(waveVector);
  double E_TM = E_inc.dot(TM_unit);
  Vec3<double> totFieldReal = E_inc + outOfScatteringPlane*E_TE*real(r_TE) + TM_unit*E_TM*real(r_TM);
  Vec3<double> totFieldImag = outOfScatteringPlane*E_TE*imag(r_TE) + TM_unit*E_TM*imag(r_TM);
  Vec3< complex<double> > totField;
  totField.setX( totFieldReal.getX() );
  totField.setY( totFieldReal.getY() );
  totField.setZ( totFieldReal.getZ() );
  totField.setImag( totFieldImag );
  
  #ifdef FRESNEL_DEBUG
    cout << "Par unit: " << paralellUnit << endl;
    cout << "TM_unit: " << TM_unit << endl;
    cout << "Field real: " << totFieldReal << endl;
    cout << "Field imag: " << totFieldImag << endl;
    cout << "Tot field. " << totField << endl;
  #endif   
  return totField;
} 
