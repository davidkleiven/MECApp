#include "gmshreader.h"
#include "facets.h"
#include "point.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;
int main( int argc, char **argv )
{
  const double PI = acos(-1.0);
  string fname("sphereMat.json");
  string fnameOut("data/illumintedSphere.vtp");
  
  // Initialize the GMSH reader
  GmshReader reader;
  
  // Parse the file and get a facets object
  double krMin = 0.01;
  double krMax = 100.0;
  vector<double> kr;
  double logwaveMin = log10(krMin);
  double logwaveMax = log10(krMax);
  unsigned int nWav = 100;
  double dlogwave = (logwaveMax - logwaveMin)/static_cast<double>(nWav-1);
  for ( unsigned int i=0;i<nWav;i++ )
  {
    double wave = pow(10.0, logwaveMin + dlogwave*static_cast<double>(i-1));
    kr.push_back(wave);
  }
  
  vector<double> scatteredPower; 
  try
  {
    Facets facets;
    reader.read(fname, facets); 
    Vec3<double> sourcePosition(0.0,0.0,-100.0);
    Vec3<double> E_inc(0.0,1.0,0.0);
    Vec3<double> obsPoint(0.0,0.0,100.0);
    facets.computeDistanceFromSource( sourcePosition );
    facets.sortByDistanceFromSource();
    facets.illuminate();
    for ( unsigned int i=0;i<nWav;i++ )
    {
      Vec3<double> waveVec(0.0, 0.0, kr[i]);
      facets.computeEquivalentCurrent( E_inc, waveVec );
      double scatPow = facets.computeScatteredPower( obsPoint ); 
      scatteredPower.push_back(scatPow);
    }
  }
  catch ( exception &exc )
  {
    cerr << exc.what() << endl;
    return 1;
  }

  // Save results
  string outfname("data/scatteredPower.csv");
  ofstream out(outfname.c_str());
  if ( !out.good() )
  {
    cout << "Could not open file " << outfname << endl;
    return 1;
  }

  out << "# Wavenumber (k*R), Scatteredpower\n";
  for ( unsigned int i=0;i<kr.size();i++ )
  {
    out << kr[i] << "," << scatteredPower[i] << "\n";
  }
  out.close();
  cout << "Data written to " << outfname << endl;
  return 0;
} 
