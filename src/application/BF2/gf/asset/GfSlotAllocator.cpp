#include "classes/gf/GfSizeAlloc.h"
#include "classes/gf/GfSlotAllocator.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfSlotAllocator::GfSlotAllocator() : m_parent(nullptr), m_buffer(nullptr), m_useFallback(true) {}

GfSlotAllocator::~GfSlotAllocator() {
    destroy();
}

void GfSlotAllocator::destroy() {
    if (m_buffer != nullptr) {
        m_parent->deallocate(m_buffer);
        m_buffer = nullptr;
    }
    m_sizeAlloc.destroy();
    m_parent = nullptr;
}

unsigned long GfSlotAllocator::getBlockSize() const {
    return m_sizeAlloc.m_blockSize;
}

void GfSlotAllocator::setupSizeAlloc(const char* name, mm::mtl::IAllocator* parent, unsigned long size,
                                     unsigned long alignment, bool useFallback) {
    m_name = name;
    m_parent = parent;
    m_useFallback = useFallback;
    m_buffer = parent->allocate(size, alignment);
    if (m_buffer != nullptr) {
        m_sizeAlloc.setup(getAllocator(ALLOCATOR(0)), 0x2000, m_buffer, size);
    }
}

void GfSlotAllocator::setup(const char* name, GfSlotAllocator* parent, unsigned long size, unsigned long alignment,
                            bool useFallback) {
    setupSizeAlloc(name, parent, size, alignment, useFallback);
}

void GfSlotAllocator::resize(unsigned long size) {
    m_sizeAlloc.resize(size);
}

void* GfSlotAllocator::allocate(unsigned long size, unsigned long alignment) {
    void* memory = m_sizeAlloc.alloc(size, false);
    if (memory != nullptr) {
        return memory;
    }
    if (m_useFallback) {
        return getAllocator(ALLOCATOR(10))->allocate(size, alignment);
    }
    return nullptr;
}

void GfSlotAllocator::deallocate(void* memory) {
    if (!m_sizeAlloc.free(memory) && m_useFallback) {
        getAllocator(ALLOCATOR(10))->deallocate(memory);
    }
}

unsigned int GfSlotAllocator::getAllocs() const {
    return m_sizeAlloc.m_allocs;
}

void* GfSlotAllocator::getBuffer() {
    return m_sizeAlloc.m_buffer;
}

unsigned long GfSlotAllocator::getBufferSize() const {
    return m_sizeAlloc.m_bufferSize;
}

const char* GfSlotAllocator::getName() const {
    return m_name.m_str;
}

}  // namespace gf
