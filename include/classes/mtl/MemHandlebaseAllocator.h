#ifndef CLASSES_MTL_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_MTL_MEMHANDLEBASEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"

namespace mtl {

// table 0x7100B793E8: monolib's own mm::mtl::IAllocator over a memory handle (its destructor slot the base's: the
// destructor is trivial and inline, as is getName)
class MemHandlebaseAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~MemHandlebaseAllocator() {}  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const { return "MemHandlebaseAllocator"; }  // slot 4

    ALLOC_HANDLE m_handle;  // allocate allocates from it
};

}  // namespace mtl

#endif
