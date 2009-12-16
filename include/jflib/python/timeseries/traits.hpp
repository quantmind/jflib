
#ifndef		__PYTHON_TIMESERIES_TRAITS_HPP__
#define		__PYTHON_TIMESERIES_TRAITS_HPP__


#include <jflib/timeseries/all.hpp>
#include <jflib/datetime/daycount.hpp>
#include <jflib/timeseries/tsoperators.hpp>
#ifdef	__JFLIB_UBLAS_NUMPY_CONVERSION__
#include <jflib/python/numpy/numpy_matrix.hpp>
#endif




namespace jflib { namespace timeseries {

template<class Key>
struct daycountertype {
	typedef Act365<Key>	type;
};



/**
 * \brief Specialization of tsvmapbase
 * The masked vector is given by ublas vectors
 */
struct ublas_tsvmap: tsvmapbase {
	typedef ublas_tsvmap	self;

	template<class Key, class T>
	struct container {
		typedef T													numtype;
		typedef boost::numeric::ublas::vector<numtype>				data_type;
		typedef boost::numeric::ublas::vector<int>					mask_type;
		typedef maskedvector<data_type,mask_type,family>			vtype;
		typedef jflib::templates::associative<Key,vtype,0>			super;
		typedef	timeseries<Key,numtype,self,family,multipleseries>	type;
	};
};


// ublas timeserie matrix tag based on boost::numeric::ublas matrix structure
struct ublas_tsmatrix: tsmatrix_base {
	typedef ublas_tsmatrix	self;

	template<class Key, class T>
	struct container {
		typedef T														numtype;
		typedef boost::numeric::ublas::matrix<numtype>					data_type;
		typedef boost::numeric::ublas::matrix<int>						mask_type;
		typedef Nil														super;
		typedef timeseries<Key,numtype,self,family,multipleseries>		type;
	};
};


#ifdef	__JFLIB_UBLAS_NUMPY_CONVERSION__

// define the timeseries matrix based on ublas-numpy
struct tsnumpy: tsmatrix_base  {
	typedef ublas_tsmatrix	self;

	template<class Key, class T>
	struct container  {
		typedef T														numtype;
		typedef jflib::python::numpy::numpy_matrix<numtype>				data_type;
		typedef jflib::python::numpy::numpy_matrix<int>					mask_type;
		typedef Nil														super;
		typedef timeseries<Key,numtype,self,family,multipleseries>		type;
	};
};

namespace traits {

template<class T>
struct matrix_traits<jflib::python::numpy::numpy_matrix<T> > {
	typedef jflib::python::numpy::numpy_matrix<T>				type;
	typedef boost::numeric::ublas::matrix_reference<type>		reference_type;
	typedef boost::numeric::ublas::vector<T>					vector_type;
	template<class E>
	struct expressions {
		typedef boost::numeric::ublas::matrix_range<E>			mrange;
		typedef boost::numeric::ublas::matrix_vector_range<E>	vrange;
	};
};

}
#endif	//	__JFLIB_UBLAS_NUMPY_CONVERSION__



}}


#endif	//	__PYTHON_TIMESERIES_TRAITS_HPP__
