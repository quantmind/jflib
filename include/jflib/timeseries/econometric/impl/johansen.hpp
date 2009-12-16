
#ifndef __JOHANSEN_COINTEGRATION_OPERATOR__HPP__
#define __JOHANSEN_COINTEGRATION_OPERATOR__HPP__

#include <jflib/ublas/inverse.hpp>
#include <jflib/timeseries/econometric/operators.hpp>
//#include <boost/numeric/ublas/banded.hpp>

#ifdef JFLIB_UBLAS_LAPACK
#	include <boost/numeric/bindings/inverse.hpp>
#endif

namespace jflib { namespace timeseries { namespace econometric { namespace impl {

template<class TS, class vtag, class MR>
class johansen;

INVALID_TS_OPERATOR(johansen,0u,false,"Johansen cointegration can be calculated on multivariate timeseries")


template<class M, class SYM>
class johansencalc {
public:
	typedef M									matrix_type;
	typedef SYM									sym_matrix_type;
	typedef typename matrix_type::size_type		size_type;
	
	johansencalc(){}

	template<class E00, class E01, class E02, class E12, class E22>
	johansencalc(const boost::numeric::ublas::matrix_expression<E00>& e00,
				 const boost::numeric::ublas::matrix_expression<E01>& e01,
				 const boost::numeric::ublas::matrix_expression<E02>& e02,
				 const boost::numeric::ublas::matrix_expression<E12>& e12,
				 const boost::numeric::ublas::matrix_expression<E22>& e22):
					M02(e00),M02(e01),M02(e02),M02(e12),M02(e22){}

	johansencalc(const johansencalc& rhs):M00(rhs.M00),M01(rhs.M01),M02(rhs.M02),M02(rhs.M12),M02(rhs.M22){}

	void resize(size_type S, size_type C) {
		M00.resize(S,S,false);
		M01.resize(S,S,false);
		M02.resize(S,C,false);
		M12.resize(S,C,false);
		M22.resize(C,C,false);
		M00.clear();
		M01.clear();
		M02.clear();
		M12.clear();
		M22.clear();
	}

	sym_matrix_type M00;	//SXS
	sym_matrix_type M01;	//SXS    same as M10
	matrix_type M02;		//SXC	 transpose of M20
	matrix_type M12;		//SXC	 transpose of M21
	matrix_type M22;		//CXC

};


template<class TS, class vtag, class MR>
class johansen: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>								super;
	typedef johansen<TS,vtag,MR>									self_type;
	typedef typename super::const_iterator							const_iterator;
public:
	typedef typename super::tstype									tstype;
	typedef typename tstype::numtype								numtype;
private:
	typedef typename traits::oper_traits_vector<numtype>::type		vector_type;
	typedef typename traits::oper_traits_matrix<numtype>::type		matrix_type;
	typedef typename traits::oper_traits_symmetric<numtype>::type	sym_matrix_type;
	typedef vector_type												diagonal_matrix;
	typedef boost::numeric::ublas::vector_range<vector_type>		vector_range;
public:
	typedef typename tstype::size_type								size_type;
	typedef typename tstype::key_type								key_type;
	typedef self_type												temp_traits;
	typedef johansencalc<matrix_type,sym_matrix_type>				temp_type;
	typedef typename traits::ts<key_type,temp_type,tsmap>::type		ts_temp_type;
	typedef MR														result_type;
	typedef typename traits::ts<key_type,result_type,tsmap>::type	ts_result_type;

	BOOST_UBLAS_INLINE
	johansen(const tstype& ts, size_type K):super(ts),m_k(K){
		QM_REQUIRE(m_k >= 2,"Cointegration order must be at least 2");
		size_type S = this->ts_series();
		QM_REQUIRE(S > 1,"Cointegration not possible, at least two timeseries are needed");
		QM_REQUIRE(this->ts_size() > m_k,"Cointegration not possible, timeseries too small");
		size_type C = this->size2();
		m_z2.resize(C);
		m_i00.resize(S,S);
		m_i01.resize(S,S);
		m_i10.resize(S,S);
		m_i11.resize(S,S);
		m_i20.resize(C,S);
		m_i21.resize(C,S);
		m_M22i.resize(C,C);
		m_S00i.resize(S,S);
		m_W.resize(S,S);
		m_E.resize(S);
	}

	BOOST_UBLAS_INLINE
	size_type size() const {return this->ts_size()-m_k;}

	BOOST_UBLAS_INLINE
	void tempinit() {
		tp.resize(this->size(),this->size2());
	}


	BOOST_UBLAS_INLINE
	void eval(temp_type& tp) {
		namespace ublas = boost::numeric::ublas;
		const_iterator it1(this->m_iter);
		const_iterator it0(--it1);
		size_type S = this->series();
		for(size_type k=1;k<m_k;++k) {
			--it0;
			vector_range vr(m_z2, ublas::range(S*(k-1),S*k));
			vr  = it1->second.data() - it0->second.data();
			it0 = --it1;
		}

		const_iterator it(this->m_iter);
		--it;
		m_z0 = this->m_iter->second.data() - it->second.data();

		tp.M00 += ublas::outer_prod(m_z0,m_z0);
		tp.M01 += ublas::outer_prod(m_z0,it->second.data());
		tp.M02 += ublas::outer_prod(m_z0,m_z2);
		tp.M12 += ublas::outer_prod(it->second.data(),m_z2);
		tp.M22 += ublas::outer_prod(m_z2,m_z2);
	}

	BOOST_UBLAS_INLINE
	result_type calculate(const temp_type& tp, size_type N) {
		namespace ublas = boost::numeric::ublas;
		size_type C = this->size2();
		size_type S = this->size();

		QM_REQUIRE(ublas::InvertMatrix(tp.M22,m_M22i),"Failed to invert matrix");

		ublas::noalias(m_i20) = ublas::prod(m_M22i,ublas::trans(tp.M20));
		ublas::noalias(m_i21) = ublas::prod(m_M22i,ublas::trans(tp.M21));

		ublas::noalias(m_i00) = ublas::prod(tp.M02,m_i20);
		ublas::noalias(m_i10) = ublas::prod(tp.M12,m_i20);
		ublas::noalias(m_i01) = ublas::prod(tp.M02,m_i21);
		ublas::noalias(m_i11) = ublas::prod(tp.M12,m_i21);

		// Note M01 and M10 are the same matrix (transpose of a symmetric matrix)
		m_S00 = tp.M00 - m_i00;
		m_S10 = tp.M01 - m_i10;
		m_S01 = tp.M01 - m_i01;
		m_S11 = tp.M11 - m_i11;

		QM_REQUIRE(ublas::InvertMatrix(m_S00,m_S00i),"Failed to invert matrix");
		//QM_REQUIRE(jflib::linalg::lapack::syevectors(m_S11,m_E),"Failed to evaluate eigenvectors");
		m_E = ublas::Sqrt(m_E);
		//matrix_type S11h(W*ES*W^t);
		//matrix_type M(ublas::prod(S11h,ublas::prod(S10,ublas::prod(S00i,ublas::prod(S01,S11h)))));
		//QM_REQUIRE(EigenVectors(M,W,E),"Failed to evaluate final eigenvectors");
	}

	template<class It>
	BOOST_UBLAS_INLINE
	void insert(typename ts_result_type::iterator ir, ts_result_type& re, unsigned r, size_type window, It it1, It it2) {
		temp_type jt((it2->second.M00-it1->second.M00)/window,
					 (it2->second.M01-it1->second.M01)/window,
					 (it2->second.M02-it1->second.M02)/window,
					 (it2->second.M12-it1->second.M12)/window,
					 (it2->second.M22-it1->second.M22)/window);
		//re.insertexpression(ir, r, it2->first, (it2->second - it1->second)/window);
	}

	BOOST_UBLAS_INLINE
	void init() {
		this->m_iter  = this->begin();
		for(size_type i=0;i<m_k;++i) ++this->m_iter;
	}
private:
	size_type	m_k;
	tstype		m_deterministic;
	vector_type m_z0;
	vector_type m_z2;
	matrix_type m_M22i;
	matrix_type m_i00;
	matrix_type m_i10;
	matrix_type m_i01;
	matrix_type m_i11;
	matrix_type m_i20;
	matrix_type m_i21;
	matrix_type m_S00;
	matrix_type m_S01;
	matrix_type m_S10;
	matrix_type m_S11;
	matrix_type m_S00i;
	matrix_type m_W;
	diagonal_matrix m_E;

	size_type   size2() {
		size_type S = this->series();
		return S*(m_k-1) + m_deterministic.series();
	}

	temp_type	tp;
};



}}}}


#endif	//	__JOHANSEN_COINTEGRATION_OPERATOR__HPP__


