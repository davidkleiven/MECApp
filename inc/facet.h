#ifndef FACET_H
#define FACET_H
#include <vector>
#include <cstdlib>
#include "point.h"

class Facet
{
  public:
    Facet();
    Facet(const Facet& other);
    ~Facet();

    Facet& operator =(const Facet& other);
    static std::vector<Vec3> nodesCrd;
    void setNodes( unsigned int newnodes[3] );
    const Vec3& centroid();
    const unsigned int* getNodes() const{return nodes;};
    double computeDistanceFromSource( const Vec3& sourcePosition );
    double computeDistanceFromSource();
    bool operator <( const Facet& rhs );
    double getDistanceFromSource() const { return _distanceFromSource;  };
    const Vec3& getNormal() { return *normalVector; };
    const Vec3& computeNormalVector();
    bool isBehindFacetPlane( const Vec3& vec ) const;
    bool isInsidePyramid( const Vec3& vec ) const;
    bool isHidden( const Facet& other ) const;
    void setIllumination( bool isIlumn ) { isIlluminated = isIlumn; };
  private:
    unsigned int nodes[3];
    bool isIlluminated{false};
    double _distanceFromSource{0.0};
    Vec3 *normalVector;
    static Vec3 _sourcePos; // Hold the position of the source to verify the direction of the normal vector
    Vec3 *center;

    void swap( const Facet &other );
};
#endif
