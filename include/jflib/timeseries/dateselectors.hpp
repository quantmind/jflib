/**
 * \brief Template definition of a timeseries based on a std::map template
 */

#ifndef __TIMESERIES_DATE_SELECTORS_HPP__
#define __TIMESERIES_DATE_SELECTORS_HPP__

#include <jflib/jflib.hpp>
#include <jflib/templates/map.hpp>
#include <jflib/timeseries/timeseries_base.hpp>


namespace jflib { namespace timeseries { namespace {

template<class TS>
struct dateselector {
	typedef TS									tstype;
	typedef typename tstype::key_type			key_type;

	static tstype weekly(const tstype& ts, const key_type& start, const key_type& end,
				  short weekday = 5, short precision = 0, short offset = 1) {
		QM_FAIL("Not available");
	}
};


template<class Key, class T, class Tag, bool M>
struct dateselector<timeseries<Key,T,Tag,0u,M> > {
	typedef timeseries<Key,T,Tag,0u,M>			tstype;
	typedef typename tstype::iterator			iterator;
	typedef typename tstype::const_iterator		const_iterator;
	typedef typename tstype::key_type			key_type;

	// Weekly. By default we choose Friday
	static tstype weekly(const tstype& ts, const key_type& start, const key_type& end,
						 short weekday = 5, short precision = 0, short offset = 1) {
		key_type st(start.nextweekday(weekday));
		short ofst = std::min(std::max(short(0),offset),short(6));
		typename key_type::week_iterator dit(st,ofst);
		tstype out;
		iterator       itou = out.begin();
		const_iterator it;
		const_iterator itend = ts.end();
		for(;dit<=end;++dit) {
			it = ts.find(*dit);
			if(it != itend)
				itou = out.insert(itou,it->second);
		}
		return out;
	}

};


}}}


#endif	//	__TIMESERIES_DATE_SELECTORS_HPP__
