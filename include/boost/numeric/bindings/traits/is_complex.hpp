//
// Copyright (c) 2009 by Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_IS_COMPLEX_HPP
#define BOOST_NUMERIC_BINDINGS_TRAITS_IS_COMPLEX_HPP

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/traits/type.h>
#include <boost/type_traits/is_complex.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace traits {

template< typename T >
struct is_complex: boost::is_complex<T> {};

template<>
struct is_complex< fcomplex_t >: boost::mpl::bool_<true> {};

template<>
struct is_complex< dcomplex_t >: boost::mpl::bool_<true> {};

}}}}

#endif
