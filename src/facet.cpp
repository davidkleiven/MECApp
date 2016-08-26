#include "facet.h"

using namespace std;

Facet::~Facet()
{
  if ( next != NULL )
  {
    delete next;
  }
}

Facet* Facet::addFacet( unsigned int nodenum[3] )
{
  Facet* newfacet = new Facet();
  newfacet->setNodes(nodenum);
  this->isHead = false;
  newfacet->next = this;
  return newfacet;
} 
