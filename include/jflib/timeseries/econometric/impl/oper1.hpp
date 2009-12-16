
#ifndef __ECONOMETRIC_OPERATOR1__HPP__
#define __ECONOMETRIC_OPERATOR1__HPP__

#include <jflib/timeseries/econometric/operators.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>


namespace jflib { namespace timeseries { namespace econometric {

template<class TS, template<class,class> class Op>
class tsoperator1<TS, Op, Nil> {
public:
	typedef TS										tstype;
	typedef typename tstype::size_type				size_type;
	typedef typename tstype::const_iterator 		const_iterator;
	typedef typename tstype::iterator 				iterator;
	typedef typename tstype::value_type				value_type;
	typedef typename tstype::mapped_type			mapped_type;
	typedef Op<mapped_type,mapped_type>				op_type;
	static tstype apply(const tstype& ts);
};

template<class TS, template<class,class> class Op, template<class> class D>
class tsoperator1<TS, Op, D<typename TS::numtype> > {
public:
	typedef TS										tstype;
	typedef typename tstype::size_type				size_type;
	typedef typename tstype::const_iterator 		const_iterator;
	typedef typename tstype::iterator 				iterator;
	typedef typename tstype::value_type				value_type;
	typedef typename tstype::mapped_type			mapped_type;
	typedef typename tstype::daycounter				daycounter;
	typedef Op<mapped_type,mapped_type>				op_type;
	typedef D<typename TS::numtype>					time_oper;
	static tstype apply(const tstype& ts);
};



template<class TS, template<class,class> class Op>
TS tsoperator1<TS, Op, Nil>::apply(const TS& ts) {
	QM_REQUIRE(ts.size() > 1,"Timeseries is too small");
	QM_REQUIRE(!ts.masked(),"Timeseries has masked values. Cannot perform operation");
	tstype re(ts.size()-1,ts.series());
	const_iterator it2 = ts.begin();
	++it2;
	const_iterator it1 = ts.begin();
	iterator io		   = re.begin();
	size_type		 r = 0;
	for(;it2!=ts.end();++it2) {
		io = re.insertexpression(io, r, it2->first, op_type::apply(it2->second,it1->second));
		r++;
		++it1;
	}
	return re;
}

template<class TS, template<class,class> class Op, template<class> class D>
TS tsoperator1<TS, Op, D<typename TS::numtype> >::apply(const TS& ts) {
	QM_REQUIRE(ts.size() > 1,"Timeseries is too small");
	QM_REQUIRE(!ts.masked(),"Timeseries has masked values. Cannot perform operation");
	daycounter dc;
	tstype re(ts.size()-1,ts.series());
	const_iterator it2 = ts.begin();
	++it2;
	const_iterator it1 = ts.begin();
	iterator io		   = re.begin();
	size_type		 r = 0;
	for(;it2!=ts.end();++it2) {
		double c = time_oper::apply(dc.dcf(it1->first,it2->first));
		io = re.insertexpression(io, r, it2->first, op_type::apply(it2->second,it1->second)/c);
		r++;
		++it1;
	}
	return re;
}

}}}

#endif	//	__ECONOMETRIC_OPERATOR1__HPP__


