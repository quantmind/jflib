
#ifndef		__JFLIB_LAPACK_TRAITS_HPP__
#define		__JFLIB_LAPACK_TRAITS_HPP__

#include <jflib/jflib.hpp>
#include <boost/type_traits.hpp>

namespace jflib { namespace linalg { namespace lapack {

template<class T>
struct is_lapackfloat {static const bool value = false;};

template<> struct is_lapackfloat<float>  {static const bool value = true;};
template<> struct is_lapackfloat<double> {static const bool value = true;};

template<class M>
struct matrix_traits;

template<class M>
struct vector_traits;

template<class T>
struct basetraits {
	BOOST_STATIC_ASSERT(is_lapackfloat<T>::value);
};

}}}


#endif	//	__JFLIB_LAPACK_TRAITS_HPP__
