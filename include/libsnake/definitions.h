#pragma once

#ifdef _WIN32
#ifdef BUILD_SHARED
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif

#ifdef __GNUC__
#define UNROLL __attribute__((optimize("unroll-loops")))
#else
#define UNROLL
#endif

#include <string>
DLLEXPORT void __assert_fail(const char* assertion, const char* file, unsigned line, const char* function, const std::string message);
#ifdef NDEBUG
#define ASSERT(EXP, MSG)
#else
#define ASSERT(EXP, MSG) (static_cast<bool>(EXP)? void(0) : __assert_fail(#EXP, __FILE__, __LINE__, __func__, MSG))
#endif