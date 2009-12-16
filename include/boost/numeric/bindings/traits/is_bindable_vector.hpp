//
// Copyright (c) 2009 by Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_IS_BINDABLE_VECTOR_HPP
#define BOOST_NUMERIC_BINDINGS_TRAITS_IS_BINDABLE_VECTOR_HPP

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/traits/vector_traits.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace traits {

template< typename T >
struct is_bindable_vector {

    typedef char yes;
    typedef char (&no)[2];

    template< typename V >
    static yes tester( typename vector_traits<V>::pointer );

    template< typename V >
    static no tester( ... );

    static bool const value = sizeof(tester<T>(0)) == sizeof(yes);

    typedef mpl::bool_<value> type;
};

}}}}

#endif
