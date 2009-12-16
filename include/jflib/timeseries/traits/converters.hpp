
#ifndef __TIMESERIES_CONVERTERS_HPP__
#define __TIMESERIES_CONVERTERS_HPP__

#include <jflib/timeseries/traits/addts.hpp>


namespace jflib { namespace timeseries { namespace traits {

template<class Key, class T, class tag, unsigned F, bool M, class vtag, unsigned vF, bool vM>
struct tovector_detail {
	typedef timeseries<Key,T,tag,F,M>						tstype;
	typedef timeseries<Key,T,vtag,vF,vM>					tsvector;
	static tsvector apply(const tstype& ts) {
		QM_FAIL("Cannot convert timeseries to timeseries vector");
	}
};

template<class TS, class vtag>
struct tovector: tovector_detail<typename TS::key_type,
								 typename TS::numtype,
								 typename TS::tag,
								 TS::family,
								 TS::multipleseries,
								 vtag,
								 vtag::family,
								 vtag::multipleseries> {};



template<class Key, class T, class tag, class vtag>
struct tovector_detail<Key,T,tag,0u,false,vtag,0u,true> {
	typedef timeseries<Key,T,tag,0u,false>			tstype;
	typedef timeseries<Key,T,vtag,0u,true>			tsvector;

	static tsvector apply(const tstype& ts) {
		tsvector tv;
		AddTs<tsvector,tstype>::apply(tv,ts);
		return tv;
	}
};

template<class Key, class T, class tag>
struct tovector_detail<Key,T,tag,0u,true,tag,0u,true> {
	typedef timeseries<Key,T,tag,0u,true>		tstype;

	static tstype apply(const tstype& ts) {
		return ts;
	}
};

template<class Key, class T, class tag, class vtag>
struct tovector_detail<Key,T,tag,1u,true,vtag,0u,true> {
	typedef timeseries<Key,T,tag,1u,true>			tstype;
	typedef timeseries<Key,T,vtag,0u,true>			tsvector;

	static tsvector apply(const tstype& ts) {
		QM_FAIL("This type of conversion is not implemented yet");
	}
};



}}}

#endif	//	__TIMESERIES_CONVERTERS_HPP__


