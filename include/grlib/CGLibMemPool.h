#ifndef GRLIB_CGLIBMEMPOOL_H
#define GRLIB_CGLIBMEMPOOL_H

#include "mtl/AllocHandle.h"
#include "nvn/nvn.h"

namespace grlib {

// an NVN memory pool over a buffer (its own, from setupHandle, or the caller's). The field names are not the
// original's.
class CGLibMemPool {
public:
    CGLibMemPool();
    ~CGLibMemPool();
    void release();
    // a buffer of size bytes (rounded up to 0x1000) allocated from the handle, the pool over it
    void setupHandle(mtl::ALLOC_HANDLE handle, unsigned int size, unsigned int flags);
    void setupBuffer(void* buffer, unsigned int size, unsigned int flags);
    NVNmemoryPool* m_pPool;  // 0x00: a slot of the context's m_memPoolTbl
    unsigned int m_size;     // 0x08: 0 while there is no pool
    void* m_pAlloc;          // 0x10: the buffer setupHandle allocated
    void* m_pBuffer;         // 0x18: the pool's storage
};

// a memory pool parts are cut from in turn (cntOffset)
class CGLibMemPoolList : public CGLibMemPool {
public:
    CGLibMemPoolList();
    ~CGLibMemPoolList();
    void release();
    void setupHandle(mtl::ALLOC_HANDLE handle, unsigned int size, unsigned int flags);
    // the offset of the next size bytes at the alignment (the end advances past them)
    unsigned int cntOffset(unsigned int size, unsigned int alignment);
    unsigned int m_offset;  // 0x20: the end of what was cut
};

class CGLibPartsMemPool;

// CGLibPartsMemPool's list links, a sub-object with its own constructor (the name is not the original's): the
// links are cleared as one block ahead of the pool's fields in CGLibMemPoolAdder::addAdder, which needs the links
// initialized by a constructor of their own
struct CGLibPartsMemPoolLink {
    CGLibPartsMemPoolLink() : m_pPrev(nullptr), m_pNext(nullptr) {}
    CGLibPartsMemPool* m_pPrev;  // 0x00
    CGLibPartsMemPool* m_pNext;  // 0x08
};

// a pool CGLibMemPoolAdder adds, in its list
class CGLibPartsMemPool : public CGLibPartsMemPoolLink {
public:
    CGLibPartsMemPool();
    ~CGLibPartsMemPool();
    void addAdder(void* buffer, unsigned int size);
    CGLibMemPool m_pool;  // 0x10
};

}  // namespace grlib

#endif
