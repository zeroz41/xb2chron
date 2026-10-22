#ifndef PTLIB_STACKALLOCATER_H
#define PTLIB_STACKALLOCATER_H

namespace ptlib {

// a block of the library's memory handed out front to back and released whole (particle_stack_allocater.cpp)
class StaticAllocObj {
public:
    StaticAllocObj(unsigned int size) : m_pTop(reinterpret_cast<unsigned char*>(this + 1)), m_size(size), m_used(0) {}
    ~StaticAllocObj() {
        m_pTop = nullptr;
        m_size = 0;
        m_used = 0;
    }

    static StaticAllocObj* create(unsigned int size, const char* file, unsigned int line);
    static void destroy(StaticAllocObj* pObj);
    // the next size bytes, the offset rounded up to align; null once the block is full
    void* sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line);

    unsigned char* m_pTop;  // the block, just past this header
    unsigned int m_size;
    unsigned int m_used;
};

}  // namespace ptlib

#endif
