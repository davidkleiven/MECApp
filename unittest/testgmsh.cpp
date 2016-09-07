#include <boost/test/unit_test.hpp>
#include "gmshreader.h"
#include "facets.h"
#include <string>
#include <iostream>
using namespace std;

BOOST_AUTO_TEST_SUITE( testread )
BOOST_AUTO_TEST_CASE( read )
{
  const string fname("squareAcc.msh");
  GmshReader reader;
  try
  {
    Facets facets;
    reader.readMesh( fname, facets );
    BOOST_CHECK_EQUAL( Facet::nodesCrd.size(), 45 );
    
    // Count facets
    BOOST_CHECK_EQUAL( facets.size(), 68 ); 
  }
  catch ( runtime_error &exc )
  {
    cout << exc.what() << endl;
  }
  catch( invalid_argument &exc )
  {
    cout << exc.what() << endl;
  }
  catch(...)
  {
    cout << "Unexpected excepiton...\n";
  }
}
BOOST_AUTO_TEST_SUITE_END()
