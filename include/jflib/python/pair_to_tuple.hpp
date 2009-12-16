

#ifndef __PAIR_TO_TUPLE_JFLIB_HPP__
#define __PAIR_TO_TUPLE_JFLIB_HPP__

#include <jflib/python/pyconfig.hpp>


namespace jflib { namespace python {

	/** \brief Automatic coversion from std::pair<A,B> to python tuple
	*/
	template<class K, class T>
	struct pair_to_tuple  {
		typedef pair_to_tuple<K,T>	converter;
		typedef std::pair<K,T>		ctype;

		static PyObject* convert(ctype const& v)  {
			return boost::python::incref(boost::python::make_tuple(v.first,v.second).ptr());
		}
		static void register_to_python()  {
			boost::python::to_python_converter<ctype,converter>();
		}
	};

	template<class P>
	struct pair_to_tuple2 {
		static void register_to_python()  {
			pair_to_tuple<typename P::first_type, typename P::second_type>::register_to_python();
		}
	};

}}

#endif // __PAIR_TO_TUPLE_JFLIB_HPP__
