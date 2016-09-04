#include "point.h"
#include <cmath>

Vec3 Vec3::operator +(const Vec3 &rhs) const
{
  double x = this->x + rhs.x;
  double y = this->y + rhs.y;
  double z = this->z + rhs.z;
  Vec3 result(x,y,z);
  return result;
}
Vec3 Vec3::operator -(const Vec3 &rhs) const
{
  double x = this->x - rhs.x;
  double y = this->y - rhs.y;
  double z = this->z - rhs.z;
  Vec3 result(x,y,z);
  return result;
}

Vec3 Vec3::operator *(double scale) const
{
  double x = scale*this->x;
  double y = scale*this->y;
  double z = scale*this->z;
  Vec3 result(x,y,z);
  return result;
}

Vec3 Vec3::operator /(double scale) const
{
  double x = this->x/scale;
  double y = this->y/scale;
  double z = this->z/scale;
  Vec3 result(x,y,z);
  return result;
}

Vec3& Vec3::operator +=(const Vec3 &rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
  return *this;
}
Vec3& Vec3::operator -=(const Vec3 &rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
  return *this;
}
Vec3& Vec3::operator *=(double scale)
{
  this->x *= scale;
  this->y *= scale;
  this->z *= scale;
  return *this;
}
Vec3& Vec3::operator /=(double scale)
{
  this->x /= scale;
  this->y /= scale;
  this->z /= scale;
  return *this;
}

void Vec3::zeros()
{
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}

double Vec3::abs() const
{
  return sqrt( x*x+y*y+z*z );
}

Vec3 Vec3::cross( const Vec3& rhs ) const
{
  Vec3 result;
  result.setX( y*rhs.z - z*rhs.y );
  result.setY( z*rhs.x - x*rhs.z );
  result.setZ( x*rhs.y - y*rhs.x );
  return result;
}

double Vec3::dot( const Vec3& rhs ) const
{
  return x*rhs.x + y*rhs.y + z*rhs.z;
}
