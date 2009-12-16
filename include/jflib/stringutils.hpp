
#ifndef		__STRING_UTILS_HPP__
#define		__STRING_UTILS_HPP__

namespace jflib {


typedef std::vector<std::string> stdstrings;


inline stdstrings split(const std::string& str, const std::string& delim)  {
    unsigned offset = 0;
    unsigned delimIndex = 0;
    delimIndex = str.find(delim, offset);
    stdstrings output;
    unsigned npo = std::string::npos;
    while (delimIndex != npo)  {
      output.push_back(str.substr(offset, delimIndex - offset));
      offset += delimIndex - offset + delim.length();
      delimIndex = str.find(delim, offset);
    }
    output.push_back(str.substr(offset));
    return output;
}


}


#endif	//	__STRING_UTILS_HPP__

