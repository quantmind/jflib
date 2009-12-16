
#include <jflib/python/pyconfig.hpp>
#include <jflib/templates/buffer.hpp>


namespace jflib { namespace python {

	namespace py    = boost::python;

	void tools_wrap() {
		typedef jflib::qm_buffer<long> ubuffer;
		py::return_value_policy<py::copy_const_reference> ccr;

		py::class_<ubuffer>("ubuffer","long buffer",py::init<int>())
			.def("__len__",				&ubuffer::size)
			.def("__setitem__",			&ubuffer::set_slow)
			.def("__getitem__",			make_function(&ubuffer::get_slow,ccr))
			;
	}

}}
