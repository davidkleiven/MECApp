#include "point.h"
#include <cmath>
#include <complex>

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

// Define allowed templates
template class Vec3<double>;
template class Vec3< complex<double> >;
