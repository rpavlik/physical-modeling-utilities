/** @file	PhysicalModeling.h
	@brief	header to include all headers in the page

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
#ifndef _PHYSICALMODELING_PHYSICALMODELING_H_
#define _PHYSICALMODELING_PHYSICALMODELING_H_

// Internal Includes
#include <PhysicalModeling/DimensionedQuantities.h>

// Library/third-party includes
// - none

// Standard includes
// - none

/** @brief Namespace for all Physical Modeling utilities.
*/
namespace PhysicalModeling {}

/**	@mainpage Physical Modeling Utilities for C++

@section intro_sec Introduction

This package will contain a number of utilities (mostly headers) to support
the development of applications that perform physical modeling tasks. Currently,
only the @ref gDimensionedQuantities "Dimensioned Quantities" module exists,
but as modular functionality is developed, it will be included.

The goal is to use modern C++ design and practices to facilitate simpler
implementation of physical modeling tasks. Templates will be used extensively.
Advanced metaprogramming may be used internally, but when possible it will
not be exposed to the developer-user.

@section module_sec Modules of Functionality
 - @ref gDimensionedQuantities "Dimensioned Quantities": Assign dimensions
 	(mass, length, speed) to your variables, and let the compiler support and
 	enforce dimensional compatibility.

*/

#endif // _PHYSICALMODELING_PHYSICALMODELING_H_
