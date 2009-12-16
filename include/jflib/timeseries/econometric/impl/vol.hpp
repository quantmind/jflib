
#ifndef __VOLATILITY_ECONOMETRIC_OPERATOR__HPP_
#define __VOLATILITY_ECONOMETRIC_OPERATOR__HPP_

#include <jflib/timeseries/econometric/operators.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {



template<class TS, class vtag, class MR>
class vol: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>							super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::size_type							size_type;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef traits::oper_traits<tstype,1u>						result_traits;
	typedef result_traits										temp_traits;
	typedef typename result_traits::type						result_type;
	typedef typename temp_traits::type							temp_type;
	typedef tstype												ts_result_type;
	typedef typename traits::ts<key_type,temp_type,tsmap>::type	ts_temp_type;

	BOOST_UBLAS_INLINE
	vol(const tstype& ts):super(ts){}

	BOOST_UBLAS_INLINE
	void tempinit() {temp_traits::init(this->ts(),tp);}

	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) {
		tp += Multiply<mapped_type,mapped_type>::apply(this->m_iter->second,this->m_iter->second);
	}

	BOOST_UBLAS_INLINE
	result_type calculate(const temp_type& tp, size_type N) {
		return boost::numeric::ublas::Sqrt(tp/N);
	}

	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
	   	   unsigned r, size_type window, It it1, It it2) {
		return re.insertexpression(ir, r, it2->first,
								   boost::numeric::ublas::Sqrt((it2->second - it1->second)/window));
	}

	temp_type	tp;
};



template<class Key, class T, class Tag, unsigned F, class vtag, class MR>
class vol<timeseries<Key,T,Tag,F,false>, vtag, MR>:
	public tsrolloperator<timeseries<Key,T,Tag,F,false>, vtag, MR> {
	typedef tsrolloperator<timeseries<Key,T,Tag,F,false>, vtag, MR>		super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::size_type							size_type;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef mapped_type											result_type;
	typedef result_type											temp_type;
	typedef tstype												ts_result_type;
	typedef tstype												ts_temp_type;

	vol(const tstype& ts):super(ts){}
	
	BOOST_UBLAS_INLINE
	void tempinit() {tp = 0;}

	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) const {
		tp += Multiply<mapped_type,mapped_type>::apply(this->m_iter->second,this->m_iter->second);
	}

	BOOST_UBLAS_INLINE
	result_type calculate(temp_type tp, size_type N) {
		return std::sqrt(tp/N);
	}
	
	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
				unsigned r, size_type window, It it1, It it2) {
		return re.insertexpression(ir, r, it2->first, std::sqrt((it2->second - it1->second)/window));
	}
	
	temp_type	tp;
};


}}}}

#endif	//	__VOLATILITY_ECONOMETRIC_OPERATOR__HPP_
