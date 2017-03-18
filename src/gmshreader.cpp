#include "gmshreader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "facets.h"
#include "facet.h"
#include <string>
//#define GMSHREADER_DEBUG
using namespace std;

GmshReader::GmshReader(){};

void GmshReader::read( const string& jsonfile, Facets& facets )
{
  ifstream in(jsonfile.c_str());
  if ( !in.good() )
  {
    string msg("Could not open file ");
    msg += jsonfile;
    throw( runtime_error(msg) );
  }
  Json::Reader reader;
  reader.parse( in, data );
  in.close();

  if ( !data.isMember("mesh") )
  {
    throw (invalid_argument("The json file does not contain a mesh file..."));
  }
  complex<double> epsInc, muInc, epsScat, muScat;
  readMatProp( "epsInc", epsInc );
  readMatProp( "muInc", muInc );
  readMatProp( "epsScat", epsScat );
  readMatProp( "muScat", muScat );

  RegionBoundary reg;
  reg.setMatProp( epsInc, muInc, RegionBoundary::Domain_t::INCIDENT );
  reg.setMatProp( epsScat, muScat, RegionBoundary::Domain_t::SCATTERED );
  reg.setMinElm( facets.size() );
  readMesh( data["mesh"].asString(), facets );
  reg.setMaxElm( facets.size() );
  facets.addRegion( reg );

}

void GmshReader::readMatProp( const string& key, complex<double> &matprop ) const
{
  if ( !data.isMember(key) )
  {
    cout << "Did not find " << key << " using default value 1\n";
    matprop = 1.0;
    return;
  }

  if ( !data[key].isMember("real") )
  {
    cout << "Did not find real part of " << key << " using default 1.0\n";
  }
  else
  {
    matprop.real(data[key]["real"].asDouble() );
  }
  if ( !data[key].isMember("imag") )
  {
    cout << "Did not find imaginary part of " << key << " using default 0.0\n";
    matprop.imag(0.0);
  }
  else
  {
    matprop.imag( data[key]["imag"].asDouble() );
  }
}

void GmshReader::readMesh( const string& fname, Facets& facets ) const
{
  string id("[GmshReader::readMesh] ");
  ifstream infile( fname.c_str() );
  if ( !infile.good() )
  {
    string msg("Could not open file ");
    msg += fname;
    msg += "...";
    throw ( runtime_error(msg) );
  }

  // Some keywords to look for
  const string nodestart("$Nodes");
  const string nodeend("$EndNodes");
  const string elementstart("$Elements");
  const string elementend("$EndElements");
  string line;

  // Read until nodestart is found + 1 line
  bool breakOnNext = false;
  #ifdef GMSHREADER_DEBUG
    cerr << id << "Searching for nodestart...\n";
  #endif
  while ( getline(infile, line) )
  {
    if ( line.find(nodestart) != string::npos )
    {
      breakOnNext = true;
      continue;
    }
    if ( breakOnNext )
    {
      break;
    }
  }
  unsigned int nodesOffset = Facet::nodesCrd.size();

  unsigned int nodeNumber;
  #ifdef GMSHREADER_DEBUG
    cerr << id << "Reading nodes...\n";
  #endif
  while( getline(infile, line) )
  {
    if ( line.find(nodeend) != string::npos )
    {
      break;
    }
    double x,y,z;
    stringstream ss;
    ss << line;
    ss >> nodeNumber;
    ss >> x >> y >> z;
    Vec3<double> point(x,y,z);
    Facet::nodesCrd.push_back(point);
  }

  // Read until start elements is found
  breakOnNext = false;
  #ifdef GMSHREADER_DEBUG
    cerr << id << "Searching for element start...\n";
  #endif
  while ( getline(infile,line) )
  {
    if ( line.find(elementstart) != string::npos )
    {
      breakOnNext=true;
      continue;
    }
    if ( breakOnNext )
    {
      break;
    }
  }

  unsigned int elementType;
  unsigned int numberOfTags;
  unsigned int elementNumber;
  bool isFirst = true;

  #ifdef GMSHREADER_DEBUG
    cerr << id << "Reading elements...\n";
  #endif
  while ( getline(infile,line) )
  {
    Facet newfacet;
    if ( line.find(elementend) != string::npos )
    {
      break;
    }
    stringstream ss;
    ss << line;
    ss >> elementNumber;
    ss >> elementType;

    if ( elementType != TRIANGLE )
    {
      continue;
    }

    ss >> numberOfTags;
    unsigned int tag;
    for ( unsigned int i=0;i<numberOfTags; i++ )
    {
      ss >> tag;
    }
    unsigned int nodenum[3];
    ss >> nodenum[0];
    ss >> nodenum[1];
    ss >> nodenum[2];
    nodenum[0] -= 1;
    nodenum[1] -= 1;
    nodenum[2] -= 1;

    // Add offset in case there are already another mesh stored
    nodenum[0] += nodesOffset;
    nodenum[1] += nodesOffset;
    nodenum[2] += nodesOffset;
    newfacet.setNodes(nodenum);
    facets.add( newfacet );
  }
  infile.close();
  #ifdef GMSHREADER_DEBUG
    cerr << id << "Leaving read function...\n";
  #endif
}
