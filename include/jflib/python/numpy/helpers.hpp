
#ifndef		__NUMPY_HELPERS_UBLAS_HPP__
#define		__NUMPY_HELPERS_UBLAS_HPP__

#include <jflib/python/numpy/numpy_array.hpp>


namespace jflib { namespace python { namespace numpy  {

namespace ublas = boost::numeric::ublas;

template<class T, class L = boost::numeric::ublas::row_major> class numpy_matrix;


inline npy_intp size_from_dims(int ndim, const npy_intp *dims) {
	if (ndim != 0)
		return std::accumulate(dims, dims+ndim, 1, std::multiplies<npy_intp>());
	else
		return 1;
}

inline bool is_row_major(boost::numeric::ublas::row_major_tag)  {
    return true;
}

inline bool is_row_major(boost::numeric::ublas::column_major_tag)  {
    return false;
}



template <class T, class L>
boost::python::handle<> matrix_to_python(numpy_matrix<T, L> const &mat)  {
    typedef numpy_matrix<T, L> mat_type;
    boost::python::handle<> orig_handle = mat.data().handle();

    npy_intp dims[] = { mat.size1(), mat.size2() };
    boost::python::handle<> result;

    if (is_row_major(typename mat_type::orientation_category()))
    {
      result = boost::python::handle<>(PyArray_New(
          &PyArray_Type, 2, dims,
          get_typenum(typename mat_type::value_type()),
          /*strides*/0,
          PyArray_DATA(orig_handle.get()),
          /* ? */ 0,
          NPY_CARRAY, NULL));
    }
    else
    {
      result = boost::python::handle<>(PyArray_New(
          &PyArray_Type, 2, dims,
          get_typenum(typename mat_type::value_type()),
          /*strides*/0,
          PyArray_DATA(orig_handle.get()),
          /* ? */ 0,
          NPY_FARRAY, NULL));
    }

    PyArray_BASE(result.get()) = boost::python::handle<>(orig_handle).release();
    return result;
}


// conversion tags ----------------------------------------------------------
template <class Contained>
class invalid_ok  {
public:
	typedef Contained contained_type;
    invalid_ok(Contained c): m_contained(c){}
    const Contained &operator*() const {return m_contained;}
    Contained &operator*() {return m_contained;}
    const Contained *operator->() const {return &m_contained;}
    Contained *operator->() {return &m_contained;}
private:
	Contained m_contained;
};


// data member treatment ----------------------------------------------------
  template <class T, class C>
  class by_value_rw_member_visitor 
  : public boost::python::def_visitor<by_value_rw_member_visitor<T, C> >
  {
    private:
      const char *m_name;
      T C::*m_member;
      const char *m_doc;

    public:
      by_value_rw_member_visitor(const char *name, T C::*member, const char *doc = 0)
        : m_name(name), m_member(member), m_doc(doc)
      { }

      template <class Class>
      void visit(Class& cl) const
      {
        cl.add_property(m_name, 
            boost::python::make_getter(m_member, 
              boost::python::return_value_policy<boost::python::return_by_value>()), 
            boost::python::make_setter(m_member), 
            m_doc);
      }
  };

template <class T, class C>
by_value_rw_member_visitor<T, C> by_value_rw_member(const char *name, T C::*member, const char *doc = 0) {
    return by_value_rw_member_visitor<T, C>(name, member, doc);
}

template <class T, class C>
class by_value_ro_member_visitor: public boost::python::def_visitor<by_value_ro_member_visitor<T, C> >  {
    private:
      const char *m_name;
      T C::*m_member;
      const char *m_doc;

    public:
      by_value_ro_member_visitor(const char *name, T C::*member, const char *doc = 0)
        : m_name(name), m_member(member), m_doc(doc)
      { }

      template <class Class>
      void visit(Class& cl) const
      {
        cl.add_property(m_name, 
            make_getter(m_member, 
              boost::python::return_value_policy<boost::python::return_by_value>()), 
            m_doc);
      }
};

template <class T, class C>
by_value_ro_member_visitor<T, C> by_value_ro_member(const char *name, T C::*member, const char *doc = 0)  {
    return by_value_ro_member_visitor<T, C>(name, member, doc);
}





}}}


#endif	//	__NUMPY_HELPERS_UBLAS_HPP__
