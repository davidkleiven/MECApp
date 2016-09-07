#ifndef GMSH_READER_H
#define GMSH_READER_H
#include <string>
#include "facets.h"
#include <complex>
#include <jsoncpp/json/reader.h>

class GmshReader
{
  public:
    GmshReader();
    void readMesh( const std::string& fname, Facets& facets ) const;
    void read( const std::string& jsonfile, Facets& facets );
    enum ElementType_t{LINE=1,TRIANGLE=2,SINGLE_POINT=15};

  private:
    void readMatProp( const std::string& key, std::complex<double> &matprop ) const;
    Json::Value data;
};
#endif
