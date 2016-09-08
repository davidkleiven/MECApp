#ifndef FACETS_H
#define FACETS_H
#include <vector>
#include <string>
#include "facet.h"
#include "point.h"
#include <set>
#include "regionBoundary.h"
#include "fresnel.h"
#include "farField.h"

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
    void addRegion( RegionBoundary &boundary );
    void computeEquivalentCurrent(const Vec3<double> &E_inc, const Vec3<double> &waveVec);
    double computeScatteredPower( const Vec3<double> &point );
  private:
    std::vector<Facet> *facets;
    std::set<RegionBoundary> *boundaries;
    bool hasComputedDistanceFromSource{false};
    Fresnel *fresnel;
    FarField *farField;

    // Store a pointer to these for convenience (this class does not own them)
    const Vec3<double> *E_inc_pointer;
    const Vec3<double> *waveVector_pointer;

    void swap( const Facets &other );
    bool hasComputedEqCurrents{false};
};
#endif
