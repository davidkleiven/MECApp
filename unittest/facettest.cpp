#include <boost/test/unit_test.hpp>
#include "facet.h"
#include <string>

BOOST_AUTO_TEST_SUITE( facet )
BOOST_AUTO_TEST_CASE( centroid )
{
  Vec3 crd0(0.0,0.0,0.0);
  Vec3 crd1(0.0,2.0,2.0);
  Vec3 crd2(1.0, -1.0,2.0);
  
  Vec3 expCentroid(1.0/3.0, 1.0/3.0, 4.0/3.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes( nodes );
  Vec3 centroid;
  centroid = facet.centroid();
  BOOST_CHECK_CLOSE( centroid.getX(), expCentroid.getX(), 0.1f );
  BOOST_CHECK_CLOSE( centroid.getY(), expCentroid.getY(), 0.1f );
  BOOST_CHECK_CLOSE( centroid.getZ(), expCentroid.getZ(), 0.1f );
}

BOOST_AUTO_TEST_CASE( isBehind )
{
  Vec3 source(0.0, 0.0, 100.0);
  Vec3 crd0(0.0,0.0,0.0);
  Vec3 crd1(0.0,1.0,0.0);
  Vec3 crd2(1.0, 0.0, 0.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes( nodes );
  facet.computeDistanceFromSource( source );
  
  Vec3 testPoint(0.2,0.2, 10.0);
  BOOST_CHECK_EQUAL( facet.isBehindFacetPlane(testPoint), false ); 
  testPoint.setZ(-10.0);
  BOOST_CHECK_EQUAL( facet.isBehindFacetPlane(testPoint), true ); 
}
  
  
BOOST_AUTO_TEST_SUITE_END()
  
  
