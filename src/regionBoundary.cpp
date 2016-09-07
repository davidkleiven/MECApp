#include "regionBoundary.h"
unsigned int nextUID = 0;

using namespace std;

unsigned int RegionBoundary::nextUID = 0;
RegionBoundary::RegionBoundary():UID(nextUID++){};
void RegionBoundary::setMatProp( complex<double> eps, complex<double> mu, Domain_t domain)
{
  switch ( domain )
  {
    case Domain_t::INCIDENT:
      incidentMat.eps = eps;
      incidentMat.mu = mu;
      break;
    case Domain_t::SCATTERED:
      scatteredMat.eps = eps;
      scatteredMat.mu = mu;
      break;
  }
}

complex<double> RegionBoundary::eps( Domain_t domain ) const
{
  switch (domain)
  {
    case Domain_t::INCIDENT:
      return incidentMat.eps;
    case Domain_t::SCATTERED:
      return scatteredMat.eps;
  }
}
    
complex<double> RegionBoundary::mu( Domain_t domain ) const
{
  switch (domain)
  {
    case Domain_t::INCIDENT:
      return incidentMat.mu;
    case Domain_t::SCATTERED:
      return scatteredMat.mu;
  }
}

bool RegionBoundary::operator <(const RegionBoundary &other) const
{
  return minElm < other.minElm;
}

const Material& RegionBoundary::getMat( Domain_t domain ) const
{
  switch (domain)
  {
    case Domain_t::INCIDENT:
      return incidentMat;
    case Domain_t::SCATTERED:
      return scatteredMat;
  }
}

