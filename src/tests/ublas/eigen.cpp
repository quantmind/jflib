//
//  Copyright Toon Knapen, Karl Meerbergen
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//#include <jflib/linalg/lapack/ublas.hpp>
//#include <jflib/linalg/lapack/eigen.hpp>

#include <jflib/tests/all.hpp>
#include <jflib/python/pyconfig.hpp>
#include <jflib/tests/ublas/random.hpp>

#include <jflib/linalg/lapack/eigen.hpp>
#include <jflib/linalg/lapack/ublas.hpp>

#include <boost/numeric/ublas/matrix.hpp>

/*
#include <boost/numeric/bindings/lapack/driver/syev.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/numeric/bindings/traits/ublas_symmetric.hpp>
#include <boost/numeric/bindings/traits/ublas_vector.hpp>
*/

//#include <jflib/linalg/traits/ublas_diagonal.hpp>
//#include <jflib/linalg/traits/ublas_symmetric.hpp>



namespace jflib { namespace tests {

// Randomize a matrix
template <typename M>
void randomize_upper(M& m) {
   typedef typename M::size_type  size_type ;
   typedef typename M::value_type value_type ;

   size_type size2 = m.size2() ;

   for(size_type i=0; i<size2; ++i) {
      for(size_type j=0; j<i; ++j) {
         m(j,i) = random_value<value_type>();
      }
   }
}



template<typename T>
int syevectors(int N) {
	namespace ublas  = boost::numeric::ublas;
	namespace lapack = jflib::linalg::lapack;
	typedef ublas::matrix<T, ublas::column_major>		matrix_type;
	typedef ublas::vector<T>						    vector_type;
	//typedef ublas::diagonal_matrix<T>				    vector_type;

	// Set matrix
	matrix_type a(N,N);
	vector_type e1(N);

	randomize_upper(a);

	//ublas::symmetric_adaptor<matrix_type,ublas::upper> sym(a);

	//lapack::syev('V',sym,e1);
	//lapack::syev('V',ublas::upper(a),e1);
	//lapack::syev('V','U',a,e1);
	lapack::syevectors(a,e1);
	return 0;
}



int TestHandle::eigenvectors(int size) {
	syevectors<float>(size);
	syevectors<double>(size);
	return 0;
}


}}


/*
template <typename T, typename W>
int do_memory_type(int N, W workspace) {
   typedef ublas::matrix<T, ublas::column_major>						matrix_type;
   //typedef ublas::symmetric_matrix<T,ublas::lower,ublas::column_major>	matrix_type;
   typedef ublas::vector<T>									            vector_type ;

   // Set matrix
   matrix_type a(N,N);
   vector_type e1(N);
   vector_type e2(N);

   randomize(a);

   lapack::syevectors(a,e1);

   // Compute Schur decomposition.
   //lapack::gees(&N, &N, a, e1, z) ;
   //lapack::gees(&N, &N, a, e1, z, workspace ) ;

   // Check Schur factorization
  // if (norm_frobenius( prod( a2, z ) - prod( z, a ) )
   //        >= safety_factor*10.0* norm_frobenius( a2 ) * std::numeric_limits< real_type >::epsilon() ) return 255 ;

   //lapack::gees( a2, e2, workspace ) ;
   //if (norm_2( e1 - e2 ) > safety_factor*norm_2( e1 ) * std::numeric_limits< real_type >::epsilon()) return 255 ;

   //if (norm_frobenius( a2 - a )
   //        >= safety_factor*10.0* norm_frobenius( a2 ) * std::numeric_limits< real_type >::epsilon() ) return 255 ;


   return 0;
}

template <typename T>
struct Workspace {
   typedef ublas::vector<T>                         array_type ;
   typedef lapack::detail::workspace1< array_type > type ;

   Workspace(size_t n)
   : work_( 3*n )
   {}

   type operator() () {
      return lapack::workspace(work_) ;
   }

   array_type work_ ;
};


template <typename T>
struct Workspace< std::complex<T> > {
   typedef ublas::vector<T>                                                 real_array_type ;
   typedef ublas::vector< std::complex<T> >                                 complex_array_type ;
   typedef lapack::detail::workspace2< complex_array_type,real_array_type > type ;

   Workspace(size_t n)
   : work_( 2*n )
   , rwork_( n )
   {}

   type operator() () {
      return lapack::workspace(work_, rwork_) ;
   }

   complex_array_type work_ ;
   real_array_type    rwork_ ;
};


template <typename T>
int do_value_type(unsigned N) {

   if(do_memory_type<T,lapack::optimal_workspace>( N, lapack::optimal_workspace() ) ) return 255 ;
   if(do_memory_type<T,lapack::minimal_workspace>( N, lapack::minimal_workspace() ) ) return 255 ;

   Workspace<T> work(N);
   do_memory_type<T,typename Workspace<T>::type >(N, work());
   return 0;
}
*/
