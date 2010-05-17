# Physical Modeling utilities
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

cmake_minimum_required(VERSION 2.6)

# Set package properties
project(physical-modeling-utilities)

# Locally-developed modules dist'ed with this app
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GetSubprojectStatus)
get_subproject_status(PM_IS_SUBPROJECT)

if(NOT PM_IS_SUBPROJECT)
	set(CPACK_PACKAGE_VENDOR "Iowa State University")
	set(CPACK_PACKAGE_VERSION_MAJOR "0")
	set(CPACK_PACKAGE_VERSION_MINOR "5")
	set(CPACK_PACKAGE_VERSION_PATCH "0")
endif()

###
# Set up options
###

# None for now

###
# Perform build configuration of dependencies
###

find_package(Boost 1.32 REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}" ${Boost_INCLUDE_DIRS})
set(PHYSICALMODELING_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" ${Boost_INCLUDE_DIRS} PARENT_SCOPE)

if(NOT PM_IS_SUBPROJECT)
	include(DoxygenTargets)
	add_doxygen(Doxyfile)
endif()

###
# Build the project
###

add_subdirectory(PhysicalModeling)

if(NOT PM_IS_SUBPROJECT)
	include(CTest)
	include(CreateDashboardScripts)

	add_subdirectory(tests)

	create_dashboard_scripts()
endif()

###
# Set packaging options (for CPack)
###

if(NOT PM_IS_SUBPROJECT)
	set(CPACK_PACKAGE_VERSION
		"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
	set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-binary")
	set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-src")

	# Choose desired package generators
	if(APPLE)
		set(CPACK_GENERATOR DragNDrop)
		set(CPACK_SOURCE_GENERATOR ZIP)
	elseif(WIN32)
		set(CPACK_GENERATOR ZIP)
		set(CPACK_SOURCE_GENERATOR ZIP)
	else()
		set(CPACK_SOURCE_GENERATOR TARGZ)
	endif()

	# Include the packaging system now that we have it all set up
	include(CPack)
endif()
