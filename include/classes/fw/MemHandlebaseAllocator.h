#ifndef CLASSES_FW_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_FW_MEMHANDLEBASEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace fw {
// table 0x7100B41FB0: an mm::mtl::IAllocator over a monolib memory handle (its destructor slot holds
// IAllocator's: the destructor is trivial and inline, as is getName, both emitted after the unit's functions)
class MemHandlebaseAllocator : public ::mm::mtl::IAllocator {
public:
    MemHandlebaseAllocator();
    virtual ~MemHandlebaseAllocator() {}  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const { return m_name.m_str; }  // slot 4
    void setMemHandle(mtl::ALLOC_HANDLE handle);
    mtl::ALLOC_HANDLE getMemHandle() const;

    mtl::ALLOC_HANDLE m_memHandle;  // setMemHandle stores it, allocate allocates from it
    // what getName returns (the constructor empties it; the name is not the original's)
    mm::mtl::FixStr<64> m_name;
};
}  // namespace fw

#endif
