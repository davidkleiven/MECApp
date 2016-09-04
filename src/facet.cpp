#include "facet.h"
#include <iostream>

using namespace std;
vector<Vec3> Facet::nodesCrd;
Facet::Facet():normalVector( new Vec3() ){};

Facet::~Facet()
{
  delete normalVector;
}

void Facet::setNodes( unsigned int newnodes[3] )
{
  nodes[0] = newnodes[0]; 
  nodes[1] = newnodes[1]; 
  nodes[2] = newnodes[2]; 
  computeNormalVector();
}

void Facet::centroid( Vec3& result )
{
  result.zeros();
  for ( unsigned int i=0;i<3;i++ )
  {
    result += nodesCrd[ nodes[i] ];
  }
  result /= 3.0; 
}  

double Facet::computeDistanceFromSource( const Vec3& sourcePosition )
{
  Vec3 centroidVec;
  this->centroid( centroidVec );
  centroidVec -= sourcePosition;
  _distanceFromSource = centroidVec.abs();
  return _distanceFromSource; 
}

bool Facet::operator <(const Facet& rhs)
{
  return this->_distanceFromSource < rhs._distanceFromSource;
}

const Vec3& Facet::computeNormalVector()
{
  *normalVector = nodesCrd[nodes[0]].cross( nodesCrd[nodes[1]] );
  *normalVector /= normalVector->abs();
  return *normalVector;
} 
