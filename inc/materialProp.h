#ifndef MATERIAL_PROP_H
#define MATERIAL_PROP_H
#include <complex>

struct Material
{
  std::complex<double> eps; // Relative dielectric function (for vacuum: 1.0)
  std::complex<double> mu;  // Relative permability (for vacuum: 1.0)
};
#endif
