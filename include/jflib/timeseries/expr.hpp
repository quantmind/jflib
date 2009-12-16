
#ifndef		__TIMESERIE_EXPR_HPP__
#define		__TIMESERIE_EXPR_HPP__

#include <jflib/timeseries/timeseries_base.hpp>
#include <jflib/timeseries/traits/base.hpp>
#include <boost/numeric/ublas/expression_types.hpp>

namespace jflib { namespace timeseries {


template<class TS>
class timeseries_expression_holder_base {
public:
	typedef TS							tstype;
	typedef typename tstype::size_type 	size_type;
	virtual size_type size() = 0;
};


template<class E, class TS>
class timeseries_expression_holder: public timeseries_expression_holder_base<TS> {
	typedef timeseries_expression_holder_base<TS>		super;
	typedef typename E::tstype							otherts;
	//BOOST_STATIC_ASSERT(boost::is_same<TS,otherts>::value);
public:
	typedef E							expression;
	typedef typename super::tstype		tstype;
	typedef typename tstype::size_type 	size_type;

	timeseries_expression_holder(const expression& e):m_e(e){}
private:
	expression	m_e;
};



template<class TS>
class tsexpression {
	typedef timeseries_expression_holder_base<TS>	holder_type;
public:
	typedef TS							tstype;
	typedef typename tstype::size_type	size_type;

	template<class E>
	tsexpression(const E& expr):m_expr(new timeseries_expression_holder<E,tstype>(expr)){}

	tsexpression(const tsexpression& rhs):m_expr(rhs.m_expr){}

	size_type size() const {return m_expr->size();}
	size_type series() const {return m_expr->series();}

private:
	boost::shared_ptr<holder_type>	m_expr;
};


template<class E>
class timeseries_expression: public timeseries_expression_holder<E, typename E::tstype> {
	typedef timeseries_expression_holder<E, typename E::tstype>		super;
public:
	typedef typename super::tstype	tstype;
	typedef E 						expression_type;

	super& as_expr() {return *this;}
	const super& as_expr() const {return *this;}

	BOOST_UBLAS_INLINE
	const expression_type &operator () () const {
		return *static_cast<const expression_type *> (this);
	}
	BOOST_UBLAS_INLINE
	expression_type &operator () () {
		return *static_cast<expression_type *> (this);
	}
};


template<class Key, class T, class Tag, unsigned F, bool M>
class timeseries_reference: public timeseries_expression<timeseries_reference<Key,T,Tag,F,M> > {
public:
	typedef timeseries<Key,T,Tag,F,M>	tstype;
	typedef typename tstype::size_type	size_type;

	timeseries_reference(const tstype& ts):m_ts(ts){}
	timeseries_reference(const timeseries_reference& ts):m_ts(ts.m_ts){}

	size_type size() const {return m_ts.size();}
	size_type series() const {return m_ts.series();}

	tstype& expression() {return m_ts;}
	const tstype& expression() const {return m_ts;}
private:
	tstype	m_ts;
};





template<class E1, class E2, class F>
class timeseries_binary: public timeseries_expression<timeseries_binary<E1,E2,F> > {
	typedef E1									expression1_type;
    typedef E2									expression2_type;
    typedef F									functor_type;
    typedef typename E1::size_type				size_type;
public:
	BOOST_UBLAS_INLINE
    timeseries_binary(const expression1_type &e1, const expression2_type &e2):m_e1(e1),m_e2(e2){}

	BOOST_UBLAS_INLINE
	size_type size() const {return BOOST_UBLAS_SAME(m_e1.size(), m_e2.size());}
private:
	expression1_type m_e1;
	expression2_type m_e2;
};




}}


#endif	//	__TIMESERIE_EXPR_HPP__
