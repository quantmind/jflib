#ifndef		__CONTAINER_HELPER_TEMPLATE_HPP__
#define		__CONTAINER_HELPER_TEMPLATE_HPP__


#include <vector>
#include <list>


namespace jflib {



template<class C, class T> struct appendtocontainer;



template<class T>
struct appendtocontainer<std::vector<T>, T > {
	typedef std::vector<T> container;
	static void push_back(container& co, const T& val) {
		co.push_back(val);
	}
};

template<class T>
struct appendtocontainer<std::list<T>, T > {
	typedef std::list<T> container;
	static void push_back(container& co, const T& val) {
		co.push_back(val);
	}
};





}

#endif	//	__CONTAINER_HELPER_TEMPLATE_HPP__

