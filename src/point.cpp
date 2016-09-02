#include "point.h"

Vec3 Vec3::operator +(const Vec3 &rhs)
{
  double x = this->x + rhs.x;
  double y = this->y + rhs.y;
  double z = this->z + rhs.z;
  Vec3 result(x,y,z);
  return result;
}
Vec3 Vec3::operator -(const Vec3 &rhs)
{
  double x = this->x - rhs.x;
  double y = this->y - rhs.y;
  double z = this->z - rhs.z;
  Vec3 result(x,y,z);
  return result;
}

Vec3 Vec3::operator *(double scale)
{
  double x = scale*this->x;
  double y = scale*this->y;
  double z = scale*this->z;
  Vec3 result(x,y,z);
  return result;
}

Vec3 Vec3::operator /(double scale)
{
  double x = this->x/scale;
  double y = this->y/scale;
  double z = this->z/scale;
  Vec3 result(x,y,z);
  return result;
}
