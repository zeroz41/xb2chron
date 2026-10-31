#include "classes/gf/GfAllocatorManager.h"
#include "classes/gf/GfAssetManager.h"
#include "gf/GfSlotMapping.h"
#include "mtl/MemManager.h"

namespace gf {

GfAllocatorManager::GfAllocatorManager() : m_initialized(false) {}

GfAllocatorManager::~GfAllocatorManager() {}

void GfAllocatorManager::initialize(const GfSetupParam&) {
    m_initialized = true;
}

void GfAllocatorManager::finalize() {
    m_initialized = false;
}

GfAllocator* GfAllocatorManager::getAllocator(ALLOCATOR allocator) {
    return &sys()->m_allocators[allocator];
}

void GfAllocatorManager::buildAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle) {
    m_allocators[allocator].m_hMem = handle;
}

void GfAllocatorManager::destroyAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE) {
    m_allocators[allocator].m_hMem = mtl::ALLOC_HANDLE();
}

mtl::ALLOC_HANDLE GfAllocator::getMemHandle() const {
    return m_hMem;
}

void* GfAllocator::allocate(unsigned long size, unsigned long alignment) {
    // allocator 11 first tries the asset slot mapping for large blocks, then allocator 0
    if (getAllocator(ALLOCATOR(11)) == this) {
        GfSlotMapping* slotMapping = GfAssetManager::getSlotMapping();
        if (size > 0x20000 && slotMapping != nullptr) {
            void* memory = slotMapping->allocateSize(size, alignment);
            if (memory != nullptr) {
                return memory;
            }
        }
        void* memory = getAllocator(ALLOCATOR(0))->allocate(size, alignment);
        if (memory != nullptr) {
            return memory;
        }
    }
    return mtl::MemManager::allocate(m_hMem, size, alignment, false, "no name", 0);
}

const char* GfAllocator::getName() const {
    return m_name.m_str;
}

}  // namespace gf
