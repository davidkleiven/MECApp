#include "facets.h"

using namespace std;
Facets::Facets(): facets(new list<Facet*>()){};
Facets::~Facets()
{
  for ( list<Facet*>::iterator it=facets->begin(); it != facets->end(); ++it )
  {
    delete *it;
  }
  delete facets;
}

void Facets::add( Facet* facet )
{
  facets->push_front( facet );
}

