
#ifndef		__JFLIB_UBLAS_BASE_HPP__
#define		__JFLIB_UBLAS_BASE_HPP__

#include <jflib/ublas/bounded.hpp>

#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>



namespace jflib { namespace ublas {

namespace detail  {
    struct begin_tag {};
    struct end_tag {};
}

// is_vector ----------------------------------------------------------------
template <typename UblasType>
struct is_vector { typedef boost::mpl::false_ type; };

template <typename ValueType, typename L>
struct is_vector<boost::numeric::ublas::vector<ValueType, L> > { typedef boost::mpl::true_ type; };

template <typename WrappedVector>
struct is_vector<boost::numeric::ublas::vector_slice<WrappedVector> > { typedef boost::mpl::true_ type; };

template <typename WrappedVector>
struct is_vector<boost::numeric::ublas::matrix_row<WrappedVector> > { typedef boost::mpl::true_ type; };

template <typename WrappedVector>
struct is_vector<boost::numeric::ublas::matrix_column<WrappedVector> > { typedef boost::mpl::true_ type; };


// matrix_iterator ----------------------------------------------------------
template<typename MatrixType, typename _is_vector = typename is_vector<MatrixType>::type>
class matrix_iterator :  public boost::iterator_facade<
    matrix_iterator<MatrixType>,  // Base
    typename MatrixType::value_type, // Value
    boost::forward_traversal_tag, // CategoryOrTraversal
    typename boost::mpl::if_<boost::is_const<MatrixType>,
      typename MatrixType::const_iterator2::reference,
      typename MatrixType::iterator2::reference
      >::type // Reference
   >   {
    typedef typename boost::mpl::if_<boost::is_const<MatrixType>,
      typename MatrixType::const_iterator1,
      typename MatrixType::iterator1
      >::type it1_t;
    typedef typename boost::mpl::if_<boost::is_const<MatrixType>,
      typename MatrixType::const_iterator2,
      typename MatrixType::iterator2
      >::type it2_t;
public:
	typedef it2_t							iterator;
	typedef typename MatrixType::size_type	size_type;
	typedef std::pair<size_type,size_type>	index_type;

    matrix_iterator() {}

    matrix_iterator(MatrixType &mat, detail::begin_tag):m_it1(mat.begin1()), m_it2(m_it1.begin()) {
		validate();
    }
	matrix_iterator(MatrixType &mat, detail::end_tag):m_it1(mat.end1()), m_it2(m_it1.begin()){}

    index_type index() const  {
		return index_type(m_it2.index1(), m_it2.index2());
    }

private:
    friend class boost::iterator_core_access;

    void validate() {
      // this makes sure that the iterator points to an existing element
		while(m_it1 != m_it1().end1() && m_it2 == m_it1.end())	{
			m_it1++;
			m_it2 = m_it1.begin();
		}
    }

    void increment() {
		m_it2++;
		validate();
    }

    bool equal(matrix_iterator const& other) const  {
		return m_it1 == other.m_it1 && m_it2 == other.m_it2;
    }

    typename it2_t::reference dereference() const {
		return *m_it2;
    }

	it1_t       m_it1;
    it2_t       m_it2;
};


/*
template<class M, class RC>
class matrix_iterator;

template<class M, class T> class matrix_row_column;

struct ROWS {};
struct COLS {};

template<class M, class Tag> struct rctraits {};



template<class M>
class matrix_row_column<M,ROWS> {
public:
	typedef typename M::size_type		size_type;
	typedef typename M::const_iterator2	const_iterator;
	typedef typename M::iterator1		Base;
	typedef typename M::iterator2		iterator;
	typedef typename boost::mpl::if_<boost::is_const<M>,
                                     typename M::const_closure_type,
                                     typename M::closure_type>::type matrix_closure_type;

	matrix_row_column(M& m, size_type index):m_el(m) {
		m_index = index;
	}
	bool operator == (matrix_row_column const& x) const {
		return m_el.same_closure(x.m_el) && m_index == x.m_index;
	}

	matrix_row_column& operator++() {
		++m_index;
		return *this;
	}
	matrix_row_column& operator--() {
		--m_index;
		return *this;
	}

	size_type index() const {
		return m_index;
	}

	size_type size() const {
		return this->end() - this->begin();
	}

	iterator begin() {
		return m_el.find2(0,m_index,0);
	}
	iterator end()   {
		return m_el.find2(0,m_index,m_el.size2());
	}

	const_iterator begin() const {
		return m_el.find2(0,m_index,0);
	}
	const_iterator end() const {
		return m_el.find2(0,m_index,m_el.size2());
	}
private:
	matrix_closure_type	m_el;
	size_type			m_index;
};



template<class M, class RC>
class matrix_iterator: public boost::iterator_facade<
		  matrix_iterator<M,RC>
		, matrix_row_column<M,RC>
		, typename boost::iterator_traversal<typename matrix_row_column<M,RC>::Base >::type
		, matrix_row_column<M,RC>&
		, typename boost::iterator_difference<typename matrix_row_column<M,RC>::Base >::type
		> {
public:
	typedef matrix_row_column<M,RC>		 Value;
	typedef typename M::size_type		 size_type;

	matrix_iterator(M& m, size_type index = 0):m_iterator(m,index){}

	matrix_iterator(matrix_iterator const& other):m_iterator(other.m_iterator) {}

private:
	friend class boost::iterator_core_access;

	Value m_iterator;

	void increment() { ++m_iterator; }

	Value& dereference() const {return const_cast<Value&>(m_iterator);}

	bool equal(matrix_iterator const& x) const {return m_iterator == x.m_iterator;}
};
*/

}}

#endif	//	__JFLIB_UBLAS_BASE_HPP__

