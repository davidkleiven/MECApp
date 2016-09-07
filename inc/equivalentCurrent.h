#ifndef EQUIVALENT_CURRENT_H
#define EQUIVALENT_CURRENT_H
#include "point.h"
#include <complex>

struct EquivalentCurrent
{
  Vec3< std::complex<double> > electric;
  Vec3< std::complex<double> > magnetic;
};
#endif 
