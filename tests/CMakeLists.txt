# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

include(BoostTestTargets)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../PhysicalModeling")
include_directories("${SRC}/..")

add_boost_test(DimensionedQuantities
	SOURCES
	test_DimensionedQuantities.cpp
	"${SRC}/DimensionedQuantities.h")


# Right now - just testing to see that it compiles.
add_boost_test(PhysicalModeling
	SOURCES
	test_PhysicalModeling.cpp
	"${SRC}/PhysicalModeling.h")
