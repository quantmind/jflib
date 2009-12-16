
#ifndef		__JFLIB_UBLAS_MATRIX_INVERSION_OPER_HPP__
#define		__JFLIB_UBLAS_MATRIX_INVERSION_OPER_HPP__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

namespace boost { namespace numeric { namespace ublas {


/* Matrix inversion routine.
    Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
template<class T, class L, class A>
bool InvertMatrix(const matrix<T,L,A>& input, ublas::matrix<T,L,A>& inverse) {
	typedef matrix<T,L,A>						matrix_type;
	typedef typename matrix_type::size_type		size_type;
 	typedef permutation_matrix<size_type>	 	pmatrix;

 	// create a working copy of the input
 	matrix_type Ai(input);
 	// create a permutation matrix for the LU-factorization
 	pmatrix pm(Ai.size1());
 	// perform LU-factorization
 	int res = lu_factorize(Ai,pm);
        if( res != 0 ) return false;
 	// create identity matrix of "inverse"
 	inverse.assign(identity_matrix<T>(Ai.size1()));
 	// backsubstitute to get the inverse
 	lu_substitute(Ai, pm, inverse);
 	return true;
}

}}}

#endif	//	__JFLIB_UBLAS_MATRIX_INVERSION_OPER_HPP__




