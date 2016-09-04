#include "facet.h"
#include <iostream>

using namespace std;
vector<Vec3> Facet::nodesCrd;

void Facet::setNodes( unsigned int newnodes[3] )
{
  nodes[0] = newnodes[0]; 
  nodes[1] = newnodes[1]; 
  nodes[2] = newnodes[2]; 
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
