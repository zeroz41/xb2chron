#ifndef FW_ALLOCATOR_H
#define FW_ALLOCATOR_H

#include "classes/fw/MemHandlebaseAllocator.h"
#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// the framework's allocators, one per memory handle (set*MemHandle installs each)
namespace Allocator {
// each allocator's class only names it (getName; the strings are 1.0.0's and 3.0.1's)
class SysAllocator : public ::fw::MemHandlebaseAllocator {
public:
    virtual const char* getName() const { return "SystemMemoryAllocator"; }  // slot 4
};
class DebAllocator : public ::fw::MemHandlebaseAllocator {
public:
    virtual const char* getName() const { return "DebugMemoryAllocator"; }  // slot 4
};
class TmpAllocator : public ::fw::MemHandlebaseAllocator {
public:
    virtual const char* getName() const { return "TempMemoryAllocator"; }  // slot 4
};
class ProcAllocator : public ::fw::MemHandlebaseAllocator {
public:
    virtual const char* getName() const { return "ProcMemoryAllocator"; }  // slot 4
};

extern SysAllocator m_SysAllocator;
extern DebAllocator m_DebAllocator;
extern TmpAllocator m_TmpAllocator;
extern ProcAllocator m_ProcAllocator;

mm::mtl::IAllocator* getSysAllocator();
mm::mtl::IAllocator* getDebAllocator();
mm::mtl::IAllocator* getTmpAllocator();
mm::mtl::IAllocator* getProcAllocator();
void setSysMemHandle(mtl::ALLOC_HANDLE handle);
void setDebMemHandle(mtl::ALLOC_HANDLE handle);
void setTmpMemHandle(mtl::ALLOC_HANDLE handle);
void setProcMemHandle(mtl::ALLOC_HANDLE handle);
}  // namespace Allocator
}  // namespace fw

#endif
