#ifndef POINT_H
#define POINT_H
#include "complexConjVec.h"
#include <iostream>

template < class T >
class Vec3
{
public:
  Vec3(T x, T y, T z):x(x), y(y), z(z){};
  Vec3():x(0.0), y(0.0), z(0.0){};
  T getX() const {return x;};
  T getY() const {return y;};
  T getZ() const {return z;};
  void setX(T newX){x=newX;};
  void setY(T newY){y=newY;};
  void setZ(T newZ){z=newZ;};
  void zeros();

  Vec3<T> operator+(const Vec3<T>& rhs) const;

  Vec3<T> operator-(const Vec3<T>& rhs) const;

  Vec3<T> operator*(T scale) const;
  Vec3<T> operator/(T scale) const;
  Vec3<T>& operator+=(const Vec3<T>& rhs);
  Vec3<T>& operator-=(const Vec3<T>& rhs);
  Vec3<T>& operator*=(T scale);
  Vec3<T>& operator/=(T scale);

  double abs() const;

  Vec3<T> cross( const Vec3<T>& rhs ) const;

  T dot( const Vec3<T>& rhs ) const;

  void setImag( const Vec3<double> &imag );
  void conj();
private:
  T x;
  T y;
  T z;

  // complexConjVec.h: Does nothing in the case of real numbers
  ComplexConjVector<T> conjugate;
  ImagAccessor<T> imagaccess; 
};

template <class T>
std::ostream& operator << (std::ostream& out, const Vec3<T> &vec)
{
  out << "x: " << vec.getX() << " y: " << vec.getY() << " z: " << vec.getZ();
  return out;
};
#endif
