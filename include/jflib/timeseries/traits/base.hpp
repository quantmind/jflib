
#ifndef __TIMESERIES_TRAITS_HPP__
#define __TIMESERIES_TRAITS_HPP__


namespace jflib { namespace timeseries { namespace traits {


template<class Key, class Value, class Tag>
class ts {
	typedef typename Tag::template container<Key,Value>	container;
public:
	typedef typename container::numtype			numtype;
	typedef typename container::super			super;
	typedef typename container::type			type;
};



}}}


#endif	//	__TIMESERIES_TRAITS_HPP__

