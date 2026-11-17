// Altered from zlib 1.2.8's inftrees.h, Copyright (C) 1995-2005, 2010 Mark Adler.
// For conditions of distribution and use, see third_party/LICENSES/zlib.txt.

#ifndef ZLIB_INFTREES_H
#define ZLIB_INFTREES_H

// zlib's inftrees.h (internal to the compression library): code tables for inflate.
#include "zlib/zutil.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Structure for decoding tables.  Each entry provides either the
   information needed to do the operation requested by the code that
   indexed that table entry, or it provides a pointer to another
   table that indexes more bits of the code.  Each entry is four bytes. */
typedef struct {
    unsigned char op;   /* operation, extra bits, table bits */
    unsigned char bits; /* bits in this part of the code */
    unsigned short val; /* offset in table or code value */
} code;

/* Maximum size of the dynamic table: 852 for literal/length codes and 592 for distance codes. */
#define ENOUGH_LENS 852
#define ENOUGH_DISTS 592
#define ENOUGH (ENOUGH_LENS + ENOUGH_DISTS)

/* Type of code to build for inflate_table() */
typedef enum { CODES, LENS, DISTS } codetype;

int ZLIB_INTERNAL inflate_table(codetype type, unsigned short* lens, unsigned codes, code** table, unsigned* bits,
                                unsigned short* work);

#ifdef __cplusplus
}
#endif

#endif
