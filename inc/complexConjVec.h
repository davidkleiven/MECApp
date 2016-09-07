#ifndef COMPLEX_CONJ_VEC_H
#define COMPLEX_CONJ_VEC_H

template <class T> class Vec3;

/**
* @brief Wrapper for computing complex conjugate
*/
template < class T >
class ComplexConjVector
{
public:
  Vec3<T>& compute( Vec3<T> &vec ) const;
};

template <>
class ComplexConjVector<double>
{
public:
  Vec3<double>& compute( Vec3<double> &vec ) const; // Do nothing
};


/**
* @brief Wrapper for setting imaginary part
*/
template <class T>
class ImagAccessor
{
public:
  void setImag( Vec3<T> &vec, const Vec3<double> &imag ) const;
};

template <>
class ImagAccessor<double>
{
public:
  void setImag( Vec3<double> &vec, const Vec3<double> &imag ) const; // Do nothing
};

#endif
