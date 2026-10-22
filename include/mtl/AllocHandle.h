#ifndef MTL_ALLOCHANDLE_H
#define MTL_ALLOCHANDLE_H

namespace mtl {

// monolib's handle to a memory allocator (gf::GfMemManager::initializeGame and the event managers' create take one
// by value): one word, none (0) until a manager hands one out
class ALLOC_HANDLE {
public:
    ALLOC_HANDLE() : m_handle(0) {}

    unsigned int m_handle;
};

}  // namespace mtl

#endif
