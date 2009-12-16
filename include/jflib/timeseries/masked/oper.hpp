/*
 * \brief Template operators for timeseries masked vectors
 */

#ifndef __MASKEDVECTOR_OPER_HPP__
#define __MASKEDVECTOR_OPER_HPP__

#include <jflib/ublas/base.hpp>
#include <jflib/ublas/oper.hpp>
#include <jflib/timeseries/masked/maskedvector.hpp>



namespace jflib {


/*
 * \brief Unary operators
 */
#define MASKEDVECTOR_UNARY_OP1(name,scalar_oper,ublas)       	            								\
template<class T,class M,unsigned F>																		\
struct name<jflib::timeseries::maskedvector<T,M,F>,false > {												\
	typedef jflib::timeseries::maskedvector<T,M,F>  masked_vector_type;										\
	typedef typename masked_vector_type::data_type	data_type;												\
	typedef typename masked_vector_type::value_type	value_type;												\
																											\
	typedef ublas::scalar_oper<value_type>											 op_type;				\
	typedef typename ublas::vector_unary_traits<data_type, op_type>::expression_type expression_type;		\
																											\
	static expression_type apply(const masked_vector_type& lhs) {											\
		return expression_type(lhs.data());																	\
	}																										\
};


/*
 * \brief Binary operators
 */
#define MASKEDVECTOR_BINARY_OP1(name,scalar_oper,ublas)       	            						\
template<class T,class M,unsigned F>																\
struct name<jflib::timeseries::maskedvector<T,M,F>, jflib::timeseries::maskedvector<T,M,F> > {		\
	typedef jflib::timeseries::maskedvector<T,M,F>  masked_vector_type;								\
	typedef typename masked_vector_type::data_type	data_type;										\
	typedef typename masked_vector_type::value_type	value_type;										\
																									\
	typedef ublas::scalar_oper<value_type,value_type>							op_type;			\
	typedef ublas::vector_binary_traits<data_type, data_type, op_type>			traits_type;		\
	typedef typename traits_type::result_type									result_type;		\
																									\
	static result_type apply(const masked_vector_type& lhs, const masked_vector_type& rhs) {		\
		typedef typename traits_type::expression_type expression_type;								\
		return expression_type(lhs.data(),rhs.data());												\
	}																								\
};





MASKEDVECTOR_UNARY_OP1(Sqrt_impl,scalar_sqrt,boost::numeric::ublas)

MASKEDVECTOR_BINARY_OP1(Add,scalar_plus,boost::numeric::ublas)
MASKEDVECTOR_BINARY_OP1(Subtract,scalar_minus,boost::numeric::ublas)
MASKEDVECTOR_BINARY_OP1(Multiply,scalar_multiplies,boost::numeric::ublas)
MASKEDVECTOR_BINARY_OP1(Divide,scalar_divides,boost::numeric::ublas)
MASKEDVECTOR_BINARY_OP1(LogRatio,scalar_logratio,boost::numeric::ublas)



}

#endif	//	__MASKEDVECTOR_OPER_HPP__

