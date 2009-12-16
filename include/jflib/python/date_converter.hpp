
#ifndef __DATE_CONVERTER_HPP__
#define __DATE_CONVERTER_HPP__

#include <jflib/python/pyconfig.hpp>
#include <datetime.h>


namespace jflib { namespace python {

	/** \brief Automatic coversion from python.datetime.date
	 *	to a D object. A D object must have a constructor of the form
	 *  D date(year,month,day)
	 *  */
	template<class D>
	struct DateFromPy  {
		//
		static void* convertible(PyObject* obj_ptr)  {
			PyDateTime_IMPORT;
			if(PyDate_Check(obj_ptr) || PyDateTime_Check(obj_ptr)) return obj_ptr;
			return 0;
		}

		//
		static void construct(PyObject* obj_ptr,
		                      boost::python::converter::rvalue_from_python_stage1_data* data)
		{
			PyDateTime_IMPORT;
			int y = PyDateTime_GET_YEAR(obj_ptr);
			int m = PyDateTime_GET_MONTH(obj_ptr);
			int d = PyDateTime_GET_DAY(obj_ptr);
			D* dte = new D(y,m,d);
			data->convertible = (void*)dte;
		}

		static void reg()  {
			boost::python::converter::registry::push_back(&DateFromPy::convertible,
														  &DateFromPy::construct,
														  boost::python::type_id<D>());
		}
	};

}}

#endif // __PAIR_TO_TUPLE_JFLIB_HPP__
