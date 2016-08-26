#include "gmshreader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;

Facet* GmshReader::read( const string& fname ) const
{
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
  while ( getline(infile, line) )
  {
    if ( line.find(nodestart) != string::npos )
    {
      breakOnNext = true;
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
  
  Point point;
  unsigned int nodeNumber;
  while( getline(infile, line) )
  {
    if ( line.find(nodeend) != string::npos )
    {
      break;
    }
    stringstream ss;
    ss << line;
    ss >> nodeNumber;
    ss >> point.x;
    ss >> point.y;
    ss >> point.z;
    Facet::nodesCrd.push_back(point);
  }

  // Read until start elements is found
  breakOnNext = false;
  while ( getline(infile,line) )
  {
    if ( line.find(elementstart) != string::npos )
    {
      breakOnNext=true;
    } 
    if ( breakOnNext )
    {
      break;
    }
  }

  unsigned int elementType;
  unsigned int numberOfTags;
  bool isFirst = true;

  Facet* first = new Facet();
  while ( getline(infile,line) )
  {
    if ( line.find(elementend) != string::npos )
    {
      break;
    }
    stringstream ss;
    ss << line;
    ss >> elementType;
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
    if ( isFirst )
    {
      first->setNodes(nodenum);
      isFirst = false;
    }
    else
    {
      first = first->addFacet( nodenum );
    }
  }
  infile.close();
  return first;
}
