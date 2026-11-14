#ifndef MM_MTL_OBJECTALLOCATOR_H
#define MM_MTL_OBJECTALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/ReservedBitflag.h"

// mm_lib's mm_mtl/internal/object_allocator.h, as the including file's include path named it (see mm/mtl/FixStr.h);
// only the application's citation is known so far
#define MM_MTL_OBJECT_ALLOCATOR_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/internal/object_allocator.h"

namespace mm { namespace mtl {

// up to a reserved number of T in one allocation, a flag per slot in use (1.0.0's ObjectAllocator<T>::reserve,
// allocate and destroy; its assertions name m_capacity, m_allocated, m_element and valid_pointer(p)). The slots are
// an Array of words (reserve asserts array.h's lines 161 to 167, destroy reads a slot through its operator[]); the
// member names other than m_capacity and m_allocated are not the original's.
template <typename T>
class ObjectAllocator {
public:
    ObjectAllocator() : m_allocated(0), m_capacity(0) {}
    ~ObjectAllocator() { destroy(); }

    void reserve(IAllocator* allocator, unsigned int size);
    T* allocate();
    // destroys every object in use and gives the slots back
    void destroy();
    // destroys an object in place, nothing for none (destroy keeps the test of the slot's address, which a test
    // written on the operator[] result folds away; the name is not the original's)
    static void destruct(T* object) {
        if (object != nullptr) {
            object->~T();
        }
    }

    // whether p lies in the slots (array.h's const begin and end: lines 44 and 46)
    bool valid_pointer(const T* p) const {
        const unsigned long* word = reinterpret_cast<const unsigned long*>(p);
        return m_buffer.begin() <= word && word <= m_buffer.end();
    }
    // the slot of an object (the name is not the original's)
    unsigned int index_of(const T* p) const {
#line 81 MM_MTL_OBJECT_ALLOCATOR_PATH
        MM_ASSERT(valid_pointer(p));
        return static_cast<unsigned int>(reinterpret_cast<const char*>(p) -
                                         reinterpret_cast<const char*>(&m_buffer[0])) /
               static_cast<unsigned int>(sizeof(T));
    }
    // destroys one object and gives its slot back (fw::SoundSsdDriver::releaseHandle inlines it; the name is not the
    // original's)
    void free(T* p) {
#line 238 MM_MTL_OBJECT_ALLOCATOR_PATH
        MM_ASSERT(m_allocated > 0);
        unsigned int index = index_of(p);
        p->~T();
        m_used.clrLocal(index);
        --m_allocated;
    }

    Array<unsigned long> m_buffer;  // 0x00: the slots, in words
    ReservedBitflag m_used;  // 0x18: a flag per slot in use
    unsigned int m_allocated;  // 0x30: the slots in use
    unsigned int m_capacity;  // 0x34: the slots reserved
};

// a new T in the first free slot, null when every slot is in use
template <typename T>
T* ObjectAllocator<T>::allocate() {
#line 132 MM_MTL_OBJECT_ALLOCATOR_PATH
    MM_ASSERT(m_allocated <= m_capacity);
    if (m_allocated != m_capacity) {
        for (unsigned int word = 0; word < m_used.m_elementNum; word++) {
            if (m_used.m_element[word] == 0xFFFFFFFF) {
                continue;
            }
            unsigned int last = word * 32 + 32 > m_capacity ? m_capacity : word * 32 + 32;
            for (unsigned int i = word * 32; i < last; i++) {
                if (!m_used.getLocal(i)) {
                    // the slot's address through an inline the original's null test survives (a test on the
                    // operator[] reference itself folds away)
                    T* p = [&](unsigned int index) -> T* {
                        return reinterpret_cast<T*>(&m_buffer[index * static_cast<unsigned int>(sizeof(T)) / sizeof(unsigned long)]);
                    }(i);
                    if (p != nullptr) {
                        T* object = new (p) T();
                        m_used.setLocal(i, true);
                        ++m_allocated;
#line 220 MM_MTL_OBJECT_ALLOCATOR_PATH
                        MM_ASSERT(m_allocated <= m_capacity);
                        return object;
                    }
                }
            }
        }
    }
    return nullptr;
}

template <typename T>
void ObjectAllocator<T>::destroy() {
    for (unsigned int i = 0; i < m_capacity; i++) {
        if (m_used.getLocal(i)) {
            destruct(reinterpret_cast<T*>(&m_buffer[i * static_cast<unsigned int>(sizeof(T)) / sizeof(unsigned long)]));
            m_used.clrLocal(i);
        }
    }
    m_allocated = 0;
    m_buffer.clear();
    m_used.destroy();
    m_capacity = 0;
}

}}  // namespace mm::mtl

#endif
