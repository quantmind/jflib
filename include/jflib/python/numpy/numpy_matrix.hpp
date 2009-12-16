
#ifndef		__NUMPY_MATRIX_UBLAS_HPP__
#define		__NUMPY_MATRIX_UBLAS_HPP__

#include <jflib/python/numpy/helpers.hpp>


namespace jflib { namespace python { namespace numpy  {

namespace ublas = boost::numeric::ublas;

// derived matrix types -----------------------------------------------------
template<class T, class L>
class numpy_matrix: public ublas::matrix<T, L, numpy_array<T> > {
private:
    typedef ublas::matrix<T, L, numpy_array<T> >    super;
public:
	typedef typename super::value_type				value_type;
    typedef typename super::size_type				size_type;
    typedef typename super::array_type				array_type;
    typedef typename super::orientation_category	orientation_category;
    numpy_matrix(){}

    numpy_matrix(size_type size1, size_type size2):super(size1, size2){}

    numpy_matrix(size_type size1, size_type size2, const value_type &init):super(size1, size2, init){}

    numpy_matrix(size_type size1, size_type size2,const array_type &data):super(size1, size2, data){}

    // observe that PyObject handles are implicitly convertible
    // to numpy_array
    numpy_matrix(const array_type &data):super(
        get_array_size1<orientation_category>(data),
        get_array_size2(data),
        data){}

    numpy_matrix(const numpy_matrix &m):super(m){}

    template<class AE>
    numpy_matrix (const boost::numeric::ublas::matrix_expression<AE> &ae):super(ae){}

    super& as_ublas() {return *this;}

    const super& as_ublas() const { return *this; }

    bool is_valid() const { return this->data().is_valid(); }

    boost::python::handle<> to_python() const { return matrix_to_python(*this); }
};


}}}



#endif	//	__NUMPY_MATRIX_UBLAS_HPP__
