#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GmshTest
#include <boost/test/unit_test.hpp>
#include "gmshreader.h"
#include <string>
using namespace std;

BOOST_AUTO_TEST_SUITE( testread )
BOOST_AUTO_TEST_CASE( read )
{
  const string fname("squareAcc.msh");
  GmshReader reader;
  Facet* facets = reader.read( fname );
  BOOST_CHECK_EQUAL( Facet::nodesCrd.size(), 45 );
  
  // Count facets
  unsigned int counter = 0;
  for ( Facet* iter=facets; iter != NULL; iter=iter->next() )
  {
    counter++;
  } 
  BOOST_CHECK_EQUAL( counter, 88 ); 
  delete facets;
}
BOOST_AUTO_TEST_SUITE_END()
