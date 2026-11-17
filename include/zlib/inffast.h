// Altered from zlib 1.2.8's inffast.h, Copyright (C) 1995-2003, 2010 Mark Adler.
// For conditions of distribution and use, see third_party/LICENSES/zlib.txt.

#ifndef ZLIB_INFFAST_H
#define ZLIB_INFFAST_H

// zlib's inffast.h (internal to the compression library).
#include "zlib/zutil.h"

#ifdef __cplusplus
extern "C" {
#endif

void ZLIB_INTERNAL inflate_fast(z_streamp strm, unsigned start);

#ifdef __cplusplus
}
#endif

#endif
