#ifndef MM_MTL_ARRAY_H
#define MM_MTL_ARRAY_H

#include <stddef.h>

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

// mm_lib's array.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_ARRAY_PATH "../../../mcl/mm_lib/source\\mm_mtl/array.h"
#else
#define MM_MTL_ARRAY_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/array.h"
#endif

namespace mm { namespace mtl {

// mm_lib's array of a length fixed when reserve allocates it (1.0.0's Array<T>::reserve(unsigned long): it
// asserts at lines 161 to 167 and constructs every element; fw::ScriptManager's constructor fills the three
// fields). The index operators assert that the elements exist, not the index (gf::GfScriptManager inlines both).
template <typename T>
class Array {
public:
    T& operator[](size_t index) {
#line 90 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element[index];
    }
    const T& operator[](size_t index) const {
#line 102 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element[index];
    }
    size_t size() const { return m_size; }

    T* m_element;
    size_t m_size;
    IAllocator* m_allocator;
};

}}  // namespace mm::mtl

#endif
