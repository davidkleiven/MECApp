#ifndef FACET_H
#define FACET_H
#include <vector>
#include <cstdlib>
#include "point.h"

class Facet
{
  public:
    Facet();
    ~Facet();

    static std::vector<Vec3> nodesCrd;
    void setNodes( unsigned int newnodes[3] );
    void centroid( Vec3& result );
    const unsigned int* getNodes() const{return nodes;};
    double computeDistanceFromSource( const Vec3& sourcePosition );
    bool operator <( const Facet& rhs );
    double getDistanceFromSource() const { return _distanceFromSource;  };
    const Vec3& getNormal() { return *normalVector; };
    const Vec3& computeNormalVector();
  private:
    unsigned int nodes[3];
    bool isIlluminated{false};
    double _distanceFromSource{0.0};
    Vec3 *normalVector;
};
#endif
