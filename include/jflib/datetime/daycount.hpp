
#ifndef		__DAY_COUNTERS_HPP__
#define		__DAY_COUNTERS_HPP__

#include <jflib/error.hpp>
#include <jflib/datetime/utils.hpp>

namespace jflib  {

template<class D>
class Act360 {
public:
	typedef D	date_type;
	virtual ~Act360(){}
  	virtual long  	daycount(const date_type& start, const date_type& end) const    {return date_type::daydiff(start,end);}
   	virtual double  dcf(const date_type& start, const date_type& end) const         {return this->daycount(start,end)/360.0;}
};

template<class D>
class Act365: public Act360<D>  {
public:
	typedef D	date_type;
	double dcf(const date_type& start, const date_type& end) const {
		return this->daycount(start,end)/365.0;
	}
};

template<class D>
class ActAct: public Act360<D>  {
public:
	typedef D	date_type;
	double dcf(const date_type& start, const date_type& end) const {
		return ActActYears(end) - ActActYears(start);
	}
};


template<class D>
class thirty360: public Act360<D>  {
public:
	typedef D	date_type;
    long daycount(const qdate& start, const qdate& end) const {
    	unsigned d1 = start.day();
    	unsigned d2 = end.day();
    	if (d1 == 31) d1 = 30;
    	if (d1 == 30 && d2 == 31) d2 = 30;
    	return counting30360(d1,d2,start.month(),end.month(),start.year(),end.year());
    }
};


}

#endif	//	__DAY_COUNTERS_HPP__

