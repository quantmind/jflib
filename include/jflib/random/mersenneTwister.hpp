



#ifndef __MERSENNE_TWISTER_RNDGEN_HPP__
#define __MERSENNE_TWISTER_RNDGEN_HPP__


#include <jflib/random/rndgen.hpp>


/*! \ingroup random Random Number Library

    Random number generation, using quasirandom generators
    and low discrepancy numbers

    @{
*/

//
/// \file
/// \brief Base classes for Random number generation

namespace jflib { namespace math { namespace rndgen {





/// \brief Mersenne Twister quasiRandomNumber generator of period 2**19937-1
/// \note For more details see http://en.wikipedia.org/wiki/Mersenne_twister and
/// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
///
/// Mersenne Twister(MT) is a pseudorandom number generating algorithm developped
/// by Makoto Matsumoto  and Takuji Nishimura (alphabetical order) in 1996/1997.
///  - Far longer period and far higher order of equidistribution than any other implemented
///    generators. (It is proved that the period is 2^19937-1, and 623-dimensional
///    equidistribution property is assured.)
template<class RealType, unsigned N = 624>
class MersenneTwister: public rndgen<RealType>  {
public:
	typedef rndgen<RealType>					super_type;
	typedef typename super_type::size_type		size_type;
	typedef typename super_type::seed_type		seed_type;
	typedef std::vector<seed_type>				ulvector;

	// if the given seed is 0, a random seed will be chosen based on clock()
    explicit MersenneTwister(seed_type seed = 0):mt(N) {seedInitialization(seed);}
    explicit MersenneTwister(const ulvector& seeds):mt(N) {seedVectorInitialization(seeds);}
    //
    // divide by 2^32
    RealType nextUniform(size_type n = 0, size_type dim = 0) const  {return (RealType(this->nextInt32()) + 0.5)/4294967296.0;}
    //
    // return  a random number on [0,0xffffffff]-interval
    seed_type nextInt32() const;

    std::string tostring() const {return "Mersenne Twister Random number generar";}

    void    seedVectorInitialization(const ulvector& seed);
    void    seedInitialization(seed_type seed);
private:
    static const size_type          M 		   = 397;
	static const seed_type	      	MATRIX_A   = 0x9908b0dfUL;  /* constant vector a */
	static const seed_type        	UPPER_MASK = 0x80000000UL;  /* most significant w-r bits */
	static const seed_type        	LOWER_MASK = 0x7fffffffUL;  /* least significant r bits */
	//
	mutable ulvector  	mt;
	mutable size_type	mti;
};



#include <jflib/random/impl/mersenneTwister_impl.hpp>



}}}


#endif	//	__MERSENNE_TWISTER_RNDGEN_HPP__


