

#ifndef BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_DIAGONAL_H
#define BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_DIAGONAL_H

#include <boost/numeric/bindings/traits/vector_traits.hpp>

#ifndef BOOST_NUMERIC_BINDINGS_POOR_MANS_TRAITS

#ifndef BOOST_UBLAS_HAVE_BINDINGS
#  include <boost/numeric/ublas/banded.hpp>
#endif


namespace boost { namespace numeric { namespace bindings { namespace traits {


// ublas::diagonal_matrix<>
template <typename T, typename L, typename ArrT, typename V>
struct vector_detail_traits< boost::numeric::ublas::diagonal_matrix<T, L, ArrT>, V >: default_vector_traits< V, T >   {
	typedef boost::numeric::ublas::diagonal_matrix<T, L, ArrT>  identifier_type;
	typedef V                                               	vector_type;
	typedef typename default_vector_traits< V, T >::pointer 	pointer;

#ifndef BOOST_NUMERIC_BINDINGS_NO_SANITY_CHECK
    BOOST_STATIC_ASSERT( (boost::is_same< identifier_type, typename boost::remove_const<V>::type >::value) );
#endif

    static pointer storage (vector_type& v) {
    	typedef typename detail::generate_const<V,ArrT>::type array_type ;
    	return vector_traits<array_type>::storage (v.data());
    }
};


}}}}

#endif // BOOST_NUMERIC_BINDINGS_POOR_MANS_TRAITS

#endif // BOOST_NUMERIC_BINDINGS_TRAITS_UBLAS_DIAGONAL_H
