//
// Copyright (c) 2009 Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_NUMERIC_BINDINGS_BLAS_SOLVE_HPP
#define BOOST_NUMERIC_BINDINGS_BLAS_SOLVE_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/map.hpp>
#include <boost/numeric/bindings/blas/level2/trsv.hpp>
#include <boost/numeric/bindings/blas/level2/tbsv.hpp>
#include <boost/numeric/bindings/blas/level2/tpsv.hpp>

#include <boost/numeric/bindings/blas/level3/trsm.hpp>

namespace mpl = ::boost::mpl;

namespace boost {
namespace numeric {
namespace bindings {
namespace blas {

namespace detail {

template< typename Matrix >
struct solve_dispatcher {
    typedef typename traits::vector_traits< Vector >::value_type value_type;

    typedef typename mpl::map<
        mpl::pair< traits::general_t, level2::trsv_impl< value_type > >,
        mpl::pair< traits::banded_t, level2::tbsv_impl< value_type > >,
        mpl::pair< traits::packed_t, level2::tpsv_impl< value_type > > > map;

    typedef typename mpl::at< map, value_type >::type routine;
};

} // namespace detail







}}}} // namespace boost::numeric::bindings::blas

#endif

