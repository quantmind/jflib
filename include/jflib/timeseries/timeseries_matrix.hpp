//
/// \ingroup timeseries
/// Timeserie class with direct access

#ifndef __TIMESERIES_MATRIX_HPP_
#define __TIMESERIES_MATRIX_HPP_


#include <jflib/jflib.hpp>
#include <jflib/timeseries/masked/oper.hpp>
#include <jflib/timeseries/structures.hpp>
#include <jflib/timeseries/traits/matrix.hpp>
#include <jflib/timeseries/traits/utils.hpp>

#include <algorithm>
#include <functional>


namespace jflib { namespace timeseries {



/**
 * \brief Timeseries class of familiy 1
 *
 * A timeseries of family 1 is based on a matrix structure for the data.
 * This type of structure facilitate econometric analysis of multivariate time-series.
 */
template<class Key, class T, class Tag>
class timeseries<Key,T,Tag,1u,true>: public timeseries_base<timeseries<Key,T,Tag,1u,true> >  {
	BOOST_STATIC_ASSERT(Tag::family == 1u);
	BOOST_STATIC_ASSERT(Tag::multipleseries);
	typedef typename Tag::template container<Key,T>							tstraits;
	typedef typename tstraits::type											self_type;
public:
	typedef Tag																tag;
	typedef Key																key_type;
	typedef typename tstraits::numtype										numtype;
	typedef typename tstraits::data_type									matrix_data_type;
	typedef typename tstraits::mask_type									matrix_mask_type;
	typedef traits::matrix_traits<matrix_data_type>							matrix_data_traits;
	typedef typename matrix_data_traits::reference_type						matrix_data_reference;
	typedef maskedvector<matrix_data_type,matrix_mask_type,tag::family>		mapped_type;
	typedef matrixmap<mapped_type>											maptag;
	typedef typename traits::ts<key_type,mapped_type,maptag>::type			map_type;

	typedef typename map_type::value_type									value_type;
	typedef typename mapped_type::size_type									size_type;

	// Map iterators
	typedef typename map_type::iterator										iterator;
	typedef typename map_type::const_iterator								const_iterator;
	typedef typename map_type::key_iterator									key_iterator;
	typedef typename map_type::const_key_iterator							const_key_iterator;
	typedef typename map_type::val_iterator									val_iterator;
	typedef typename map_type::const_val_iterator							const_val_iterator;

	typedef typename daycountertype<key_type>::type							daycounter;

	//Shared pointers
	typedef typename mapped_type::traits_type	 							matrix_type;
	typedef typename mapped_type::traits_type_ptr 							matrix_type_ptr;

	static const unsigned family 	 = tag::family;
	static const bool multipleseries = true;

	timeseries():m_data(new matrix_type){}
	timeseries(const std::string& name):m_name(name),m_data(new matrix_type){}
	timeseries(size_type TT, size_type NN):m_data(new matrix_type(TT,NN)){}
	timeseries(const std::string& name, size_type TT, size_type NN):m_name(name),m_data(new matrix_type(TT,NN)){}
	timeseries(const timeseries& rhs):m_name(rhs.m_name),m_data(rhs.m_data),m_map(rhs.m_map){}

	// Template Copy constructor
	template<class Ctag, unsigned F2, bool M2>
	static self_type make(const timeseries<key_type,numtype,Ctag,F2,M2>& rhs) {
		typedef timeseries<key_type,numtype,Ctag,F2,M2> tstype;

		if(rhs.empty()) {
			timeseries t;
			return t;
		}
		timeseries ts(rhs.size(),rhs.series());
		size_type r = 0;
		iterator it1 = ts.begin();
		map_type map = ts.map();
		for(typename tstype::const_iterator it=rhs.begin(); it!=rhs.end(); ++it) {
			mapped_type row(ts.m_data, r);
			it1 = map.insert(it1, value_type(it->first,row));
			traits::CopyRow<tstype::multipleseries,multipleseries>::copy(it->second,row);
			r++;
		}
		return ts;
	}

	const std::string& name() const {return m_name;}
	bool	  empty()      const  {return m_map.empty();}
	size_type size()       const  {return m_map.size();}
	size_type series()     const  {return m_data->data.size2();}
	size_type	masked()	const {return 0;}

	size_type removemasked() {QM_FAIL("Cannot remove masked values in this timeseries structure");}

	const self_type& apply() const {return *this;}
	bool has_key(const key_type& key) const {return m_map.has_key(key);}
	const mapped_type& at(const key_type& key) const {return m_map.at(key);}
	void add(const key_type& key, const mapped_type& value) {QM_FAIL("Cannot add items to this timeseries");}
	bool is_valid() const {return true;}

	// Functions used by Python.
	matrix_data_type data() const {return m_data->data;}
	matrix_mask_type mask() const {return m_data->mask;}

	const map_type& map() const {return m_map;}

	iterator				begin()			  {return m_map.begin();}
	iterator				end()			  {return m_map.end();}
	const_iterator			begin()		const {return m_map.begin();}
	const_iterator			end()		const {return m_map.end();}

	// The map keys iterators
	key_iterator			key_begin()       {return m_map.key_begin();}
	key_iterator	    	key_end()		  {return m_map.key_end();}
	const_key_iterator  	key_begin() const {return m_map.key_begin();}
	const_key_iterator  	key_end()   const {return m_map.key_end();}

	// The map values iterators
	val_iterator			val_begin()       {return m_map.val_begin();}
	val_iterator	    	val_end()		  {return m_map.val_end();}
	const_val_iterator  	val_begin() const {return m_map.val_begin();}
	const_val_iterator  	val_end()   const {return m_map.val_end();}

	const value_type&		front()		const {return m_map.front();}
	const value_type&		back()		const {return m_map.back();}

	self_type copy(const key_type& start, const key_type& end) const {
		QM_FAIL("copy not implemented");
	}

	self_type clone() const {
		QM_FAIL("copy not implemented");
	}

	template<class AE>
	iterator insertexpression(iterator it, size_type r, const key_type& key, const AE& ae) {
		mapped_type m(m_data, r);
		m = ae;
		return m_map.insert(it, value_type(key,m));
	}

	matrix_type_ptr             support() {return m_data;}
	const matrix_data_type&		internal_data() const {return m_data->data;}
	matrix_data_type&			internal_data() {return m_data->data;}

	self_type tomatrix() const {return *this;}
private:
	std::string			m_name;
	matrix_type_ptr		m_data;
	map_type			m_map;
};


}}


namespace jflow {



}

#endif	//	__TIMESERIES_MATRIX_HPP_
