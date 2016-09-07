#include "point.h"
#include <cmath>
#include <complex>
#include "complexConjVec.h"

using namespace std;
template <class T>
Vec3<T> Vec3<T>::operator *(T scale) const
{
  T x = scale*this->x;
  T y = scale*this->y;
  T z = scale*this->z;
  Vec3<T> result(x,y,z);
  return result;
}

template <class T>
Vec3<T> Vec3<T>::operator /(T scale) const
{
  T x = this->x/scale;
  T y = this->y/scale;
  T z = this->z/scale;
  Vec3<T> result(x,y,z);
  return result;
}

template <class T>
Vec3<T>& Vec3<T>::operator +=(const Vec3<T> &rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
  return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator -=(const Vec3<T> &rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
  return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator *=(T scale)
{
  this->x *= scale;
  this->y *= scale;
  this->z *= scale;
  return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator /=(T scale)
{
  this->x /= scale;
  this->y /= scale;
  this->z /= scale;
  return *this;
}

template <class T>
void Vec3<T>::zeros()
{
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}

template <class T>
double Vec3<T>::abs() const
{
  return sqrt( std::abs(x)*std::abs(x)+std::abs(y)*std::abs(y)+std::abs(z)*std::abs(z) );
}

template <class T>
Vec3<T> Vec3<T>::cross( const Vec3<T>& rhs ) const
{
  Vec3<T> result;
  result.setX( y*rhs.z - z*rhs.y );
  result.setY( z*rhs.x - x*rhs.z );
  result.setZ( x*rhs.y - y*rhs.x );
  return result;
}

template <class T>
T Vec3<T>::dot( const Vec3<T>& rhs ) const
{
  return x*rhs.x + y*rhs.y + z*rhs.z;
}


template <class T>
Vec3<T> Vec3<T>::operator +(const Vec3<T> &rhs) const
{
  T x = this->x + rhs.x;
  T y = this->y + rhs.y;
  T z = this->z + rhs.z;
  Vec3<T> result(x,y,z);
  return result;
}

template <class T>
Vec3<T> Vec3<T>::operator -(const Vec3<T> &rhs) const
{
  T x = this->x - rhs.x;
  T y = this->y - rhs.y;
  T z = this->z - rhs.z;
  Vec3<T> result(x,y,z);
  return result;
}

template <class T>
void Vec3<T>::setImag( const Vec3<double>& imag )
{
  imagaccess.setImag( *this, imag );
}

template <class T>
void Vec3<T>::conj()
{
  conjugate.compute(*this);
}
// Define allowed templates
template class Vec3<double>;
template class Vec3< complex<double> >;
