#ifndef POINT_H
#define POINT_H

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

  template< class S >
  Vec3<T> operator+(const Vec3<S>& rhs) const;

  template < class S >
  Vec3<T> operator-(const Vec3<S>& rhs) const;

  Vec3<T> operator*(T scale) const;
  Vec3<T> operator/(T scale) const;
  Vec3<T>& operator+=(const Vec3<T>& rhs);
  Vec3<T>& operator-=(const Vec3<T>& rhs);
  Vec3<T>& operator*=(T scale);
  Vec3<T>& operator/=(T scale);

  double abs() const;

  template <class S>
  Vec3<T> cross( const Vec3<S>& rhs ) const;

  template <class S>
  T dot( const Vec3<S>& rhs ) const;
private:
  T x;
  T y;
  T z;
};

#include "pointTemplateMembers.h"
#endif
