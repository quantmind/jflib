

#ifndef __TIMESERIES_WRAP_ADD_JFLIB_HPP__
#define __TIMESERIES_WRAP_ADD_JFLIB_HPP__


#include <jflib/python/pyconfig.hpp>
#include <jflib/timeseries/all.hpp>



namespace jflib { namespace python {



namespace {


	template<class TS, class Tag>
	struct MatrixConversion {
		typedef boost::python::class_<TS>			tsptype;
		static void reg(tsptype& tsp) {
			tsp.def("tomatrix",		&TS::template tomatrix<Tag>,"Create a matrix timeseries structure");
		}
	};

	template<class TS>
	struct MatrixConversion<TS,Nil> {
		typedef boost::python::class_<TS>			tsptype;
		static void reg(tsptype& tsp) {}
	};


	/**
	 * \brief mpl iteration class
	 */
	template<class TS, class iter, class finished>
	struct addtsiter {
		typedef boost::python::class_<TS>			tsptype;

		static void regi(tsptype& tsp) {
			typedef typename boost::mpl::next<iter>::type  next;
			typedef typename boost::mpl::deref<iter>::type TS2;
			tsp.def("addts",		&jflib::timeseries::traits::AddTs<TS,TS2>::apply,"merge an existing timeseries");
			addtsiter<TS,next,finished>::regi(tsp);
		}
	};

	/**
	 * \brief Stop the loop
	 */
	template<class TS, class F>
	struct addtsiter<TS,F,F> {
		typedef boost::python::class_<TS>			tsptype;
		static void regi(tsptype& tsp) {}
	};



	/**
	 * \brief Loop over the mpl::vector V and register the addts methods
	 */
	template<class TS, class V>
	struct addts {
		typedef boost::python::class_<TS>			tsptype;
		typedef typename boost::mpl::end<V>::type	finished;

		static void reg(tsptype& tsp) {
			typedef typename boost::mpl::begin<V>::type	iter;
			addtsiter<TS,iter,finished>::regi(tsp);
		}
	};

	/**
	 * \brief specialization which does nothing
	 */
	template<class TS>
	struct addts<TS,Nil> {
		static void reg(boost::python::class_<TS>& tsp) {}
	};

}



}}



#endif // __TIMESERIES_WRAP_ADD_JFLIB_HPP__

