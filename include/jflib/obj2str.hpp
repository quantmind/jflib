

#ifndef __OBJ2STR_JFLIB_HPP__
#define __OBJ2STR_JFLIB_HPP__

#include <boost/lexical_cast.hpp>

namespace jflib {


/**
 * \brief Template class for converting objects to string
 */
template<class T>
struct obj2string {
	static std::string get(const T& obj) {return "";}
};

template<class T>
std::string obj2str(const T& obj) {
	return obj2string<T>::get(obj);
}


//////////////////////////////////////////////////////////////////////////
//	SPECIALIZATIONS


//Shared pointer specification
template<class T>
struct obj2string<boost::shared_ptr<T> > {
	static std::string get(const boost::shared_ptr<T>& ptr) {
		return obj2string<T>::get(*ptr);
	}
};



#define QM_OBJ_TO_STRING_NUMBER(name)							\
template<> struct obj2string<name>  {							\
	static std::string get(name y)  {							\
		return boost::lexical_cast<std::string>(y);				\
	}															\
};

QM_OBJ_TO_STRING_NUMBER(int)
QM_OBJ_TO_STRING_NUMBER(bool)
QM_OBJ_TO_STRING_NUMBER(short)
QM_OBJ_TO_STRING_NUMBER(long)
QM_OBJ_TO_STRING_NUMBER(unsigned short)
QM_OBJ_TO_STRING_NUMBER(unsigned)
QM_OBJ_TO_STRING_NUMBER(unsigned long)
QM_OBJ_TO_STRING_NUMBER(float)
QM_OBJ_TO_STRING_NUMBER(double)


// Specialization for std::pair
template<class K, class T>
struct obj2string<std::pair<K,T> >  {
	typedef std::pair<K,T> pair_type;
	static std::string get(const pair_type& pa)  {
		return obj2str(pa.first) + ": " + obj2str(pa.second);
	}
};



template<class C>
std::string stdcontainer2str(const C& co,
							 const std::string& open = "[",
							 const std::string& close = "]",
							 const std::string& sep = ", ")  {
	typedef typename C::value_type value_type;
	std::string r(open);
	bool first = true;
	for(typename C::const_iterator it=co.begin();it!=co.end();++it) {
		if(!first)
			r += sep;
		first = false;
		r += obj2string<value_type>::get(*it);
	}
	r += close;
	return r;
}

template<class T, class A>
struct obj2string<std::vector<T,A> > {
	static std::string get(const std::vector<T,A>& co)  {return stdcontainer2str(co);}
};
template<class T, class A>
struct obj2string<std::list<T,A> > {
	static std::string get(const std::list<T,A>& co)  {return stdcontainer2str(co);}
};
template<class K, class T, class C, class A>
struct obj2string<std::map<K,T,C,A> > {
	static std::string get(const std::map<K,T,C,A>& co)  {return stdcontainer2str(co,"{","}");}
};


#define REGISTER2STRING(name)						\
template<> struct obj2string<name>  {				\
	static std::string get(const name& x)  {		\
		return x.tostring();						\
	}												\
};



}


#endif	//	__OBJ2STR_JFLIB_HPP__
