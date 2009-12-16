

#include <jflib/python/pyconfig.hpp>
#include <jflib/templates/tablefunc.hpp>
#include <boost/python/stl_iterator.hpp>




namespace jflib { namespace python {

namespace ts = jflib::templates;
namespace py = boost::python;

template<class K, class T>
struct tablefuncname {};

template<>
struct tablefuncname<double,double> {
	static std::string name() {return "tablefunction";}
};


template<class K, class T>
struct exposetablefunc {
	typedef ts::tablefunction<K,T>		tfunc;
	typedef typename tfunc::value_type	value_type;
	typedef tablefuncname<K,T>			tname;

	static std::string repr(const tfunc& f) {
		return tname::name() + ": "  + f.name();
	}

	static tfunc fromtuplelist(const std::string& name, py::list li) {
		typedef py::stl_input_iterator<py::tuple> tupleiter;
		tupleiter begin(li), end;
		tfunc f(name);
		typename tfunc::iterator io = f.begin();
		for(tupleiter it=begin;it!=end;++it) {
			K k = py::extract<K>((*it)[0]);
			T v = py::extract<K>((*it)[1]);
			io = f.insert(io,value_type(k,v));
		}
		return f;
	}

	static void apply(const std::string& descr) {
		std::string name = tname::name();

		py::class_<tfunc>(name.c_str(),descr.c_str(),py::init<const std::string&>())
			.def("__str__",				repr)
			.def("__repr__",			repr)
			.def("__len__",				&tfunc::size)
			.def("__call__",			&tfunc::at)
			.def("__iter__",			py::iterator<tfunc>(),"Iterator over key-value pairs")
			;

		py::def(name.c_str(),fromtuplelist,py::args("name","tuplelist"),"Create a table function from a list of tuples");
	}
};



void taplefunction_wrap() {

	exposetablefunc<double,double>::apply("A numeric table function");
}


}}


