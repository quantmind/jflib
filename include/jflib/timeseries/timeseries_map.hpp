/**
 * \brief Template definition of a timeseries based on a std::map template
 */

#ifndef __TIMESERIES_MAP_HPP__
#define __TIMESERIES_MAP_HPP__

#include <jflib/jflib.hpp>
#include <jflib/templates/map.hpp>
#include <jflib/timeseries/timeseries_base.hpp>
#include <jflib/timeseries/traits/utils.hpp>


namespace jflib { namespace timeseries {

/** \brief Timeserie template base on a std::map
 *
 * This timeserie template is an associative unique
 * container. For each key there is one and only one value.
 */
template<class Key, class T, class Tag, bool M>
class timeseries<Key,T,Tag,0u,M>:
	public timeseries_base<timeseries<Key,T,Tag,0u,M> >,
	public traits::ts<Key,T,Tag>::super {

    BOOST_STATIC_ASSERT(Tag::family 		== 0u);
    BOOST_STATIC_ASSERT(Tag::multipleseries == M);

	typedef traits::ts<Key,T,Tag>					tstraits;
	typedef typename tstraits::type					self_type;
	typedef typename tstraits::super				super_type;
public:
	typedef Tag										tag;
	typedef typename tstraits::numtype				numtype;
	typedef typename super_type::key_type			key_type;
	typedef typename super_type::mapped_type		mapped_type;
	typedef typename super_type::value_type			value_type;
	typedef typename super_type::size_type			size_type;
	typedef typename super_type::iterator			iterator;
	typedef typename super_type::const_iterator		const_iterator;

	typedef mapped_type								matrix_type;
	typedef mapped_type								masked_type;

	typedef typename daycountertype<key_type>::type	daycounter;

	static const unsigned family = tag::family;
	static const bool multipleseries = tag::multipleseries;

	timeseries(){}
	timeseries(const std::string& name):m_name(name){}
	timeseries(size_type r, size_type c){}
	timeseries(const timeseries& rhs):super_type(rhs),m_name(rhs.m_name){}

	size_type	 series()  const   {return traits::CalcNumSeries<self_type>::apply(*this);}

	const std::string& name() const {return m_name;}

	const self_type& apply() const {return *this;}

	size_type masked() const {
		size_type m = 0;
		for(const_iterator it=this->begin(); it!=this->end(); ++it) {
			m += masked_values(it->second);
		}
		return m;
	}

	size_type removemasked() {
		size_type m = 0;
		iterator it=this->begin();
		while(it!=this->end()) {
			if(masked_values(it->second)) {
				m++;
				this->erase(it++);
			}
			else ++it;
		}
		return m;
	}

	const mapped_type& at(const key_type& key) const {
		const_iterator it = this->find(key);
		if(it != this->end()) return it->second;
		else QM_FAIL("Key not available");
	}

	const value_type& front() const {
		QM_REQUIRE(this->size(),"Out of bound");
		return *this->begin();
	}

	const value_type& back() const {
		QM_REQUIRE(this->size(),"Out of bound");
		return *this->rbegin();
	}



	self_type copy(const key_type& start, const key_type& end) const {
		self_type ts(m_name);
		this->_copy(ts,this->upper_bound(start),this->upper_bound(end));
		return ts;
	}

	self_type clone() const {
		self_type ts(m_name);
		this->_copy(ts,this->begin(),this->end());
		return ts;
	}

	matrix_type data() const {QM_FAIL("Not yet available");}
	masked_type mask() const {QM_FAIL("Not yet available");}

	template<class MTag>
	typename traits::ts<key_type,numtype,MTag>::type
	tomatrix() const {
		BOOST_STATIC_ASSERT(MTag::family == 1u);
		typedef typename traits::ts<key_type,numtype,MTag>::type 	tsmat;
		return tsmat::make(*this);
	}

	template<class AE>
	iterator insertexpression(iterator it, size_type r, const key_type& key, const AE& ae) {
		return this->insert(it,value_type(key,mapped_type(ae)));
	}
private:
	std::string	m_name;

	void _copy(self_type& ts, const_iterator start, const_iterator end) const {
		iterator io = ts.begin();
		for(const_iterator it = start; it != end; ++it) {
			io = ts.insert(io, value_type(it->first,it->second));
		}
	}
};




}}



#endif	//	__TIMESERIES_MAP_HPP__
