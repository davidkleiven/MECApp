#include <boost/test/unit_test.hpp>
#include <iostream>
#include "farField.h"
#include "facet.h"
#include <complex>

using namespace std;

complex<double> IM_UNIT(0.0,1.0);
// Testing class
class FarFieldTester: public FarField
{
  public:
    FarFieldTester(){};
    void setA( double newa ){a=newa;};
    void setB( double newb ){b=newb;};
    double getA() const {return a;};
    double getB() const {return b;};
    complex<double> surfIntegral( const Facet &facet, double k, double newa, double newb )
    {
      runUnitTest = true; // The function should not compute its own a and b
      a = newa;
      b = newb; 
      surfaceIntegral(facet,k);
      return surfaceIntegralValue;
    };
    void computeAandB(const Facet &facet, double wavenumber) { computeIntegralCoefficients(facet,wavenumber);};
};

BOOST_AUTO_TEST_SUITE( farFieldTestSuite )
BOOST_AUTO_TEST_CASE( surfaceIntegral )
{
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,1.0,0.0);
  Vec3<double> crd2(1.0,0.0,0.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes(nodes);

  Vec3<double> obsPoint(10.0,10.0,10.0);
  double k = 1.0;
  Vec3<double> waveVec(0.0,0.0,k);
  Vec3<double> E_inc(0.0,1.0,0.0);

  FarFieldTester ffTest;
  ffTest.setObservationDirection(obsPoint);
  Vec3<double> H_inc = waveVec.cross(E_inc);
  ffTest.computePoynting(E_inc, H_inc);

  // Test with fixed values of a and b
  double a = 0.0;
  double b = 0.0;
  complex<double> surfInt = ffTest.surfIntegral( facet, k, a, b ); 
  BOOST_CHECK_CLOSE( facet.area(), real(surfInt), 0.1f );
  
  a = 1.0;
  complex<double> expected = 2.0*facet.area()*exp(-IM_UNIT/3.0)*(1.0+IM_UNIT - exp(IM_UNIT));
  surfInt = ffTest.surfIntegral( facet, k, a, b );
  BOOST_CHECK_CLOSE( real(expected), real(surfInt), 0.1f );
  BOOST_CHECK_CLOSE( imag(expected), imag(surfInt), 0.1f );

  a = 0.0;
  b = 1.0;
  surfInt = ffTest.surfIntegral( facet, k, a, b );
  BOOST_CHECK_CLOSE( real(expected), real(surfInt), 0.1f );
  BOOST_CHECK_CLOSE( imag(expected), imag(surfInt), 0.1f );

  a = 1.0;
  b = 1.0;
  expected = 2.0*facet.area()*exp(-2.0*IM_UNIT/3.0)*(exp(IM_UNIT)*(1.0-IM_UNIT) - 1.0 );
  surfInt = ffTest.surfIntegral( facet, k, a, b ); 
  BOOST_CHECK_CLOSE( real(expected), real(surfInt), 0.1f );
  BOOST_CHECK_CLOSE( imag(expected), imag(surfInt), 0.1f );

  b = 2.0;
  expected = 2.0*facet.area()*exp(-IM_UNIT )*(exp(2.0*IM_UNIT) - 2.0*exp(IM_UNIT) + 1.0)/(-2.0);
  surfInt = ffTest.surfIntegral( facet, k, a, b ); 
  BOOST_CHECK_CLOSE( real(expected), real(surfInt), 0.1f );
  BOOST_CHECK_CLOSE( imag(expected), imag(surfInt), 0.1f );

  // Check that the internal computation computes the coefficients correct
  ffTest.computeAandB(facet,k); // Compute the coefficients using the wave vector and observation point
  double aExp = k/sqrt(3.0);
  double bExp = k/sqrt(3.0);
  BOOST_CHECK_CLOSE(aExp, ffTest.getA(), 0.1f );
  BOOST_CHECK_CLOSE(bExp, ffTest.getB(), 0.1f );
}
BOOST_AUTO_TEST_SUITE_END();
