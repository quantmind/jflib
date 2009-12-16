
#ifndef __TIMESERIES_STRUCTURES_HPP__
#define __TIMESERIES_STRUCTURES_HPP__


#include <jflib/templates/map.hpp>
#include <jflib/timeseries/timeseries_base.hpp>


namespace jflib { namespace timeseries {


/** \brief Tag struct for a timeseries map
 *
 * A Map-Timeseries is a timeseries based on a map structure
 */
struct tsmap {
	static const unsigned family		 = 0u;
	static const bool	  multipleseries = false;

	template<class Key, class T>
	struct container {
		typedef T													numtype;
		typedef jflib::templates::associative<Key,T,0u>				super;
		typedef	timeseries<Key,T,tsmap,family,multipleseries>		type;
	};
};


/**
 * \brief Specialization of tsmap
 * Base class for timeseries tag which support multi
 */
struct tsvmapbase {
	static const unsigned	family		   = 0u;
	static const bool		multipleseries = true;
};



// ublas timeserie matrix tag based on boost::numeric::ublas matrix structure
struct tsmatrix_base {
	static const unsigned family 			= 1;
	static const bool	  multipleseries 	= true;
};


// \brief matrixmap structure
template<class M>
struct matrixmap {
	typedef matrixmap<M>	self_type;
	static const unsigned	family = 0;
	static const bool		multipleseries = true;
	static const bool		locked		   = true;

	template<class Key, class T>
	struct container {
		typedef M															vtype;
		typedef typename vtype::numtype										numtype;
		typedef jflib::templates::associative<Key,vtype,family>				super;
		typedef	timeseries<Key,vtype,self_type,family,multipleseries>		type;
	};
};



}}


#endif	//	__TIMESERIES_STRUCTURES_HPP__

