#ifndef WND_POOLOBJECTMEMORY_H
#define WND_POOLOBJECTMEMORY_H

#include <new>

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/IntrusiveList.h"

// wndlib's wnd_object_pool_memory.h, as wndlib's own files' include path named it (the only spelling known)
#define WND_OBJECT_POOL_MEMORY_PATH "../../src\\wndlib/base/wnd_object_pool_memory.h"

namespace wnd {
// objects of T kept for reuse: alloc takes a freed one before it allocates, free keeps it for the next (T carries
// an intrusive list node at its start). The lists' names are the original's (its assertions name them), the rest
// are not.
template <typename T>
class PoolObjectMemory {
public:
    ~PoolObjectMemory();
    // where new objects come from: only while the pool holds none
    void setAllocator(mm::mtl::IAllocator* allocator) {
#line 102 WND_OBJECT_POOL_MEMORY_PATH
        MM_ASSERT(m_freeList.empty());
#line 103 WND_OBJECT_POOL_MEMORY_PATH
        MM_ASSERT(m_useList.empty());
        m_pAllocator = allocator;
    }
    T* alloc();
    // ptr back to the pool, unconstructed
    void free(T* ptr) {
        m_useList.remove(ptr);
        m_freeList.push_back(ptr);
    }

    mm::mtl::IAllocator* m_pAllocator;  // where a new object comes from; none, alloc makes none
    mm::mtl::IntrusiveList<T> m_useList;  // what alloc gave out
    mm::mtl::IntrusiveList<T> m_freeList;  // what free took back
};

// every object back to the allocator, unconstructed, the freed ones first
template <typename T>
PoolObjectMemory<T>::~PoolObjectMemory() {
    if (m_pAllocator != nullptr) {
        while (!m_freeList.empty()) {
            T* ptr = m_freeList.pop_front();
            m_pAllocator->deallocate(ptr);
        }
        while (!m_useList.empty()) {
            T* ptr = m_useList.pop_front();
            m_pAllocator->deallocate(ptr);
        }
    }
}

template <typename T>
T* PoolObjectMemory<T>::alloc() {
    if (!m_freeList.empty()) {
        T* ptr = m_freeList.pop_front();
        m_useList.push_back(ptr);
        return ptr;
    }
    if (m_pAllocator == nullptr) {
        return nullptr;
    }
    T* ptr = new (m_pAllocator->allocate(sizeof(T), 16)) T();
    m_useList.push_back(ptr);
    return ptr;
}
}  // namespace wnd

#endif
