#ifndef POINT_TEMPLATE_MEMBERS_H
#define POINT_TEMPLATE_MEMBERS_H

template <class T> template <class S>
Vec3<T> Vec3<T>::cross( const Vec3<S>& rhs ) const
{
  Vec3<T> result;
  result.setX( y*rhs.z - z*rhs.y );
  result.setY( z*rhs.x - x*rhs.z );
  result.setZ( x*rhs.y - y*rhs.x );
  return result;
}

template <class T> template <class S>
T Vec3<T>::dot( const Vec3<S>& rhs ) const
{
  return x*rhs.x + y*rhs.y + z*rhs.z;
}


template <class T> template<class S>
Vec3<T> Vec3<T>::operator +(const Vec3<S> &rhs) const
{
  T x = this->x + rhs.x;
  T y = this->y + rhs.y;
  T z = this->z + rhs.z;
  Vec3<T> result(x,y,z);
  return result;
}

template <class T> template <class S>
Vec3<T> Vec3<T>::operator -(const Vec3<S> &rhs) const
{
  T x = this->x - rhs.x;
  T y = this->y - rhs.y;
  T z = this->z - rhs.z;
  Vec3<T> result(x,y,z);
  return result;
}

#endif
