


#ifndef __TABLE_FUNCTION_HPP__
#define __TABLE_FUNCTION_HPP__


#include <jflib/templates/map.hpp>


namespace jflib { namespace templates {

/** \brief Timeserie template base on a std::map
 *
 * This timeserie template is an associative unique
 * container. For each key there is one and only one value.
 */
template<class Key, class T>
class tablefunction: public associative<Key,T,0,true>  {
	typedef associative<Key,T,0,true>				super_type;
public:
	typedef typename super_type::key_type				key_type;
	typedef typename super_type::mapped_type			num_type;
	typedef typename super_type::const_iterator			const_iterator;
	typedef std::pair<const_iterator,const_iterator>	rangepair;

	tablefunction(){}
	tablefunction(const std::string& name):m_name(name){}

	const std::string& name() const {return m_name;}
	num_type  at(const key_type& k) const {
		const_iterator p2 = this->lower_bound(k);
		const_iterator p1(p2);
		p1--;
		num_type du = p2->first - p1->first;
		return ((k - p1->first)*p2->second + (p2->first - k)*p1->second)/du;
	}
private:
	std::string	m_name;
};




}}



#endif	//	__TABLE_FUNCTION_HPP__
