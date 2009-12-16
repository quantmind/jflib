/**\file
 * \brief date class specification
 * \ingroup dates
 *
 * This class wraps basic functionalities of boost_date_time and introduces several
 * methods for daycounting. This is a minimal class for financial date calculation.
 *
 * The full potential of the boost date_time library can be seen at
 * http://www.boost.org/doc/html/date_time.html
 */

#ifndef __BOOSTDATE_JFLIB_HPP__
#define __BOOSTDATE_JFLIB_HPP__

#include <jflib/datetime/juldate.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/ptime.hpp>


namespace jflib  {


class qdate : public basedate {
public:
	typedef	boost::gregorian::date							date_type;
	typedef date_type::calendar_type						calendar_type;
	typedef boost::gregorian::day_iterator					day_iterator;
	typedef boost::gregorian::week_iterator					week_iterator;
	typedef boost::gregorian::first_day_of_the_week_after	first_day_of_the_week_after;

	qdate(){}
	qdate(const juldate& dte){}
	qdate(const date_type& dte):m_date(dte){}
	qdate(const qdate& dte):m_date(dte.m_date){}
	qdate(int y, int m, int d):m_date(y,m,d){}
	//Unrelated but handy function to calculate Unix timestamp from GMT
	boost::int64_t  timegm()		  const;

	qdate& operator = (qdate const& other) {m_date = other.m_date; return *this;}
	qdate& operator = (date_type const& other) {m_date = other; return *this;}

	int   year()          const  {return m_date.year();}
	int   month()         const  {return m_date.month();}
	int   day()           const  {return m_date.day();}
	short day_of_week()   const  {return m_date.day_of_week();}
	qdate end_of_month()  const  {return qdate(m_date.end_of_month());}
	bool  isvalid()       const  {return !m_date.is_not_a_date();}
	bool  isweekend()     const  {short dow = m_date.day_of_week(); return dow == 0 || dow == 6;}
	qdate nextweekday(unsigned short w) {first_day_of_the_week_after fdaf(w); return fdaf.get_date(m_date);}

	bool operator <  (const qdate& rhs) const {return m_date < rhs.m_date;}
	bool operator >  (const qdate& rhs) const {return m_date > rhs.m_date;}
	bool operator <= (const qdate& rhs) const {return m_date <= rhs.m_date;}
	bool operator >= (const qdate& rhs) const {return m_date >= rhs.m_date;}
	bool operator == (const qdate& rhs) const {return m_date == rhs.m_date;}

	long inner() const  {return m_date.day_number();}
	const date_type&  boostdate() const {return m_date;}
	operator date_type() const {return m_date;}
	//const date_type&  operator () const {return m_date;}
	//date_type&  operator () {return m_date;}

	/// \brief Number of days between two dates
	///
	///@param start The start qdate
	///@param end The end qdate
	///@return The number of days between start nad end
	static long daydiff(const qdate& start, const qdate& end)  {
		return (end.m_date - start.m_date).days();
	}
protected:
	date_type	m_date;
};

inline boost::int64_t qdate::timegm() const {
	return 86400*(m_date.day_number() - 2440588);
}


REGISTER2STRING(qdate);



}

#endif	//	__BOOSTDATE_JFLIB_HPP__

