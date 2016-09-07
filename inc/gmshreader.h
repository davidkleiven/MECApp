#ifndef GMSH_READER_H
#define GMSH_READER_H
#include <string>
#include "facets.h"

class GmshReader
{
  public:
    GmshReader();
    void read( const std::string& fname, Facets& facets ) const;
    enum ElementType_t{LINE=1,TRIANGLE=2,SINGLE_POINT=15};
};
#endif
