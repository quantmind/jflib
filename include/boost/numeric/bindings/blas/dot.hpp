//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_DOT_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_DOT_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/map.hpp>
#include <boost/numeric/bindings/blas/level1/dot.hpp>
#include <boost/numeric/bindings/blas/level1/dotc.hpp>
#include <boost/numeric/bindings/blas/level1/dotu.hpp>

namespace mpl = ::boost::mpl;

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

namespace detail {

template< typename Vector >
struct dot_dispatcher {
    typedef typename traits::vector_traits< Vector >::value_type value_type;
    typedef typename mpl::map<
        mpl::pair< float, level1::dot_impl< value_type > >,
        mpl::pair< double, level1::dot_impl< value_type > >,
        mpl::pair< traits::complex_f, level1::dotc_impl< value_type > >,
        mpl::pair< traits::complex_d, level1::dotc_impl< value_type > > > map;
    typedef typename mpl::at< map, value_type >::type routine;
};

} // namespace detail

template< typename VectorX, typename VectorY >
inline typename detail::dot_dispatcher< VectorX >::routine::return_type
dot( VectorX& x, VectorY& y ) {
    typedef typename detail::dot_dispatcher< VectorX >::routine routine;
    return routine::invoke( x, y );
}

}}}} // namespace boost::numeric::bindings::blas

#endif
