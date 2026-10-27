#include "gf/GfSlotMapping.h"
#include "gf/GfSlotAll.h"
#include "classes/gf/GfSlotAllocator.h"
#include "classes/gf/GfAllocator.h"
#include "mtl/MemManager.h"

namespace gf {

unsigned long GfSlotMapping::getAllSize() {
    return 0x24eb0000;
}

GfSlotMapping::GfSlotMapping() : m_slotAll(nullptr), m_memTop(0), m_memEnd(0) {
#line 382
    m_slotAll = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSlotAll();
    m_slotAllocator = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSlotAllocator();
}

GfSlotMapping::~GfSlotMapping() {
    if (m_slotAllocator != nullptr) {
        delete m_slotAllocator;
        m_slotAllocator = nullptr;
    }
    if (m_slotAll != nullptr) {
        delete m_slotAll;
        m_slotAll = nullptr;
    }
}

void GfSlotMapping::setup(const GfSetupParam& param, GfAllocator* allocator, unsigned long size) {
    m_slotAllocator->setupSizeAlloc("SLOT_ALL", allocator, size, 0x2000, false);
    createMapping(param);
    m_memTop = (unsigned long)mtl::MemManager::getTopAdr(getAllocator(ALLOCATOR(3))->getMemHandle());
    m_memEnd = m_memTop + mtl::MemManager::getTotalSize(getAllocator(ALLOCATOR(3))->getMemHandle());
}

void GfSlotMapping::update(const fw::UpdateInfo& info) {
    updateSlotRequest(info);
}

void GfSlotMapping::releaseSlot(GF_SLOT_HANDLE* handle) {
    m_slotAll->releaseSlot(handle);
}

void* GfSlotMapping::allocateSize(unsigned long size, unsigned long alignment) {
    return m_slotAll->fn_71001C77B8(18, size, alignment);
}

bool GfSlotMapping::deallocateSize(void* memory) {
    if (m_memTop > (unsigned long)memory) {
        return false;
    }
    if (m_memEnd > (unsigned long)memory) {
        m_slotAll->deallocateSize(memory);
        return true;
    }
    return false;
}

}  // namespace gf
