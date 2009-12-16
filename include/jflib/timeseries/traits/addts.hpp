

#ifndef __ADD_TIMESERIES_HPP__
#define __ADD_TIMESERIES_HPP__

#include <jflib/timeseries/timeseries_map.hpp>
#include <jflib/timeseries/structures.hpp>

namespace jflib { namespace timeseries { namespace traits {


template<class TS1, class TS2>
struct AddTs {
	TS1 apply(TS1& ts1, const TS2& ts2) {
		QM_FAIL("Adding timeseries is not possible for this type");
	}
};

template<class TS>
struct AddTsDummy {
	typedef typename TS::numtype	numtype;
	TS constant(TS& ts, numtype v) {
		QM_FAIL("Adding timeseries constant is not possible for this type");
	}
};


/**
 * \breif Add a tsmap to a timeseries vector map
 */
template<class K, class T, class tag1, class tag2>
struct AddTs<timeseries<K,T,tag1,0u,true>, timeseries<K,T,tag2,tag2::family,tag2::multipleseries> > {
	typedef timeseries<K,T,tag1,0u,true>								TS1;
	typedef timeseries<K,T,tag2,tag2::family,tag2::multipleseries>		TS2;
	typedef typename TS1::iterator										iterator;
	typedef typename TS1::value_type									value_type;
	typedef typename TS1::size_type										size_type;
	typedef typename TS1::mapped_type									mapped_type;

	static TS1 apply(TS1& ts1, const TS2& ts2) {
		if(ts2.empty())
			return ts1;

		iterator  i1 = ts1.begin();
		size_type  S = ts1.series();
		size_type S2 = ts1.series();


		// if timeserie is empty simply copy timeserie2
		if(!S) {
			size_type r = 0;
			for(typename TS2::const_iterator it=ts2.begin();it!=ts2.end();++it) {
				i1 = ts1.insertexpression(i1,r++,it->first,it->second);
			}
		}
		else {
			// Loop over timeseries 2
			for(typename TS2::const_iterator it=ts2.begin();it!=ts2.end();++it) {
				i1 = ts1.lower_bound(it->first);

				if(i1 != ts1.end()) {
					// Found data with same date, append to vector
					if(i1->first == it->first) {
						i1->second.push_back(it->second);
					}
					// No data found
					else {
						mapped_type ne(S);
						ne.push_back(it->second);
						ts1.insert(i1,value_type(it->first,ne));
					}
				}
				else {
					mapped_type ne(S);
					ne.push_back(it->second);
					ts1.insert(value_type(it->first,ne));
				}
			}

			// And now check for othe missing values
			for(i1 = ts1.begin(); i1!= ts1.end(); ++i1) {
				if(i1->second.size() == S)
					i1->second.push_empty(S2);
			}
		}
		return ts1;
	}
};

/*
template<class K, class T, class tag1, class tag2>
struct AddTs<timeseries<K,T,tag1,0u,true>, timeseries<K,T,tag2,tag2::family,true> > {
	typedef timeseries<K,T,tag1,0u,true>			TS1;
	typedef timeseries<K,T,tag2,tag2::family,true>	TS2;
	typedef typename TS1::iterator					iterator;
	typedef typename TS1::value_type				value_type;
	typedef typename TS1::size_type					size_type;
	typedef typename TS1::mapped_type				mapped_type;

	static TS1 apply(TS1& ts1, const TS2& ts2) {
		if(ts2.empty())
			return ts1;

		iterator  i1 = ts1.begin();
		size_type  S = ts1.series();
		size_type NS = ts2.series();

		// if timeserie is empty simply copy timeserie2
		if(!S) {
			size_type r = 0;
			for(typename TS2::const_iterator it=ts2.begin();it!=ts2.end();++it) {
				i1 = ts1.insertexpression(i1,r++,it->first,it->second);
			}
		}
		else {
			// Loop over timeseries 2
			for(typename TS2::const_iterator it=ts2.begin();it!=ts2.end();++it) {
				i1 = ts1.lower_bound(it->first);
				if(i1 != ts1.end()) {
					if(i1->first == it->first) {
						i1->second.push_back(it->second);
					}
					else {
						ts1.insert(i1,value_type(it->first,mapped_type(S,it->second)));
					}
				}
				else {
					ts1.insert(value_type(it->first,mapped_type(S,it->second)));
				}
			}

			// And now check for missing values
			size_type s;
			for(i1 = ts1.begin(); i1!= ts1.end(); ++i1) {
				if(i1->second.size() == S)
					for(s=0;s<NS;++s)
						i1->second.push_empty();
			}
		}
		return ts1;
	}
};
*/


template<class K, class T, class tag>
struct AddTsDummy<timeseries<K,T,tag,0u,true> > {
	typedef timeseries<K,T,tag,0u,true>				tstype;
	typedef typename tstype::iterator				iterator;
	typedef typename tstype::numtype				numtype;

	static tstype constant(tstype& ts, numtype v) {
		for(iterator it=ts.begin();it!=ts.end();++it) {
			it->second.push_back(v);
		}
		return ts;
	}
};

template<class K, class T, class tag>
struct AddTsDummy<timeseries<K,T,tag,1u,true> > {
	typedef timeseries<K,T,tag,1u,true>				tstype;
	typedef typename tstype::iterator				iterator;
	typedef typename tstype::size_type				size_type;
	typedef typename tstype::numtype				numtype;

	static tstype constant(tstype& ts, numtype v) {
		size_type N = ts.size();
		if(!N)
			return ts;
		size_type S = ts.series();
		ts.internal_data().resize(N,S+1);
		for(size_type r=0;r<N;++r)
			ts.internal_data()(r,S) = v;
		return ts;
	}
};



}}}


#endif		//	__ADD_TIMESERIES_HPP__
