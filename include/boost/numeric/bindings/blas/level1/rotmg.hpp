//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_ROTMG_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_LEVEL1_ROTMG_HPP

#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/blas/detail/blas.h>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {
namespace level1 {

// overloaded functions to call blas
namespace detail {
    inline void rotmg( float& d1, float& d2, float& x1, float const y1,
            float* sparam ) {
        BLAS_SROTMG( &d1, &d2, &x1, &y1, sparam );
    }
    inline void rotmg( double& d1, double& d2, double& x1, double const y1,
            double* dparam ) {
        BLAS_DROTMG( &d1, &d2, &x1, &y1, dparam );
    }
}

// value-type based template
template< typename ValueType >
struct rotmg_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;
    typedef void return_type;

    // templated specialization
    template< typename VectorDPARAM >
    static return_type invoke( real_type& d1, real_type& d2, real_type& x1,
            real_type const y1, VectorDPARAM& dparam ) {
        detail::rotmg( d1, d2, x1, y1, traits::vector_storage(dparam) );
    }
};

// low-level template function for direct calls to level1::rotmg
template< typename VectorDPARAM >
inline typename rotmg_impl< typename traits::vector_traits<
        VectorDPARAM >::value_type >::return_type
rotmg( typename traits::vector_traits< VectorDPARAM >::value_type& d1,
        typename traits::vector_traits< VectorDPARAM >::value_type& d2,
        typename traits::vector_traits< VectorDPARAM >::value_type& x1,
        typename traits::vector_traits< VectorDPARAM >::value_type const y1,
        VectorDPARAM& dparam ) {
    typedef typename traits::vector_traits<
            VectorDPARAM >::value_type value_type;
    rotmg_impl< value_type >::invoke( d1, d2, x1, y1, dparam );
}

}}}}} // namespace boost::numeric::bindings::blas::level1

#endif
