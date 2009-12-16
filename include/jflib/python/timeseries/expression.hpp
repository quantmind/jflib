

#ifndef __TIMESERIES_EXPRESSION_PYTHON_WRAP_HPP__
#define __TIMESERIES_EXPRESSION_PYTHON_WRAP_HPP__


#include <jflib/python/pair_to_tuple.hpp>
#include <jflib/timeseries/expr.hpp>



namespace jflib { namespace python {


template<class TS>
struct pytsexpression {
	typedef TS						tstype;
	typedef tsexpression<tstype>	expression;

	static void reg(const std::string& name) {
		namespace py = boost::python;

		py::class_<expression>(name.c_str(),py::init<const expression&>())
			.add_property("size",		&expression::size)
			.def('apply',				&expression::apply)
			;
	}
};



}}


#endif	//	__TIMESERIES_EXPRESSION_PYTHON_WRAP_HPP__



