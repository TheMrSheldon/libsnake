FetchContent_Declare(
	catch
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.4
)
FetchContent_MakeAvailable(catch)

add_executable(tests main.cpp move.cpp position.cpp snake_flags.cpp gamemodes/standard.cpp gamemodes/squad.cpp gamemodes/wrapped.cpp)
#target_compile_features(tests PRIVATE cxx_std_20)

target_link_libraries(tests PRIVATE libsnake Catch2::Catch2)
target_compile_features(tests PRIVATE cxx_std_20)

add_test(NAME libsnaketests COMMAND tests)


if (WIN32)
	add_custom_command(TARGET tests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
		COMMAND_EXPAND_LISTS
	)
endif()