#include <libsnake/definitions.h>
#include <iostream>

void __assert_fail(const char* assertion, const char* file, unsigned line, const char* function, const std::string message) {
    (void) function;
    std::cerr << "Assertion " << assertion << " failed\n";
    std::cerr << "\tfile: " << file << '(' << line << ")\n";
    std::cerr << "\twith message: " << message;
    abort();
}