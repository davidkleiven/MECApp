#ifndef FACET_H
#define FACET_H
#include <vector>
#include <cstdlib>
#include "point.h"

class Facet
{
  public:
    Facet(){};
    ~Facet();

    static std::vector<Vec3> nodesCrd;
    void setNodes( unsigned int newnodes[3] );
    const unsigned int* getNodes() const{return nodes;};
    Facet* addFacet( unsigned int newnodes[3] );
    Facet* next(){return _next;};
  private:
    unsigned int nodes[3];
    Facet* _next{NULL};
    bool isHead{true};
    bool isIlluminated{false};
};
#endif
