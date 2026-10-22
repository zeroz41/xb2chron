#ifndef ANM_ARRAY_H
#define ANM_ARRAY_H

#include "mm/MMStdBase.h"

// anmlib's anm_array-inl.h, as the including file's include path named it: the game's own files reach it from
// application/BF2, anmlib's own (MM_LIB_FROM_LIBS) from their build folder
#ifdef MM_LIB_FROM_LIBS
#define ANM_ARRAY_PATH "../../src\\anmlib/base/anm_array-inl.h"
#else
#define ANM_ARRAY_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_array-inl.h"
#endif

// anmlib's anm_array.h, the same way: ArrayIterartor's dereference asserts `m_pData` at line 58, its increment at
// line 69 (1.0.0's std::__lower_bound<..., anm::ArrayIterartor<...>> instances and GfExtendPacking::registerSoundTrigger),
// stepping back at 83, forward at 97, and the distance between two asserts both at 123 and 124 (3.0.1's
// std::__upper_bound<..., anm::ArrayIterartor<...>> instances and their callers)
#ifdef MM_LIB_FROM_LIBS
#define ANM_ARRAY_H_PATH "../../src\\anmlib/base/anm_array.h"
#else
#define ANM_ARRAY_H_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_array.h"
#endif

namespace std { inline namespace __1 { struct random_access_iterator_tag; } }

namespace anm {
// an iterator over an Array's elements (the name is the original's, 1.0.0 spells it ArrayIterartor)
template <typename T>
class ArrayIterartor {
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef long difference_type;

    explicit ArrayIterartor(T* pData) : m_pData(pData) {}
    // user-provided (std::__upper_bound's `__first = ++__m` compiles the original's way only so); copies stay trivial
    ArrayIterartor& operator=(const ArrayIterartor& rhs) {
        m_pData = rhs.m_pData;
        return *this;
    }
    T& operator*() const {
#line 58 ANM_ARRAY_H_PATH
        MM_ASSERT(m_pData);
        return *m_pData;
    }
    ArrayIterartor& operator++() {
#line 69 ANM_ARRAY_H_PATH
        MM_ASSERT(m_pData);
        ++m_pData;
        return *this;
    }
    ArrayIterartor operator-(difference_type n) const {
#line 83 ANM_ARRAY_H_PATH
        MM_ASSERT(m_pData);
        return ArrayIterartor(m_pData - n);
    }
    ArrayIterartor& operator+=(difference_type n) {
#line 97 ANM_ARRAY_H_PATH
        MM_ASSERT(m_pData);
        m_pData += n;
        return *this;
    }
    difference_type operator-(const ArrayIterartor& rhs) const {
#line 123 ANM_ARRAY_H_PATH
        MM_ASSERT(m_pData);
#line 124 ANM_ARRAY_H_PATH
        MM_ASSERT(rhs.m_pData);
        return m_pData - rhs.m_pData;
    }
    bool operator==(const ArrayIterartor& other) const { return m_pData == other.m_pData; }
    bool operator!=(const ArrayIterartor& other) const { return m_pData != other.m_pData; }

    T* m_pData;  // anm_array.h asserts `m_pData`
};

// anmlib's view of elements kept elsewhere (a resource's): indexing one asserts `m_pElements` and
// `index < m_size` (anm_array-inl.h lines 231 and 232)
template <typename T>
class Array {
public:
    unsigned int size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    ArrayIterartor<const T> begin() const { return ArrayIterartor<const T>(m_pElements); }
    ArrayIterartor<const T> end() const { return ArrayIterartor<const T>(m_pElements + m_size); }
    const T& operator[](unsigned int index) const {
#line 231 ANM_ARRAY_PATH
        MM_ASSERT(m_pElements);
#line 232 ANM_ARRAY_PATH
        MM_ASSERT(index < m_size);
        return m_pElements[index];
    }

    T* m_pElements;
    unsigned int m_size;
};
}  // namespace anm

#endif
