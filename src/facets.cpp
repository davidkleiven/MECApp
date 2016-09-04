#include "facets.h"
#include <stdexcept>
#include <algorithm>

using namespace std;
Facets::Facets(): facets(new vector<Facet>()){};
Facets::Facets( const Facets &other ): facets(new vector<Facet>())
{
  this->swap(other);
}

Facets& Facets::operator =( const Facets &other )
{
  this->swap(other);
  return *this;
}

Facets::~Facets()
{
  delete facets;
}

void Facets::add( Facet facet )
{
  facets->push_back( facet );
}

void Facets::computeDistanceFromSource( const Vec3 &sourcePos )
{
  for ( unsigned int i=0;i<facets->size();i++ )
  {
    (*facets)[i].computeDistanceFromSource( sourcePos );
  }
  hasComputedDistanceFromSource = true;
  reverse( facets->begin(), facets->end() ); // Swap to descending
} 

void Facets::sortByDistanceFromSource()
{
  if ( !hasComputedDistanceFromSource )
  {
    throw (invalid_argument("You have to call computeDistanceFromSource before any call to sortByDistanceFromSource!") );
  }
  sort( facets->begin(), facets->end() );
}


void Facets::swap( const Facets& other )
{
  *facets = *other.facets;
  hasComputedDistanceFromSource = other.hasComputedDistanceFromSource;
} 
