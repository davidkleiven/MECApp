#include <boost/test/unit_test.hpp>
#include <iostream>
#include "point.h"
#include "fresnel.h"
#include <cmath>

using namespace std;

BOOST_AUTO_TEST_SUITE( FresnelTestSuite )
BOOST_AUTO_TEST_CASE( fresneltest )
{
  const double PI = acos(-1.0);
  Fresnel fresnel;
  Material incident;
  Material scatter;
  incident.eps = 1.0; 
  incident.mu = 1.0;
  scatter.eps=2.25;
  scatter.mu = 1.0;

  fresnel.setMaterial( incident, RegionBoundary::Domain_t::INCIDENT );
  fresnel.setMaterial( scatter, RegionBoundary::Domain_t::SCATTERED );

  Vec3<double> normal(0.0,0.0,1.0);
  double k = 1.0;
  double incAngle = 30.0;
  Vec3<double> waveVec;
  waveVec.setX( k*sin( incAngle*PI/180.0 ) ); 
  waveVec.setZ( -k*cos( incAngle*PI/180.0 ) );
  complex<double> rTE = fresnel.reflectionTE( normal, waveVec );
  complex<double> rTM = fresnel.reflectionTM( normal, waveVec );

  double rTEexact = -0.240408;
  double rTMexact = 0.1588998;
  BOOST_CHECK_CLOSE( real(rTE), rTEexact, 0.1f );
  BOOST_CHECK_CLOSE( real(rTM), rTMexact, 0.1f );
  BOOST_CHECK_CLOSE( imag(rTE), 0.0, 0.1f );
  BOOST_CHECK_CLOSE( imag(rTM), 0.0, 0.1f );

  // TE case
  Vec3<double> E_inc(0.0,1.0,0.0);
  Vec3< complex<double> > E_tot = fresnel.totalField( E_inc, normal, waveVec );
  Vec3<double> expectedTotal = E_inc  + E_inc*rTEexact;
  BOOST_CHECK_CLOSE( expectedTotal.getY(), real(E_tot.getY()), 0.1f); 

  // TM case
  E_inc.setY(0.0);
  E_inc.setX( k*cos(incAngle*PI/180.0) );
  E_inc.setZ( k*sin(incAngle*PI/180.0) );
  E_tot = fresnel.totalField( E_inc, normal, waveVec );
  expectedTotal = E_inc + E_inc*rTMexact;
  BOOST_CHECK_CLOSE( expectedTotal.getX(), real(E_tot.getX()), 0.1f );
  BOOST_CHECK_CLOSE( expectedTotal.getZ(), real(E_tot.getZ()), 0.1f ); 
}
BOOST_AUTO_TEST_SUITE_END()

  
