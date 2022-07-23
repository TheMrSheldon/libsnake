cmake_minimum_required(VERSION 3.14)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_COMPILE_FEATURES OFF)
#set(CMAKE_CXX_COMPILER "g++-10")
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fno-implicit-templates")


project(libsnake VERSION 0.1.0)

include(FetchContent)
include(CTest)
enable_testing()

add_library(libsnake SHARED src/state.cpp src/snake_flags.cpp src/definitions.cpp src/gamemodes/standard.cpp src/gamemodes/challenge.cpp src/gamemodes/squad.cpp)
target_compile_features(libsnake PRIVATE cxx_std_20)
target_compile_definitions(libsnake PRIVATE BUILD_SHARED)

include_directories(PUBLIC include)

##########################################################################################
# DOXYGEN
##########################################################################################
option(BUILD_DOC "Build documentation" ON)

if (BUILD_DOC)
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		set(DOXYGEN_OUTPUT_DIRECTORY doc)
		set(DOXYGEN_QUIET YES)
		#set(DOXYGEN_EXTRACT_PRIVATE YES)
		set(DOXYGEN_STRIP_FROM_PATH ./include/libsnake)
		set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
		set(DOXYGEN_GENERATE_TREEVIEW YES)
		
		doxygen_add_docs(doxygen
			README.md
			${PROJECT_SOURCE_DIR}/include/libsnake/
			docs/
			ALL
			COMMENT "Generate documentation")
	else()
		message("No doxygen installation was found")
	endif()
endif()
unset(BUILD_DOC CACHE)

##########################################################################################
# Testing
##########################################################################################
# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
	add_subdirectory(tests)
endif()

##########################################################################################
# Benchmarking
##########################################################################################
# Benchmarking only available if this is the main app
option(BENCHMARKS "Build benchmarks" ON)
if(BENCHMARKS)
	add_subdirectory(benchmarks)
endif()
