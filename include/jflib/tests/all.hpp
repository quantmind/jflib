
#ifndef		__JFLIB_PYTHON_TESTS_ALL_HPP_
#define		__JFLIB_PYTHON_TESTS_ALL_HPP_

namespace jflib {

namespace python {

	void expose_tests();

}



namespace tests {

class TestHandle {
public:
	TestHandle(){}

	int ublasmatrix();
	int eigenvectors(int size);
};

}


}



#endif	//	__JFLIB_PYTHON_TESTS_ALL_HPP_


