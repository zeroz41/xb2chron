#ifndef GRLIB_CGLIBMEMPOOLADDER_H
#define GRLIB_CGLIBMEMPOOLADDER_H

#include "mtl/AllocHandle.h"
#include "ml/CriticalSection.h"

namespace grlib {
class CGLibMemPool;
class CGLibPartsMemPool;

// the memory pools added for the GPU (CGLibGPUCache's add/release functions): a list of CGLibPartsMemPool under a
// lock (the field names are not the original's)
class CGLibMemPoolAdder {
public:
    CGLibMemPoolAdder();
    ~CGLibMemPoolAdder();
    void release();
    void setup();
    // the pool whose storage holds p (null when none does)
    CGLibMemPool* getMemPool(const void* p);
    void addAdder(mtl::ALLOC_HANDLE handle);
    void addAdder(void* buffer, unsigned int size);
    void releaseAdder(mtl::ALLOC_HANDLE handle);
    void releaseAdder(void* buffer);
    static const ml::CriticalSection& getCriticalSection();
    CGLibPartsMemPool* m_pHead;  // 0x0
    CGLibPartsMemPool* m_pTail;  // 0x8
};
}  // namespace grlib

#endif
