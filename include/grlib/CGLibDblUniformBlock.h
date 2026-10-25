#ifndef GRLIB_CGLIBDBLUNIFORMBLOCK_H
#define GRLIB_CGLIBDBLUNIFORMBLOCK_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {

// the platform part of a double-buffered uniform block: getGPUAdress reads the GPU address at 0x18 of the
// buffer CGLibManager::s_nDblNowIdx selects. Which class holds which field is not known, so this one holds them
// all; the field names are not the original's.
class CGLibDblUniformBlock_plf {
public:
    CGLibDblUniformBlock_plf() : m_pBuff(), m_gpuAddress() {}
    unsigned long getGPUAdress() const;

    unsigned char* m_pBuff[2];  // 0x0, one per frame
    int m_size;  // 0x10
    unsigned long m_gpuAddress[2];  // 0x18
    CGLibMemType m_mem;  // 0x28, both buffers
};

// a double-buffered uniform block (0x38 bytes: DrShdLgtClustered keeps six of them 0x38 apart): the frame's
// buffer (CGLibManager::s_nDblNowIdx) is written and bound
class CGLibDblUniformBlock : public CGLibDblUniformBlock_plf {
public:
    CGLibDblUniformBlock();
    ~CGLibDblUniformBlock();
    void release();
    void setup(int size);
    // returns the bytes the block takes from mem
    unsigned int setupArray(int size, CGLibMemType& mem, unsigned int ofs);
    void updateData();
    void updateData(unsigned int ofs, unsigned int size);
    unsigned char* getBuff();
    void setUniformBlock(unsigned int location);
    void setStorageBuffer(unsigned int location);
    void setUniformBlock(unsigned int location, unsigned int ofs, unsigned int size);
    void setStorageBuffer(unsigned int location, unsigned int ofs, unsigned int size);
};

}  // namespace grlib

#endif
