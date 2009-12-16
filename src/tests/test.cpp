
#include <jflib/python/pyconfig.hpp>
#include <jflib/tests/all.hpp>


namespace jflib { namespace python {

	namespace py = boost::python;

	void expose_tests() {
		typedef jflib::tests::TestHandle handle;

		py::class_<handle>("TestHandle",py::init<>())
			.def("ublasmatrix",		&handle::ublasmatrix,"Ublas matrix operations")
			.def("eigenvectors",	&handle::eigenvectors,py::arg("dimension"),"Eigenvectors test")
			;
	}

}}
