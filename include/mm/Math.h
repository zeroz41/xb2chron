#ifndef MM_MATH_H
#define MM_MATH_H

#include "math.h"
#include "mm/MMStdBase.h"

// mm_lib's mm_math/mm_math.h: inline, so known only by what callers inline and the assertions they cite.
// Its citations name it as the including file's include path did: the game's own files reach it from
// application/BF2, the libraries under libs/ (MM_LIB_FROM_LIBS) from their own build folder
#ifdef MM_LIB_FROM_LIBS
#define MM_MATH_PATH "../../../mcl/mm_lib/source\\mm_math/mm_math.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (DrShdLgtClustered::planeVsCone's acos cites it so)
#define MM_MATH_PATH "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_math/mm_math.h"
#else
#define MM_MATH_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_math/mm_math.h"
#endif

namespace mm {

inline float fabs(float x) {
    return ::fabsf(x);
}

// the arc cosine of a cosine within [-1, 1], up to rounding (one past 1.001 asserts)
inline float acos(float r) {
#line 546 MM_MATH_PATH
    MM_ASSERT(mm::fabs(r) < 1.001f);
    if (mm::fabs(r) >= 1.0f) {
        return r > 0.0f ? 0.0f : 3.14159265f;
    }
    return ::acosf(r);
}

// the arc sine of a sine within [-1, 1], up to rounding (one past 1.001 asserts)
inline float asin(float r) {
#line 581 MM_MATH_PATH
    MM_ASSERT(mm::fabs(r) < 1.001f);
    if (mm::fabs(r) >= 1.0f) {
        return r > 0.0f ? 1.57079637f : -1.57079637f;
    }
    return ::asinf(r);
}

// a value's magnitude in its own type: a short's comes back as a short (UIObjectOffsetPlugin::execute)
template <typename T>
inline T abs(T x) {
    return x < 0 ? -x : x;
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
