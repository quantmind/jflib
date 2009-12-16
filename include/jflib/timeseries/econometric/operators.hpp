
#ifndef __ECONOMETRIC_OPERATORS_HPP__
#define __ECONOMETRIC_OPERATORS_HPP__

#include <jflib/timeseries/traits/oper.hpp>
#include <jflib/timeseries/masked/oper.hpp>


namespace jflib { namespace timeseries { namespace econometric {



template<class TS, template<class,class> class Op, class A> class tsoperator1;

template<class TS, class vtag, class MR>
class tsrolloperator {
public:
	typedef TS									tstype;
	typedef typename tstype::numtype			numtype;
	typedef typename tstype::size_type			size_type;
	typedef typename tstype::const_iterator		const_iterator;
	typedef typename tstype::key_type			key_type;

	BOOST_STATIC_ASSERT(boost::is_floating_point<numtype>::value);

	tsrolloperator(const tstype& ts):m_ts(ts){}
	virtual ~tsrolloperator() {}

	void init()					  {this->iter_init(); this->tempinit();}
	size_type	ts_size()   const {return m_ts.size();}
	size_type	ts_series() const {return m_ts.series();}
	const tstype& ts() const {return m_ts;}
	size_type	masked() const {return m_ts.masked();}

	virtual size_type size()   const {return this->ts_size();}
	virtual size_type series() const {return this->ts_series();}

	// Virtual functions
	virtual void iter_init()			 {m_iter = this->begin();}
	virtual const key_type& date() const {return m_iter->first;}
	virtual bool alive() const			 {return m_iter != this->end();}
	virtual void advance()				 {++m_iter;}
protected:
	tstype			m_ts;
	const_iterator  m_iter;

	const_iterator begin() const {return m_ts.begin();}
	const_iterator end()   const {return m_ts.end();}
	virtual void tempinit(){}
};


template<class TS, class vtag, class MR>
class tsrolloperatorlag: public tsrolloperator<TS,vtag,MR> {
	typedef tsrolloperator<TS,vtag,MR>			super;
public:
	typedef TS									tstype;
	typedef typename tstype::size_type			size_type;
	typedef typename tstype::const_iterator		const_iterator;
	typedef typename tstype::key_type			key_type;

	tsrolloperatorlag(const tstype& ts, size_type lag):super(ts),m_n(lag){
		QM_REQUIRE(m_n,"Lag must be positive");
		QM_REQUIRE(this->ts_size() > m_n + 1,"Analysis not possible. Timeseries too small");
	}

	size_type series() const {return this->ts_series()-1;}

	void iter_init() {
		this->m_iter  = this->begin();
		this->m_iter0 = this->begin();
		for(size_type i=0;i<m_n;++i) ++this->m_iter;
	}

	void advance() {
		++this->m_iter;
		++this->m_iter0;
	}

protected:
	const_iterator  m_iter0;
	size_type		m_n;
};




template<class TS, class vtag, class MR, template<class,class,class> class Op>
class rollanalysis {
public:
	typedef Op<TS,vtag,MR>								optype;
	typedef typename optype::tstype						tstype;
	typedef typename optype::size_type					size_type;
	typedef typename optype::result_type				result_type;
	typedef typename optype::ts_temp_type				ts_temp_type;
	typedef typename optype::ts_result_type				ts_result_type;

	static result_type calc(optype& op) {
		op.init();
		while(op.alive()) {
			op.eval(op.tp);
			op.advance();
		}
		return op.calculate(op.tp,op.size());
	}

	/**
	 * \brief The rolling function.
	 *
	 * @param window,	a positive integer specifying the size of the rolling window
	 * @return a timeserie object
	 */
	static ts_result_type roll(optype& op, size_type window) {
		QM_REQUIRE(op.size() >= window,"window too large for timeserie");
		
		ts_temp_type tsp;
		typename ts_temp_type::iterator io = tsp.begin();
		op.init();
		while(op.alive()) {
			op.eval(op.tp);
			io = tsp.insertexpression(io,0,op.date(),op.tp);
			op.advance();
		}
		size_type rollsize = op.size() - window + 1;
		ts_result_type ret(rollsize, op.series());

		typename ts_temp_type::const_iterator it2 = tsp.begin();
		typename ts_temp_type::const_iterator it1 = tsp.begin();
		for(size_type i=0;i<window;++i) ++it2;

		typename ts_result_type::iterator ir = ret.begin();
		size_type r = 0;
		for(;it2!=tsp.end();++it2) {
			ir = op.insert(ir,ret,r,window,it1,it2);
			++it1;
			++r;
		}
		return ret;
	}
};



}}}


#endif	//	__ECONOMETRIC_OPERATORS_HPP__
