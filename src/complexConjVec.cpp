#include "complexConjVec.h"
#include "point.h"
#include <complex>

using namespace std;
template < class T >
Vec3<T>& ComplexConjVector<T>::compute( Vec3<T> &vec ) const
{
  vec.setX( conj(vec.getX()) );
  vec.setY( conj(vec.getY()) );
  vec.setZ( conj(vec.getZ()) );
  return vec;
};

//template <>
Vec3<double>& ComplexConjVector<double>::compute( Vec3<double> &vec ) const
{
  return vec;
}


template <class T>
void ImagAccessor<T>::setImag( Vec3<T> &vec, const Vec3<double> &imag ) const
{
  complex<double> x = vec.getX();
  x.imag( imag.getX() );
  vec.setX(x);
  
  complex<double> y = vec.getY();
  y.imag( imag.getY() );
  vec.setY(y);

  complex<double > z = vec.getZ();
  z.imag( imag.getZ() );
  vec.setZ(z);
}  

//template <>
void ImagAccessor<double>::setImag( Vec3<double> &vec, const Vec3<double> &imag ) const{};

// Explicit instanciation
template class ComplexConjVector<double>;
template class ComplexConjVector< complex<double> >;
template class ImagAccessor<double>;
template class ImagAccessor< complex<double> >;
