
#ifndef __PROD_TIMESERIES_HPP__
#define __PROD_TIMESERIES_HPP__


namespace jflib { namespace timeseries { namespace traits {

template<class TS>
struct ProdTSV;


template<class Key, class T, class Tag, unsigned F>
struct ts_inner_prod<timeseries<Key,T,Tag,F,false> > {
	typedef timeseries<Key,T,Tag,F,false>				tstype;
	typedef typename tstype::numtype					numtype;

	static tstype apply(const tstype& ts, numtype v) {
		return tstype * numtype;
	}
};

template<class Key, class T, class Tag, unsigned F>
struct ts_inner_prod<timeseries<Key,T,Tag,F,true> > {
	typedef timeseries<Key,T,Tag,F,false>				tstype;
	typedef typename tstype::numtype					numtype;
	typedef typename ts<Key,numtype,tsmap>::type		result_type;
	typedef typename result_type						value_type;
	typedef typename tstype::mapped_type				mapped_type;
	typedef typename mapped_type::vector_type			vector_type;

	static result_type apply(const tstype& ts, vector_type v) {
		result_type re;
		typename result_type::iterator io = re.begin();
		for(typename tstype::const_iterator it=ts.begin();it!=ts.end();++it) {
			io = re.insert(io, value_type(it->first,inner_prod(it->second,v)));
		}
		return re;
	}
};

}}}

#endif	//	__PROD_TIMESERIES_HPP__
