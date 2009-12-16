

#ifndef __BASE_RNDGEN_QM_HPP__
#define __BASE_RNDGEN_QM_HPP__

/** Header file for random library
 */


#include <jflib/jflib.hpp>
#include <boost/math/concepts/distributions.hpp>



namespace jflib { namespace math {



namespace rndgen {

template<class RealType> class rndgen;

}


/**
 * Random number generator
 *
 */
template<class ND>
class random {
public:
	typedef ND											normal_distribution;
	typedef typename normal_distribution::value_type	RealType;
	typedef jflib::math::rndgen::rndgen<RealType>		gen_type;
	typedef boost::shared_ptr<gen_type>					gen_ptr;
	typedef typename gen_type::size_type				size_type;

	random(const gen_ptr& gen):m_gen(gen){}

	random(const random& rhs):m_gen(rhs.m_gen){}

	std::string name() const {return m_gen->name();}

	RealType nextUniform(size_type idx = 0, size_type dim = 0) const {return m_gen->nextUniform(idx,dim);}

	/// \brief generate a standard normal variate
	/// @param idx Index indicating the position in sample set of a montecarlo method
	/// @param dim Dimension associated with idx
	/// @return A standard normal variate in \f$(-\infty,\infty)\f$
	RealType nextNormalVariate(size_type idx = 0, size_type dim = 0) const {
		return boost::math::concepts::quantile(m_norm,this->nextUniform(idx,dim));
	}

	/// \brief generate a poisson time arrival
	/// @param lambda the integrated inetnsity
	/// @param idx Index indicating the position in sample set of a montecarlo method
	/// @param dim Dimension associated with idx
	/// @return A poisson arrival
	RealType nextArrival(size_type idx = 0, size_type dim = 0) const {
		return -std::log(this->nextUniform(idx,dim));
	}
private:
	gen_ptr					m_gen;
	normal_distribution		m_norm;
};


}}


#endif  //  __BASE_RNDGEN_QM_HPP__


