#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"
#include "classes/fw/FrameworkMemory.h"
#include "ml/MlMem.h"
#include "ml/WorkRoot.h"
#include "fw/Allocator.h"
#include "mm/mtl/Hash.h"

namespace fw {

MemorySectionInfo::MemorySectionInfo() : m_kind(0), m_size(0), m_alignment(0x20), m_flag(true), m_type(mtl::AllocatorType(1)) {}

FrameworkMemory::FrameworkMemory() : m_isInitialized(false) {}

void FrameworkMemory::initialize(mtl::ALLOC_HANDLE handle, unsigned int count) {
    FrameworkMemory* memory = getPtr();
    if (memory->m_isInitialized) {
        return;
    }
    memory->m_isInitialized = true;
    memory->m_allocator.setMemHandle(handle);
    memory->m_sections.setAllocator(&memory->m_allocator);
    memory->m_sections.reserve(count);
}

void FrameworkMemory::finalize() {
    FrameworkMemory* memory = getPtr();
    if (!memory->m_isInitialized) {
        return;
    }
    for (unsigned long i = 0; i < memory->m_sections.size(); i++) {
        if (memory->m_sections[i].m_handle.m_handle != 0) {
            memory->removeSection(memory->m_sections[i].m_handle);
        }
    }
    memory->m_sections.clear();
    memory->m_isInitialized = false;
}

void FrameworkMemory::removeSection(mtl::ALLOC_HANDLE handle) {
    if (!m_isInitialized || handle.m_handle == 0) {
        return;
    }
    for (unsigned long i = 0; i < m_sections.size(); i++) {
        if (m_sections[i].m_handle.m_handle == handle.m_handle) {
            removeChildSection(handle);
            if (m_sections[i].m_handle.m_handle != 0) {
                mtl::MemManager::erase(m_sections[i].m_handle);
                m_sections[i].m_handle = mtl::ALLOC_HANDLE();
            }
            m_sections[i].clear();
            return;
        }
    }
}

void FrameworkMemory::removeChildSection(mtl::ALLOC_HANDLE handle) {
    if (!m_isInitialized || handle.m_handle == 0) {
        return;
    }
    for (unsigned long i = 0; i < m_sections.size(); i++) {
        if (m_sections[i].m_handle.m_handle != 0 && m_sections[i].m_info.m_parent.m_handle == handle.m_handle) {
            removeChildSection(m_sections[i].m_handle);
            if (m_sections[i].m_handle.m_handle != 0) {
                mtl::MemManager::erase(m_sections[i].m_handle);
                m_sections[i].m_handle = mtl::ALLOC_HANDLE();
            }
            m_sections[i].clear();
            return;
        }
    }
}

mtl::ALLOC_HANDLE FrameworkMemory::createSection(const MemorySectionInfo& info) {
    SectionRegistInfo& section = m_sections[info.m_kind];
    if (section.m_handle.m_handle != 0) {
        return mtl::ALLOC_HANDLE();
    }
    mtl::ALLOC_HANDLE handle;
    if (info.m_flag) {
        handle = mtl::MemManager::create(info.m_parent, info.m_size, info.m_name.m_str, true, info.m_type,
                                         info.m_alignment, "no name", 0);
    } else {
        handle = mtl::MemManager::create(info.m_parent, info.m_size, info.m_name.m_str, false, info.m_type,
                                         info.m_alignment, "no name", 0);
    }
    if (handle.m_handle != 0) {
        section.m_info = info;
        section.m_handle = handle;
        section.m_hash = mm::mtl::hashStrCrc(info.m_name.m_str);
        section.m_allocator.setMemHandle(handle);
    }
    return handle;
}

mtl::ALLOC_HANDLE FrameworkMemory::getMem(unsigned int kind) {
    switch (kind) {
    case 1:
        return ml::MlMem::getProductMem();
    case 2:
        return ml::MlMem::getDebugMem();
    case 3:
        return ml::WorkRoot::getMemTMP();
    }
    FrameworkMemory* memory = getPtr();
    if (!memory->m_isInitialized) {
        return mtl::ALLOC_HANDLE();
    }
    return memory->m_sections[kind].m_handle;
}

mm::mtl::IAllocator* FrameworkMemory::getAllocator(unsigned int kind) {
    switch (kind) {
    case 1:
        return Allocator::getSysAllocator();
    case 2:
        return Allocator::getDebAllocator();
    case 3:
        return Allocator::getTmpAllocator();
    }
    FrameworkMemory* memory = getPtr();
    if (!memory->m_isInitialized) {
        return nullptr;
    }
    return &memory->m_sections[kind].m_allocator;
}

}  // namespace fw

void* operator new(unsigned long size, mm::mtl::IAllocator* allocator, int alignment, const char* file,
                   unsigned long line) {
    return allocator->allocate(size, alignment);
}
