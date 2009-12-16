/**
 * \brief Timeseries operation traits
 */

#ifndef __TIMESERIES_OPER_TRAITS_HPP_
#define __TIMESERIES_OPER_TRAITS_HPP_

#include <jflib/timeseries/structures.hpp>
#include <jflib/timeseries/traits/matrix.hpp>
#include <boost/numeric/ublas/symmetric.hpp>

// Boost numeric bindings
//#include <jflib/linalg/lapack/eigen.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/numeric/bindings/traits/ublas_vector.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/lapack/driver/gels.hpp>

namespace jflib { namespace timeseries {

namespace lapack = boost::numeric::bindings::lapack;

}}

namespace jflib { namespace timeseries { namespace traits {

template<class TS, unsigned D>
class oper_traits;

template<class TS>
struct oper_traits<TS,0u> {};

template<class T>
struct oper_traits_vector {
	typedef boost::numeric::ublas::vector<T>	type;
};
template<class T>
struct oper_traits_matrix {
	typedef boost::numeric::ublas::matrix<T>	type;
};
template<class T>
struct oper_traits_symmetric {
	typedef boost::numeric::ublas::symmetric_matrix<T>	type;
};
template<class T, unsigned D>
struct oper_traits_bounded_vector {
	typedef boost::numeric::ublas::bounded_array<T,D>		storage_type;
	typedef boost::numeric::ublas::vector<T,storage_type>	type;
	//typedef boost::numeric::ublas::bounded_vector<numtype,D>	type;
};




template<class Key, class T, class Tag, unsigned F>
class oper_traits<timeseries<Key,T,Tag,F,false>, 1u> {
public:
	typedef typename ts<Key,T,Tag>::type	tstype;
	typedef typename tstype::numtype		numtype;
	typedef numtype							type;

	static void init(const tstype& ts, type& v) {v = 0;}
};

template<class Key, class T, class Tag, unsigned F, unsigned D>
class oper_traits<timeseries<Key,T,Tag,F,false>, D> {
public:
	typedef typename ts<Key,T,Tag>::type							tstype;
	typedef typename tstype::numtype								numtype;
	typedef typename oper_traits_bounded_vector<numtype,D>::type	type;

	static void init(const tstype& ts, type& v) {
		v.resize(D,false);
		std::fill(v.begin(),v.end(),0);
	}
};


template<class TS>
class oper_traits<TS,1u> {
public:
	typedef TS												tstype;
	typedef typename tstype::numtype						numtype;
	typedef typename oper_traits_vector<numtype>::type		type;

	static void init(const tstype& ts, type& v) {
		v.resize(ts.series(),false);
		std::fill(v.begin(),v.end(),0);
	}
};

template<class TS, unsigned D>
class oper_traits {
public:
	typedef TS														tstype;
	typedef typename tstype::numtype								numtype;
	typedef typename oper_traits_vector<numtype>::type				vectype;
	typedef typename oper_traits_bounded_vector<vectype,D>::type	type;

	static void init(const tstype& ts, type& v) {
		vectype vec(ts.series(), 0);
		v.resize(D,false);
		std::fill(v.begin(),v.end(),vec);
	}
};


}}}


#endif	//	__TIMESERIES_OPER_TRAITS_HPP_


