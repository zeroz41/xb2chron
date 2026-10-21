#ifndef MM_MATH_H
#define MM_MATH_H

#include "math.h"
#include "mm/MMStdBase.h"

// mm_lib's mm_math/mm_math.h: inline, so known only by what callers inline and the assertions they cite
namespace mm {

inline float fabs(float x) {
    return ::fabsf(x);
}

// the arc cosine of a cosine within [-1, 1], up to rounding (one past 1.001 asserts)
inline float acos(float r) {
    // the original's mm_math/mm_math.h, as its include path named it
#line 546 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_math/mm_math.h"
    MM_ASSERT(mm::fabs(r) < 1.001f);
    if (mm::fabs(r) >= 1.0f) {
        return r > 0.0f ? 0.0f : 3.14159265f;
    }
    return ::acosf(r);
}

// by reference: a bound read from memory is read again after the assertion's call
template <typename T>
inline T clamp(const T& x, const T& mi, const T& ma) {
#line 819
    MM_ASSERT(mi<=ma);
    return x < mi ? mi : (x > ma ? ma : x);
}

}  // namespace mm

#endif
