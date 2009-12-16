
#include <jflib/python/pyconfig.hpp>
#include <jflib/datetime/date.hpp>
#include <jflib/datetime/daycount.hpp>
#include <jflib/datetime/tcs.hpp>


namespace jflib { namespace python {

	using namespace boost::python;

	template<class D>
	void export_daycounts() {
		typedef Act360<D>	basedc;

		class_<basedc>("Act360",init<>())
			.def("daycount",	&basedc::daycount)
			.def("dcf",			&basedc::dcf)
			;

		class_<Act365<D>, bases<basedc> >("Act365",init<>());
		class_<ActAct<D>, bases<basedc> >("ActAct",init<>());
		class_<thirty360<D>, bases<basedc> >("thirty360",init<>());
	}

	void datetime_wrap() {
		typedef TradingCentreBase<qdate>	tcb;
		typedef TradingCentre<qdate>		tc;
		typedef TradingCentres<qdate>		tcs;

		register_ptr_to_python<boost::shared_ptr<tc> >();

		class_<basedate>("BaseDate","Base class for dates. Not used in python",no_init)
			.def("__str__",				 &basedate::tostring)
			.def("__repr__",			 &basedate::tostring)
			.add_property("year",		 &basedate::year)
			.add_property("month",		 &basedate::month)
			.add_property("day",		 &basedate::day)
			.add_property("day_of_week", &basedate::day_of_week)
			;

		class_<juldate, bases<basedate> >("juldate","Julian datetime object")
    		.add_property("inner",		&juldate::jdate)
    		;

		class_<qdate, bases<basedate> >("boostdate","Date class from boost library",init<>())
			.def(init<int,int,int>())
			.def("nextweekday", &qdate::nextweekday,arg("week day number"),"return the next day of the week corresponding to the input")
			.def("inner",		&qdate::inner)
			.def("timegm",		&qdate::timegm)
			.def(self < self)
			.def(self > self)
			.def(self >= self)
			.def(self <= self)
			.def(self == self)
			;

		class_<tcb>("TradingCentreBase",no_init)
			.def("__str__",					&tcs::code)
			.def("__repr__",				&tcs::code)
			.def("numbizdays",				&tcs::numbizdays)
			.def("isbizday",				&tcs::isbizday)
			.def("nextbizday",				&tcs::nextbizday)
			.def("prevbizday",				&tcs::prevbizday)
			;

		class_<tc, bases<tcb> >("TradingCentres","Trading Centres date iterators",no_init)
			;

		class_<tcs, bases<tcb> >("TradingCentres","Trading Centres date iterators",init<>())
			.add_property("__len__",		&tcs::size)
			;

		def("tradingcentre",&tc::make,arg("code"),"Create a new trading centre");

		export_daycounts<qdate>();
	}

}}
