#ifndef POINT_H
#define POINT_H

class Vec3
{
public:
  Vec3(double x, double y, double z):x(x), y(y), z(z){};
  Vec3():x(0.0), y(0.0), z(0.0){};
  double getX() const {return x;};
  double getY() const {return y;};
  double getZ() const {return z;};
  void setX(double newX){x=newX;};
  void setY(double newY){y=newY;};
  void setZ(double newZ){z=newZ;};
  void zeros();
  Vec3 operator+(const Vec3& rhs);
  Vec3 operator-(const Vec3& rhs);
  Vec3 operator*(double scale);
  Vec3 operator/(double scale);
  Vec3& operator+=(const Vec3& rhs);
  Vec3& operator-=(const Vec3& rhs);
  Vec3& operator*=(double scale);
  Vec3& operator/=(double scale);
private:
  double x;
  double y;
  double z;
};
#endif
