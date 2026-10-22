#ifndef MM_MTL_QUEUE_H
#define MM_MTL_QUEUE_H

#include <stddef.h>

#include "mm/MMStdBase.h"
#include "classes/mm/mtl/IAllocator.h"

// mm_lib's queue.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_QUEUE_PATH "../../../mcl/mm_lib/source\\mm_mtl/queue.h"
#else
#define MM_MTL_QUEUE_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/queue.h"
#endif

namespace mm { namespace mtl {

// a first-in first-out ring of elements in memory from an allocator: m_size of them from m_head on. Only what
// anm::ThreadPool and anm::JobQueue inline is here, and the names are not the original's (push_back's is: it is out
// of line).
template <typename T>
class Queue {
public:
    explicit Queue(IAllocator* allocator)
        : m_buffer(nullptr), m_size(0), m_head(0), m_capacity(0), m_alignment(8), m_allocator(allocator) {}
    ~Queue() {
        clear();
        if (m_buffer != nullptr) {
#line 835 MM_MTL_QUEUE_PATH
            MM_ASSERT(m_allocator);
            m_allocator->deallocate(m_buffer);
        }
    }
    // room for capacity elements from the allocator (anm::JobQueue's constructor inlines it)
    void reserve(size_t capacity) {
        m_buffer = static_cast<T*>(m_allocator->allocate(capacity * sizeof(T), m_alignment));
        m_head = 0;
        m_capacity = capacity;
    }
    // destroys the elements from the last
    void clear() {
        while (!empty()) {
            --m_size;
            at((m_head + m_size) % m_capacity).~T();
        }
        m_size = 0;
        m_head = 0;
    }
    void push_back(const T& value);  // out of line (Queue<anm::JobEntry>'s in anim_manager.cpp)
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
    size_t m_alignment;        // the buffer's: 8
    IAllocator* m_allocator;  // queue.h asserts `m_allocator` before giving the buffer back
};

}}  // namespace mm::mtl

#endif
