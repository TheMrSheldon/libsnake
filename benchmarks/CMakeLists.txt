FetchContent_Declare(
	catch
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.4
)
FetchContent_MakeAvailable(catch)

add_executable(benchmarks
	main.cpp
	game_simulation.cpp
)

target_link_libraries(benchmarks PRIVATE libsnake Catch2::Catch2)
target_compile_features(benchmarks PRIVATE cxx_std_20)

add_test(NAME libsnakebenchmarks COMMAND benchmarks)


if (WIN32)
	add_custom_command(TARGET benchmarks POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:benchmarks> $<TARGET_FILE_DIR:benchmarks>
		COMMAND_EXPAND_LISTS
	)
endif()