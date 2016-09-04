#include "facet.h"
#include <iostream>

using namespace std;
vector<Vec3> Facet::nodesCrd;
Vec3 Facet::_sourcePos(0.0,0.0,0.0);

Facet::Facet():normalVector( new Vec3() ), center( new Vec3() ){};
Facet::Facet(const Facet &other):normalVector(new Vec3()), center( new Vec3() )
{
  this->swap(other);
}

Facet& Facet::operator =(const Facet &other)
{
  swap(other);
  return *this;
}

void Facet::swap( const Facet &other )
{
  *normalVector = *other.normalVector;
  *center = *other.center;
  for ( unsigned int i=0;i<3;i++)
  {
    nodes[i] = other.nodes[i];
  }
  isIlluminated = other.isIlluminated;
  _distanceFromSource = other._distanceFromSource;   
}

Facet::~Facet()
{
  delete normalVector;
  delete center;
}

void Facet::setNodes( unsigned int newnodes[3] )
{
  nodes[0] = newnodes[0]; 
  nodes[1] = newnodes[1]; 
  nodes[2] = newnodes[2]; 
  computeNormalVector();
  centroid();
}

const Vec3& Facet::centroid()
{
  center->zeros();
  for ( unsigned int i=0;i<3;i++ )
  {
    *center += nodesCrd[ nodes[i] ];
  }
  *center /= 3.0; 
  return *center;
}  

double Facet::computeDistanceFromSource( const Vec3& sourcePosition )
{
  _sourcePos = sourcePosition;
  Vec3 centroidVec = centroid();
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

bool Facet::isBehindFacetPlane( const Vec3& vec ) const
{
  Vec3 sourceDir = *center - _sourcePos;
  double sign = sourceDir.dot( *normalVector ) > 0.0 ? -1.0:1.0;
  return sign*normalVector->dot( vec - *center ) < 0.0; 
}

