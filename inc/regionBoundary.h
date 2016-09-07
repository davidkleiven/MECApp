#ifndef REGION_BOUNDARY_H
#define REGION_BOUNDARY_H
#include "materialProp.h"

/**
* @brief: Contains information of the material of either side of the boundary
*         As it is assumed that each region is contained in one file
*         the elements belonging to one region will have IDs between a minumum
*         value and a maximum value.
*/
class RegionBoundary
{
  public:
    enum class Domain_t {INCIDENT, SCATTERED};
    RegionBoundary();
    void setMatProp( std::complex<double> eps, std::complex<double> mu, Domain_t domain);
    void setMinElm( unsigned int elmIndx ) { minElm = elmIndx; };
    void setMaxElm( unsigned int elmIndx ) { maxElm = elmIndx; };
    std::complex<double> eps(Domain_t domain) const;
    std::complex<double> mu(Domain_t domain) const;
    unsigned int getMinElm() const {return minElm;};
    unsigned int getMaxElm() const {return maxElm;};
    unsigned int getUID() const { return UID; };
    bool operator <(const RegionBoundary &other) const;
  private:
    Material incidentMat;
    Material scatteredMat;
    unsigned int minElm{0};
    unsigned int maxElm{0};
    unsigned int UID;
    static unsigned int nextUID;
}; 
#endif
