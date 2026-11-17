// Altered from zlib 1.2.8's zutil.c, Copyright (C) 1995-2005, 2010, 2011, 2012 Jean-loup Gailly,
// and adler32.c, Copyright (C) 1995-2011 Mark Adler.
// For conditions of distribution and use, see third_party/LICENSES/zlib.txt.

// zlib (NintendoSDK's libz 3.5.0) as the split places it: zutil.c's allocator, the SDK's middleware marker and
// adler32.c (zlib 1.2.x, len an uInt: before 1.2.9's adler32_z).
#include <stdlib.h>
#include "nn/util.h"
#include "zlib/zlib.h"

extern "C" {

voidpf zcalloc(voidpf opaque, unsigned items, unsigned size) {
    if (opaque) items += size - size; /* make compiler happy */
    return sizeof(uInt) > 2 ? (voidpf)malloc(items * size) : (voidpf)calloc(items, size);
}

void zcfree(voidpf opaque, voidpf ptr) {
    free(ptr);
    if (opaque) return; /* make compiler happy */
}

void Libz_SigloMiddlewareInfo(void) {
    static const char info[] = "SDK MW+Nintendo+NintendoSDK_libz-3_5_0-Release";
    nn::util::ReferSymbol(info);
}

#define BASE 65521UL /* largest prime smaller than 65536 */
#define NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define DO1(buf, i)  {adler += (buf)[i]; sum2 += adler;}
#define DO2(buf, i)  DO1(buf, i); DO1(buf, i + 1);
#define DO4(buf, i)  DO2(buf, i); DO2(buf, i + 2);
#define DO8(buf, i)  DO4(buf, i); DO4(buf, i + 4);
#define DO16(buf)    DO8(buf, 0); DO8(buf, 8);

#define MOD(a) a %= BASE
#define MOD4(a) a %= BASE

uLong adler32(uLong adler, const Bytef* buf, uInt len) {
    unsigned long sum2;
    unsigned n;

    /* split Adler-32 into component sums */
    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;

    /* in case user likes doing a byte at a time, keep it fast */
    if (len == 1) {
        adler += buf[0];
        if (adler >= BASE)
            adler -= BASE;
        sum2 += adler;
        if (sum2 >= BASE)
            sum2 -= BASE;
        return adler | (sum2 << 16);
    }

    /* initial Adler-32 value (deferred check for len == 1 speed) */
    if (buf == Z_NULL)
        return 1L;

    /* in case short lengths are provided, keep it somewhat fast */
    if (len < 16) {
        while (len--) {
            adler += *buf++;
            sum2 += adler;
        }
        if (adler >= BASE)
            adler -= BASE;
        MOD4(sum2);             /* only added so many BASE's */
        return adler | (sum2 << 16);
    }

    /* do length NMAX blocks -- requires just one modulo operation */
    while (len >= NMAX) {
        len -= NMAX;
        n = NMAX / 16;          /* NMAX is divisible by 16 */
        do {
            DO16(buf);          /* 16 sums unrolled */
            buf += 16;
        } while (--n);
        MOD(adler);
        MOD(sum2);
    }

    /* do remaining bytes (less than NMAX, still just one modulo) */
    if (len) {                  /* avoid modulos if none remaining */
        while (len >= 16) {
            len -= 16;
            DO16(buf);
            buf += 16;
        }
        while (len--) {
            adler += *buf++;
            sum2 += adler;
        }
        MOD(adler);
        MOD(sum2);
    }

    /* return recombined sums */
    return adler | (sum2 << 16);
}

}  // extern "C"
