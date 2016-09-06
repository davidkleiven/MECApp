#include "gmshreader.h"
#include "facets.h"
#include "point.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;
int main( int argc, char **argv )
{
  string fname("sphere.msh");
  string fnameOut("data/illumintedSphere.vtp");
  
  // Initialize the GMSH reader
  GmshReader reader;
  
  // Parse the file and get a facets object
  try
  {
    Facets facets = reader.read(fname); 
    Vec3 sourcePosition(-100.0,0.0,0.0);
    facets.computeDistanceFromSource( sourcePosition );
    facets.sortByDistanceFromSource();
    facets.illuminate();
    facets.saveIlluminationVTK( fnameOut );
  }
  catch ( exception &exc )
  {
    cerr << exc.what() << endl;
    return 1;
  }

  return 0;
} 
