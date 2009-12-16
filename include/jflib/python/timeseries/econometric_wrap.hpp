

#ifndef __ECONOMETRIC_PYTHON_WRAP_HPP__
#define __ECONOMETRIC_PYTHON_WRAP_HPP__


#include <jflib/python/pyconfig.hpp>
#include <jflib/python/timeseries/traits.hpp>


namespace jflib { namespace python {


template<class TS, class vtag, class MT>
struct pyeconometric {

	typedef TS																	tstype;
	typedef MT																	matrix_type;
	typedef jflib::timeseries::econometric::analysis<tstype,vtag,matrix_type>	econtype;
	typedef boost::python::class_<tstype>										tsptype;

	static void reg(const std::string& name, tsptype& tsp) {
		namespace py   = boost::python;

		std::string econame = name + "_econometric";

		py::class_<econtype>(econame.c_str(),"econometric analysis handle",py::init<const tstype&>())
			.def(py::init<const econtype&>())
			.add_property("size",	&econtype::size)
			.def("delta",			&econtype::delta,"First order differentiation")
			.def("logdelta",		&econtype::logdelta,"First order log-differentiation")
			.def("sdelta",			&econtype::sdelta,"First order differentiation divided by the squared-root of delta-time")
			.def("slogdelta",		&econtype::slogdelta,"First order log-differentiation divided by the squared-root of delta-time")
			.def("vol",				&econtype::vol,"Standard deviation (volatility) of timeseries")
			.def("roll_vol",		&econtype::roll_vol,py::arg("window"),"Rolling standard deviation (volatility) of timeseries")
			//.def("sharpe",			&econtype::sharpe,"Sharpe ratio of timeseries")
			//.def("roll_sharpe",		&econtype::roll_sharpe,py::arg("window"),"Rolling sharpe ratio of timeseries")
			.def("ar",				&econtype::ar,py::arg("order"),"Auto-regression coefficient")
			.def("roll_ar",			&econtype::roll_ar,py::args("window","order"),"Rolling auto-regression coefficient")
			.def("mdd",				&econtype::mdd,"The maximum drawdown as percentage of pick value")
			.def("var",				&econtype::var,py::arg("order"),"Vector auto-regression for multivariate or auto-regression for univariate timeseries")
			.def("covar",			&econtype::covar,"Covariance matrix evaluation")
			.def("roll_covar",		&econtype::roll_covar,py::arg("window"),"Rolling covariance matrix evaluation")
			.def("correl",			&econtype::correl,"Correlation matrix evaluation")
			.def("roll_correl",		&econtype::roll_correl,py::arg("window"),"Rolling correlation matrix evaluation")
			//.def("coint",			&econtype::coint,py::arg("order"),"Cointegration using Johansen methodology")
			.def("ols",				&econtype::ols,"Ordinary Least Squares")
			;

		tsp.add_property("econometric", py::make_function(&econtype::make),"Econometric handle for timeseries");
	}
};


template<class TS, class vtag>
struct pyeconometric<TS,vtag,Nil> {
	typedef boost::python::class_<TS>						tsptype;
	static void reg(const std::string& name, tsptype& tsp){}
};


template<class TS, class T, class Tag, bool B>
struct pytsoperations_detail {
	typedef boost::python::class_<TS>						tsptype;
	static void reg(tsptype& tsp){}
};

template<class TS, class T>
struct pytsoperations_detail<TS,T,jflib::timeseries::tsmap,true> {
	typedef TS												tstype;
	typedef boost::python::class_<TS>						tsptype;
	static void reg(tsptype& tsp){
		namespace tsop = jflib::timeseries::operators;
		tsp
			.def("__add__", 	&tsop::tsoperator1<tstype,Add>::apply1)
			.def("__add__", 	&tsop::tsoperator2<tstype,Add>::apply)
			.def("__radd__", 	&tsop::tsoperator1<tstype,Add>::apply2)
			.def("__sub__",		&tsop::tsoperator1<tstype,Subtract>::apply1)
			.def("__sub__",		&tsop::tsoperator2<tstype,Subtract>::apply)
			.def("__rsub__",	&tsop::tsoperator1<tstype,Subtract>::apply2)
			.def("__mul__",		&tsop::tsoperator1<tstype,Multiply>::apply1)
			.def("__mul__",		&tsop::tsoperator2<tstype,Multiply>::apply)
			.def("__rmul__",	&tsop::tsoperator1<tstype,Multiply>::apply2)
			.def("__div__",		&tsop::tsoperator1<tstype,Divide>::apply1)
			.def("__div__",		&tsop::tsoperator2<tstype,Divide>::apply)
			.def("__rdiv__",	&tsop::tsoperator1<tstype,Divide>::apply2)
			;
	}
};

template<class TS, class T>
struct pytsoperations: pytsoperations_detail<TS,T,typename TS::tag,boost::is_floating_point<T>::value> {};



}}

#endif	//	__ECONOMETRIC_PYTHON_WRAP_HPP__

