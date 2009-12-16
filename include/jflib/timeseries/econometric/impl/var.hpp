
#ifndef __AUTO_REGRESSION_HPP_
#define __AUTO_REGRESSION_HPP_

#include <jflib/timeseries/econometric/operators.hpp>


namespace jflib { namespace timeseries { namespace econometric { namespace impl {



template<class TS>
class VAR: public linearanalysis<TS,2u> {
	typedef linearanalysis<TS,2u>					super;
public:
	typedef typename super::tstype					tstype;
	typedef typename super::key_type				key_type;
	typedef typename super::size_type				size_type;
	typedef typename super::const_iterator			const_iterator;
	typedef typename super::num_type				num_type;
	typedef typename super::temp_type				temp_type;
	typedef typename super::result_type				result_type;

	VAR(const tstype& ts, size_type n):super(ts),m_n(n){
		QM_REQUIRE(this->tssize() > m_n + 1,"Autoregression not possible. Timeseries too small");
	}

private:
	const_iterator	m_it1, m_it2;
	size_type		m_n;

	const key_type& date() const {return m_it2->first;}

	temp_type eval() const {
		temp_type tv(2);
		tv[0] = m_it2->second * m_it1->second;
		tv[1] = m_it1->second * m_it1->second;
		return tv;
	}

	result_type	calculate(const temp_type& tp, size_type N) const {
		return tp[0]/tp[1];
	}

	void init() {
		m_it1 = this->begin();
		m_it2 = this->begin();
		for(size_type i=0;i<m_n;++i) ++m_it2;
	}

	void advance() {
		++m_it1;
		++m_it2;
	}

	bool alive() {return m_it2 != this->end();}
};

}}}}

#endif	//	__AUTO_REGRESSION_HPP_
