/********************************************************************************
 * qmlib/math/rndgen.hpp
 *
 * Copyright (C) 2007-2008 Luca Sbardella <luca.sbardella@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          quant.mind@gmail.com
 * Bugs:                 quant.mind@gmail.com
 *
 * For more information, please see the quantmind Home Page:
 *    http://www.quantmind.com
 *
 *******************************************************************************/


#ifndef __RNDGEN_QM_HPP__
#define __RNDGEN_QM_HPP__


#include <jflib/random/base.hpp>


/*! \ingroup random Random Number Library

    Random number generation, using quasirandom generators
    and low discrepancy numbers

    @{
*/

//
/// \file
/// \brief Base classes for Random number generation

namespace jflib { namespace math { namespace rndgen {


/// \brief Interface class for random number generator
template<class RealType>
class rndgen {
public:
	typedef unsigned 		size_type;
	typedef unsigned long	seed_type;

    /// \brief generate a uniform random number in [0,1]
    /// @param idx Index indicating the position in sample set of a montecarlo method
    /// @param dim Dimension associated with idx
    /// @return A uniform random number in [0,1]
    virtual RealType nextUniform(size_type idx = 0, size_type dim = 0) const {QM_FAIL("nextUniform not implemented");}

    virtual size_type maxdimension() const {return std::numeric_limits<size_type>::infinity();}
protected:
   	/// \brief seed initializer
    seed_type   initialseed() const;
};



/// \brief Seed generator for random number generator
/// \ingroup random
template<class G>
class SeedGenerator  {
public:
	typedef G									gen_type;
	typedef typename gen_type::seed_type		seed_type;
  	SeedGenerator();
  	seed_type get() const {return m_rng.nextInt32();}
private:
   	gen_type  m_rng;
   	void initialize();
};






/// \brief Base class for low Discrepacy Sequence Generator
template<class RealType>
class lowDiscrepacySequenceGenerator: public rndgen<RealType>  {
public:
	typedef rndgen<RealType>				super_type;
	typedef typename super_type::size_type	size_type;
  	typedef std::vector<RealType>       	samples;
   	typedef std::vector<samples>   	    	vector_samples;

   	lowDiscrepacySequenceGenerator(size_type dim, size_type start):m_dimensionality(dim),m_start(start){}
   	virtual ~lowDiscrepacySequenceGenerator(){}

   	size_type maxdimension()	const { return m_dimensionality;}

   	size_type dimension()		const { return m_dimensionality;}
   	size_type sequenceCounter() const { return m_sequence.size();}

   	/// \brief A point in the sample space
   	/// @param n point in the sequence
   	/// @param dim dimensionality of the point
   	/// @return a point in the sample space [1,big number]x[1,dimension]
   	RealType nextUniform(size_type n, size_type dim) const;

protected:
   	size_type                 m_dimensionality;
   	size_type				  m_start;
   	mutable vector_samples    m_sequence;

   	/// \brief generate the next sequence of points for all dimensions
   	virtual void nextSequence() const = 0;
};


}}}


#endif  //  __RNDGEN_QM_HPP__

/*! @} */

