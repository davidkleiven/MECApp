#ifndef FACETS_H
#define FACETS_H
#include <vector>
#include <string>
#include "facet.h"
#include "point.h"
#include <set>
#include "regionBoundary.h"

class Facets
{
  public:
    Facets();
    Facets(const Facets &other);
    Facets& operator =(const Facets &other);
    ~Facets();
    void add( const Facet &newfacet );
    unsigned int size() const { return facets->size(); };
    void computeDistanceFromSource( const Vec3<double> &sourcePos );
    void sortByDistanceFromSource();
    Facet& getFacet( unsigned int indx ) const { return (*facets)[indx]; };
    void saveIlluminationVTK( const std::string &fname ) const;
    void illuminate();
  private:
    std::vector<Facet> *facets;
    std::set<RegionBoundary> *boundaries;
    bool hasComputedDistanceFromSource{false};

    void swap( const Facets &other );
};
#endif
