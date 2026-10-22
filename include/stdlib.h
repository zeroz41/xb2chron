#ifndef STDLIB_H
#define STDLIB_H

// The C library's stdlib functions, as the module imports them from NintendoSDK.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void free(void* pointer);

#ifdef __cplusplus
}
#endif

#endif
