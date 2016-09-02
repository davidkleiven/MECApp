#include "facet.h"

using namespace std;
vector<Vec3> Facet::nodesCrd;

Facet::~Facet()
{
  if ( _next != NULL )
  {
    delete _next;
  }
}

Facet* Facet::addFacet( unsigned int nodenum[3] )
{
  Facet* newfacet = new Facet();
  newfacet->setNodes(nodenum);
  this->isHead = false;
  newfacet->_next = this;
  this->_prev = newfacet;
  return newfacet;
} 

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
