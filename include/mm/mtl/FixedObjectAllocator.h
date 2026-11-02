#ifndef MM_MTL_FIXEDOBJECTALLOCATOR_H
#define MM_MTL_FIXEDOBJECTALLOCATOR_H

#include "mm/MMStdBase.h"
#include "mm/mtl/Bitflag.h"

// mm_lib's mm_mtl/internal/fixed_object_allocator.h, as the including file's include path named it (see
// mm/mtl/FixStr.h); only monolib_mm's citation is known so far
#define MM_MTL_FIXED_OBJECT_ALLOCATOR_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/internal/fixed_object_allocator.h"

namespace mm { namespace mtl {

// N objects of T in place, a flag per slot (mm_mtl/internal/fixed_object_allocator.h; its assertions name the count
// `m_allocated` and test `valid_pointer(p)`). The class's name follows the file's; it and the other members' names
// are not the original's. Layout per ml::DevFileArchiveNx::Param (T of 0x118 bytes, N 16).
template <typename T, unsigned long N>
class FixedObjectAllocator {
public:
    FixedObjectAllocator() : m_allocated(0), m_capacity(N) { m_used.reset(); }
    ~FixedObjectAllocator() {
        for (unsigned int i = 0; i < m_capacity; i++) {
            if (m_used.test(i)) {
                m_used.reset(i);
            }
        }
        m_allocated = 0;
    }

    // a free slot's object, constructed (mtl::MemManager::Region's copy 0x71006E8910); not written yet
    T* allocate();
    // gives p's slot back: its object destroyed and its flag cleared (Region's copy 0x71006E8600)
    void deallocate(T* p) {
        if (p == nullptr) {
            return;
        }
#line 240 MM_MTL_FIXED_OBJECT_ALLOCATOR_PATH
        MM_ASSERT(m_allocated > 0);
        unsigned int index = index_of(p);
        p->~T();
        m_used.resetAt(index);
        --m_allocated;
    }
    // every slot given back (Region's copy 0x71006EB948); not written yet
    void clear();
    // p's slot (deallocate's; the name is not the original's)
    unsigned int index_of(const T* p) const {
#line 86 MM_MTL_FIXED_OBJECT_ALLOCATOR_PATH
        MM_ASSERT(valid_pointer(p));
        return static_cast<unsigned int>(reinterpret_cast<const unsigned char*>(p) - m_buffer) /
               static_cast<unsigned int>(sizeof(T));
    }
    // whether p is inside the slots (index_of's assertion; the name is the assertion's)
    bool valid_pointer(const T* p) const {
        return reinterpret_cast<const unsigned char*>(p) <= &m_buffer[N * sizeof(T)] &&
               &m_buffer[0] <= reinterpret_cast<const unsigned char*>(p);
    }

    unsigned char m_buffer[sizeof(T) * N];  // the slots
    Bitflag<N> m_used;  // a flag per slot in use
    unsigned int m_allocated;  // the slots in use
    unsigned int m_capacity;  // N
};

}}  // namespace mm::mtl

#endif
