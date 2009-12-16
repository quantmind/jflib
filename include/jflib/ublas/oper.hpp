
#ifndef		__UBLAS_JFLIB_EXTENSIONS_OPER_HPP__
#define		__UBLAS_JFLIB_EXTENSIONS_OPER_HPP__

#include <jflib/jflib.hpp>
#include <boost/numeric/ublas/vector.hpp>



namespace boost { namespace numeric { namespace ublas {

/*
 * \brief Define a new scalar operation which calculate square root of a number
 *
 */
template<class T>
struct scalar_sqrt: public scalar_unary_functor<T> {
	typedef typename scalar_unary_functor<T>::argument_type		argument_type;
    typedef typename scalar_unary_functor<T>::result_type		result_type;

    static BOOST_UBLAS_INLINE result_type apply(argument_type t) {
		return std::sqrt(t);
    }
};

/*
 * \brief Define a new scalar operation which calculate the log of the ratio of two numbers
 *
 */
template<class T1, class T2>
struct scalar_logratio: public scalar_binary_functor<T1, T2> {
	typedef typename scalar_binary_functor<T1, T2>::argument1_type 	argument1_type;
    typedef typename scalar_binary_functor<T1, T2>::argument2_type 	argument2_type;
    typedef typename scalar_binary_functor<T1, T2>::result_type 	result_type;

    static BOOST_UBLAS_INLINE result_type apply(argument1_type t1, argument2_type t2) {
    	return std::log(t1/t2);
    }
};


// Square Root Function for vector expressions
template<class E>
BOOST_UBLAS_INLINE
typename vector_unary_traits<E, scalar_sqrt<typename E::value_type> >::result_type
Sqrt(const vector_expression<E> &e) {
	typedef typename vector_unary_traits<E, scalar_sqrt<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}



}}}


namespace jflib {

#define UBLASVECTOR_UNARY_OP1(name,scalar_oper,ublas)							\
template<class E>																\
struct name<ublas::vector_expression<E>, false > {								\
	typedef ublas::scalar_oper<typename E::value_type>	op_type;				\
	typedef ublas::vector_unary_traits<E, op_type>		traits_type;			\
	typedef typename traits_type::expression_type		expression_type;		\
	typedef typename traits_type::result_type			result_type;			\
	typedef const ublas::vector_expression<E>&			argument_type;			\
																				\
	static BOOST_UBLAS_INLINE result_type apply(argument_type e) {				\
		return expression_type(e());											\
	}																			\
};

UBLASVECTOR_UNARY_OP1(Sqrt_impl,scalar_sqrt,boost::numeric::ublas)

}




#endif	//	__UBLAS_JFLIB_EXTENSIONS_OPER_HPP__
