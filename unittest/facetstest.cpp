#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace std;

BOOST_AUTO_TEST_SUITE( facetsList )
BOOST_AUTO_TEST_CASE( sort )
{ 
  // Clear the node coordinates
  Facet::nodesCrd.clear();
  const string fname("squareAcc.msh");
  GmshReader reader;
  try
  {
    Facets facets;
    reader.readMesh( fname, facets );
    Vec3<double> sourcePos(-30.0,-10.0,-4.0);
    facets.computeDistanceFromSource( sourcePos );
    facets.sortByDistanceFromSource();
    bool everythingOK = true;
    for ( unsigned int i=0;i<facets.size();i++ )
    {
      for ( unsigned int j=i+1;j<facets.size();j++ )  
      {
        if ( facets.getFacet(i).getDistanceFromSource() > facets.getFacet(j).getDistanceFromSource() )
        {
          everythingOK = false;
          break;
        }
      }
      if ( !everythingOK )
      {
        break;
      }
    } 
    BOOST_CHECK_EQUAL( everythingOK, true );
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
