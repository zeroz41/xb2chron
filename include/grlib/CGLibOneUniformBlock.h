#ifndef GRLIB_CGLIBONEUNIFORMBLOCK_H
#define GRLIB_CGLIBONEUNIFORMBLOCK_H

#include "grlib/CGLibMemHandle.h"
#include "grlib/CGLibVtlMemPool.h"

namespace grlib {

// a single-buffered uniform block (0x28 bytes; CGLibCtlVertex::setUniformVertex binds it as a vertex stream). The
// field names are not the original's.
class CGLibOneUniformBlock {
public:
    CGLibOneUniformBlock();
    ~CGLibOneUniformBlock();
    void release();
    void setup(int size);
    void setup(CGLibVtlMemPool* pool, unsigned int size, unsigned int ofs);
    // returns the bytes the block takes from mem
    unsigned int setupArray(int size, CGLibMemType& mem, unsigned int ofs);
    void setupArray(CGLibVtlMemPool* pool, unsigned int size, unsigned int ofs);
    void updateData();
    void updateData(unsigned int ofs, unsigned int size);
    void setUniformBlock(unsigned int location);
    void setStorageBuffer(unsigned int location);
    void setStorageBuffer(unsigned int location, unsigned int ofs, unsigned int size);
    unsigned char* getMapping();

    unsigned char* m_pBuff;  // 0x0
    int m_size;  // 0x8
    unsigned char pad_C[0x4];
    unsigned long m_gpuAddress;  // 0x10
    CGLibMemType m_mem;  // 0x18
};
}  // namespace grlib

#endif
