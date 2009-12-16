///////////////////////////////////////////////////////////////////////////////
/// \file time_series_base.hpp
/// The Curiously Recurring Template Pattern (CRTP) base class for all series.
/// This is used for static polymorphism.
//

#ifndef __TIMESERIES_BASE_HPP_
#define __TIMESERIES_BASE_HPP_

#include <jflib/jflib.hpp>


namespace jflib { namespace timeseries {

class timeseries_root {
public:
};

/**
 * \brief Base class for timeseries
 */
template<typename Derived>
class timeseries_base: public timeseries_root   {
public:
	typedef Derived derived_type;

    Derived& cast()  {
		return *static_cast<Derived *>(this);
    }
    Derived const& cast() const  {
		return *static_cast<Derived const *>(this);
	}
};

/**
 * Forward declaration of timeseries and masked vectors
 */
template<class Key, class T, class Tag, unsigned F, bool M> class timeseries;
template<class, class, unsigned> class maskedvector;
template<class> class maskedvectorelem;
template<class Key> struct daycountertype;
template<class TS, bool S = false>	struct ts_data_range;



template<class TS, class C>
C tsdcf(const TS& ts, long window) {
	typedef typename TS::const_iterator iterator;
	typedef typename TS::key_type		key_type;
	typedef typename TS::daycounter		daycounter;
	QM_REQUIRE(window>0,"Window for timeseries day count must be a positive number");
	long mw = 0;
	daycounter	dcounter;
	iterator start = ts.begin();
	iterator end   = ts.begin();
	C c;
	for(;end!=ts.end();++end) {
		if(mw == window) break;
		mw++;
	}
	if(mw < window) return c;

	for(;end!=ts.end();++end) {
		appendtocontainer<C,double>::push_back(c,dcounter.dcf(start->first,end->first));
		++start;
	}
	return c;
}


namespace {

	template<class T>
	struct count_masked_values {
		static unsigned long apply(const T& v) {return 0;}
	};

	template<class T>
	inline unsigned long masked_values(const T& v) {
		return count_masked_values<T>::apply(v);
	}

	template<class T>
	struct maskedvalue {
		static T value() {T v; return v;}
	};

#	define MASKEDNA(name)														\
	template<> struct maskedvalue<name> {										\
		static name value() {return std::numeric_limits<name>::quiet_NaN();}	\
	};

	MASKEDNA(float)
	MASKEDNA(double)

}



}}


// STRING REPRESENTATIONS

namespace jflib {


template<class K, class T, class Tag, unsigned F, bool M>
struct obj2string<jflib::timeseries::timeseries<K,T,Tag,F,M> > {
	typedef jflib::timeseries::timeseries<K,T,Tag,F,M> tstype;
	static std::string get(const tstype& ts) {
		bool first = true;
		std::string d;
		for(typename tstype::const_iterator it=ts.begin();it!=ts.end();++it) {
			if(!first)
				d += "\n";
			first = false;
			d += obj2str(it->first) + ": " + obj2str(it->second);
		}
		return d;
	}
};

/**
 * \brief	Export to python the maskedvector
 */
template<class T, class M, unsigned F>
struct obj2string<jflib::timeseries::maskedvector<T,M,F> > {
	typedef jflib::timeseries::maskedvector<T,M,F> masked_type;
	static std::string get(const masked_type& ts) {
		std::string d = "[";
		bool first = true;
		for(typename masked_type::const_iterator it=ts.begin();it!=ts.end();++it) {
			if(!first)
				d+=", ";
			first = false;
			d += obj2str(*it);
		}
		d+="]";
		return d;
	}
};

template<class T>
struct obj2string<jflib::timeseries::maskedvectorelem<T> > {
	typedef jflib::timeseries::maskedvectorelem<T> masked_type;
	static std::string get(const masked_type& ts) {
		if(ts.get_mask())
			return obj2str(ts.get_data());
		else
			return "#N/A";
	}
};


}

#endif	//	__TIMESERIES_BASE_HPP_

