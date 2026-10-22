#ifndef CXXABI_H
#define CXXABI_H

// The C++ runtime's ABI functions, as the module imports them (libc++abi).
#include <stddef.h>

namespace abi {
extern "C" {
// `mangledName` demangled into a buffer of malloc's (or `outputBuffer`, grown); null when it is not a mangled name
char* __cxa_demangle(const char* mangledName, char* outputBuffer, size_t* length, int* status);
}
}  // namespace abi

#endif
