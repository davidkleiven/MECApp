#ifndef FACETS_H
#define FACETS_H
#include <list>
#include "facet.h"
#include "point.h"

class Facets
{
  public:
    Facets();
    ~Facets();
    void add( Facet* newfacet );
    unsigned int size() { return facets->size(); };
  private:
    std::list<Facet*> *facets;
};
#endif
