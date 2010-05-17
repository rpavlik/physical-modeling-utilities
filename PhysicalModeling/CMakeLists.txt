# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

set(HEADERS
	DimensionedQuantities.h
	PhysicalModeling.h)

if(NOT PM_IS_SUBPROJECT)
	install(FILES ${HEADERS}
		DESTINATION include/PhysicalModeling)

	include(CppcheckTargets)
	add_cppcheck_sources(physicalmodeling-headers STYLE ${HEADERS})
endif()
