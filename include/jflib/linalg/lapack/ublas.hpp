
#ifndef		__JFLIB_LAPACK_UBLAS_TRAITS_HPP__
#define		__JFLIB_LAPACK_UBLAS_TRAITS_HPP__

#include <jflib/linalg/lapack/traits.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>


namespace jflib { namespace linalg { namespace lapack {


template<class T, class A>
struct matrix_traits<boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major, A> >:
	basetraits<T> {
	typedef boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major, A>	matrix_type;
	typedef typename matrix_type::value_type											value_type;

	static value_type* data(matrix_type& m) {return m.data().begin();}
};

template<class T, class A>
struct vector_traits<boost::numeric::ublas::vector<T, A> >:
	basetraits<T> {
	typedef boost::numeric::ublas::vector<T, A>		vector_type;
	typedef typename vector_type::value_type		value_type;

	static value_type* data(vector_type& m) {return m.data().begin();}
};

template<class T, class A>
struct matrix_traits<boost::numeric::ublas::diagonal_matrix<T, A> >:
	basetraits<T> {
	typedef boost::numeric::ublas::diagonal_matrix<T, A>	matrix_type;
	typedef typename matrix_type::value_type				value_type;

	static value_type* data(matrix_type& m) {return m.data().begin();}
};

}}}


#endif	//	__JFLIB_LAPACK_UBLAS_TRAITS_HPP__
