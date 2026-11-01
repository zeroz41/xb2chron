#ifndef STDIO_H
#define STDIO_H

// The C library's stdio functions, as the module imports them from NintendoSDK.
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int vsnprintf(char* buffer, size_t size, const char* format, va_list arguments);
int snprintf(char* buffer, size_t size, const char* format, ...);

// the stream dlmalloc's malloc_stats prints to
typedef struct _IO_FILE FILE;
extern FILE* const stderr;
int fprintf(FILE* stream, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
