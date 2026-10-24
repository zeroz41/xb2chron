#ifndef GRLIB_CGLIBMEMHANDLE_H
#define GRLIB_CGLIBMEMHANDLE_H

namespace grlib {
// a block of GPU-visible memory: CGLibMemHandle allocates and frees it. The field names are not the original's.
struct CGLibMemType {
    CGLibMemType() {
        m_type = 5;
        m_pMem = nullptr;
    }

    void* m_pMem;  // 0x0
    int m_type;  // 0x8, 5 until a CGLibMemHandle call fills the block
};

// the allocator of CGLibMemType blocks (static members: the callers pass only the block)
class CGLibMemHandle {
public:
    static void free(CGLibMemType& mem);
    static void allocVertex(CGLibMemType& mem, unsigned int size);
    // the block takes memory owned elsewhere (a CGLibVtlMemPool's)
    static void setMemBuff(CGLibMemType& mem, void* buffer);
};
}  // namespace grlib

#endif
