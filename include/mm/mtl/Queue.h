#ifndef MM_MTL_QUEUE_H
#define MM_MTL_QUEUE_H

#include <stddef.h>

#include "mm/MMStdBase.h"

// mm_lib's queue.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_QUEUE_PATH "../../../mcl/mm_lib/source\\mm_mtl/queue.h"
#else
#define MM_MTL_QUEUE_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/queue.h"
#endif

namespace mm { namespace mtl {

// a first-in first-out ring of elements in memory from an allocator: m_size of them from m_head on. Only what
// anm::ThreadPool inlines is here, and the names are not the original's.
template <typename T>
class Queue {
public:
    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    T& at(size_t index) {
#line 65 MM_MTL_QUEUE_PATH
        MM_ASSERT(m_buffer != 0);
        return m_buffer[index];
    }
    T& front() { return at(m_head); }
    void pop() {
#line 781 MM_MTL_QUEUE_PATH
        MM_ASSERT(!empty());
        size_t head = m_head;
        m_head = (m_head + 1) % m_capacity;
        --m_size;
        at(head).~T();
    }

private:
    T* m_buffer;
    size_t m_size;
    size_t m_head;
    size_t m_capacity;
    unsigned char pad_20[0x10];
};

}}  // namespace mm::mtl

#endif
