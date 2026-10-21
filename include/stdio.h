#ifndef STDIO_H
#define STDIO_H

// The C library's stdio functions, as the module imports them from NintendoSDK.
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int vsnprintf(char* buffer, size_t size, const char* format, va_list arguments);

#ifdef __cplusplus
}
#endif

#endif
