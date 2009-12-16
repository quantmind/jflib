
#ifndef		__NUMPY_VECTOR_UBLAS_HPP__
#define		__NUMPY_VECTOR_UBLAS_HPP__

#include <jflib/python/numpy/helpers.hpp>


namespace jflib { namespace python { namespace numpy  {

template <class T>  class numpy_strided_vector;
template <class T>  class numpy_vector;



namespace detail {

	template<class Derived, class Super>
	struct vector_functionality {
		Derived copy() const {return Derived(static_cast<const Derived *>(this)->array());}

		// numpy array metadata
		bool is_valid() const { return static_cast<const Derived *>(this)->array().is_valid(); }
		
		typename Super::size_type ndim() const { return static_cast<const Derived *>(this)->array().ndim(); }
      
		const npy_intp *dims() const { return static_cast<const Derived *>(this)->array().dims(); }
      
		const npy_intp dim(npy_intp i) const { return static_cast<const Derived *>(this)->array().dim(i); }
      
		const npy_intp *strides() const { return static_cast<const Derived *>(this)->array().strides(); }
      
		const npy_intp stride(npy_intp i) const { return static_cast<const Derived *>(this)->array().stride(i); }
      
		npy_intp itemsize() const { return sizeof(typename Derived::value_type); }
      
		bool writable() const { return static_cast<const Derived *>(this)->array().writable(); }

		// several-d subscripts
		typename Super::value_type &sub(npy_intp i) { 
			return *reinterpret_cast<typename Super::value_type *>(
			PyArray_GETPTR1(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i)); 
		}
		const typename Super::value_type &sub(npy_intp i) const  { 
			return *reinterpret_cast<const typename Super::value_type *>(
				PyArray_GETPTR1(
				static_cast<const Derived *>(this)->data().handle().get(), 
				i)); 
		}
		typename Super::value_type &sub(npy_intp i, npy_intp j) { 
			return *reinterpret_cast<typename Super::value_type *>(
				PyArray_GETPTR2(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j)); 
		}
		const typename Super::value_type &sub(npy_intp i, npy_intp j) const  { 
			return *reinterpret_cast<const typename Super::value_type *>(
				PyArray_GETPTR2(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j)); 
		}
		typename Super::value_type &sub(npy_intp i, npy_intp j, npy_intp k) { 
			return *reinterpret_cast<typename Super::value_type *>(
				PyArray_GETPTR3(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j, k)); 
		}
		const typename Super::value_type &sub(npy_intp i, npy_intp j, npy_intp k) const { 
			return *reinterpret_cast<const typename Super::value_type *>(
				PyArray_GETPTR3(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j, k)); 
		}
		typename Super::value_type &sub(npy_intp i, npy_intp j, npy_intp k, npy_intp l) { 
			return *reinterpret_cast<typename Super::value_type *>(
				PyArray_GETPTR4(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j, k, l)); 
		}
		const typename Super::value_type &sub(npy_intp i, npy_intp j, npy_intp k, npy_intp l) const  { 
			return *reinterpret_cast<const typename Super::value_type *>(
				PyArray_GETPTR4(
				static_cast<const Derived *>(this)->array().handle().get(), 
				i, j, k, l)); 
		}

		// shape manipulation 
		void reshape(int ndim_, const npy_intp *dims_, NPY_ORDER order=NPY_CORDER)  {
			static_cast<Derived *>(this)->data().reshape(ndim_, dims_, order);
		}

		boost::python::handle<> to_python() const  {
			return static_cast<const Derived *>(this)->array().handle();
		}
	};

	template<class T>
    class numpy_vec_iterator : public boost::iterator_facade<numpy_vec_iterator<T>, T,
                                      boost::numeric::ublas::dense_random_access_iterator_tag>    {
	private:
        typedef  boost::iterator_facade<numpy_vec_iterator, T,
                 boost::numeric::ublas::dense_random_access_iterator_tag> 
                   self_t;
	public:
        typedef typename self_t::difference_type difference_type;

        numpy_vec_iterator() 
        : it(0)
        { }

        numpy_vec_iterator(T *it)
        : it(it)
        { }

        // private:
        friend class boost::iterator_core_access;

        bool equal(numpy_vec_iterator const &other) const 
        {
          return other.it == this->it;
        }

        void increment() 
        { ++it; }

        T& dereference() const 
        { return *it; }

        void decrement() 
        { --it; }

        difference_type distance_to (numpy_vec_iterator const &other) const 
        { return (other.it - this->it);}

        void advance (difference_type n) 
        { it += n; }

        T* it;
    };

}	//	end of namespace detail

template<class T>
class numpy_vector: public boost::numeric::ublas::vector<T, numpy_array<T> >,
	public detail::vector_functionality<numpy_vector<T>, boost::numeric::ublas::vector<T, numpy_array<T> > > {
private:
	typedef numpy_array<T>											nyarray;
	typedef boost::numeric::ublas::vector<T, nyarray>				super;
	typedef detail::vector_functionality<numpy_vector<T>,super>		func;
public:
	typedef detail::numpy_vec_iterator<T> iterator;
    typedef detail::numpy_vec_iterator<const T> const_iterator;

	numpy_vector(){}

	numpy_vector(const numpy_array<T> &s):super(s.size(),s) {}

	numpy_vector(int ndim_, const npy_intp *dims_):super(size_from_dims(ndim_, dims_),nyarray(ndim_,dims_)){}
	
	template<class AE>
      numpy_vector(int ndim_, const npy_intp *dims_, 
          const boost::numeric::ublas::vector_expression<AE> &ae)
        : super(ae)
      { 
        assert(this->size() == size_from_dims(ndim_, dims_));
        array().reshape(ndim_, dims_);
      }

    explicit 
    numpy_vector(typename super::size_type size): super(size){}

    numpy_vector(typename super::size_type size, const typename super::value_type &init):super(size, init){}

    numpy_vector (const numpy_vector &v):super(v){}

    template<class AE>
    numpy_vector(const boost::numeric::ublas::vector_expression<AE> &ae):super(ae){}

    // as-ublas accessor
    super &as_ublas() { return *this; }

    const super &as_ublas() const { return *this; }

    boost::numeric::ublas::slice stride_slice() const  {
		if (this->ndim() == 1)  {
			npy_intp stride = this->stride(0)/npy_intp(sizeof(T));
			typename super::size_type sz = this->size();

			if (stride < 0)  {
				return boost::numeric::ublas::slice(sz-1, stride, this->dim(0));
			}
			else
				return boost::numeric::ublas::slice(0, stride, this->dim(0));
		}
		else if (this->ndim() == 0)
			return boost::numeric::ublas::slice(0, 1, 1);
		else
			PYUBLAS_PYERROR(ValueError, 
				"cannot generate a stride-respecting 1D slice "
				"for 2D or higher arrays");
	}

    numpy_strided_vector<T> as_strided() { return numpy_strided_vector<T>(*this, stride_slice());}

    boost::numeric::ublas::vector_slice<const numpy_vector> as_strided() const  {
		return boost::numeric::ublas::vector_slice<const numpy_vector>(*this, stride_slice());
    }

	numpy_array<T> &array(){ return super::data(); }

    numpy_array<T> const &array() const { return super::data(); }

    iterator begin() { return iterator(array().begin()); }

    iterator end() { return iterator(array().end()); }

    const_iterator begin() const { return const_iterator(array().begin()); }

    const_iterator end() const { return const_iterator(array().end()); }

};



namespace detail {

    /* This is dumb, but necessary: In numpy_strided_vector, the 
     * vector needs to be initialized before the slice referring 
     * to it. But if the vector is a member, and the slice is a 
     * base class, that won't happen. Therefore, move the vector
     * to an artificial base class that can be specified first in
     * the base-specifier-list. (cf. 12.6.2.5 in '96 working paper)
     */
	template <class V>
    class vector_holder   {
    public:
		V m_vector;
        vector_holder(const V &v): m_vector(v) { }
    };


    template<typename T>
    class numpy_strided_vec_iterator 
    : public boost::iterator_facade<
      numpy_strided_vec_iterator<T>, T,
      boost::numeric::ublas::dense_random_access_iterator_tag>
    {
      private:
        typedef  boost::iterator_facade<
          numpy_strided_vec_iterator, T,
          boost::numeric::ublas::dense_random_access_iterator_tag>
        self_t;

      public:
        typedef typename self_t::difference_type difference_type;
        typedef typename numpy_strided_vector<T>::stride_type stride_type;

        numpy_strided_vec_iterator(T *it, stride_type s)
        : stride(s), it(it)
        { }

        // private:

        friend class boost::iterator_core_access;

        bool equal (numpy_strided_vec_iterator const& other) const 
        { return other.it == this->it; }

        void increment() 
        { it += stride; }

        T& dereference() const 
        { return *it; }

        void decrement() 
        { it -= stride; }

        difference_type
        distance_to (numpy_strided_vec_iterator const& other) const 
        { return (other.it - this->it)/difference_type (stride);}

        void advance (difference_type n) 
        { it += n*stride; }

      private:
        stride_type stride;
        T* it;
    };
  
} // end namespace detail


       

template <class T>
class numpy_strided_vector: public detail::vector_holder<numpy_vector<T> >,
  public boost::numeric::ublas::vector_slice< numpy_vector<T> >,
  public detail::vector_functionality<numpy_strided_vector<T>,
    boost::numeric::ublas::vector_slice< numpy_vector<T> > >  {
private:
	typedef detail::vector_holder<numpy_vector<T> >					vector_holder;
    typedef boost::numeric::ublas::vector_slice< numpy_vector<T> >  super;

    // Make a fake 0-length array just for default constructor
    static numpy_array<T> make_fake_array() { return numpy_array<T>(0); }

public:
	numpy_strided_vector():vector_holder (make_fake_array()),
        super(this->m_vector, boost::numeric::ublas::slice(0, 1, this->m_vector.size()))
      { }

      // observe that PyObject handles are implicitly convertible
      // to numpy_array
      numpy_strided_vector(const numpy_array<T> &s)
        : vector_holder(s),
        super(this->m_vector, boost::numeric::ublas::slice(0, 1, s.size()))
      { }

      numpy_strided_vector(const numpy_strided_vector &v)
        : vector_holder(v.m_vector),
        super(this->m_vector, boost::numeric::ublas::slice(
              v.start(), v.stride(), v.size()))
      { }

      numpy_strided_vector(numpy_vector<T> &v, boost::numeric::ublas::slice const &s)
        : vector_holder(v), super(this->m_vector, s)
      { }

      template<class AE>
      numpy_strided_vector(const boost::numeric::ublas::vector_expression<AE> &ae)
      : vector_holder(ae),
      super(this->m_vector, boost::numeric::ublas::slice(0, 1, ae().size()))
      { }

      // as-ublas accessor
      super &as_ublas() 
      { return *this; }

      const super &as_ublas() const
      { return *this; }

      numpy_array<T> &array()
      { return this->m_vector.data(); }
       
      numpy_array<T> const &array() const
      { return this->m_vector.data(); }

      typename super::difference_type stride() const
      { return super::stride(); }

      typename super::difference_type stride(npy_intp i) const
      { return this->m_vector.stride(i); }

      typedef npy_intp stride_type;

      typedef detail::numpy_strided_vec_iterator<T> iterator;
      typedef detail::numpy_strided_vec_iterator<const T> const_iterator;

      iterator begin() 
      { 
        if (stride() >= 0)
          return iterator(this->m_vector.array().begin(), stride()); 
        else
          return iterator(this->m_vector.array().end()-1, stride()); 
      }

      iterator end() 
      {
        if (stride() >= 0)
          return iterator(this->m_vector.array().end(), stride()); 
        else
          return iterator(this->m_vector.array().end() - 1 - this->size(), stride()); 
      }

      const_iterator begin() const 
      { 
        if (stride() >= 0)
          return const_iterator(this->m_vector.array().begin(), stride()); 
        else
          return const_iterator(this->m_vector.array().end()-1, stride()); 
      }

      const_iterator end() const 
      {
        if (stride() >= 0)
          return const_iterator(this->m_vector.array().end(), stride()); 
        else
          return const_iterator(this->m_vector.array().end() - 1 - this->size(), stride()); 
      }
  };

}}}


#endif	//	__NUMPY_VECTOR_UBLAS_HPP__

