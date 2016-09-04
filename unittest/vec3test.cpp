#include <boost/test/unit_test.hpp>
#include "point.h"
#include <string>
#include <cmath>
using namespace std;

BOOST_AUTO_TEST_SUITE( vec3 )
BOOST_AUTO_TEST_CASE( add )
{
  double x1 = 1.0;
  double y1 = -1.4;
  double z1 = 3.2;
  double x2 = 10.0;
  double y2 = -21.3;
  double z2 = 1.2;
  Vec3 v1(x1,y1,z1);
  Vec3 v2(x2,y2,z2);
  Vec3 sum = v1+v2;
  BOOST_CHECK_CLOSE(sum.getX(), 11.0, 0.1f);
  BOOST_CHECK_CLOSE(sum.getY(), -22.7, 0.1f);
  BOOST_CHECK_CLOSE(sum.getZ(), 4.4, 0.1f);
}
BOOST_AUTO_TEST_CASE( addEqual )
{
  double x1 = 1.0;
  double y1 = -1.4;
  double z1 = 3.2;
  double x2 = 10.0;
  double y2 = -21.3;
  double z2 = 1.2;
  Vec3 v1(x1,y1,z1);
  Vec3 v2(x2,y2,z2);
  v1 += v2;
  BOOST_CHECK_CLOSE(v1.getX(), 11.0, 0.1f);
  BOOST_CHECK_CLOSE(v1.getY(), -22.7, 0.1f);
  BOOST_CHECK_CLOSE(v1.getZ(), 4.4, 0.1f);
}

BOOST_AUTO_TEST_CASE( subtract )
{
  double x1 = 1.0;
  double y1 = -1.4;
  double z1 = 3.2;
  double x2 = 10.0;
  double y2 = -21.3;
  double z2 = 1.2;
  Vec3 v1(x1,y1,z1);
  Vec3 v2(x2,y2,z2);
  Vec3 sum = v1-v2;
  BOOST_CHECK_CLOSE(sum.getX(), -9.0, 0.1f);
  BOOST_CHECK_CLOSE(sum.getY(), 19.9, 0.1f);
  BOOST_CHECK_CLOSE(sum.getZ(), 2.0, 0.1f);
}

BOOST_AUTO_TEST_CASE( subtractEqual )
{
  double x1 = 1.0;
  double y1 = -1.4;
  double z1 = 3.2;
  double x2 = 10.0;
  double y2 = -21.3;
  double z2 = 1.2;
  Vec3 v1(x1,y1,z1);
  Vec3 v2(x2,y2,z2);
  v1 -= v2;
  BOOST_CHECK_CLOSE(v1.getX(), -9.0, 0.1f);
  BOOST_CHECK_CLOSE(v1.getY(), 19.9, 0.1f);
  BOOST_CHECK_CLOSE(v1.getZ(), 2.0, 0.1f);
}

BOOST_AUTO_TEST_CASE( multiplyWithScalar )
{
  double x1 = 2.0;
  double y1 = 3.0;
  double z1 = 4.0;
  Vec3 vec(x1,y1,z1);
  Vec3 vec2 = vec*4.0;
  BOOST_CHECK_CLOSE( vec2.getX(), 8.0, 0.1f);
  BOOST_CHECK_CLOSE( vec2.getY(), 12.0, 0.1f);
  BOOST_CHECK_CLOSE( vec2.getZ(), 16.0, 0.1f);
}

BOOST_AUTO_TEST_CASE( multiplyWithScalarEqual )
{
  double x1 = 2.0;
  double y1 = 3.0;
  double z1 = 4.0;
  Vec3 vec(x1,y1,z1);
  vec *= 4.0;
  BOOST_CHECK_CLOSE( vec.getX(), 8.0, 0.1f);
  BOOST_CHECK_CLOSE( vec.getY(), 12.0, 0.1f);
  BOOST_CHECK_CLOSE( vec.getZ(), 16.0, 0.1f);
}

BOOST_AUTO_TEST_CASE( divideByScalar )
{
  double x1 = 2.0;
  double y1 = 3.0;
  double z1 = 4.0;
  Vec3 vec(x1,y1,z1);
  Vec3 vec2 = vec/4.0;
  BOOST_CHECK_CLOSE( vec2.getX(), 0.5, 0.1f);
  BOOST_CHECK_CLOSE( vec2.getY(), 0.75, 0.1f);
  BOOST_CHECK_CLOSE( vec2.getZ(), 1.0, 0.1f);
}
  
BOOST_AUTO_TEST_CASE( divideByScalarEqual )
{
  double x1 = 2.0;
  double y1 = 3.0;
  double z1 = 4.0;
  Vec3 vec(x1,y1,z1);
  vec /= 4.0;
  BOOST_CHECK_CLOSE( vec.getX(), 0.5, 0.1f);
  BOOST_CHECK_CLOSE( vec.getY(), 0.75, 0.1f);
  BOOST_CHECK_CLOSE( vec.getZ(), 1.0, 0.1f);
}
BOOST_AUTO_TEST_CASE( absVal )
{
  Vec3 vec(1.0, 2.0, 3.0);
  double expected = sqrt( 1.0+4.0+9.0 );
  BOOST_CHECK_CLOSE( expected, vec.abs(), 0.1f );
}
BOOST_AUTO_TEST_CASE( cross )
{
  Vec3 vec(1.0,2.0,3.0);
  Vec3 rhs(-1.0, 3.0,-2.0);
  Vec3 result = vec.cross(rhs);
  BOOST_CHECK_CLOSE( result.getX(), -13.0, 0.1f );
  BOOST_CHECK_CLOSE( result.getY(), -1.0, 0.1f );
  BOOST_CHECK_CLOSE( result.getZ(), 5.0, 0.1f );
}
BOOST_AUTO_TEST_SUITE_END()
