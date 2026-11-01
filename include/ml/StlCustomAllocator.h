#ifndef ML_STLCUSTOMALLOCATOR_H
#define ML_STLCUSTOMALLOCATOR_H

#include <stddef.h>
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace ml {

// An allocator for the C++ library's containers that takes its memory from one monolib allocator (the handle it
// holds), as fw::EffectManager's std::unordered_map instances name it. Blocks are allocated unnamed ("no name", 0)
// at the element's alignment and given back with size 0.
template <class _Tp>
class StlCustomAllocator {
public:
    typedef _Tp value_type;
    template <class _Up>
    struct rebind {
        typedef StlCustomAllocator<_Up> other;
    };

    StlCustomAllocator() {}
    explicit StlCustomAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}
    template <class _Up>
    StlCustomAllocator(const StlCustomAllocator<_Up>& other) : m_handle(other.m_handle) {}

    _Tp* allocate(size_t n) {
        return static_cast<_Tp*>(mtl::MemManager::allocate(m_handle, n * sizeof(_Tp), alignof(_Tp), false, "no name", 0));
    }
    void deallocate(_Tp* p, size_t) { mtl::MemManager::deallocate(p, 0, false); }

    mtl::ALLOC_HANDLE m_handle;
};

}  // namespace ml

#endif
