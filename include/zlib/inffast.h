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
