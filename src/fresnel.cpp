#include "fresnel.h"
#include <cmath>
#include <stdexcept>

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
  double kNormalInc = abs(waveVector.dot(normalVec));
  Vec3<double> kParallel = waveVector.cross(normalVec);

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
  double kNormalInc = abs(waveVector.dot(normalVec));
  Vec3<double> kParallel = waveVector.cross(normalVec);

  complex<double> n_inc = sqrt( incident->eps*incident->mu );
  complex<double> n_scat = sqrt( scattered->eps*scattered->mu );
  complex<double> kNormalScat = sqrt( k*k - pow(n_inc*kParallel.abs()/n_scat, 2) );
  
  complex<double> numerator = sqrt(scattered->eps/scattered->mu)*kNormalInc - sqrt(incident->eps/incident->mu)*kNormalScat;
  complex<double> denum = sqrt(scattered->eps/scattered->mu)*kNormalInc + sqrt(incident->eps/incident->mu)*kNormalScat;
  return numerator/denum; 
} 

Vec3< complex<double> > Fresnel::scatteredField( const Vec3<double> &E_inc, const Vec3<double> &normalVec, const Vec3<double> &waveVector ) const
{
  double sign = waveVector.dot(normalVec) > 0.0 ? -1.0:1.0; // Normal vector should be pointing in opposite direction of k
  complex<double> r_TE = reflectionTE( normalVec, waveVector );
  complex<double> r_TM = reflectionTM( normalVec, waveVector );
} 
