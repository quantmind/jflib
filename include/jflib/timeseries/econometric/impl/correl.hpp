
#ifndef		__CORRELATION_ECONOMETRIC_OPERATOR__HPP_
#define		__CORRELATION_ECONOMETRIC_OPERATOR__HPP_


#include <jflib/timeseries/econometric/impl/invalid.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {

template<class TS, class vtag, class MR>
class correl;

INVALID_TS_OPERATOR(correl,0u,false,"Correlation can be calculated on multivariate timeseries")


// \brief Covariance estimation
template<class TS, class vtag, class MR>
class correl: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>								super;
	typedef correl<TS,vtag,MR>										self_type;
public:
	typedef typename super::tstype									tstype;
	typedef typename tstype::size_type								size_type;
	typedef typename tstype::key_type								key_type;
	typedef MR														result_type;
	typedef typename traits::ts<key_type,result_type,tsmap>::type	ts_result_type;
	typedef typename tstype::numtype								numtype;
	typedef result_type												temp_type;
	typedef ts_result_type											ts_temp_type;

	correl(const tstype& ts):super(ts){}

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

	template<class E>
	BOOST_UBLAS_INLINE
	result_type calculate(const boost::numeric::ublas::matrix_expression<E>& tp, size_type N) {
		result_type m(tp / N);
		numtype vii,co;
		for(size_type i = 0; i < m.size1 (); ++ i) {
			vii    = m(i,i);
			m(i,i) = std::sqrt(vii);
			for(unsigned j = i+1; j < m.size2 (); ++ j) {
				co = m(i,j)/std::sqrt(vii*m(j,j));
				m(i, j) = co;
				m(j, i) = co;
			}
		}
		return m;
	}

	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re, unsigned r, size_type window, It it1, It it2) {
		result_type cor(this->calculate(it2->second - it1->second, window));
		return re.insertexpression(ir, r, it2->first, cor);
	}

	temp_type	tp;
};


}}}}

#endif	//	__CORRELATION_ECONOMETRIC_OPERATOR__HPP_


