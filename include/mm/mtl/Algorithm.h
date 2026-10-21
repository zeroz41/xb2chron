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
        for (; n != 0; --n, ++first, ++result) {
            new (result) T(*first);
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

// destroys the n objects from first on
template <typename T>
inline void destroy_n(T* first, size_t n) {
    for (; n != 0; --n, ++first) {
        first->~T();
    }
}

}}  // namespace mm::mtl

#endif
