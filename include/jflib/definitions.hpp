//
/// \file
/// \ingroup config
/// \brief definitions for qmlib library
//
#ifndef __DEFINITIONS_JFLIB_HPP__
#define __DEFINITIONS_JFLIB_HPP__

#include <vector>
#include <list>
#include <map>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <cstddef>
#include <cmath>

#include <boost/assert.hpp>

#ifndef NDEBUG
#	ifndef	_DEBUG
#		define _DEBUG
#	endif
#	define QM_ERROR_LINES
#	define QM_ERROR_FUNCTIONS
#endif

//
#if !defined(BOOST_ENABLE_ASSERT_HANDLER)
    #define BOOST_ENABLE_ASSERT_HANDLER
#endif


namespace jflib {

struct Nil {};



}


#endif	//	__DEFINITIONS_JFLIB_HPP__
