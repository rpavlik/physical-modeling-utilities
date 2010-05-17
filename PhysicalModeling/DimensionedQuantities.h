/** @file	DimensionedQuantities.h
	@brief	header for dimension-aware quantities

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
#ifndef _PHYSICALMODELING_DIMENSIONEDQUANTITIES_H_
#define _PHYSICALMODELING_DIMENSIONEDQUANTITIES_H_

// Internal Includes
// - none

// Library/third-party includes
/// @name Boost MPL headers
/// @{
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
/// @}

// Standard includes
// - none

namespace PhysicalModeling {

/** @brief Namespace for all typedefs and classes required for Dimensioned
	Quantities support.

	Enable the use of this module in your code as follows - each variable
	declaration is equivalent and just shows an alternate method.
	@code
	// Required include line
	#include <PhysicalModeling/DimensionedQuantities.h>

	// Standard, lengthy way of creating a variable to store a length
	PhysicalModeling::DimensionedQuantities::Quantity<PhysicalModeling::DimensionedQuantities::dims::length> myvar;

	// Namespace aliasing, for tidier code: recommended practice
	namespace dq = PhysicalModeling::DimensionedQuantities;
	dq::Quantity<dq::dims::length> myvar2; // notice how much tidier this is
	@endcode

	There is one additional way to access these facilities even easier,
	but it comes with an important warning - never use it in a header file!
	Use it inside a function in a .cpp, or at the top of a .cpp.
	@code
	// The shortest alternative: import the things you want.
	// NEVER DO THIS IN A HEADER FILE!
	using PhysicalModeling::DimensionedQuantities::Quantity;
	using PhysicalModeling::DimensionedQuantities::dims;

	Quantity<dims::length> myvar3; // a little neater
	@endcode
*/

namespace DimensionedQuantities {
/** @defgroup gDimensionedQuantities Dimensioned Quantities
	@brief Let the compiler enforce the dimensional validity of your calculations.

	Allows specification of dimensions (mass, length, etc) as a part of a
	C++ type, which will then enforce dimensional compatibility (can't add
	a mass and a length) and allow for dimensional analysis-type computation
	(mass times acceleration produces a force).

	For example, here is some code using the basic Quantity<>
	template class:

	@code
	#include <PhysicalModeling/DimensionedQuantities.h>
	namespace dq = PhysicalModeling::DimensionedQuantities; // Namespace alias, for tidier code
	dq::Quantity<dq::dims::mass> m(20.0); // mass of 20 (think kg)
	dq::Quantity<dq::dims::accel> a(9.810); // accel of 9.81 (think m/s^2 - accel due to gravity)
	dq::Quantity<dq::dims::force> F = m * a; // Newton's second law, F should contain ~197.4
	std::cout << m + a << std::endl; // won't compile: m and a have incompatible dimensions for addition
	@endcode

	If you'll be working in SI units (recommended), you might like using
	the typedefs at the bottom, which include Meters, Seconds, Kilograms,
	and so on. Then, you can do the above computation:
	@code
	#include <PhysicalModeling/DimensionedQuantities.h>
	namespace dq = PhysicalModeling::DimensionedQuantities; // Namespace alias, for tidier code
	dq::Kilograms m(20.0);
	dq::MetersPerSecondPerSecond a(9.810);
	dq::Newtons F = m * a;
	@endcode

	@remark The code itself is based on the information included in the Boost MPL
	documentation/tutorial, but extended for physical modeling and for having
	a default precision. If you want to go beyond just using this header as-is,
	you can find information on the basic principles in use at
	http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/tutorial/dimensional-analysis.html

	@{
*/

	/** @def PHYSICALMODELING_DEFAULT_PRECISION
		@brief Optional define to set an alternate default precision

		You may define this to whatever type you wish (float, double, int, etc)
		before including this file to change the default precision of
		quantities.

		See DefaultPrecision for more info.
	*/


	/** @brief Default precision type, for use when no precision is specified
		for a dimensioned quantity.

		If the preprocessor symbol PHYSICALMODELING_DEFAULT_PRECISION is defined,
		it will be used as the default precision, otherwise the built-in
		double type will be used.
	*/
#ifdef PHYSICALMODELING_DEFAULT_PRECISION
	typedef PHYSICALMODELING_DEFAULT_PRECISION DefaultPrecision;
#else
	typedef double DefaultPrecision;
#endif

	// Namespace alias, since DimensionedQuantities strongly relies on boost::mpl
	namespace mpl = boost::mpl;

	/** @brief Dimension types, to use as template parameters for Quantity.
		All dimensions that are not a base, irreducible dimension are
		defined as products of powers of other dimensions.
	*/
	namespace dims {
	/// @name Base dimensions
	/// @{

	// Order of dimension elements: Time, Mass, Length, Angle
	// Value of dimension elements: exponent of that unit type

	/** @brief Dimensionless scalar:

		Available if you have a unit-less, dimension-less coefficient:
		don't use it to avoid declaring the dimensions of values! That would
		defeate the purpose of using this module.
	*/
	typedef mpl::vector_c<int,0,0,0,0,0,0,0,0> dimensionless;

	/// @brief Time (by convention, in seconds @f$ s @f$)
	typedef mpl::vector_c<int,1,0,0,0,0,0,0,0> time;

	/// @brief Mass (by convention, in @f$ kg @f$)
	typedef mpl::vector_c<int,0,1,0,0,0,0,0,0> mass;

	/// @brief Length (by convention, in @f$ m @f$)
	typedef mpl::vector_c<int,0,0,1,0,0,0,0,0> length;

	/// @brief Angle (by convention, in radians @f$ rad @f$)
	typedef mpl::vector_c<int,0,0,0,1,0,0,0,0> angle;
	/// @}

	/// @name Compound dimensions
	/// @{

	/// @brief Area (by convention, in @f$ m^2 @f$)
	typedef mpl::vector_c<int,0,0,2,0,0,0,0,0> area;

	/// @brief Volume (by convention, in @f$ m^3 @f$)
	typedef mpl::vector_c<int,0,0,3,0,0,0,0,0> volume;

	/// @brief Density (by convention, in @f$ \frac{kg}{m^3} @f$)
	typedef mpl::vector_c<int,0,1,-3,0,0,0,0,0> density;

	/// @brief Speed (by convention, in @f$ \frac{m}{s} @f$)
	typedef mpl::vector_c<int,-1,0,1,0,0,0,0,0> speed;

	/// @brief Acceleration (by convention, in @f$ \frac{m}{s^2} @f$)
	typedef mpl::vector_c<int,-2,0,1,0,0,0,0,0> accel;

	/// @brief Angular velocity (by convention, in @f$ \frac{rad}{s} @f$)
	typedef mpl::vector_c<int,-1,0,0,1,0,0,0,0> ang_vel;

	/// @brief Angular acceleration (by convention, in @f$ \frac{rad}{s^2} @f$)
	typedef mpl::vector_c<int,-2,0,0,1,0,0,0,0> ang_accel;

	/// @brief Force (by convention, in Newtons, equivalent to @f$ \frac{kg\cdot m}{s^2} @f$)
	typedef mpl::vector_c<int,-2,1,1,0,0,0,0,0> force;

	/// @brief Linear stiffness (by convention, in @f$ \frac{N}{m} @f$, equivalent to  @f$ \frac{kg}{s^2} @f$)
	typedef mpl::vector_c<int,-2,0,1,0,0,0,0,0> stiffness;

	/// @brief Damping coefficient (viscosity) (by convention, in @f$ \frac{N\cdot s}{m} @f$, equivalent to @f$ \frac{kg}{s} @f$)
	typedef mpl::vector_c<int,-1,0,1,0,0,0,0,0> viscosity;

	/// @brief Torque (by convention, in @f$N m @f$)
	typedef mpl::vector_c<int,-2,1,2,0,0,0,0,0> torque;

	/// @brief Angular stiffness, (by convention, in @f$ \frac{N \cdot m}{rad} @f$, equivalent to @f$ \frac{kg \cdot m^2}{rad \cdot s^2} @f$)
	typedef mpl::vector_c<int,-2,1,2,-1,0,0,0,0> ang_stiffness;

	/// @brief Angular damping coefficient (angular viscosity) (by convention, in @f$ \frac{N\cdot m \cdot s}{rad} @f$)
	typedef mpl::vector_c<int,-1,1,2,-1,0,0,0,0> ang_viscosity;

	/// @}

	} // end of namespace dims


	/** @brief Template class to define a data type with appropriate dimensions.

		This is the most common element to directly use from this file:
		it allows you to declare a variable that has some dimensional meaning
		(mass, length, etc) and optionally some numerical precision (defaults
		to DefaultPrecision.) The documentation for the
		@ref gDimensionedQuantities "dimensioned quantities" module contains
		some examples and details.

		@ingroup gDimensionedQuantities

		@tparam Dimensions One of the dimension typedefs from this file.
		@tparam Precision (Optional) The value type to store, defaults to
		::PhysicalModeling::DimensionedQuantities::DefaultPrecision
	*/
	template <class Dimensions, class Precision = DefaultPrecision>
	struct Quantity
	{
		/// @brief Constructor from value of type Precision
		explicit Quantity(Precision x)
		: m_value(x)
		{}

		/** @brief Conversion constructor, to handle results of multiplication
			and division.

			Compile-time assert included to handle dimensions safely:  See
			http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/tutorial/implementing.html
			for why this conversion and assert is needed.
		*/
		template <class OtherDimensions>
		Quantity(Quantity<OtherDimensions, T> const& rhs)
				: _value(rhs.value()) {
			BOOST_STATIC_ASSERT((
				mpl::equal<Dimensions,OtherDimensions>::type::value
			));
		}

		/// @brief Retrieve the quantity's value without dimensional data.
		Precision value() const { return _value; }
	private:
		Precision _value;
	};

	/// @name Dimensionally-aware operators
	/// @{

	/** @brief Addition operator for quantities with dimensions

		Prevents addition of quantities with incompatible dimensions, and
		allows addition of quantities with equal dimensions.
	*/
	template<class D, class T>
	Quantity<D, T> operator+(const Quantity<D, T> & l, const Quantity<D, T> & r) {
		return Quantity<D,T>(l.value() + r.value());
	}

	/** @brief Subtraction operator for quantities with dimensions

		Prevents subtraction of quantities with incompatible dimensions, and
		allows subtraction of quantities with equal dimensions.
	*/
	template<class D, class T>
	Quantity<D, T> operator-(const Quantity<D, T> & l, const Quantity<D, T> & r) {
		return Quantity<D,T>(l.value() - r.value());
	}

	/** @cond innerworkings
		@{
	*/
	/// @brief Internal workings for multiplication and division dimension operations
	namespace Internal {
		using namespace mpl::placeholders;
		/// @name Metafunction classes
		/// @{

		template <class D1, class D2>
		struct multiply_dimensions
		: mpl::transform<D1,D2,mpl::add<_1,_2> >
		{};

		template <class D1, class D2>
		struct divide_dimensions
		: mpl::transform<D1,D2,mpl::minus<_1,_2> >
		{};
		/// @}
	} // end of Internal namespace

	/**
		@}
		@endcond
	*/

	/** @brief Multiplication operator that produces results with new,
		appropriate dimensions.
	*/
	template <class D1, class D2, class T>
	Quantity<T, typename Internal::multiply_dimensions<D1,D2>::type>
	operator*(Quantity<D1, T> l, Quantity<D2, T> r) {
		return Quantity<typename Internal::multiply_dimensions<D1,D2>::type, T>(
			l.value() * r.value());
	}


	/** @brief Division operator that produces results with new,
		appropriate dimensions.
	*/
	template <class D1, class D2, class T>
	Quantity<T, typename Internal::divide_dimensions<D1,D2>::type>
	operator/(Quantity<D1, T> l, Quantity<D2, T> r) {
		return Quantity<typename Internal::divide_dimensions<D1,D2>::type, T>(
			l.value() / r.value());
	}


	/// @name Complete type names using SI units
	/// These are for convenience only - the standard Quantity template may
	/// always be used interchangeably with these.
	/// @{
	typedef Quantity<mass> Kilograms;
	typedef Quantity<length> Meters;
	typedef Quantity<force> Newtons;
	typedef Quantity<speed> MetersPerSecond;
	typedef Quantity<accel> MetersPerSecondPerSecond;
	typedef Quantity<torque> NewtonMeters;
	typedef Quantity<stiffness> NewtonsPerMeter;
	/// @}

/// @}
// end of doxygen module

} // end of DimensionedQuantities namespace



} // end of PhysicalModeling namespace

#endif // __PHYSICALMODELING_DIMENSIONEDQUANTITIES_H__
