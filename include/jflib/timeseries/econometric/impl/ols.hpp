#ifndef __ORDINARY_LEAST_SQUARES_ECONOMETRIC_OPERATOR__HPP_
#define __ORDINARY_LEAST_SQUARES_ECONOMETRIC_OPERATOR__HPP_

#include <jflib/timeseries/econometric/impl/invalid.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {


template<class TS, class vtag, class MR>
class ols;

INVALID_TS_OPERATOR(ols,0u,false,"OLS can be calculated on matrix timeseries only")
INVALID_TS_OPERATOR(ols,0u,true,"OLS can be calculated on matrix timeseries only")


/**
 * Ordinary Least Squared Regression
 *
 * TS	timeseries type
 * MR	Matrix type. This matrix must have
 */
template<class TS, class vtag, class MR>
class ols: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>							super;
	typedef ols<TS,vtag,MR>										self_type;
public:
	typedef typename super::tstype								tstype;
	typedef typename super::numtype								numtype;
	typedef typename tstype::size_type							size_type;
	typedef typename tstype::key_type							key_type;
private:
	typedef MR													matrix_type;
	typedef traits::matrix_traits<matrix_type>					matrix_traits;
	typedef typename matrix_traits::reference_type				matrix_reference;
	typedef typename matrix_traits::vector_type					vector_type;
	typedef typename traits::range								range;
public:
	typedef vector_type											result_type;
	typedef typename traits::ts<key_type,numtype,vtag>::type	ts_result_type;
	typedef result_type											temp_type;
	typedef ts_result_type										ts_temp_type;

	size_type series() const {return this->ts_series() - 1;}

	BOOST_UBLAS_INLINE
	ols(const tstype& ts):super(ts),m_mat(ts.internal_data()) {
		QM_REQUIRE(this->ts_series() > 1,"OLS calculation can be performed on multiple timeseries only");
		QM_REQUIRE(this->ts_series() - 1 < this->ts_size(),"OLS Calculation cannot be performed");
		QM_REQUIRE(!this->masked(),"OLS calculation not possible. Timeseries have missing data");
	}

	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) {}

	BOOST_UBLAS_INLINE
	result_type calculate(const temp_type& tp, size_type N) {
		typedef typename matrix_traits::template expressions<matrix_type> 	etype;
		size_type S = this->ts_series();
		matrix_type A(typename etype::mrange(m_mat,range(0,N),range(1,S)));
		matrix_type b(typename etype::mrange(m_mat,range(0,N),range(0,1)));
		lapack::gels('N',A,b);
		vector_type re(S-1);
		for(size_type i=0;i<S-1;++i) {
			re[i] = b(i,0);
		}
		return re;
		//return vector_type(typename etype::vrange(b,range(0,S-1),range(0,S-1)));
		//return vector_type(typename etype::mcolumn(b,0));
	}

	template<class It>
	BOOST_UBLAS_INLINE
	typename ts_result_type::iterator
	insert(typename ts_result_type::iterator ir, ts_result_type& re, unsigned r, size_type window, It it1, It it2) {
		//result_type b(tp.data(0,it1,it2));
		//re.insertexpression(ir, r, it2->first, (it2->second - it1->second)/window);
		return ir;
	}

	result_type			tp;
private:
	matrix_type			m_mat;
};


}}}}


#endif	//	__ORDINARY_LEAST_SQUARES_ECONOMETRIC_OPERATOR__HPP_
