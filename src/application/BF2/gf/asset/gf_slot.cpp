#include "mm/mtl/FixedList.h"
#include "classes/gf/GfSizeAlloc.h"
#include <string.h>

namespace gf {

void GfSizeAlloc::setup(mm::mtl::IAllocator* allocator, unsigned int blockSize, void* buffer,
                        unsigned long bufferSize) {
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_blockSize = blockSize;
    m_buffer = buffer;
    m_bufferSize = bufferSize;
    m_allocs = 0;
    m_blockNum = bufferSize / m_blockSize;
    memset(buffer, 0xFD, bufferSize);
    m_blocks = static_cast<unsigned int*>(allocator->allocate(static_cast<unsigned long>(m_blockNum) * 4, 4));
    memset(m_blocks, 0, static_cast<unsigned long>(m_blockNum) * 4);
    m_allocs = 0;
    m_list.push_back(0);
    m_blocks[0] = m_blockNum;
    m_allocator = allocator;
}

void GfSizeAlloc::destroy() {
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_allocs = 0;
    m_blockNum = 0;
    m_buffer = nullptr;
    m_bufferSize = 0;
}

void GfSizeAlloc::resize(unsigned long bufferSize) {
    unsigned int blockNum = bufferSize / m_blockSize;
    m_bufferSize = bufferSize;
    m_blockNum = blockNum;
    memset(m_buffer, 0xFD, bufferSize);
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_blocks = static_cast<unsigned int*>(m_allocator->allocate(static_cast<unsigned long>(m_blockNum) * 4, 4));
    memset(m_blocks, 0, static_cast<unsigned long>(m_blockNum) * 4);
    m_blocks[0] = m_blockNum;
}

// alloc and free (and the FixedList<unsigned int, 64>::erase they instantiate) are in progress in
// session14/gfslot/wip/gf_slot_wip.cpp: not identical yet, so not here

}  // namespace gf
