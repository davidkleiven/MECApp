#ifndef FACET_H
#define FACET_H
#include <vector>
#include <cstdlib>
#include "point.h"
#include "equivalentCurrent.h"

class Facet
{
  public:
    Facet();
    Facet(const Facet& other);
    ~Facet();

    Facet& operator =(const Facet& other);
    static std::vector<Vec3<double> > nodesCrd;
    void setNodes( unsigned int newnodes[3] );
    const Vec3<double>& centroid();
    const unsigned int* getNodes() const{return nodes;};
    double computeDistanceFromSource( const Vec3<double>& sourcePosition );
    double computeDistanceFromSource();
    bool operator <( const Facet& rhs );
    double getDistanceFromSource() const { return _distanceFromSource;  };
    const Vec3<double>& getNormal() { return *normalVector; };
    const Vec3<double>& computeNormalVector();
    bool isBehindFacetPlane( const Vec3<double>& vec ) const;
    bool isInsidePyramid( const Vec3<double>& vec ) const;
    bool isBehindOther( const Facet& other ) const;
    void setIllumination( bool isIlumn ) { isIlluminated = isIlumn; };
    bool getIllumination() const { return isIlluminated; };
    const Vec3<double>& getSourcePosition() const { return _sourcePos; };
    const Vec3<double>& getNormalVector() const { return *normalVector; };
    EquivalentCurrent& getEquivalentCurrent(){return *current;};
  private:
    unsigned int *nodes;
    bool isIlluminated{true};
    double _distanceFromSource{0.0};
    Vec3<double> *normalVector;
    static Vec3<double> _sourcePos; // Hold the position of the source to verify the direction of the normal vector
    Vec3<double> *center;

    void swap( const Facet &other );
    EquivalentCurrent *current;
};
#endif
