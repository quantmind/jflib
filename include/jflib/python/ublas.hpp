

#ifndef __UBLAS_PYTHON_JFLIB_HPP__
#define __UBLAS_PYTHON_JFLIB_HPP__

#include <jflib/python/pyconfig.hpp>
#include <jflib/ublas/base.hpp>


namespace jflib { namespace python {

namespace ublas = boost::numeric::ublas;

template<class P>
void expose_matrix_proxy(const std::string& name, const std::string& info)  {
	typedef P	proxy_type;
	using namespace boost::python;

	class_<proxy_type>(name.c_str(),info.c_str(),no_init)
		.def("__len__",			&proxy_type::size)
		.add_property("index",	&proxy_type::index)
		.def("__iter__",		iterator<proxy_type>(),"Iterator over elements")
		;
}


	template<class T, unsigned N>
	struct ublas_bounded_array_to_list  {
		typedef ublas_bounded_array_to_list<T,N>	converter;
		typedef ublas::bounded_array<T,N>			storage_type;
		typedef ublas::vector<T,storage_type>		array_type;

		static PyObject* convert(array_type const& v)  {
			boost::python::list li;
			for(typename array_type::const_iterator it=v.begin();it!=v.end();++it)
				li.append(*it);
			return boost::python::incref(li.ptr());
		}
		static void register_to_python()  {
			boost::python::to_python_converter<array_type,converter>();
		}
	};


}}

#endif // __UBLAS_PYTHON_JFLIB_HPP__
