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