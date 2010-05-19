/** @file	LinearSpringDamper.h
	@brief	header for a linear spring-damper system

	@date	2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2010
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#pragma once
#ifndef _PHYSICALMODELING_LINEARSPRINGDAMPER_H_
#define _PHYSICALMODELING_LINEARSPRINGDAMPER_H_

// Internal Includes
#include <PhysicalModeling/DimensionedQuantities.h>

// Library/third-party includes
// - none

// Standard includes
#include <limits>

namespace PhysicalModeling {

/** @addtogroup gSpringDamperSystems Spring-Damper Systems
	These classes provide simple support for spring-damper systems.
	@{
 */

template<class Precision = DefaultPrecision>
class LinearSpringDamper {
	public:
		typedef DimensionedQuantities::Quantity<DimensionedQuantities::dims::mass, Precision> mass_t;
		typedef DimensionedQuantities::Quantity<DimensionedQuantities::dims::length, Precision> length_t;
		typedef DimensionedQuantities::Quantity<DimensionedQuantities::dims::stiffness, Precision> stiffness_t;
		typedef DimensionedQuantities::Quantity<DimensionedQuantities::dims::viscosity, Precision> viscosity_t;
		typedef DimensionedQuantities::Quantity<DimensionedQuantities::dims::force, Precision> force_t;

		LinearSpringDamper(const mass_t & mass, const stiffness_t & stiffness, const viscosity_t & viscosity = 0) :
				_m(mass),
				_K(stiffness),
				_B(viscosity),
				_x(std::numeric_limits<Precision>::max()),
				_f(std::numeric_limits<Precision>::max()) {}

		void setDisplacement(const length_t & displacement);

		const force_t & force();


	protected:
		/// @name parameters for spring-damper system
		/// @{
		mass_t _m;
		stiffness_t _K;
		viscosity_t _B;
		/// @}

		/// @name parameters for status of system
		/// @{

		/// @brief displacement
		length_t _x;

		/// @}

		/// @name Cached results of computation, to be able to return const &
		/// @{
		force_t _f;
		/// @{


};

// -- inline implementations -- //
inline void LinearSpringDamper<Precision>::setDisplacement(const length_t & displacement) {
	_x = displacement;
}

inline const force_t & LinearSpringDamper<Precision>::force() {

}
/// @}
// end of doxygen module

} // end of PhysicalModeling namespace

#endif // _PHYSICALMODELING_DIMENSIONEDQUANTITIES_H_
