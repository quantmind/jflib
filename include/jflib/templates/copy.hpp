
#ifndef __TEMPLATES_EXTENDED_COPY_HPP_
#define __TEMPLATES_EXTENDED_COPY_HPP_

#include <algorithm>

namespace jflib { namespace templates {

template<class InputIterator, class OutputIterator>
void copy2D(InputIterator start, InputIterator end, OutputIterator output)  {
	for(;start!=end;++start)  {
		std::copy(start->begin(),start->end(),output.begin());
		++output;
	}
}


}}


#endif	//	__TEMPLATES_EXTENDED_COPY_HPP_
