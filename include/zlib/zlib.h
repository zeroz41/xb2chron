#ifndef ZLIB_ZLIB_H
#define ZLIB_ZLIB_H

// zlib (NintendoSDK's libz 3.5.0, zlib 1.2.x), as far as the module links it: C functions (their names are C names).
// The types and names are zlib's own.
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef void* voidpf;

#define Z_NULL 0

uLong adler32(uLong adler, const Bytef* buf, uInt len);

// zutil.c's default allocator (zlib's internal functions)
voidpf zcalloc(voidpf opaque, unsigned items, unsigned size);
void zcfree(voidpf opaque, voidpf ptr);

// NintendoSDK's middleware marker: refers to the library's version string so the linker keeps it
void Libz_SigloMiddlewareInfo(void);

#ifdef __cplusplus
}
#endif

#endif
