#include <boost/test/unit_test.hpp>
#include "gmshreader.h"
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
