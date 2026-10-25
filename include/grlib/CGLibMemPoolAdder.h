#ifndef GRLIB_CGLIBMEMPOOLADDER_H
#define GRLIB_CGLIBMEMPOOLADDER_H

#include "mtl/AllocHandle.h"

namespace grlib {
// the memory pools added for the GPU (CGLibGPUCache's add/release functions): a list of pool entries, the head
// and the tail (the field names are not the original's; the size is not known)
class CGLibMemPoolAdder {
public:
    void addAdder(mtl::ALLOC_HANDLE handle);
    void addAdder(void* buffer, unsigned int size);
    void releaseAdder(mtl::ALLOC_HANDLE handle);
    void releaseAdder(void* buffer);

    void* m_pHead;  // 0x0
    void* m_pTail;  // 0x8
};
}  // namespace grlib

#endif
