
#ifndef		__JFLIB_LAPACK_EIGEN_HPP__
#define		__JFLIB_LAPACK_EIGEN_HPP__


#include <jflib/linalg/lapack/traits.hpp>
#include <boost/numeric/bindings/lapack/driver/syev.hpp>
/*
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/numeric/bindings/traits/vector_traits.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/traits/ublas_vector2.hpp>
#include <boost/numeric/bindings/traits/c_array.hpp>
#include <complex>
*/


namespace jflib { namespace linalg { namespace lapack {

/** Function-wrapper for syev.
    @see syev */
template<class M, class V>
struct syev_t {
	typedef matrix_traits<M>						mtraits;
	typedef vector_traits<V>						vtraits;
	typedef typename mtraits::matrix_type			matrix_type;
	typedef typename vtraits::vector_type			vector_type;
	typedef typename mtraits::value_type			value_type;
	typedef boost::is_same<value_type,typename vtraits::value_type>   sametype;
	BOOST_STATIC_ASSERT(sametype::value);

	static void calc(matrix_type& a, vector_type& v, const char& jobz) {
		namespace impl = boost::numeric::bindings::lapack::detail;
		//impl::syev(jobz,a,v);

		char      uplo  = 'L';
		integer_t n     = a.size2();
		integer_t lda   = a.size1();
		integer_t lwork =-1;
		integer_t info  = 0;
		value_type dlwork;
		impl::syev(jobz, uplo, n, mtraits::data(a), lda, vtraits::data(v), &dlwork, lwork, info);
	}
};


/** Compute all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A.
    The eigenvalues and eigenvectors of a symmetric matrix
    \f$A\in\mathbf{K}^{n\times n}\f$ can be computed.

    The eigenvectors are orthogonal by nature and normalised by definition.
    If the matrix \f$E\f$ contains the eigenvectors of \f$A\f$, then the
    eigentransform can be written as (\f$E\f$ is orthonormal \f$\Rightarrow\f$
    \f$E^{-1}=E^\top\f$):
    \f[A=E\,\Lambda\,E^\top\f]

    Where \f$\Lambda=\mathop{diag}(\lambda_1,\lambda_2,\ldots,\lambda_n)\f$ is
    a diagonal matrix with the eigenvalues
    \f$\lambda_1,\lambda_2,\ldots,\lambda_n\f$ in ascending order.

    See manpage <A HREF="man:/dsyev">dsyev(1)</A> for more documentation.

    Compute eigenvalues and, optionally, the eigenvectors of A.
    @param A Symmetric matrix (with upper storage) to compute
    eigentransform for.
    @param E Pointer to matrix, where the eigenvectors have to be written
    to (may be \c NULL, if it is of no interest).
    @return Diagonal matrix with eigenvalues in ascending order.
    @see syev_t */


template<class M, class V>
void syevectors(M& a, V& v) {
	syev_t<M,V>::calc(a,v,'V');
}

template<class M, class V>
void syevalues(M& a, V& v) {
	syev_t<M,V>::calc(a,v,'N');
}



}}}

#endif	//	__JFLIB_LAPACK_EIGEN_HPP__



