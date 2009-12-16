//
// Copyright (c) 2009 by Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_IS_BINDABLE_MATRIX_HPP
#define BOOST_NUMERIC_BINDINGS_TRAITS_IS_BINDABLE_MATRIX_HPP

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/traits/matrix_traits.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace traits {

template< typename T >
struct is_bindable_matrix {

    typedef char yes;
    typedef char (&no)[2];

    template< typename M >
    static yes tester( typename matrix_traits<M>::pointer );

    template< typename M >
    static no tester( ... );

    static bool const value = sizeof(tester<T>(0)) == sizeof(yes);

    typedef mpl::bool_<value> type;
};

}}}}

#endif
