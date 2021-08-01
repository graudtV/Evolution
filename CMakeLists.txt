cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -------------------------------------------
# cmake helper functions
# -------------------------------------------

function(add_catch2_unit_test_target
	TARGET # name that will be available as "make check-TARGET"
	# TEST_NAMES ... 
	)
	list(POP_FRONT ARGV)

	set(SOURCES ${ARGV})
	list(TRANSFORM SOURCES APPEND ".cpp")

	include_directories(${CMAKE_SOURCE_DIR})
	add_executable("${TARGET}" EXCLUDE_FROM_ALL
		"${CMAKE_SOURCE_DIR}/External/Catch2/catch_main.cpp"
		${SOURCES}
	)
	add_custom_target("check-${TARGET}"
		COMMAND ${TARGET}
		DEPENDS ${TARGET}
		VERBATIM
	)
endfunction()

# -------------------------------------------

project(Evolution)

# Evo subprojects
add_subdirectory(Support)
add_subdirectory(Snake)

# Test subtargets
add_custom_target(check DEPENDS
	check-support
)