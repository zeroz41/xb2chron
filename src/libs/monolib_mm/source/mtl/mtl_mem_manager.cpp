#define MM_LIB_FROM_MONOLIB_MM
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "mtl/MemManagerRegion.h"
#include "ml/CriticalSection.h"
#include "classes/mtl/IMemAllocator.h"
#include "classes/mtl/DlAllocator.h"
#include "classes/mtl/NullAllocator.h"
#include "classes/mtl/MemHandlebaseAllocator.h"
#include "classes/mtl/AssetAllocator.h"
#include "classes/mm/mtl/HeapAllocator.h"
#include <new>
#include <stdlib.h>

namespace mtl {

// the heap createAllocator makes the allocators in
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100ED26D0)
static mm::mtl::HeapAllocator s_allocatorHeap;

mm::mtl::FixedVector<MemManager::HandleRegion, 512> MemManager::_existHandle;

DlAllocator::~DlAllocator() {}

}  // namespace mtl

void operator delete(void* p) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

namespace mtl {

void DlAllocator::destroy() {
    m_mspace = nullptr;
    m_base = nullptr;
    m_size = 0;
}

void* DlAllocator::allocate(unsigned long size, unsigned long alignment) {
    return allocate(size, 16, "no name", 0);
}

const char* DlAllocator::getName() const {
    return m_name.m_str;
}

ALLOC_HANDLE MemManager::create(void* p, unsigned long size, const char* name, bool flag) {
    return create(p, size, name, flag, static_cast<AllocatorType>(1));
}

ALLOC_HANDLE MemManager::create(ALLOC_HANDLE parent, unsigned long size, const char* name, bool flag, const char* file,
                                int line) {
    return create(parent, size, name, flag, static_cast<AllocatorType>(1), 16, file, line);
}

void MemManager::deallocate(void* p, unsigned long size, bool flag) {
    if (s_bInitialize) {
        deallocate_section(p, size, flag);
    }
}

IMemAllocator* MemManager::createAllocator(AllocatorType type) {
    IMemAllocator* allocator = nullptr;
    switch (type) {
    case 1:
        allocator = new (s_allocatorHeap.allocate(sizeof(DlAllocator), 8)) DlAllocator();
        break;
    case 2:
        allocator = new (s_allocatorHeap.allocate(sizeof(AssetAllocator<1024>), 8)) AssetAllocator<1024>();
        break;
    case 0:
        allocator = new (s_allocatorHeap.allocate(sizeof(NullAllocator), 8)) NullAllocator();
        break;
    }
    return allocator;
}

void* MemHandlebaseAllocator::allocate(unsigned long size, unsigned long alignment) {
#line 1906
    return MemManager::allocate(m_handle, size, alignment, false, __FILE__, __LINE__);
}

void MemHandlebaseAllocator::deallocate(void* memory) {
    MemManager::deallocate(memory, 0, false);
}

}  // namespace mtl

void* operator new(unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                   bool flag) {
    return mtl::MemManager::allocate(handle, static_cast<int>(size), alignment, flag, file, line);
}

void* operator new[](unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                     bool flag) {
    return mtl::MemManager::allocate(handle, static_cast<int>(size), alignment, flag, file, line);
}

void* operator new(unsigned long size) {
    return malloc(size);
}

void* operator new[](unsigned long size) {
    return malloc(size);
}

void operator delete[](void* p) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

void operator delete(void* p, const std::nothrow_t&) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

void operator delete[](void* p, const std::nothrow_t&) noexcept {
    mtl::MemManager::deallocate(p, 0, false);
}

namespace mtl {

IMemAllocator::~IMemAllocator() {}

}  // namespace mtl

namespace mtl {

void MemManager::setHaltAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_HALT_ALLOC : region->m_flags | Region::FLAG_HALT_ALLOC;
    }
}

void MemManager::setWarnAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_WARN_ALLOC : region->m_flags | Region::FLAG_WARN_ALLOC;
    }
}

void MemManager::setLogAlloc(ALLOC_HANDLE handle, bool flag) {
    if (handle.m_handle == 0) {
        return;
    }
    Region* region = s_ptrMap.find(handle.m_handle);
    if (region != nullptr) {
        region->m_flags = !flag ? region->m_flags & ~Region::FLAG_LOG_ALLOC : region->m_flags | Region::FLAG_LOG_ALLOC;
    }
}

}  // namespace mtl
