#include "classes/fw/MemHandlebaseAllocator.h"
#include "fw/Allocator.h"
#include "mtl/MemManager.h"

namespace fw {

MemHandlebaseAllocator::MemHandlebaseAllocator() {}

void MemHandlebaseAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) {
    m_memHandle = handle;
}

mtl::ALLOC_HANDLE MemHandlebaseAllocator::getMemHandle() const {
    return m_memHandle;
}

void* MemHandlebaseAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_memHandle, size, alignment, false, "no name", 0);
}

void MemHandlebaseAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

namespace Allocator {

SysAllocator m_SysAllocator;
DebAllocator m_DebAllocator;
TmpAllocator m_TmpAllocator;
ProcAllocator m_ProcAllocator;

mm::mtl::IAllocator* getSysAllocator() {
    return &m_SysAllocator;
}

mm::mtl::IAllocator* getDebAllocator() {
    return &m_DebAllocator;
}

mm::mtl::IAllocator* getTmpAllocator() {
    return &m_TmpAllocator;
}

mm::mtl::IAllocator* getProcAllocator() {
    return &m_ProcAllocator;
}

void setSysMemHandle(mtl::ALLOC_HANDLE handle) {
    m_SysAllocator.setMemHandle(handle);
}

void setDebMemHandle(mtl::ALLOC_HANDLE handle) {
    m_DebAllocator.setMemHandle(handle);
}

void setTmpMemHandle(mtl::ALLOC_HANDLE handle) {
    m_TmpAllocator.setMemHandle(handle);
}

void setProcMemHandle(mtl::ALLOC_HANDLE handle) {
    m_ProcAllocator.setMemHandle(handle);
}

}  // namespace Allocator
}  // namespace fw
