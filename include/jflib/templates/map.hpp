///////////////////////////////////////////////////////////////////////////////
//

#ifndef __TEMPLATES_EXTENDED_MAP_HPP_
#define __TEMPLATES_EXTENDED_MAP_HPP_

#include <map>
#include <functional>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>


namespace jflib { namespace templates {

template<class K, class T, int multi = 0, bool orderd = true> class associative;


namespace {

	template<typename K, typename T>
	struct take_first  {
		typedef std::pair<K,T>		argument_type;
		typedef K					result_type;
		const result_type& operator () (const argument_type& p) const {
			return p.first;
		}
	};

	template<typename K, typename T>
	struct take_second  {
		typedef std::pair<K,T>		argument_type;
		typedef T					result_type;
		const result_type& operator () (const argument_type& p) const {
			return p.second;
		}
	};
}


template<class TS> class maprange;


template<class Key, class T>
class associative<Key,T,0,true>  {
	typedef std::map<Key,T>												container;
	typedef boost::shared_ptr<container>								container_ptr;
	typedef take_first<Key,T>											key_transform;
	typedef take_second<Key,T>											val_transform;
public:
	typedef typename container::size_type								size_type;
	typedef typename container::value_type								value_type;
	typedef typename container::key_type								key_type;
	typedef typename container::mapped_type								mapped_type;

	typedef typename container::iterator								iterator;
	typedef typename container::const_iterator							const_iterator;
	typedef typename container::reverse_iterator						reverse_iterator;
	typedef typename container::const_reverse_iterator					const_reverse_iterator;
	typedef boost::transform_iterator<key_transform, iterator>			key_iterator;
	typedef boost::transform_iterator<key_transform, const_iterator>	const_key_iterator;
	typedef boost::transform_iterator<val_transform, iterator>			val_iterator;
	typedef boost::transform_iterator<val_transform, const_iterator>	const_val_iterator;

	// Zip iterator
	typedef boost::tuple<const_iterator,const_iterator>					const_tuple_iterator;
	typedef boost::zip_iterator<const_tuple_iterator>					const_zip_iterator;

	typedef std::pair<const_iterator,const_iterator>					const_iterator_pair;


	associative():m_ptr(new container),m_eval(true){}
	associative(const associative& rhs):m_ptr(rhs.m_ptr),m_eval(rhs.m_eval){}
	associative(bool eval):m_ptr(new container),m_eval(eval){}

	virtual ~associative(){}

	bool		 ismulti() const   {return false;}
	bool		 orderd()  const   {return true;}

	// Iterators
	iterator				begin()			  {return m_ptr->begin();}
	iterator				end()			  {return m_ptr->end();}
	const_iterator			begin()		const {return m_ptr->begin();}
	const_iterator			end()		const {return m_ptr->end();}

	reverse_iterator 		rbegin()		  {return m_ptr->rbegin();}
	reverse_iterator 		rend()			  {return m_ptr->rend();}
	const_reverse_iterator 	rbegin() 	const {return m_ptr->rbegin();}
	const_reverse_iterator 	rend() 		const {return m_ptr->rend();}

	key_iterator			key_begin()       {this->unwind(); return boost::make_transform_iterator(this->begin(),key_transform());}
	key_iterator	    	key_end()		  {this->unwind(); return boost::make_transform_iterator(this->end(),  key_transform());}
	const_key_iterator  	key_begin() const {this->unwind(); return boost::make_transform_iterator(this->begin(),key_transform());}
	const_key_iterator  	key_end()   const {this->unwind(); return boost::make_transform_iterator(this->end(),  key_transform());}

	val_iterator			val_begin()       {this->unwind(); return boost::make_transform_iterator(this->begin(),val_transform());}
	val_iterator			val_end()         {this->unwind(); return boost::make_transform_iterator(this->end(),  val_transform());}
	const_val_iterator  	val_begin() const {this->unwind(); return boost::make_transform_iterator(this->begin(),val_transform());}
	const_val_iterator  	val_end()   const {this->unwind(); return boost::make_transform_iterator(this->end(),  val_transform());}

	const_zip_iterator		range_begin(unsigned long range) const {return const_zip_iterator(this->rangestart(range));}
	const_zip_iterator		range_end() const {return const_zip_iterator(const_tuple_iterator(this->end(),this->end()));}

	//range_iterator			range_begin(unsigned long range)  {return boost::make_transform_iterator(this->begin(),range_transform(range));}
	//range_iterator			range_end()  {return boost::make_transform_iterator(this->begin(),range_transform());}

	// Map methods
	size_type				size()									const 	{return m_ptr->size();}
	bool					empty()									const	{return m_ptr->empty();}
	size_type 				count(const key_type& x) 				const 	{this->unwind(); return m_ptr->count(x);}
	iterator            	find(const key_type& x) 						{return m_ptr->find(x);}
	const_iterator         	find(const key_type& x)  				const	{return m_ptr->find(x);}
	void					erase(iterator position) 						{m_ptr->erase(position);}
	iterator				erase(iterator first, iterator last)			{return m_ptr->erase(first,last);}
	size_type  				erase(const key_type& x)						{return m_ptr->erase(x);}
	iterator				lower_bound(const key_type& x)					{return m_ptr->lower_bound(x);}
	const_iterator			lower_bound(const key_type& x)			const	{return m_ptr->lower_bound(x);}
	iterator				upper_bound(const key_type& x)					{return m_ptr->upper_bound(x);}
	const_iterator			upper_bound(const key_type& x)			const	{return m_ptr->upper_bound(x);}

	std::pair<iterator,iterator> equal_range(const key_type& x) {return m_ptr->equal_range(x);}
	std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const {return m_ptr->equal_range(x);}

	std::pair<iterator, bool> 	insert(const value_type& x)						{return m_ptr->insert(x);}
	iterator 					insert(iterator position, const value_type& x)	{return m_ptr->insert(position,x);}

	template <class InputIterator>
	void	insert(InputIterator first, InputIterator last)	{return m_ptr>insert(first,last);}

	// New methods
	void add(const key_type& key, const mapped_type& value) {
			std::pair<iterator, bool> res = m_ptr->insert(value_type(key,value));
			res.first->second = value;
		}

	bool is_valid() const {return true;}

	bool	has_key(const Key& k) const {return m_ptr->find(k) == m_ptr->end() ? false : true;}
	bool	eval() const	{return m_eval;}


	const_tuple_iterator rangestart(unsigned long range) const {
		const_iterator start = this->begin();
		const_iterator end   = this->begin();
		unsigned long r=1;
		while(r<range && end != this->end()) {
			r++;
			++end;
		}
		if(r == range)
			return const_tuple_iterator(start,end);
		else
			QM_FAIL("Out of bound");
	}

	container_ptr	inner() const {return m_ptr;}

protected:
	container_ptr 	m_ptr;
	bool			m_eval;
	virtual void unwind()  const   {}
};



template<class TS>
class maprange {
public:
	typedef TS									tstype;
	typedef typename tstype::size_type			size_type;
	typedef typename tstype::const_zip_iterator	iterator;

	static maprange make(const tstype& ts, size_type range) {return maprange(ts,range);}

	maprange(const tstype& ts, size_type range):m_ts(ts),m_range(range){}
	maprange(const maprange& rhs):m_ts(rhs.m_ts),m_range(rhs.m_range){}

	size_type	size() const {QM_REQUIRE(m_ts.size()>=m_range,"Out of bound"); return m_ts.size() - m_range;}
	size_type	range() const {return m_range;}

	iterator	begin() const {return m_ts.range_begin(m_range);}
	iterator	end() const {return m_ts.range_end();}
private:
	tstype		m_ts;
	size_type	m_range;
};


template<class C>
struct zip_operator_traits {
	typedef C																container;
	typedef typename container::const_tuple_iterator						const_tuple_iterator;
	typedef typename std::unary_function<const const_tuple_iterator&, void>	unary_func;
};



template<class C, class Op, class R>
class zip_operator: public zip_operator_traits<C>::unary_func {
public:
	typedef C		container;
	typedef R		result_type;
	typedef typename container::const_tuple_iterator	const_tuple_iterator;

	void operator () (const const_tuple_iterator& t) const  {
		//Op::apply(m_result,t.get<0>(),t.get<1>());
	}

	const result_type& apply(const container& ts, unsigned long range) const {
		std::for_each(ts.range_begin(range),ts.range_end(),*this);
	}
private:
	result_type		m_result;
};




}}


#endif	//	__TEMPLATES_EXTENDED_MAP_HPP_
