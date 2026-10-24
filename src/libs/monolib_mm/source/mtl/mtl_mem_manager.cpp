#define MM_LIB_FROM_MONOLIB_MM
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "classes/mtl/IMemAllocator.h"
#include "classes/mtl/DlAllocator.h"
#include "classes/mtl/NullAllocator.h"
#include "classes/mtl/MemHandlebaseAllocator.h"
#include "new"
#include "stdlib.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "classes/mtl/IMemAllocator.h"
#include "classes/mtl/DlAllocator.h"
#include "classes/mtl/NullAllocator.h"
#include "classes/mtl/MemHandlebaseAllocator.h"
#include <new>
#include <stdlib.h>

namespace mtl {

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

void MemManager::deallocate(void* p, unsigned long size, bool flag) {
    if (s_bInitialize) {
        deallocate_section(p, size, flag);
    }
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
