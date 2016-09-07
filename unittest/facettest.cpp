#include <boost/test/unit_test.hpp>
#include "facet.h"
#include <string>

BOOST_AUTO_TEST_SUITE( facet )
BOOST_AUTO_TEST_CASE( centroid )
{
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,2.0,2.0);
  Vec3<double> crd2(1.0, -1.0,2.0);
  
  Vec3<double> expCentroid(1.0/3.0, 1.0/3.0, 4.0/3.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes( nodes );
  Vec3<double> centroid;
  centroid = facet.centroid();
  BOOST_CHECK_CLOSE( centroid.getX(), expCentroid.getX(), 0.1f );
  BOOST_CHECK_CLOSE( centroid.getY(), expCentroid.getY(), 0.1f );
  BOOST_CHECK_CLOSE( centroid.getZ(), expCentroid.getZ(), 0.1f );
}

BOOST_AUTO_TEST_CASE( isBehindPlane )
{
  Vec3<double> source(0.0, 0.0, 100.0);
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,1.0,0.0);
  Vec3<double> crd2(1.0, 0.0, 0.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes( nodes );
  facet.computeDistanceFromSource( source );

  Vec3<double> sourceSet = facet.getSourcePosition();
  BOOST_CHECK_CLOSE( sourceSet.getX(), source.getX(), 0.1f );
  BOOST_CHECK_CLOSE( sourceSet.getY(), source.getY(), 0.1f );
  BOOST_CHECK_CLOSE( sourceSet.getZ(), source.getZ(), 0.1f );
  
  Vec3<double> testPoint(0.2,0.2, 0.1);
  BOOST_CHECK_EQUAL( facet.isBehindFacetPlane(testPoint), false ); 
  testPoint.setZ(-0.1);
  BOOST_CHECK_EQUAL( facet.isBehindFacetPlane(testPoint), true ); 

  testPoint.setX(0.1);
  testPoint.setY(0.1);
  testPoint.setZ(0.0);
  Facet::nodesCrd[2].setX(0.0);
  Facet::nodesCrd[2].setZ(1.0);
  BOOST_CHECK_EQUAL( facet.isBehindFacetPlane(testPoint), false );

}

BOOST_AUTO_TEST_CASE( normalVector )
{
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,1.0,0.0);
  Vec3<double> crd2(1.0, 0.0, 0.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes(nodes);
  Vec3<double> normal = facet.getNormalVector();
  BOOST_CHECK_CLOSE(normal.getX(), 0.0, 0.1f);  
  BOOST_CHECK_CLOSE(normal.getY(), 0.0, 0.1f);  
  BOOST_CHECK_CLOSE(abs(normal.getZ()), 1.0, 0.1f);   
}

BOOST_AUTO_TEST_CASE( isInsidePyamid )
{
  Vec3<double> source(0.0, 0.0, 100.0);
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,1.0,0.0);
  Vec3<double> crd2(1.0, 0.0, 0.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  unsigned int nodes[3] = {0,1,2};
  Facet facet;
  facet.setNodes( nodes );
  facet.computeDistanceFromSource( source );
  
  Vec3<double> testPoint(0.1, 0.1, 10.0);
  BOOST_CHECK_EQUAL( facet.isInsidePyramid(testPoint), true );
  testPoint.setX(2.0);
  testPoint.setZ(0.0);
  BOOST_CHECK_EQUAL( facet.isInsidePyramid(testPoint), false);

  testPoint.setX(0.1);
  testPoint.setZ(-10.0);
  BOOST_CHECK_EQUAL( facet.isInsidePyramid(testPoint), true);

  testPoint.setZ(-100000000.0);
  BOOST_CHECK_EQUAL( facet.isInsidePyramid(testPoint), true);
}
  
BOOST_AUTO_TEST_CASE( isBehindOther )
{
  Vec3<double> source(0.0,0.0,1000.0);
  Vec3<double> crd0(0.0,0.0,0.0);
  Vec3<double> crd1(0.0,1.0,0.0);
  Vec3<double> crd2(1.0, 0.0, 0.0);
  Vec3<double> crd3(1.0,0.0,-1.0);
  Facet::nodesCrd.clear();
  Facet::nodesCrd.push_back(crd0);
  Facet::nodesCrd.push_back(crd1);
  Facet::nodesCrd.push_back(crd2);
  Facet::nodesCrd.push_back(crd3);

  Facet facet1;
  Facet facet2;
  unsigned int nodes1[3] = {0,1,2};
  unsigned int nodes2[3] = {0,1,3};
  facet1.setNodes(nodes1);
  facet2.setNodes(nodes2);
  facet1.computeDistanceFromSource(source);
  facet2.computeDistanceFromSource(source);
  
  bool result = facet2.isBehindOther(facet1);
  BOOST_CHECK_EQUAL( result, true );

  // Change the height
  Facet::nodesCrd[2].setZ(1.0);
  facet1.centroid();
  facet1.computeNormalVector();
  result = facet2.isBehindOther(facet1);
  BOOST_CHECK_EQUAL( result, true );

  // Change height
  Facet::nodesCrd[2].setZ(1.0);
  Facet::nodesCrd[2].setX(0.0);
  facet1.centroid();
  facet1.computeNormalVector();
  result = facet2.isBehindOther(facet1);
  bool planeResult = facet1.isBehindFacetPlane( facet2.centroid() ); // Check if centroid of facet2 is behind facet1
  BOOST_CHECK_EQUAL(planeResult, false);
  BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_SUITE_END()
  
  
