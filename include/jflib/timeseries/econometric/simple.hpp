
#ifndef __ECONOMETRIC_SIMPLE_HPP_
#define __ECONOMETRIC_SIMPLE_HPP_

#include <jflib/timeseries/timeseries_base.hpp>


namespace jflib { namespace timeseries {


	struct _delta {
		template<class T>
		static T apply(const T& v0, const T& v1) {return v1-v0;}
	};
	struct _logdelta {
		template<class T>
		static T apply(const T& v0, const T& v1) {return std::log(v1/v0);}
	};

	template<class T>
	struct delta {
		static T apply(const T& v0, const T& v1) {return v1-v0;}
	};
	template<class T>
	struct logdelta {
		static T apply(const T& v0, const T& v1) {return std::log(v1/v0);}
	};
	template<class T>
	struct delta2 {
		static T apply(const T& v0, const T& v1) {return (v1-v0)*(v1-v0);}
	};
	template<class T>
	struct logdelta2 {
		static T apply(const T& v0, const T& v1) {T l = std::log(v1/v0); return l*l;}
	};


	template<class TS, template<class> class Op>
	class EcoSimple {
		typedef typename TS::mapped_type	value_type;
		typedef typename TS::const_iterator	const_iterator;
		typedef Op<value_type>				oper_type;
	public:
		static TS d0oper(const TS& ts) {
			QM_REQUIRE(ts.size()>0,"Time series must have at least one point");
			TS 		   rs;
			for(const_iterator it = ts.begin();it!=ts.end();++it) {
				rs.add(it->first,oper_type::apply(it->second));
			}
			return rs;
		}
		static TS d1oper(const TS& ts) {
			QM_REQUIRE(ts.size()>1,"Time series must have more than one point");
			TS 		   rs;
			value_type v1,v0;
			const_iterator it = ts.begin();
			v1   	= it->second;
			++it;
			for(;it!=ts.end();++it) {
				v0 = v1;
				v1 = it->second;
				rs.add(it->first,oper_type::apply(v0,v1));
			}
			return rs;
		}
	};


	template<class Key, class T, template<class> class Acc>
	struct UnivariateAnalysis {
		typedef timeseries<Key,T,tsmap,tsmap::family>	tstype;
		typedef Acc<T>									accumulator;
		typedef typename accumulator::value_type		value_type;
		typedef typename tstype::const_iterator			const_iterator;

		static value_type apply(const tstype& ts) {
			if(ts.size() <= 1)
				QM_FAIL("Timeseries too short");
			const_iterator it1=ts.begin();
			const_iterator it2=ts.begin();
			it2++;
			accumulator ac(it1->second);
			typename tstype::daycounter dc;
			for(;it2!=ts.end();++it2) {
				ac.push(it1->second, it2->second, dc.dcf(it1->first,it2->first));
				++it1;
			}
			return ac.calculate();
		}
	};

	/**
	 * \brief Calculate annualized univariate statistics for a given timeseries
	 *
	 * *	Annualized return
	 * *	Annualized Standard deviation
	 * *	Max Draw-down
	 */
	template<class T, class diff>
	struct Moments {
		typedef boost::numeric::ublas::bounded_array<T,7> value_type;

		Moments(T x1):m_max(x1), m_dd(0), m_tret(0), m_var(0), m_skew(0), m_kurt(0), m_t(0), m_n(0){}

		void push(T x1, T x2, double dt) {
			m_n++;
			m_t    += dt;
			T r     = diff::apply(x1,x2);
			T r2    = r*r/dt;
			T r1    = std::sqrt(r2);
			m_tret += r;
			m_var  += r2;
			m_skew += r2*r1;
			m_kurt += r2*r2;
			m_max   = std::max(x2, m_max);
			m_dd    = std::max(m_dd, (m_max - x2)/m_max);
		}

		value_type calculate() const {
			value_type		v(7);
			v[0] = m_tret;
			v[1] = std::sqrt(m_var/m_n);
			v[2] = m_skew/(m_var*std::sqrt(m_var));
			v[3] = m_kurt/(m_var*m_var) - 3.;
			v[4] = m_dd;
			v[6] = m_t;
			return v;
		}
	private:
		T		   m_max, m_dd, m_tret, m_var, m_skew, m_kurt, m_t;
		unsigned   m_n;
	};

	template<class T> struct NorMoments: public Moments<T,_delta> {
		NorMoments(T x1):Moments<T,_delta>(x1){}
	};
	template<class T> struct LogMoments: public Moments<T,_logdelta> {
		LogMoments(T x1):Moments<T,_logdelta>(x1){}
	};

}}


#endif	//	__ECONOMETRIC_SIMPLE_HPP_
