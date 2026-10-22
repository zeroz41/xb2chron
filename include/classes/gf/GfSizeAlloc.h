#ifndef CLASSES_GF_GFSIZEALLOC_H
#define CLASSES_GF_GFSIZEALLOC_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixedList.h"

namespace gf {
// table 0x7100B459E8: blocks of one size cut from a buffer, with a word of bookkeeping per block (setup, resize, alloc,
// free and destroy are application/BF2/gf/asset/gf_slot.cpp's; the destructor and constructor are inline, emitted by
// GfSlotAllocator, whose member it is). The field names are not the original's: they are what setup and the
// GfSlotAllocator accessors (getBuffer, getBufferSize, getBlockSize, getAllocs) read and write.
class GfSizeAlloc {
public:
    GfSizeAlloc()
        : m_buffer(nullptr), m_bufferSize(0), m_blocks(nullptr), m_allocs(0), m_blockSize(0), m_allocator(nullptr) {}
    virtual ~GfSizeAlloc() {  // slot 0
        destroy();
    }

    void setup(mm::mtl::IAllocator* allocator, unsigned int blockSize, void* buffer, unsigned long bufferSize);
    void destroy();
    void resize(unsigned long bufferSize);
    void* alloc(unsigned long size, bool flag);
    bool free(void* memory);

    void* m_buffer;  // setup's buffer, filled with 0xFD
    unsigned long m_bufferSize;
    unsigned int* m_blocks;  // a word per block, taken from m_allocator
    unsigned int m_allocs;
    unsigned int m_blockNum;  // m_bufferSize / m_blockSize
    unsigned long m_blockSize;
    mm::mtl::FixedList<unsigned int, 64> m_list;
    mm::mtl::IAllocator* m_allocator;  // setup's allocator, which m_blocks comes from
};
}  // namespace gf

#endif
