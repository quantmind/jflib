
#ifndef __AUTOREGRESSION_ECONOMETRIC_OPERATOR__HPP_
#define __AUTOREGRESSION_ECONOMETRIC_OPERATOR__HPP_

#include <jflib/timeseries/econometric/operators.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {

template<class TS, class vtag, class MR> class ar;


template<class TS, class vtag, class MR>
class ar: public tsrolloperatorlag<TS,vtag,MR> {
	typedef tsrolloperatorlag<TS,vtag,MR>						super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef typename tstype::size_type							size_type;
	typedef traits::oper_traits<tstype,2u>						temp_traits;
	typedef traits::oper_traits<tstype,1u>						result_traits;
	typedef typename result_traits::type						result_type;
	typedef typename temp_traits::type							temp_type;
	typedef tstype												ts_result_type;
	typedef typename traits::ts<key_type,temp_type,tsmap>::type	ts_temp_type;

	ar(const tstype& ts, size_type n):super(ts,n){}

	void tempinit() {
		temp_traits::init(this->ts(),tp);
	}

	void eval(temp_type& tp) const {
		tp[0] += Multiply<mapped_type,mapped_type>::apply(this->m_iter->second,this->m_iter0->second);
		tp[1] += Multiply<mapped_type,mapped_type>::apply(this->m_iter0->second,this->m_iter0->second);
	}

	result_type calculate(const temp_type& tp, size_type N) {
		return boost::numeric::ublas::element_div(tp[0],tp[1]);
	}

	template<class It>
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
		   unsigned r, size_type window, It it1, It it2) {
		return re.insertexpression(ir, r, it2->first,
			boost::numeric::ublas::element_div((it2->second - it1->second)(0),(it2->second - it1->second)(1)));
	}

	temp_type	tp;
};


template<class Key, class T, class Tag, unsigned F, class vtag, class MR>
class ar<timeseries<Key,T,Tag,F,false>, vtag, MR>:
	public tsrolloperatorlag<timeseries<Key,T,Tag,F,false> , vtag, MR> {
	typedef tsrolloperatorlag<timeseries<Key,T,Tag,F,false>, vtag, MR>		super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef typename tstype::size_type							size_type;
	typedef traits::oper_traits<tstype,2u>						temp_traits;
	typedef traits::oper_traits<tstype,1u>						result_traits;
	typedef typename result_traits::type						result_type;
	typedef typename temp_traits::type							temp_type;
	typedef tstype												ts_result_type;
	typedef typename traits::ts<key_type,temp_type,Tag>::type	ts_temp_type;
	
	BOOST_UBLAS_INLINE
	ar(const tstype& ts, size_type n):super(ts,n){}
	
	BOOST_UBLAS_INLINE
	void tempinit() {temp_traits::init(this->ts(),tp);}

	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) const {
		tp[0] += Multiply<mapped_type,mapped_type>::apply(this->m_iter->second,this->m_iter0->second);
		tp[1] += Multiply<mapped_type,mapped_type>::apply(this->m_iter0->second,this->m_iter0->second);
	}
	
	BOOST_UBLAS_INLINE
	result_type calculate(temp_type& tp, size_type N) {
		return tp[0]/tp[1];
	}
	
	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
				unsigned r, size_type window, It it1, It it2) {
		return re.insertexpression(ir, r, it2->first,
							(it2->second - it1->second)(0)/(it2->second - it1->second)(1));
	}
	
	temp_type	tp;
};



}}}}

#endif	//	__AUTOREGRESSION_ECONOMETRIC_OPERATOR__HPP_
