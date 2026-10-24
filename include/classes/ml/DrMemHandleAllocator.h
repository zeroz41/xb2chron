#ifndef CLASSES_ML_DRMEMHANDLEALLOCATOR_H
#define CLASSES_ML_DRMEMHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/MemManager.h"

namespace ml {
// table 0x7100B7AD10
class DrMemHandleAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~DrMemHandleAllocator() {}  // slot 0
    virtual void* allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3

    mtl::ALLOC_HANDLE m_allocHandle;  // 0x8, allocate's heap (the name is not the original's)
};
}  // namespace ml

#endif
