#ifndef STDLIB_H
#define STDLIB_H

// The C library's stdlib functions, as the module imports them from NintendoSDK.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* malloc(size_t size);
void free(void* pointer);
void* realloc(void* pointer, size_t size);
void* aligned_alloc(size_t alignment, size_t size);
int atoi(const char* text);
double atof(const char* text);

#ifdef __cplusplus
}
#endif

#endif
