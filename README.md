# What is libsnake?
[TODO: Insert text here]

# Using libsnake within another CMake project
Adding libsnake to your CMake project is easy. Simply add the following lines to your CMake project where `target` is the target you would like to link libsnake to.
```cmake
FetchContent_Declare(
	libsnake_lib
	GIT_REPOSITORY https://github.com/TheMrSheldon/libsnake.git
	GIT_TAG gamemodes
)
FetchContent_MakeAvailable(libsnake_lib)
FetchContent_GetProperties(libsnake_lib)
target_include_directories(mytarget PRIVATE ${libsnake_SOURCE_DIR}/include/)
target_link_libraries(mytarget PRIVATE libsnake)
```

# Building libsnake with VSCode (we highly recommend VSCode)
## Prerequisite
 * CMake
 * VSCode
 * CMake Extension for VSCode
 * Working C++ compiler

## Build process:
 1. Clone this repository
 1. Open the cloned repository in VSCode
 1. Strg+Shift+P and enter "CMake: Configure"
 1. You may get asked to select a Kit: select your prefered compiler
 1. Strg+Shift+P and enter "CMake: Build"