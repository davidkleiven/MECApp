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
  private:
    static std::vector<Point> nodesCrd;
    static bool nodesAreInitialized;
    unsigned int nodes[3];
    Facet* next{NULL};
    bool isHead{false};
};
#endif
