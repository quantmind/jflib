
#ifndef __INVALID_ECONOMETRIC_OPERATOR__HPP__
#define __INVALID_ECONOMETRIC_OPERATOR__HPP__

#include <jflib/timeseries/econometric/operators.hpp>

namespace jflib { namespace timeseries { namespace econometric { namespace impl {



#define INVALID_TS_OPERATOR(name,family,multi,errormsg)							\
template<class Key, class T, class Tag, class vtag, class MR>					\
class name<timeseries<Key,T,Tag,family,multi>, vtag, MR>:						\
	public tsrolloperator<timeseries<Key,T,Tag,family,multi>, vtag, MR> {		\
	typedef tsrolloperator<timeseries<Key,T,Tag,family,multi>, vtag, MR> super;	\
public:																			\
	typedef typename super::tstype		tstype;									\
	typedef typename super::size_type	size_type;								\
	typedef typename tstype::numtype	numtype;								\
	typedef numtype						result_type;							\
	typedef numtype						temp_type;								\
	typedef tstype						ts_result_type;							\
	typedef tstype						ts_temp_type;							\
																				\
	name(const tstype& ts):super(ts){}											\
																				\
	void eval(temp_type& tp) {													\
		QM_FAIL(errormsg);														\
	}																			\
																				\
	result_type	calculate(const temp_type& tp, size_type N) {					\
		QM_FAIL(errormsg);														\
	}																			\
																				\
	template<class It>															\
	typename ts_result_type::iterator											\
	insert(typename ts_result_type::iterator ir, ts_result_type& re,			\
		   unsigned r, size_type window, It it1, It it2) {						\
		QM_FAIL(errormsg);														\
	}																			\
																				\
	temp_type tp;																\
};


}}}}


#endif	//	__INVALID_ECONOMETRIC_OPERATOR__HPP__
