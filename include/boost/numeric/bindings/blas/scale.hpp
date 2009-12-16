//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_SCALE_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_SCALE_HPP

#include <boost/numeric/bindings/blas/level1/scal.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

template< typename VectorX >
inline typename level1::scal_impl<
    typename traits::vector_traits< VectorX >::value_type >::return_type
scale( typename traits::vector_traits< VectorX >::value_type const a,
       VectorX& x ) {
    typedef typename traits::vector_traits< VectorX >::value_type value_type;
    level1::scal_impl< value_type >::invoke( a, x );
}

}}}} // namespace boost::numeric::bindings::blas

#endif
