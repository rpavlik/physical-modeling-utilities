/** @file	test_PhysicalModeling.cpp
	@brief	PhysicalModeling test driver

	@date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE PhysicalModeling basic tests

// Module to test
#include <PhysicalModeling/PhysicalModeling.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

using namespace boost::unit_test;

// System includes
// - none

BOOST_AUTO_TEST_CASE(NullTest) {
	using namespace PhysicalModeling;
}
