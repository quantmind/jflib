/**
 * \brief Timeseries utility traits
 */

#ifndef __TIMESERIES_UTILS_TRAITS_HPP_
#define __TIMESERIES_UTILS_TRAITS_HPP_

#include <jflib/timeseries/traits/base.hpp>


namespace jflib { namespace timeseries { namespace traits {


template<class TS>
struct CalcNumSeries;


template<bool,bool>	struct CopyRow;


template<class Key, class T, class Tag, unsigned F>
struct CalcNumSeries<timeseries<Key,T,Tag,F,false> > {
	typedef timeseries<Key,T,Tag,F,false> 	tstype;

	static unsigned apply(const tstype& ts) {
		return 1;
	}
};

template<class Key, class T, class Tag>
struct CalcNumSeries<timeseries<Key,T,Tag,0u,true> > {
	typedef timeseries<Key,T,Tag,0u,true>	tstype;

	static unsigned apply(const tstype& ts) {
		if(ts.empty())
			return 0;
		else
			return ts.front().second.size();
	}
};


template<>
struct CopyRow<true,true> {
	template<class T1, class T2>
	static void copy(const T1& c1, T2& c2) {
		typename T1::const_mask_iterator 	m1 = c1.mask_begin();
		typename T2::iterator 				d2 = c2.begin();
		typename T2::mask_iterator 			m2 = c2.mask_begin();

		for(typename T1::const_iterator d1 = c1.begin();d1!=c1.end();++d1) {
			*d2 = *d1;
			*m2 = *m1;
			++m1;
			++d2;
			++m2;
		}
	}
};

template<>
struct CopyRow<false,true> {
	template<class T1, class T2>
	static void copy(const T1& c1, T2& c2) {
		typename T2::iterator 				d2 = c2.begin();
		typename T2::mask_iterator 			m2 = c2.mask_begin();
		*d2 = c1;
		*m2 = T2::not_masked_value;
	}
};


}}}


#endif	//	__TIMESERIES_UTILS_TRAITS_HPP_
