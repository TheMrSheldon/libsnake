#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __GNUC__
#define UNROLL  __attribute__((optimize("unroll-loops")))
#else
#define UNROLL
#endif