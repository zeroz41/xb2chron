#ifndef MM_MTL_ALGORITHM_H
#define MM_MTL_ALGORITHM_H

#include <new>
#include <stddef.h>
#include <string.h>

#include "mm/MMStdBase.h"

// mm_lib's algorithm.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_ALGORITHM_PATH "../../../mcl/mm_lib/source\\mm_mtl/algorithm.h"
#else
#define MM_MTL_ALGORITHM_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/algorithm.h"
#endif

namespace mm { namespace mtl {

// constructs n copies of first's elements at result: a block copy for types copied bit for bit, which must not
// overlap the source ahead of it
template <typename T>
inline void uninitialized_copy_n(const T* first, size_t n, T* result) {
    if (__has_trivial_copy(T)) {
#line 224 MM_MTL_ALGORITHM_PATH
        MM_ASSERT((first + n <= result) || result < first);
        memcpy(result, first, n * sizeof(T));
    } else {
        for (size_t i = 0; i < n; ++i) {
            new (&result[i]) T(first[i]);
        }
    }
}

// constructs n copies of value from first on
template <typename T>
inline void uninitialized_fill_n(T* first, size_t n, const T& value) {
    for (size_t i = 0; i < n; ++i, ++first) {
        if (first != nullptr) {
            new (first) T(value);
        }
    }
}

// destroys the n objects from first on. Indexed: a destructor that only stores (gf::GfFieldLod::BdatInfo's, in
// GfFieldLod's destructor and destroy) comes out interleaved by 4 with the remainder after, as the original's does;
// the pointer-walking form gave a runtime-unrolled loop with the remainder first
template <typename T>
inline void destroy_n(T* first, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        first[i].~T();
    }
}

// copies n elements from first to result, which must not overlap the source ahead of it (FixStr<128>::insert
// inlines it; algorithm.h asserts the overlap at line 264; the name is not the original's)
template <typename T>
inline T* copy_n(const T* first, size_t n, T* result) {
#line 264 MM_MTL_ALGORITHM_PATH
    MM_ASSERT(result >= first + n || result < first);
    memcpy(result, first, n * sizeof(T));
    return result + n;
}

// moves n elements from from to result, overlapping or not (FixStr<128>::insert inlines it; algorithm.h asserts
// `from != result || n == 0` at line 393; the name is not the original's)
template <typename T>
inline void move_n(const T* from, size_t n, T* result) {
#line 393 MM_MTL_ALGORITHM_PATH
    MM_ASSERT(from != result || n == 0);
    if (result > from && result < from + n) {
        memmove(result, from, n * sizeof(T));
    } else {
        copy_n(from, n, result);
    }
}

}}  // namespace mm::mtl

#endif
