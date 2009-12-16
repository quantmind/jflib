//
//  errors.h
//  Classes and functions for error handling
//
#ifndef __ERROR_JFLIB_HPP__
#define __ERROR_JFLIB_HPP__

#include <jflib/definitions.hpp>
#include <exception>
#include <sstream>
#include <stdexcept>

/*! \defgroup utility Utilities

    Several classes for general usage

    @{
*/


namespace jflib {


/// \brief Base error class
class Error: public std::exception  {
public:
	Error(const std::string& file, long line, const std::string& function,
		  const std::string& message = "");
    ~Error() throw() {}

	const char* what() const throw () {return m_message->c_str();}
private:
	boost::shared_ptr<std::string> m_message;
};


///  \brief throw an error (possibly with file and line information)
#define QM_FAIL(message) \
do { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} while (false)
//
//
/// \brief throw an error if the given condition is not verified
#define QM_ASSERT(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else
//
//
/// \brief throw an error if the given pre-condition is not verified
#define QM_REQUIRE(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else
//
//
/// \brief throw an error if the given post-condition is not verified
#define QM_ENSURE(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else


#ifdef	NDEBUG
#	define	QMIND_PRECONDITION(X,Y)
#else
#	define	QMIND_PRECONDITION(X,Y)	QM_ASSERT(X,Y)
#endif

}


/*! @} */


#endif	//	__ERROR_JFLIB_HPP__

