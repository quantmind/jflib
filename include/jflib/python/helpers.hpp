


#ifndef __PYTHON_HELPERS_HPP__
#define __PYTHON_HELPERS_HPP__

#include <jflib/error.hpp>
#include <boost/python.hpp>
#include <vector>


#define PYUBLAS_PYERROR(TYPE, REASON)		\
{											\
  PyErr_SetString(PyExc_##TYPE, REASON);	\
  throw boost::python::error_already_set(); \
}




namespace jflib { namespace python  {

	template <typename T>
	inline PyObject *pyobject_from_new_ptr(T* ptr)  {
		return typename boost::python::manage_new_object::apply<T *>::type()(ptr);
	}

	/// \brief python handle object from a pointer to T
	///
	/// @param ptr a pointer to T. T must be either a type derived from PyObject
	/// or a POD type (http://www.boost.org/doc/libs/1_37_0/libs/python/doc/v2/definitions.html#POD)
	/// @return a boost::python::handle object (a smart pointer to a python object type).
	template <typename T>
	inline boost::python::handle<> handle_from_new_ptr(T* ptr)  {
		return boost::python::handle<>(
			typename boost::python::manage_new_object::apply<T *>::type()(ptr));
	}

	template <typename T>
	inline boost::python::handle<> handle_from_existing_ptr(T *ptr) {
		return boost::python::handle<>(
			typename boost::python::reference_existing_object::apply<T *>::type()(ptr)
        );
	}

	template <typename T>
	inline boost::python::handle<> handle_from_existing_ref(T &ptr) {
		return boost::python::handle<>(
			typename boost::python::reference_existing_object::apply<T &>::type()(ptr)
			);
	}

	inline boost::python::handle<> handle_from_object(const boost::python::object &obj)	{
		return boost::python::handle<>(boost::python::borrowed(obj.ptr()));
	}

	template <typename T>
	inline boost::python::handle<> handle_from_rvalue(const T &val) {
		boost::python::object obj(val);
		return handle_from_object(obj);
	}

	template<class T>
	inline void ListToVector(boost::python::list const& li, std::vector<T>& ve)  {
		unsigned N = boost::python::extract<unsigned>(li.attr("__len__")());
		try  {
	      for(unsigned i=0;i<N;++i)
	        ve.push_back(boost::python::extract<T>(li[i]));
	    }
	    catch(...)  {
			QM_FAIL("could not convert python list to target vector");
	    }
	}
}}


#endif	//	__PYTHON_HELPERS_HPP__


