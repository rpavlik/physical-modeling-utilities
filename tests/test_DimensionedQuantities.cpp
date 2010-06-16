/** @file	test_HeadCollection.cpp
	@brief	HeadCollection test driver

	@date	2010

	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE HeadCollection basic tests

// Module to test
#include <PhysicalModeling/DimensionedQuantities.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>


using namespace boost::unit_test;

using PhysicalModeling::DimensionedQuantities::Quantity;
namespace dims = PhysicalModeling::DimensionedQuantities::dims;
using namespace PhysicalModeling::DimensionedQuantities::SI;

// System includes
// - none

typedef boost::mpl::list<
	Kilograms,
	Meters,
	Newtons,
	Radians,
	Seconds,
	MetersPerSecond,
	MetersPerSecondSquared,
	NewtonMeters,
	NewtonsPerMeter,
	NewtonMetersPerRadian,
	NewtonSecondsPerMeter,
	KilogramsPerSecond,
	NewtonMeterSecondsPerRadian,
	KilogramMetersSquared
	> shortcut_SI_types;

typedef boost::mpl::list<
	dims::dimensionless,
	dims::time,
	dims::mass,
	dims::length,
	dims::angle,
	dims::area,
	dims::volume,
	dims::density,
	dims::speed,
	dims::accel,
	dims::ang_speed,
	dims::ang_accel,
	dims::force,
	dims::stiffness,
	dims::viscosity,
	dims::torque,
	dims::ang_stiffness,
	dims::ang_viscosity
	> all_dimensions;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstructShortcutTypes, T, shortcut_SI_types) {
	T x(0.0);
	T x2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddShortcutTypes, T, shortcut_SI_types) {
	T x1(0.5), x2(0.5);
	T result = x1 + x2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SubtractShortcutTypes, T, shortcut_SI_types) {
	T x1(0.5), x2(0.5);
	T result = x1 - x2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstructTemplatedTypes, T, all_dimensions) {
	Quantity<T> x(0.0);
	Quantity<T> x2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddTemplatedTypes, T, all_dimensions) {
	Quantity<T> x1(0.5), x2(0.5);
	Quantity<T> result = x1 + x2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SubtractTemplatedTypes, T, all_dimensions) {
	Quantity<T> x1(0.5), x2(0.5);
	Quantity<T> result = x1 - x2;
}

/*
BOOST_AUTO_TEST_CASE(SimpleSqrtSanityChecks) {
	Quantity<dims::area> area(25.0);
	Quantity<dims::length> length = PhysicalModeling::DimensionedQuantities::sqrt(area);
}
*/

BOOST_AUTO_TEST_CASE(SimpleConversionSanityChecks) {
	Kilograms m(20);
	MetersPerSecondSquared a(9.8);
	Newtons F = m * a;
}
