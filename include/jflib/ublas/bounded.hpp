
#ifndef		__UBLAS_BOUNDED_VECTOR_EXTENSIONS_OPER_HPP__
#define		__UBLAS_BOUNDED_VECTOR_EXTENSIONS_OPER_HPP__

#include <jflib/jflib.hpp>
#include <boost/numeric/ublas/vector.hpp>



namespace boost { namespace numeric { namespace ublas {

namespace impl {

template<class T, unsigned D, unsigned I>
struct bounded_assign_impl {
	static
	BOOST_UBLAS_INLINE
	void apply(bounded_vector<T,D>& vec, const T& v) {
		vec[I] = v;
		bounded_assign_impl<T,D,I-1>::apply(vec,v);
	}
};

template<class T, unsigned D>
struct bounded_assign_impl<T,D,0u> {
	static
	BOOST_UBLAS_INLINE
	void apply(bounded_vector<T,D>& vec, const T& v) {
		vec[0] = v;
	}
};


template<class T, unsigned D>
struct bounded_assign {
	static
	BOOST_UBLAS_INLINE
	void apply(bounded_vector<T,D>& vec, const T& v) {
		impl::bounded_assign_impl<T,D,D-1u>::apply(vec,v);
	}
};

template<class T>
struct bounded_assign<T,0u> {
	static
	BOOST_UBLAS_INLINE
	void apply(bounded_vector<T,0u>& vec, const T& v) {}
};

}

template<class T, unsigned D>
BOOST_UBLAS_INLINE
void assign_bound_array(bounded_vector<T,D>& vec, const T& v) {
	impl::bounded_assign<T,D>::apply(vec,v);
}


}}}


#endif	//	__UBLAS_BOUNDED_VECTOR_EXTENSIONS_OPER_HPP__
