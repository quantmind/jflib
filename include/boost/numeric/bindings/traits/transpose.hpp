//
// Copyright Kresimir Fresl, Toon Knapen, and Karl Meerbergen 2002, 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_BINDINGS_TRANSPOSE_HPP
#define BOOST_BINDINGS_TRANSPOSE_HPP

#include <boost/numeric/bindings/traits/matrix_traits.hpp>
#include <boost/numeric/bindings/traits/is_decorated.hpp>

namespace boost { namespace numeric { namespace bindings { namespace traits {

const char NO_TRANSPOSE = 'N' ;
const char TRANSPOSE    = 'T' ;
const char CONJUGATE    = 'C' ;

struct no_transpose_t {};
struct transpose_t {};
struct conjugate_t {};

template< typename Matrix, typename Decoration >
struct decoration_impl {
    typedef Matrix underlying_type;
    typedef Decoration decoration_type;
    decoration_impl( Matrix &m ): m_matrix(m) {}
    inline underlying_type& get() {
        return m_matrix;
    }
    Matrix& m_matrix;
};

template< typename Matrix >
decoration_impl< Matrix, transpose_t > trans( Matrix &m ) {
    return decoration_impl<Matrix, transpose_t >(m);
}

template< typename Matrix >
decoration_impl< Matrix, conjugate_t > conj( Matrix &m ) {
    return decoration_impl<Matrix, conjugate_t >(m);
}

}}}}

#endif
