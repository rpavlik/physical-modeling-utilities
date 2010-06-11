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
if(PM_IS_SUBPROJECT)
	set(PHYSICALMODELING_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" ${Boost_INCLUDE_DIRS} PARENT_SCOPE)
else()
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

if(NOT PM_IS_SUBPROJECT)

	###
	# Create config files to allow easy use of this library
	###

	# Set up use from build tree
	#set(BUILD_TREE_TARGETS VPSTools osgVPS)

	configure_file(physicalmodelingutils-config-build-tree.cmake.in PhysicalModelingUtilsConfig.cmake @ONLY)
	#export(TARGETS ${BUILD_TREE_TARGETS}
	#	NAMESPACE pmutils_buildtree_
	#	FILE physicalmodelingutils-targets.cmake)
	export(PACKAGE PhysicalModelingUtils)

	# Set up use from install tree
	if(WIN32)
		set(EXPORT_DIR cmake)
	else()
		set(EXPORT_DIR ${LIB_DIR}/PhysicalModelingUtils)
	endif()
	#install(EXPORT vpstools-sdk
	#	DESTINATION ${EXPORT_DIR}
	#	NAMESPACE pmutils_exported_
	#	FILE physicalmodelingutils-targets.cmake)
	configure_file(physicalmodelingutils-config.cmake.in physicalmodelingutils-config-for-install.cmake @ONLY)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/physicalmodelingutils-config-for-install.cmake
		RENAME physicalmodelingutils-config.cmake
		DESTINATION ${EXPORT_DIR})


	###
	# Set packaging options (for CPack)
	###


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
