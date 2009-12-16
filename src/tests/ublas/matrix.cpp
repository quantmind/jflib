
#include <jflib/tests/all.hpp>
#include <jflib/python/pyconfig.hpp>
#include <boost/numeric/ublas/matrix.hpp>


namespace jflib { namespace tests {

namespace ublas = boost::numeric::ublas;

template<class T>
int matrix_assign() {
	ublas::matrix<T> m1(10,10,1);
	ublas::matrix<T> m2(m1);
	m1(1,1) = 45;
	if(m1(1,1) == m2(1,1))
		return 0;
	else
		return 1;

}


int TestHandle::ublasmatrix() {
	return matrix_assign<double>();
}

}}
