#ifndef FACETS_H
#define FACETS_H
#include <vector>
#include "facet.h"
#include "point.h"

class Facets
{
  public:
    Facets();
    ~Facets();
    void add( Facet newfacet );
    unsigned int size() { return facets->size(); };
    void computeDistanceFromSource( const Vec3 &sourcePos );
    void sortByDistanceFromSource();
    Facet& getFacet( unsigned int indx ) const { return (*facets)[indx]; };
  private:
    std::vector<Facet> *facets;
    bool hasComputedDistanceFromSource{false};
};
#endif
