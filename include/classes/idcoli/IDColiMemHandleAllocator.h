#ifndef CLASSES_IDCOLI_IDCOLIMEMHANDLEALLOCATOR_H
#define CLASSES_IDCOLI_IDCOLIMEMHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"

namespace idcoli {
// table 0x7100B7F030
class IDColiMemHandleAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~IDColiMemHandleAllocator() {}  // slot 0
    virtual void* allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    mtl::ALLOC_HANDLE m_allocHandle;  // 0x8, allocate's heap (the name is not the original's)
};
}  // namespace idcoli

#endif
