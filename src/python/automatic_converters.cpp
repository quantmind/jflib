
#include <jflib/python/pair_to_tuple.hpp>
#include <jflib/python/date_converter.hpp>
#include <jflib/python/ublas.hpp>
#include <jflib/datetime/date.hpp>


namespace jflib { namespace python {

	void automatic_converters()  {
		namespace py    = boost::python;

		pair_to_tuple<double const,py::object>::register_to_python();
		pair_to_tuple<double const,double>::register_to_python();

		pair_to_tuple<jflib::qdate const,py::object>::register_to_python();
		pair_to_tuple<jflib::qdate const,double>::register_to_python();

		pair_to_tuple<double,bool>::register_to_python();

		DateFromPy<qdate>::reg();
		
		/*
		ublas_bounded_array_to_list<double,1>::register_to_python();
		ublas_bounded_array_to_list<double,2>::register_to_python();
		ublas_bounded_array_to_list<double,3>::register_to_python();
		ublas_bounded_array_to_list<double,4>::register_to_python();
		ublas_bounded_array_to_list<double,5>::register_to_python();
		ublas_bounded_array_to_list<double,6>::register_to_python();
		ublas_bounded_array_to_list<double,7>::register_to_python();
		ublas_bounded_array_to_list<double,8>::register_to_python();
		ublas_bounded_array_to_list<double,9>::register_to_python();
		ublas_bounded_array_to_list<double,10>::register_to_python();
		*/
	}

}}
