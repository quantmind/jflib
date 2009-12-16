
#ifndef __COVARIANCE_ECONOMETRIC_OPERATOR__HPP__
#define __COVARIANCE_ECONOMETRIC_OPERATOR__HPP__

#include <jflib/timeseries/econometric/impl/invalid.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {

template<class TS, class vtag, class MR>
class covar;

INVALID_TS_OPERATOR(covar,0u,false,"Covariance can be calculated on multivariate timeseries")


// \brief Covariance estimation
template<class TS, class vtag, class MR>
class covar: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>								super;
	typedef covar<TS,vtag,MR>										self_type;
public:
	typedef typename super::tstype									tstype;
	typedef typename tstype::size_type								size_type;
	typedef typename tstype::key_type								key_type;
	typedef self_type												temp_traits;
	typedef MR														result_type;
	typedef typename traits::ts<key_type,result_type,tsmap>::type	ts_result_type;
	typedef typename tstype::numtype								numtype;
	typedef result_type												temp_type;
	typedef ts_result_type											ts_temp_type;

	covar(const tstype& ts):super(ts){}

	BOOST_UBLAS_INLINE
	void tempinit() {
		size_type S = this->ts_series();
		tp.resize(S,S,false);
		tp.clear();
	}

	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) {
		tp += boost::numeric::ublas::outer_prod(this->m_iter->second.data(),this->m_iter->second.data());
	}

	BOOST_UBLAS_INLINE
	result_type calculate(const temp_type& tp, size_type N) {
		return result_type(tp / N);
	}

	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re,
		   unsigned r, size_type window, It it1, It it2) {
		return re.insertexpression(ir, r, it2->first, (it2->second - it1->second)/window);
	}

	temp_type	tp;
};



}}}}


#endif	//	__COVARIANCE_ECONOMETRIC_OPERATOR__HPP__


