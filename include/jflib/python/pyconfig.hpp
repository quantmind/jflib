//
/// @defgroup python
/// @defgroup python_bloomberg
/// \file
/// \brief Configuration file for python wrappers
//
#ifndef   __WRAP_PYTHON_CONFIG_JFLIB_HPP__
#define   __WRAP_PYTHON_CONFIG_JFLIB_HPP__
//
/// \brief Boost Python Pure Virtual overaload flag for Microsoft Visual Studio
#define BOOST_PYTHON_MSVS_VIRTUAL         1300
//
/// \brief Boost Python Pure Virtual overaload flag for Microsoft Visual Studio
#define BOOST_PYTHON_MSVS_VIRTUAL_BASE    1500
//
//
//
//
#include <jflib/jflib.hpp>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/detail/prefix.hpp>
#include <boost/python/converter/return_from_python.hpp>
#include <boost/python/call.hpp>


namespace jflib {

template<>
struct obj2string<boost::python::object> {
	static std::string get(const boost::python::object& obj) {
		return boost::python::extract<std::string>(obj.attr("__str__")());
	}
};

template<class T>
struct appendtocontainer<boost::python::list, T > {
	typedef boost::python::list container;
	static void push_back(container& co, const T& val) {
		co.append(val);
	}
};

}
//
//
//
//
//
#endif // __WRAP_PYTHON_CONFIG_JFLIB_HPP__
//
