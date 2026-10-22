#ifndef WND_POOLOBJECTMEMORY_H
#define WND_POOLOBJECTMEMORY_H

#include <new>

#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/IntrusiveList.h"

namespace wnd {
// objects of T kept for reuse: alloc takes a freed one before it allocates, free keeps it for the next (T carries
// an intrusive list node at its start). The names of the members are not the original's.
template <typename T>
class PoolObjectMemory {
public:
    T* alloc();
    // ptr back to the pool, unconstructed
    void free(T* ptr) {
        m_usedList.remove(ptr);
        m_freeList.push_back(ptr);
    }

    mm::mtl::IAllocator* m_pAllocator;  // where a new object comes from; none, alloc makes none
    mm::mtl::IntrusiveList<T> m_usedList;  // what alloc gave out
    mm::mtl::IntrusiveList<T> m_freeList;  // what free took back
};

template <typename T>
T* PoolObjectMemory<T>::alloc() {
    if (!m_freeList.empty()) {
        T* ptr = m_freeList.pop_front();
        m_usedList.push_back(ptr);
        return ptr;
    }
    if (m_pAllocator == nullptr) {
        return nullptr;
    }
    T* ptr = new (m_pAllocator->allocate(sizeof(T), 16)) T();
    m_usedList.push_back(ptr);
    return ptr;
}
}  // namespace wnd

#endif
