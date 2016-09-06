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

Facets GmshReader::read( const string& fname ) const
{
  string id("[GmshReader::read] ");
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
  if ( Facet::nodesCrd.size() > 0 )
  {
    throw( invalid_argument("Node coordinates is already initialized...") );
  }
  
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
    Vec3 point(x,y,z);
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

  Facets facetlist;
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
    newfacet.setNodes(nodenum);
    facetlist.add( newfacet );
  }
  infile.close();
  #ifdef GMSHREADER_DEBUG
    cerr << id << "Leaving read function...\n";
  #endif
  return facetlist;
}
