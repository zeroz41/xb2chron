#ifndef CLASSES_ML_IRRVOL_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_ML_IRRVOL_MEMHANDLEBASEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"

namespace ml { namespace irrvol {
// table 0x7100B7B5F8
class MemHandlebaseAllocator : public ::mm::mtl::IAllocator {
public:
    MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}
    // inline: the table's complete-destructor slot holds IAllocator's
    virtual ~MemHandlebaseAllocator() {}  // slot 0
    virtual void* allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3

    mtl::ALLOC_HANDLE m_handle;  // 0x8, allocate passes it to mtl::MemManager (the name is not the original's)
};
}}  // namespace ml::irrvol

#endif
