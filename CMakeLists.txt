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

add_library(libsnake SHARED src/state.cpp src/winner.cpp src/definitions.cpp src/gamemodes/arena.cpp)
target_compile_features(libsnake PRIVATE cxx_std_20)
target_compile_definitions(libsnake PRIVATE BUILD_SHARED)

include_directories(PUBLIC include)

##########################################################################################
# Testing
##########################################################################################
# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
	add_subdirectory(tests)
endif()
