#ifndef MTL_ALLOCHANDLE_H
#define MTL_ALLOCHANDLE_H

namespace mtl {

// monolib's handle to a memory allocator (gf::GfMemManager::initializeGame and the event managers' create take one
// by value): one word, none (0) until a manager hands one out
class ALLOC_HANDLE {
public:
    ALLOC_HANDLE() : m_handle(0) {}
    // a copy of its own, so calls pass one through memory: fw::FrameworkMemory::getMem returns one to its caller's
    // stack and fw::LayerSetManager::initialize hands layer::LayerManager's constructor that slot's address
    ALLOC_HANDLE(const ALLOC_HANDLE& other) : m_handle(other.m_handle) {}

    unsigned int m_handle;
};

}  // namespace mtl

#endif
