
#ifndef __TIMESERIES_OPERATORS_HPP__
#define __TIMESERIES_OPERATORS_HPP__


namespace jflib { namespace timeseries { namespace operators {


/**
 * Number - timeserie
 */
template<class TS, template<class,class> class Op>
class tsoperator1 {
public:
	typedef TS									tstype;
	typedef typename tstype::key_type			key_type;
	typedef typename tstype::mapped_type		mapped_type;
	typedef typename tstype::size_type			size_type;
	typedef typename tstype::numtype			numtype;
	typedef typename tstype::iterator			iterator;
	typedef typename tstype::const_iterator		const_iterator;
	typedef Op<numtype,mapped_type>				optype;

	static const int complexity = 0;

	static tstype apply1(const tstype& ts, numtype num){
		tstype re;
		iterator io = re.begin();
		size_type r = 0;
		for(const_iterator it=ts.begin(); it!=ts.end(); ++it)  {
			io = re.insertexpression(io,r,it->first,optype::apply(it->second,num));
			++r;
		}
		return re;
	}
	static tstype apply2(const tstype& ts, numtype num){
		tstype re;
		iterator io = re.begin();
		size_type r = 0;
		for(const_iterator it=ts.begin(); it!=ts.end(); ++it)  {
			io = re.insertexpression(io,r,it->first,optype::apply(num,it->second));
			++r;
		}
		return re;
	}
	static tstype applyeq(tstype& ts, numtype num){
		for(const_iterator it=ts.begin(); it!=ts.end(); ++it)  {
			it->second = optype(it->second,num);
		}
		return ts;
	}
};

/**
 * timeserie - timeserie
 */
template<class TS, template<class,class> class Op>
class tsoperator2 {
public:
	typedef TS									tstype;
	typedef typename tstype::key_type			key_type;
	typedef typename tstype::size_type			size_type;
	typedef typename tstype::mapped_type		mapped_type;
	typedef typename tstype::iterator			iterator;
	typedef typename tstype::const_iterator		const_iterator;
	typedef Op<mapped_type,mapped_type>			optype;

	static const int complexity = 1;

	static tstype apply(const tstype& ts1, const tstype& ts2){
		tstype re;
		iterator io = re.begin();
		size_type r = 0;
		for(const_iterator it=ts1.begin(); it!=ts1.end(); ++it)  {
			const_iterator it2 = ts2.find(it->first);
			if(it2 != ts2.end()) {
				io = re.insertexpression(io,r,it->first,optype::apply(it->second,it2->second));
				++r;
			}
		}
		return re;
	}
};


}}}



#endif	//	__TIMESERIES_OPERATORS_HPP__
