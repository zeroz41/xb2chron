#ifndef MM_MTL_ALGORITHM_H
#define MM_MTL_ALGORITHM_H

#include <new>
#include <stddef.h>
#include <string.h>

#include "mm/MMStdBase.h"

// mm_lib's algorithm.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_ALGORITHM_PATH "../../../mcl/mm_lib/source\\mm_mtl/algorithm.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's (mtl::DlAllocator::allocate's fill cites it so)
#define MM_MTL_ALGORITHM_PATH "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/algorithm.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (ml::DrEnvironmentAnim's unit carries it)
#define MM_MTL_ALGORITHM_PATH "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/algorithm.h"
#else
#define MM_MTL_ALGORITHM_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/algorithm.h"
#endif

namespace mm { namespace mtl {

// a type for each value of N, to pick an overload by a compile-time value (mtl_detail::copy_construct_n's last
// parameter)
template <int N>
struct int_to_type {
    enum { value = N };
};

namespace mtl_detail {
// constructs n copies of first's elements at result, one by one (int_to_type<0>: a type not copied bit for bit).
// Out of line where the copies are long: Vector<skd::Node>::extend calls 3.0.1's copy. Declared inline (threshold
// 325): copy_construct_n<anm::Util::PairName> then inlines it with PairName's copy (no inline deferral) and stays out of
// line in Vector<PairName>::expand, as in fw::AnimResAsmResolver's unit.
template <typename T>
inline void copy_construct_n(const T* first, size_t n, T* result, int_to_type<0>) {
    for (size_t i = 0; i < n; ++i) {
        new (&result[i]) T(first[i]);
    }
}
// the block copy (int_to_type<1>: a type copied bit for bit), which must not overlap the source ahead of it
template <typename T>
inline void copy_construct_n(const T* first, size_t n, T* result, int_to_type<1>) {
#line 224 MM_MTL_ALGORITHM_PATH
    MM_ASSERT((first + n <= result) || result < first);
    memcpy(result, first, n * sizeof(T));
}
}  // namespace mtl_detail

// constructs n copies of first's elements at result, as the type copies. Not declared inline: 3.0.1 keeps it out of
// line where the element's copy is long (copy_construct_n<gmk::GmkTrigger>, <gmk::GmkLandmark>,
// <anm::Util::PairName>, called by Vector's expand and extend)
template <typename T>
void copy_construct_n(const T* first, size_t n, T* result) {
    mtl_detail::copy_construct_n(first, n, result, int_to_type<__has_trivial_copy(T)>());
}

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
// the pointer-walking form gave a runtime-unrolled loop with the remainder first. The name is the original's: its
// out-of-line copies are mm::mtl::destruct_n<T>(T*, unsigned long) (0x710062DE68, 0x710026BB70), called from Vector's clear.
// Not declared inline: destruct_n<std::pair<GF_OBJ_HANDLE*, gmk::GmkRouteNavi>> (inline cost 280) stays out of line
// in Vector::destroy as the original's does, which the inline-hint threshold (325) would inline
template <typename T>
void destruct_n(T* first, size_t n) {
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

// fills size bytes from top with value, 4 bytes at a time, unrolled by 8 (DlAllocator::allocate inlines it to mark
// new memory; algorithm.h asserts top's alignment at line 465; the name is not the original's)
inline void fill_4byte(void* top, unsigned int value, size_t size) {
#line 465 MM_MTL_ALGORITHM_PATH
    MM_ASSERT((reinterpret_cast<size_t>(top) & 0x03) == 0);
    unsigned int* p = static_cast<unsigned int*>(top);
    unsigned int* end = p + size / 4;
    switch ((size / 4) & 7) {
        case 0:
            while (p != end) {
                *p++ = value;
                case 7:
                    *p++ = value;
                case 6:
                    *p++ = value;
                case 5:
                    *p++ = value;
                case 4:
                    *p++ = value;
                case 3:
                    *p++ = value;
                case 2:
                    *p++ = value;
                case 1:
                    *p++ = value;
            }
    }
}

// assigns value to the n elements from first on, unrolled by 8 with the remainder first (FixStr<256>::insert(int,
// int, char) inlines it: its jump table on n & 7; the name is not the original's)
template <typename T>
inline void fill_n(T* first, int n, const T& value) {
    T* last = first + n;
    switch (n & 7) {
        case 0:
            while (first != last) {
                *first++ = value;
                case 7:
                    *first++ = value;
                case 6:
                    *first++ = value;
                case 5:
                    *first++ = value;
                case 4:
                    *first++ = value;
                case 3:
                    *first++ = value;
                case 2:
                    *first++ = value;
                case 1:
                    *first++ = value;
            }
    }
}

// assigns [first, last) to result on, front to back, as std::copy does (Vector's and FixedVector's erase
// shift: the original keeps the source and destination pointers apart, Vector<IntrusivePtr<fw::ReferenceFrame>>::erase
// and GfMenuSequence<GfMenuObjQuestLog, 8>::wait_anim)
template <typename T>
inline T* copy_forward(T* first, T* last, T* result) {
    while (first != last) {
        *result++ = *first++;
    }
    return result;
}

}}  // namespace mm::mtl

#endif
