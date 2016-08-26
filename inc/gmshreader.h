#ifndef GMSH_READER_H
#define GMSH_READER_H
#include <string>
#include "facet.h"

class GmshReader
{
  public:
    GmshReader(){};
    Facet* read( const std::string& fname ) const;
};
#endif
