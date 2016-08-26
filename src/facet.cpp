#include "facet.h"

using namespace std;

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
  return newfacet;
} 
