#ifndef ZLIB_ZUTIL_H
#define ZLIB_ZUTIL_H

// zlib's zutil.h (internal to the compression library), as far as the inflate and crc32 code uses it.
#include <stdlib.h>
#include <string.h>
#include "zlib/zlib.h"

#define ZLIB_INTERNAL

typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;

#define DEF_WBITS MAX_WBITS /* default windowBits for decompression */

#define zmemcpy memcpy

/* Diagnostic functions (DEBUG off) */
#define Assert(cond, msg)
#define Trace(x)
#define Tracev(x)
#define Tracevv(x)
#define Tracec(c, x)
#define Tracecv(c, x)

#define ZALLOC(strm, items, size) (*((strm)->zalloc))((strm)->opaque, (items), (size))
#define ZFREE(strm, addr) (*((strm)->zfree))((strm)->opaque, (voidpf)(addr))
#define TRY_FREE(s, p) \
    { \
        if (p) ZFREE(s, p); \
    }

/* Reverse the bytes in a 32-bit value */
#define ZSWAP32(q) ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + (((q)&0xff00) << 8) + (((q)&0xff) << 24))

#endif
