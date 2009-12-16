
#ifndef __SHARPE_ECONOMETRIC_OPERATOR__HPP_
#define __SHARPE_ECONOMETRIC_OPERATOR__HPP_

#include <jflib/timeseries/econometric/operators.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {

template<class TS, class vtag, class MR> class sharpe;

template<class TS>
class tpsharpe {
public:
	typedef TS									tstype;
	typedef typename tstype::numtype			numtype;
	typedef traits::oper_traits<tstype,3u>		temp_traits;
	typedef typename temp_traits::type			temp_type;
	
	tpsharpe(){}
	tpsharpe(const tpsharpe& r1, const tpsharpe& r2):time(r2.time-r1.time),tmp(r2.tmp-r1.tmp){}

	void init(const tstype& ts) {
		time = 0;
		temp_traits::init(ts,tmp);
	}

	numtype	    time;
	temp_type   tmp;
};


template<class TS, class vtag, class MR>
class sharpe: public tsrolloperatorlag<TS,vtag,MR> {
	typedef tsrolloperatorlag<TS,vtag,MR>						super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef typename tstype::size_type							size_type;
	typedef typename tstype::numtype							numtype;
	typedef traits::oper_traits<tstype,1u>						result_traits;
	typedef typename result_traits::type						result_type;
	typedef tpsharpe<tstype>									temp_type;
	typedef tstype												ts_result_type;
	typedef typename tstype::daycounter							daycounter;
	typedef traits::ts<key_type,temp_type,tsmap>				ts_temp_type;

	BOOST_UBLAS_INLINE
	sharpe(const tstype& ts):super(ts,1){}

	BOOST_UBLAS_INLINE
	void tempinit() {
		tp.init(this->ts());
	}
	
	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) const {
		numtype c = m_dc.dcf(this->m_iter0->first,this->m_iter->first);
		tp.tmp[0]  = LogRatio<mapped_type,mapped_type>::apply(this->m_iter->second,this->m_iter0->second);
		tp.time   += c;
		tp.tmp[1] += tp.tmp[0];
		tp.tmp[2] += boost::numeric::ublas::element_prod(tp.tmp[0],tp.tmp[0])/c;
	}

	BOOST_UBLAS_INLINE
	result_type calculate(const temp_type& tp, size_type N) {
		return boost::numeric::ublas::element_div(tp.tmp[1],tp.time*boost::numeric::ublas::Sqrt(tp.tmp[2]/N));
	}

	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
		   unsigned r, size_type window, It it1, It it2) {
		temp_type tp(it1->second,it2->second);
		return re.insertexpression(ir, r, it2->first,
			boost::numeric::ublas::element_div(tp.tmp[1],tp.time*boost::numeric::ublas::Sqrt(tp.tmp[2]/window)));
	}

	temp_type tp;
protected:
	daycounter	m_dc;
};



template<class Key, class T, class Tag, unsigned F, class vtag, class MR>
class sharpe<timeseries<Key,T,Tag,F,false>, vtag, MR>:
	public tsrolloperatorlag<timeseries<Key,T,Tag,F,false> , vtag, MR> {
	typedef tsrolloperatorlag<timeseries<Key,T,Tag,F,false>, vtag, MR>		super;
public:
	typedef typename super::tstype								tstype;
	typedef typename tstype::key_type							key_type;
	typedef typename tstype::mapped_type						mapped_type;
	typedef typename tstype::size_type							size_type;
	typedef typename tstype::numtype							numtype;
	typedef traits::oper_traits<tstype,1u>						result_traits;
	typedef typename result_traits::type						result_type;
	typedef tpsharpe<tstype>									temp_type;
	typedef tstype												ts_result_type;
	typedef typename traits::ts<key_type,temp_type,tsmap>::type	ts_temp_type;
	typedef typename tstype::daycounter							daycounter;
	
	BOOST_UBLAS_INLINE
	sharpe(const tstype& ts):super(ts,1){}
	
	BOOST_UBLAS_INLINE
	void tempinit() {
		tp.init(this->ts());
	}
	
	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) const {
		numtype c = m_dc.dcf(this->m_iter0->first,this->m_iter->first);
		tp.tmp[0]  = LogRatio<mapped_type,mapped_type>::apply(this->m_iter->second,
															  this->m_iter0->second);
		tp.time   += c;
		tp.tmp[1] += tp.tmp[0];
		tp.tmp[2] += tp.tmp[0]*tp.tmp[0]/c;
	}
	
	BOOST_UBLAS_INLINE
	result_type calculate(temp_type& tp, size_type N) {
		return tp.tmp[1]/(std::sqrt(tp.tmp[2]/N)*tp.time);
	}
	
	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
				unsigned r, size_type window, It it1, It it2) {
		temp_type tp(it1->second,it2->second);
		return re.insertexpression(ir, r, it2->first, this->calculate(tp,window));
	}
	
	temp_type tp;
protected:
	daycounter	m_dc;
};


}}}}

#endif	//	__SHARPE_ECONOMETRIC_OPERATOR__HPP_
