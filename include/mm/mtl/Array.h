#ifndef MM_MTL_ARRAY_H
#define MM_MTL_ARRAY_H

#include <new>
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
    Array() : m_element(nullptr), m_size(0), m_allocator(nullptr) {}
    // empty, its elements to come from allocator (fw::ScriptManager's constructor)
    explicit Array(IAllocator* allocator) : m_element(nullptr), m_size(0), m_allocator(allocator) {}
    ~Array() { clear(); }
    // destroys the elements and gives them back to the allocator (fw::ScriptManager's destructor calls each
    // element's virtual destructor; the name is not the original's)
    void clear() {
        if (m_element != nullptr) {
            for (size_t i = 0; i < m_size; i++) {
                if (T* element = &m_element[i]) {
                    element->~T();
                }
            }
            m_allocator->deallocate(m_element);
            m_size = 0;
            m_allocator = nullptr;
            m_element = nullptr;
        }
    }
    // the allocator reserve takes the elements from; an array holding another one's elements gives them back
    // first (the name is not the original's)
    void setAllocator(IAllocator* allocator) {
        if (m_allocator != allocator) {
            clear();
            m_allocator = allocator;
        }
    }
    void reserve(size_t size);
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
    // the elements' range (GfObjPropertyCharacter's reset walks it: array.h asserts the elements exist at its lines
    // 43 and 45)
    T* begin() {
#line 43 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element;
    }
    T* end() {
#line 45 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element + m_size;
    }
    // the same of a const array (fw::PointerMap::begin and end; array.h's lines 44 and 46)
    const T* begin() const {
#line 44 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element;
    }
    const T* end() const {
#line 46 MM_MTL_ARRAY_PATH
        MM_ASSERT(m_element);
        return m_element + m_size;
    }

    T* m_element;
    size_t m_size;
    IAllocator* m_allocator;
};

template <typename T>
void Array<T>::reserve(size_t size) {
#line 161 MM_MTL_ARRAY_PATH
    MM_ASSERT(size != 0);
#line 162 MM_MTL_ARRAY_PATH
    MM_ASSERT(m_element == 0);
#line 163 MM_MTL_ARRAY_PATH
    MM_ASSERT(m_allocator != 0);
    m_element = static_cast<T*>(m_allocator->allocate(size * sizeof(T), 8));
#line 167 MM_MTL_ARRAY_PATH
    MM_ASSERT(m_element != 0);
    m_size = size;
    // a trivially constructed element is left as it is (UIShape::setupBuffer sets its vertices itself)
    if (!__has_trivial_constructor(T)) {
        for (size_t i = 0; i < m_size; i++) {
            if (T* element = &m_element[i]) {
                new (element) T();
            }
        }
    }
}

}}  // namespace mm::mtl

#endif
