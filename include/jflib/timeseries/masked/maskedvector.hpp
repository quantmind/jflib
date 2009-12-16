/**
 * \brief Specialization for a maskedvector of a timeseries based on a std::map template
 */

#ifndef __MASKED_VECTOR_TIMESERIES_HPP__
#define __MASKED_VECTOR_TIMESERIES_HPP__

#include <jflib/timeseries/timeseries_base.hpp>
#include <jflib/ublas/base.hpp>
#include <jflib/ublas/oper.hpp>



namespace jflib { namespace timeseries {


namespace {

template<class,class,unsigned> struct mvtraits;

template<class T, class M>
struct mvtraits<T,M,0u> {
	typedef T									data_type;
	typedef M									mask_type;
	typedef typename data_type::value_type		value_type;
	typedef typename mask_type::value_type		value_mask_type;
	typedef typename data_type::size_type		size_type;

	static void add(data_type& data, mask_type& mask, const value_type& d, const value_mask_type& m) {
		size_type s = data.size();
		data.resize(s+1);
		mask.resize(s+1);
		data[s] = d;
		mask[s] = m;
	}

	template<class T2, class M2>
	static void add(data_type& data, mask_type& mask, const T2& d, const M2& m) {
		size_type s2 = d.size();
		if(s2) {
			size_type s = data.size();
			data.resize(s+s2);
			mask.resize(s+s2);
			for(size_type i=0;i<s2;++i) {
				data[s+i] = d[i];
				mask[s+i] = m[i];
			}
		}
	}
};


template<class T, class M>
struct mvtraits<T,M,1u> {
	typedef T														matrix_data_type;
	typedef M														matrix_mask_type;
	typedef typename matrix_data_type::value_type					value_type;
	typedef typename matrix_mask_type::value_type					value_mask_type;
	typedef typename matrix_data_type::size_type					size_type;
	typedef boost::numeric::ublas::matrix_row<matrix_data_type>		data_type;
	typedef boost::numeric::ublas::matrix_row<matrix_mask_type>		mask_type;

	static void add(data_type& data, mask_type& mask, const value_type& d, const value_mask_type& m) {
		QM_FAIL("Cannot add series to this masked vector");
	}

	template<class T2, class M2>
	static void add(data_type& data, mask_type& mask, const T2& d, const M2& m) {
		QM_FAIL("Cannot add series to this masked vector");
	}

	mvtraits(){}
	mvtraits(size_type R, size_type C):data(R,C),mask(R,C){}

	size_type rows() const {return data.size1();}
	size_type cols() const {return data.size2();}

	matrix_data_type data;
	matrix_mask_type mask;
};

template<class T, class M, unsigned F>
class maskedbase {
protected:
	maskedbase() {BOOST_STATIC_ASSERT(F == 0u);}
	maskedbase(unsigned s) {}
};


}



/**
 * \brief Masked Vector for a timeseries map structure
 */
template<class T, class M, unsigned F>
class maskedvector: public maskedbase<T,M,F> {
	typedef maskedvector<T,M,F>								self_type;
	typedef maskedbase<T,M,F>								super;
public:
	typedef mvtraits<T,M,F>									traits_type;
	typedef typename traits_type::data_type					data_type;
	typedef typename traits_type::mask_type					mask_type;
	typedef typename traits_type::value_type				value_type;
	typedef typename traits_type::value_mask_type			value_mask_type;
	typedef typename traits_type::size_type					size_type;

	typedef typename data_type::iterator					iterator;
	typedef typename data_type::const_iterator				const_iterator;

	typedef typename mask_type::iterator					mask_iterator;
	typedef typename mask_type::const_iterator				const_mask_iterator;

	typedef value_type										numtype;

	typedef boost::shared_ptr<traits_type>					traits_type_ptr;
	typedef boost::shared_ptr<data_type>					data_type_ptr;
	typedef boost::shared_ptr<mask_type>					mask_type_ptr;


	static const value_mask_type masked_value     = 0;
	static const value_mask_type not_masked_value = 1;

	maskedvector():m_data(new data_type),m_mask(new mask_type){}

	maskedvector(const value_type& v):
		m_data(new data_type(1, v)),m_mask(new mask_type(1, 1)) {}

	maskedvector(size_type S):
		m_data(new data_type(S, masked_elem())),m_mask(new mask_type(S, 0)) {}

	maskedvector(size_type S, const value_type& v):
		m_data(new data_type(S, v)),m_mask(new mask_type(S, 1)) {}

	maskedvector(traits_type_ptr data, size_type row):
		super(row),m_data(new data_type(data->data,row)), m_mask(new mask_type(data->mask,row)) {}

	template<class T2, class M2, unsigned F2>
	maskedvector(const maskedvector<T2,M2,F2>& mv):
		m_data(new data_type(mv.data())),m_mask(new mask_type(mv.mask())) {}


	template<class AE>
	maskedvector(const boost::numeric::ublas::vector_expression<AE>& ae):
		super(1),m_data(new data_type(ae)) {
		m_mask = mask_type_ptr(new mask_type(m_data->size(), 1));
	}

	/*
	 * \brief the extended copy costructor
	 */
	template<class AE>
	maskedvector& operator = (const boost::numeric::ublas::vector_expression<AE>& ae) {
		(*m_data) = ae;
		return *this;
	}


	size_type	size() const {return m_data->size();}
	size_type   index() const {QM_FAIL("Index not available");}
	size_type	masked() const {
		size_type m = 0;
		for(const_mask_iterator it=this->mask_begin();it!=this->mask_end();++it) {if(!*it) ++m;}
		return m;
	}
	value_type   masked_elem() const {return maskedvalue<value_type>::value();}

	value_type& operator [] (size_type i) {return (*m_data)[i];}
	const value_type& operator [] (size_type i) const {return (*m_data)[i];}

	value_type& operator () (size_type i) {return (*m_data)[i];}
	const value_type& operator () (size_type i) const {return (*m_data)[i];}

	// Iterators
	iterator				begin()			  	  {return m_data->begin();}
	iterator				end()				  {return m_data->end();}

	const_iterator			begin()			const {return m_data->begin();}
	const_iterator			end()			const {return m_data->end();}

	mask_iterator			mask_begin()		  {return m_mask->begin();}
	mask_iterator			mask_end()			  {return m_mask->end();}

	const_mask_iterator		mask_begin()	const {return m_mask->begin();}
	const_mask_iterator		mask_end()		const {return m_mask->end();}

	void	push_back(const value_type& v) {traits_type::add(*m_data,*m_mask,v,1);}

	template<class T2, class M2, unsigned F2>
	void	push_back(const maskedvector<T2,M2,F2>& v) {traits_type::add(*m_data,*m_mask,v.data(),v.mask());}

	void	push_empty() {
		traits_type::add(*m_data,*m_mask,masked_elem(),0);
	}

	void	push_empty(size_type n) {
		for(size_type i=0;i<n;++i)
			traits_type::add(*m_data,*m_mask,masked_elem(),0);
	}

	data_type& data() {return *m_data;}
	const data_type& data() const {return *m_data;}

	mask_type& mask() {return *m_mask;}
	const mask_type& mask() const {return *m_mask;}

private:
	data_type_ptr	m_data;
	mask_type_ptr	m_mask;
};




namespace {

	template<class T, class M, unsigned F>
	struct count_masked_values<maskedvector<T,M,F> > {
		typedef maskedvector<T,M,F>	 value_type;
		static unsigned long apply(const value_type& v) {return v.masked();}
	};

}


}}


#endif	//	__MASKED_VECTOR_TIMESERIES_HPP__
