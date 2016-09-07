#include "gmshreader.h"
#include "facets.h"
#include "point.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;
int main( int argc, char **argv )
{
  const double PI = acos(-1.0);
  string fname("sphereMat.json");
  string fnameOut("data/illumintedSphere.vtp");
  
  // Initialize the GMSH reader
  GmshReader reader;
  
  // Parse the file and get a facets object
  double wavelength = 0.05;
  double wavenumber = 2.0*PI/wavelength;
  try
  {
    Facets facets;
    reader.read(fname, facets); 
    Vec3<double> sourcePosition(-100.0,0.0,0.0);
    Vec3<double> E_inc(0.0,1.0,0.0);
    Vec3<double> waveVec(wavenumber,0.0,0.0);
    facets.computeDistanceFromSource( sourcePosition );
    facets.sortByDistanceFromSource();
    facets.illuminate();
    facets.computeEquivalentCurrent( E_inc, waveVec );
    facets.saveIlluminationVTK( fnameOut );
  }
  catch ( exception &exc )
  {
    cerr << exc.what() << endl;
    return 1;
  }

  return 0;
} 
