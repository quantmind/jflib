
/**
 * \breief	Register timeseries objects and theri functuonality to Python
 *
 * Four timeseries objects are handled
 */


#include <jflib/datetime/date.hpp>
#include <jflib/python/timeseries/timeseries_wrap.hpp>

#include <jflib/python/ublas.hpp>
#include <jflib/python/helpers.hpp>
#include <jflib/python/pair_to_tuple.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace jflib { namespace python {

	// Define some common namespaces
	namespace py    = boost::python;
	namespace ts    = jflib::timeseries;
	namespace ublas = boost::numeric::ublas;

	// Timeseries tags
	typedef ts::tsmap				tsmaptag;			//	simple map-timeserie
	typedef ts::ublas_tsvmap		tsvmaptag;			//	vector map-timeserie
#	ifdef	__JFLIB_UBLAS_NUMPY_CONVERSION__	//	matrix timeserie
	typedef ts::tsnumpy				tsmatrixtag;
#	else
	typedef ts::ublas_tsmatrix		tsmatrixtag;
#	endif

	// Date to use as key
	typedef	qdate										tgtdate;

	// calculation matrix
	//typedef ts::traits::ts<tgtdate,double,tsmatrixtag>::support	ublasmatrix;
	typedef ublas::matrix<double,ublas::column_major>			calcmatrix;

	// Timeseries types_________________________________________________________________________________
	typedef ts::traits::ts<tgtdate,py::object,tsmaptag>::type	tsmapobj;
	typedef ts::traits::ts<tgtdate,double,tsmaptag>::type		tsmap;

	typedef ts::traits::ts<tgtdate,double,tsvmaptag>::type		tsvmap;
	typedef ts::traits::ts<tgtdate,py::object,tsvmaptag>::type	tsvmapobj;

	typedef ts::traits::ts<tgtdate,double,tsmatrixtag>::type	tsmatrix;

	typedef ts::traits::ts<tgtdate,calcmatrix,tsmaptag>::type	tsmapmatrix;
	//__________________________________________________________________________________________________


	template<>
	py::list json<tsmap>(const tsmap& rhs)  {
		typedef tsmap::const_iterator const_iterator;
		py::list li;
		boost::int64_t mul = 1000;
		boost::int64_t res;
		for(const_iterator it = rhs.begin(); it != rhs.end(); ++it)  {
			res = mul*it->first.timegm();
			li.append(py::make_tuple(res,it->second));
		}
		return li;
	}


	void timeseries_wrap() {
		//typedef ts::numeric::tsoper	tsoper;

		// MPL vector for implementing addts method
		typedef boost::mpl::vector3<tsmap,tsvmap,tsmatrix>	ts_add_types;

		// Expose 4 timeseries objects
		pyts<tsmapobj, tsvmaptag>::reg("dateseries");
		pyts<tsvmapobj, tsvmaptag>::reg("datevseries");
		pyts<tsmap,    tsvmaptag, calcmatrix, ts_add_types, tsmatrixtag>::reg("numericts");
		pyts<tsvmap,   tsvmaptag, calcmatrix, ts_add_types, tsmatrixtag>::reg("numerictsv");
		pyts<tsmatrix, tsvmaptag, calcmatrix>::reg("matrixseries");

		// Register map timeseries with matrices and its key-value pair _________________
		pyts<tsmapmatrix, tsvmaptag>::reg("mapmatrixseries");
		pair_to_tuple<tgtdate const,calcmatrix>::register_to_python();
		//_______________________________________________________________________________

		//py::class_<tsoper>("tsoper","Time serie operator wrapper for efficient time series operations",py::no_init)
		//	.def("apply",	&ts::numeric::tsoper::apply, "Perform calculations")
		//	;

		// Expose the tsmatrix proxy element for a row
		//expose_matrix_proxy<tsmatrix::mapped_type>("matrix_row_double","Proxy for a matrix row");

		py::def("toflot",json<tsmap>,py::arg("timeseries"),"Convert a date-numeric timeseries into a timestamp-numeric tuple list");

//#		define EXPOSEOPER(name,type1,Op,type2) 	py::def(name,tsoper<tstype>::make<type1,Op,type2>)

		/*
		typedef tsoper::tstype tstype;
		EXPOSEOPER("tsAdd",double,Add,tstype);
		EXPOSEOPER("tsAdd",double,Add,tsoper);
		EXPOSEOPER("tsAdd",tstype,Add,double);
		EXPOSEOPER("tsAdd",tsoper,Add,double);
		EXPOSEOPER("tsAdd",tstype,Add,tstype);
		EXPOSEOPER("tsAdd",tstype,Add,tsoper);
		EXPOSEOPER("tsAdd",tsoper,Add,tstype);
		EXPOSEOPER("tsAdd",tsoper,Add,tsoper);

		EXPOSEOPER("tsSubtract",double,Subtract,tstype);
		EXPOSEOPER("tsSubtract",double,Subtract,tsoper);
		EXPOSEOPER("tsSubtract",tstype,Subtract,double);
		EXPOSEOPER("tsSubtract",tsoper,Subtract,double);
		EXPOSEOPER("tsSubtract",tstype,Subtract,tstype);
		EXPOSEOPER("tsSubtract",tstype,Subtract,tsoper);
		EXPOSEOPER("tsSubtract",tsoper,Subtract,tstype);
		EXPOSEOPER("tsSubtract",tsoper,Subtract,tsoper);

		EXPOSEOPER("tsMultiply",double,Multiply,tstype);
		EXPOSEOPER("tsMultiply",double,Multiply,tsoper);
		EXPOSEOPER("tsMultiply",tstype,Multiply,double);
		EXPOSEOPER("tsMultiply",tsoper,Multiply,double);
		EXPOSEOPER("tsMultiply",tstype,Multiply,tstype);
		EXPOSEOPER("tsMultiply",tstype,Multiply,tsoper);
		EXPOSEOPER("tsMultiply",tsoper,Multiply,tstype);
		EXPOSEOPER("tsMultiply",tsoper,Multiply,tsoper);

		EXPOSEOPER("tsDivide",double,Divide,tstype);
		EXPOSEOPER("tsDivide",double,Divide,tsoper);
		EXPOSEOPER("tsDivide",tstype,Divide,double);
		EXPOSEOPER("tsDivide",tsoper,Divide,double);
		EXPOSEOPER("tsDivide",tstype,Divide,tstype);
		EXPOSEOPER("tsDivide",tstype,Divide,tsoper);
		EXPOSEOPER("tsDivide",tsoper,Divide,tstype);
		EXPOSEOPER("tsDivide",tsoper,Divide,tsoper);
		*/
	}

}}
