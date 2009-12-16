
#ifndef		__TIMESERIES_INNER_PROD_EXPRESSION_HPP__
#define		__TIMESERIES_INNER_PROD_EXPRESSION_HPP__


#include <jflib/timeseries/expr.hpp>

namespace jflib { namespace timeseries {

namespace details {

template<class E1, class E2>
struct timeseries_inner_prod_traits;

}


template<class E1, class E2, class TS>
class inner_prod_expression: public timeseries_expression<inner_prod_expression<E1,E2,TS> > {
	typedef inner_prod_expression<E1,E2,TS>			self_type;
public:
	typedef E1										expression1_type;
	typedef E2										expression2_type;
	typedef TS										tstype;
	typedef typename tstype::size_type				size_type;

	inner_prod_expression(const E1& e1, const E2& e2):m_e1(e1),m_e2(e2){}
	inner_prod_expression(const inner_prod_expression& rhs):m_e1(rhs.m_e1),m_e2(rhs.m_e2){}

	size_type size() const {return m_e1.size();}
	size_type series() const {return 1;}

	tstype apply() const {
		return details::timeseries_inner_prod_traits<E1,E2>::apply(m_e1,m_e2);
	}
private:
	expression1_type m_e1;
	expression2_type m_e2;
};


template<class E1, class E2>
typename details::timeseries_inner_prod_traits<E1,E2>::result_type
inner_prod(const timeseries_expression<E1>& e1, const timeseries_expression<E2>& e2) {
	typedef typename details::timeseries_inner_prod_traits<E1,E2>::expression_type expression_type;
	return expression_type(e1(), e2());
}



template<class E1, class E2>
tsexpression<typename details::timeseries_inner_prod_traits<E1,E2>::tstype>
inner_prod_expr(const E1& e1, const E2& e2) {
	typedef tsexpression<typename details::timeseries_inner_prod_traits<E1,E2>::tstype>	expr_type;
	return expr_type(inner_prod(e1,e2));
}

namespace details {


template<class Key, class T, class Tag, unsigned F, bool M, class E2>
struct timeseries_inner_prod_traits<timeseries<Key,T,Tag,F,M>, E2> {
	typedef timeseries<Key,T,Tag,F,M>											expression1_type;
	typedef E2																	expression2_type;
	typedef typename expression1_type::key_type									key_type;
	typedef typename expression1_type::numtype									numtype;
	typedef typename traits::ts<key_type,numtype,tsmap>::type					tstype;
	typedef inner_prod_expression<expression1_type,expression2_type,tstype>		expression_type;
	typedef timeseries_expression<expression_type>								result_type;

	static tstype apply(const tstype& ts, const E2& v) {
		QM_FAIL("Inner product not available");
	}
};


template<class Key, class T, class Tag, unsigned F>
struct timeseries_inner_prod_traits<timeseries<Key,T,Tag,F,false>,
									typename timeseries<Key,T,Tag,F,false>::numtype> {
	typedef timeseries<Key,T,Tag,F,false>					tstype;
	typedef typename tstype::numtype						numtype;
	typedef inner_prod_expression<tstype,numtype,tstype>	expression_type;
	typedef timeseries_expression<expression_type>			result_type;

	static tstype apply(const tstype& ts, const numtype& v) {
		return ts * v;
	}
};

template<class Key, class T, class Tag, unsigned F, class E2>
struct timeseries_inner_prod_traits<timeseries<Key,T,Tag,F,true>, E2> {
	typedef timeseries<Key,T,Tag,F,true>										expression1_type;
	typedef E2																	expression2_type;
	typedef typename expression1_type::key_type									key_type;
	typedef typename expression1_type::numtype									numtype;
	typedef typename traits::ts<key_type,numtype,tsmap>::type					tstype;
	typedef inner_prod_expression<expression1_type,expression2_type,tstype>		expression_type;
	typedef timeseries_expression<expression_type>								result_type;

	static tstype apply(const expression1_type& ts, const expression2_type& v) {
		tstype re;
		typename tstype::iterator io = re.begin();
		for(typename expression1_type::const_iterator it=ts.begin();it!=ts.end();++it) {
			io = re.insert(io, typename tstype::value_type(it->first,inner_prod(it->second,v)));
		}
		return re;
	}
};



}


}}



#endif	//	__TIMESERIES_INNER_PROD_EXPRESSION_HPP__

