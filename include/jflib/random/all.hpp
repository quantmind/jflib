

#ifndef __ALL_RNDGEN_QM_HPP__
#define __ALL_RNDGEN_QM_HPP__


#include <jflib/random/base.hpp>
#include <jflib/random/rndgen.hpp>
#include <jflib/random/mersenneTwister.hpp>
//#include <jflib/random/sobol.hpp>


namespace jflow { namespace math {

/*
template<class D, class ND>
inline D randomdate(const random<ND>& gen, const D& start, const D& end)  {
	double d = D::daydiff(start,end);
	QM_REQUIRE(d>0,"Dates are not correct for random generation");
	unsigned dr = (unsigned)(gen.nextUniform()*d);
	D re(start);
	re.add_days(dr);
	return re;
}
*/


}}


#endif  //  __ALL_RNDGEN_QM_HPP__

