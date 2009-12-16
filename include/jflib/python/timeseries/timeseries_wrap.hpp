

#ifndef __TIMESERIES_WRAP_JFLIB_HPP__
#define __TIMESERIES_WRAP_JFLIB_HPP__


#include <jflib/python/pair_to_tuple.hpp>
#include <jflib/python/timeseries/timeseries_add.hpp>
#include <jflib/python/timeseries/econometric_wrap.hpp>
#include <jflib/timeseries/traits/converters.hpp>
#include <jflib/timeseries/expressions/all.hpp>




namespace jflib { namespace python {


template<class tsmap>
boost::python::list tolist(const tsmap& ts)  {
	typedef typename tsmap::value_type value_type;
	boost::python::list li;
	BOOST_FOREACH( const value_type& k, ts )  {
		li.append(k.first);
	}
	return li;
}


/**
 * \brief Convert timeseries to JSON object
 */
template<class TS>
boost::python::list json(const TS&) {
	boost::python::list l;
	return l;
}


namespace {


	template<class tstype>
	boost::python::list daycount(const tstype& ts, unsigned long window)  {
		typedef typename tstype::value_type 			value_type;
		typedef jflib::templates::maprange<tstype>		rangetype;
		rangetype range(ts,window);
		boost::python::list li;
		unsigned w = 0;
		for(typename rangetype::iterator it=range.begin();it!=range.end();++it) {
			w++;
		}
		for(typename rangetype::iterator it=range.begin();it!=range.end();++it) {
			double a = 0;
			li.append(a);
		}
		return li;
	}


	/**
	 * \brief template for registering timeseries mapped_type to python
	 *
	 * By default do nothing
	 */
	template<class K, class T>
	struct pytsmapped {
		static void reg(const std::string& name) {};
	};


	// BOOST PYTHON WRAPPER FOR A TIMESERIES
	template<class TS, class vtag, class V, class CTag, class MT>
	struct pytsimpl  {
		typedef TS													tstype;
		//typedef jflib::timeseries::numeric::tsoper<tstype>		tsoper;
		typedef typename tstype::key_type							key_type;
		typedef typename tstype::value_type							value_type;
		typedef typename tstype::mapped_type						mapped_type;
		typedef typename tstype::numtype							numtype;
		typedef typename tstype::iterator							iterator;
		typedef typename tstype::size_type							size_type;
		typedef typename tstype::key_iterator						key_iterator;
		typedef typename tstype::val_iterator						val_iterator;
		typedef typename jflib::templates::maprange<tstype>			rangetype;
		typedef jflib::timeseries::tsexpression<tstype>				expr_type;

		static void reg(const std::string& name) {
			namespace py = boost::python;

			//Register mapped_type if needed
			pytsmapped<key_type,mapped_type>::reg(name);

			py::return_value_policy<py::copy_const_reference> ccr;
			std::string exprname  = "_" + name + "_expression";
			std::string rangename = "_" + name + "_range";

			//py::class_<rangetype>(rangename.c_str(),py::init<tstype, size_type>())
			//	.def("__len__",				&rangetype::size)
			//	.add_property("size",		&rangetype::size)
			//	.add_property("range",		&rangetype::range)
			//	.def("__iter__",			py::iterator<rangetype>())
			//	;

			py::class_<tstype> tsp(name.c_str(),"A numeric timeseries object build on a C++ std::map."
							"This timeseries is very efficient in adding and retriving data",py::init<>());
			tsp
				.def(py::init<const std::string&>())
				.def("__str__",				&obj2string<tstype>::get)
				.def("__repr__",			&obj2string<tstype>::get)
				.def("__len__",				&tstype::size)
				.add_property("name",		py::make_function(&tstype::name,ccr))
				.add_property("code",		py::make_function(&tstype::name,ccr))
				.add_property("size",		&tstype::size)
				.add_property("masked",		&tstype::masked)
				.add_property("nseries",	&tstype::series,"Number of time series")
				.add_property("is_valid",	&tstype::is_valid,"True if timeseries are valid")
				.add_property("empty",		&tstype::empty,"true if timeseries are empty")
				.add_property("data",		&tstype::data,"Internal timeseries data")
				.add_property("mask",		&tstype::mask,"mask matrix")
				.def("__setitem__",			&tstype::add)
				.def("__getitem__",			py::make_function(&tstype::at,ccr))
				.def("has_key",				&tstype::has_key,py::arg("key"),"Return true if key is available")
				.def("items",				py::iterator<tstype>(),"Iterator over key-value pairs")
				.def("values",				py::range(pytsimpl::vbegin, pytsimpl::vend),"Iterator over values")
				.def("keys",				py::range(pytsimpl::kbegin, pytsimpl::kend),"Iterator over keys")
				//.def("range",				&rangetype::make,py::arg("range"),"Iterator over ranges")
				.def("daycounts",			jflib::timeseries::tsdcf<tstype,py::list>)
				.def("__iter__",			py::range(pytsimpl::kbegin, pytsimpl::kend),"Iterator over keys")
				.def("front",				py::make_function(&tstype::front,ccr))
				.def("back",				py::make_function(&tstype::back,ccr))
				//.def("json",				json<tstype>)
				.def("apply",				py::make_function(&tstype::apply,ccr))
				.def("copy",				&tstype::copy,py::args("start","end"),"Copy timeseries from start to end")
				.def("clone",				&tstype::clone,"Clone the timeseries")
				.def("tovector",			&jflib::timeseries::traits::tovector<tstype,vtag>::apply,"Conver timeseries to a map vector timeseries structure")
				.def("removemasked",		&tstype::removemasked,"Remove masked values from timeseries")
				.def("addconstant",			&jflib::timeseries::traits::AddTsDummy<tstype>::constant,py::arg("value"),"Add a constant timeseries to self")
				//
				//.def("inner_prod",			jflib::timeseries::inner_prod_expr<tstype,numtype>,py::('weights'),"Inner product")
				;

			MatrixConversion<tstype,CTag>::reg(tsp);
			addts<tstype,V>::reg(tsp);
			pyeconometric<tstype,vtag,MT>::reg(name,tsp);
			pytsoperations<tstype,numtype>::reg(tsp);

			py::class_<expr_type>(exprname.c_str(),"Timeseries expression",py::init<const expr_type&>())
				.add_property("size",		&expr_type::size)
				;
		}

	private:
		//static iterator begin(tstype& x) {return x.begin();}
		//static iterator end(tstype& x) {return x.end();}
		static key_iterator kbegin(tstype& x) {return x.key_begin();}
		static key_iterator kend(tstype& x)   {return x.key_end();}
		static val_iterator vbegin(tstype& x) {return x.val_begin();}
		static val_iterator vend(tstype& x)   {return x.val_end();}
	};


	/**
	 * \brief Structure to register masked arrays
	 */
	template<class K, class D, class M, unsigned F>
	struct pytsmapped<K, jflib::timeseries::maskedvector<D,M,F> > {

		typedef jflib::timeseries::maskedvector<D,M,F>	container;

		static void reg(const std::string& name) {
			namespace py = boost::python;

			std::string mname = name + "_values";

			py::class_<container>(mname.c_str(),py::no_init)
				.def("__str__",				&obj2string<container>::get)
				.def("__repr__",			&obj2string<container>::get)
				.def("__len__",				&container::size)
				.add_property("size",		&container::size)
				.add_property("index",		&container::index)
				.def("__iter__",			py::iterator<container>(),"Iterator over values")
				.add_property("masked",		&container::masked)
				;

			pair_to_tuple<K const,container>::register_to_python();
		}
	};

}


template<class TS, class vtag, class MT = Nil, class V = Nil, class C = Nil>
struct pyts {
	static void reg(const std::string& name) {
		pytsimpl<TS, vtag, V, C, MT>::reg(name);
	}
};



}}



#endif // __TIMESERIES_WRAP_JFLIB_HPP__

