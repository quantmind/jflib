
#include <jflib/python/pyconfig.hpp>
#include <jflib/python/all.hpp>
#include <jflib/tests/all.hpp>

#ifdef	__JFLIB_UBLAS_NUMPY_CONVERSION__
#include <jflib/python/numpy/all.hpp>
#endif	//	__JFLIB_UBLAS_NUMPY_CONVERSION__



#	ifdef NDEBUG
BOOST_PYTHON_MODULE(_jflib)  {
	boost::python::scope().attr("__version__") = "0.10";
#	else
BOOST_PYTHON_MODULE(_jflib_debug)  {
    boost::python::scope().attr("__version__") = "0.10 Debug";
#	endif

    boost::python::scope().attr("__doc__") = "jflow c++ library";
	using namespace jflib::python;

	automatic_converters();
	tools_wrap();
	datetime_wrap();
	timeseries_wrap();
	taplefunction_wrap();

	expose_tests();


#	ifdef	__JFLIB_UBLAS_NUMPY_CONVERSION__
	using namespace jflib::python::numpy;
	numpy_expose_converters();
#	endif	//	__JFLIB_UBLAS_NUMPY_CONVERSION__
}


