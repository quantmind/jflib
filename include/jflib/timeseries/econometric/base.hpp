
#ifndef __ECONOMETRIC_BASE_HPP_
#define __ECONOMETRIC_BASE_HPP_

#include <jflib/timeseries/timeseries_base.hpp>

#include <jflib/timeseries/econometric/impl/oper1.hpp>

#include <jflib/ublas/oper.hpp>

#include <jflib/timeseries/econometric/impl/vol.hpp>
#include <jflib/timeseries/econometric/impl/ar.hpp>
//#include <jflib/timeseries/econometric/impl/sharpe.hpp>
#include <jflib/timeseries/econometric/impl/covar.hpp>
#include <jflib/timeseries/econometric/impl/correl.hpp>
#include <jflib/timeseries/econometric/impl/ols.hpp>
#include <jflib/timeseries/econometric/impl/johansen.hpp>


namespace jflib { namespace timeseries { namespace econometric {



template<class TS, class vtag, class MT>
class analysis {
public:
	typedef TS												tstype;
	typedef typename tstype::size_type						size_type;
	typedef typename tstype::numtype						numtype;
	typedef boost::numeric::ublas::scalar_sqrt<numtype>		sqrt_type;

	typedef rollanalysis<TS,vtag,MT,impl::vol>					vol_type;
	typedef rollanalysis<TS,vtag,MT,impl::ar>					ar_type;
	//typedef rollanalysis<TS,vtag,MT,impl::sharpe>				sharpe_type;
	typedef rollanalysis<TS,vtag,MT,impl::covar>				covar_type;
	typedef rollanalysis<TS,vtag,MT,impl::correl>				correl_type;
	typedef rollanalysis<TS,vtag,MT,impl::johansen>				coint_type;
	typedef rollanalysis<TS,vtag,MT,impl::ols>					ols_type;

	analysis(const tstype& ts):m_ts(ts){}
	analysis(const analysis& ts):m_ts(ts.m_ts){}
	analysis& operator = (const analysis& rhs) {m_ts = rhs.m_ts; return *this;}

	static analysis make(const tstype& ts) {analysis a(ts); return a;}

	size_type size() const {return m_ts.size();}

	tstype delta()       const {return tsoperator1<tstype,Subtract,Nil>::apply(m_ts);}
	tstype logdelta()    const {return tsoperator1<tstype,LogRatio,Nil>::apply(m_ts);}
	tstype sdelta()      const {return tsoperator1<tstype,Subtract,sqrt_type>::apply(m_ts);}
	tstype slogdelta()   const {return tsoperator1<tstype,LogRatio,sqrt_type>::apply(m_ts);}
	tstype mdd() const {QM_FAIL("not available");}

	typename vol_type::result_type	vol() const {
		typename vol_type::optype op(m_ts);
		return vol_type::calc(op);
	}
	typename vol_type::ts_result_type roll_vol(size_type window) const {
		typename vol_type::optype op(m_ts);
		return vol_type::roll(op,window);
	}

	typename ar_type::result_type	ar(size_type order) const {
		typename ar_type::optype op(m_ts,order);
		return ar_type::calc(op);
	}
	typename ar_type::ts_result_type roll_ar(size_type window, size_type order) const {
		typename ar_type::optype op(m_ts,order);
		return ar_type::roll(op,window);
	}

	/*
	typename sharpe_type::result_type	sharpe() const {
		typename sharpe_type::optype op(m_ts);
		return sharpe_type::calc(op);
	}
	typename sharpe_type::ts_result_type roll_sharpe(size_type window) const {
		typename sharpe_type::optype op(m_ts);
		return sharpe_type::roll(op,window);
	}
	*/

	typename covar_type::result_type covar() const {
		typename covar_type::optype op(m_ts);
		return covar_type::calc(op);
	}
	typename covar_type::ts_result_type roll_covar(size_type window) const {
		typename covar_type::optype op(m_ts);
		return covar_type::roll(op,window);
	}

	typename correl_type::result_type correl() const {
		typename correl_type::optype op(m_ts);
		return correl_type::calc(op);
	}
	typename correl_type::ts_result_type roll_correl(size_type window) const {
		typename correl_type::optype op(m_ts);
		return correl_type::roll(op,window);
	}

	typename coint_type::result_type coint(size_type order) const {
		typename coint_type::optype op(m_ts, order);
		return coint_type::calc(op);
	}
	typename coint_type::ts_result_type roll_coint(size_type window, size_type order) const {
		typename coint_type::optype op(m_ts, order);
		return coint_type::roll(op,window);
	}

	typename ols_type::result_type ols() const {
		typename ols_type::optype op(m_ts);
		return ols_type::calc(op);
	}
	typename ols_type::ts_result_type roll_ols(size_type window) const {
		typename ols_type::optype op(m_ts);
		return ols_type::roll(op,window);
	}

	tstype var(size_type n) {QM_FAIL("not available");}
private:
	tstype	m_ts;
};



}}}


#endif	//	__ECONOMETRIC_BASE_HPP_
