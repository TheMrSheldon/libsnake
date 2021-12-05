FetchContent_Declare(
	catch
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.4
)
FetchContent_MakeAvailable(catch)

add_executable(tests main.cpp state.cpp move.cpp eval.cpp)
#target_compile_features(tests PRIVATE cxx_std_20)

target_link_libraries(tests PRIVATE libsnake Catch2::Catch2)

add_test(NAME libsnaketests COMMAND tests)