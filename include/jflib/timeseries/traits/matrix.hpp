
#ifndef __TIMESERIES_MATRIX_TRAITS_HPP__
#define __TIMESERIES_MATRIX_TRAITS_HPP__

#include <jflib/timeseries/traits/base.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

namespace jflib { namespace timeseries { namespace traits {


typedef boost::numeric::ublas::range	range;

template<class M>
struct matrix_traits;




template<class T, class L, class A>
struct matrix_traits<boost::numeric::ublas::matrix<T,L,A> > {
	typedef boost::numeric::ublas::matrix<T,L,A>				type;
	typedef boost::numeric::ublas::matrix_reference<type>		reference_type;
	typedef boost::numeric::ublas::vector<T>					vector_type;
	template<class E>
	struct expressions {
		typedef boost::numeric::ublas::matrix_range<E>			mrange;
		typedef boost::numeric::ublas::matrix_vector_range<E>	vrange;
		typedef boost::numeric::ublas::matrix_column<E>			mcolumn;
	};
};



}}}



#endif	//	__TIMESERIES_MATRIX_TRAITS_HPP__
