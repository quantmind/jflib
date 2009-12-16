
#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_SYMMETRIC_ADAPTOR_H
#define BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_SYMMETRIC_ADAPTOR_H

#include <boost/numeric/binding/lapack/driver/syev.hpp>
#include <boost/numeric/binding/traits/ublas_symmetric.hpp>



namespace boost { namespace numeric { namespace ublas {

/*
template<typename Matrix>
symmetric_adaptor<M,ublas::upper> upper(Matrix& m) {
	return symmetric_adaptor<Matrix, upper>(m);
}

template<typename Matrix>
symmetric_adaptor<M,ublas::lower> lower(Matrix& m) {
	return symmetric_adaptor<Matrix, lower>(m);
}
*/


}}}



namespace boost { namespace numeric { namespace bindings { namespace lapack {


// template function to call syev, default workspace type
template< typename MatrixA, typename VectorW >
inline integer_t syev( char const jobz, MatrixA&& a, VectorW& w ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    syev_impl< value_type >::invoke( jobz, a, w, info, optimal_workspace() );
    return info;
}


}}}}

#endif	//	BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_SYMMETRIC_ADAPTOR_H

