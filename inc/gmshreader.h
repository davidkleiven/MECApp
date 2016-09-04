#ifndef GMSH_READER_H
#define GMSH_READER_H
#include <string>
#include "facets.h"

class GmshReader
{
  public:
    GmshReader();
    Facets read( const std::string& fname ) const;
};
#endif
