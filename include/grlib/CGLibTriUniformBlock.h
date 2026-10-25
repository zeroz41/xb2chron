#ifndef GRLIB_CGLIBTRIUNIFORMBLOCK_H
#define GRLIB_CGLIBTRIUNIFORMBLOCK_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {

// a triple-buffered uniform block (0x48 bytes): the frame's buffer (CGLibManager::s_nTriNowIdx) and the previous
// frame's are written and bound. The field names are not the original's.
class CGLibTriUniformBlock {
public:
    CGLibTriUniformBlock();
    ~CGLibTriUniformBlock();
    void release();
    void setup(int size);
    // returns the bytes the block takes from mem
    unsigned int setupArray(int size, CGLibMemType& mem, unsigned int ofs);
    void updateData();
    void updateData(unsigned int ofs, unsigned int size);
    void updateOldData();
    unsigned char* getBuff();
    unsigned char* getOldBuff();
    void setUniformBlock(unsigned int location);
    void setOldUniformBlock(unsigned int location);

    unsigned char* m_pBuff[3];  // 0x0, one per frame
    int m_size;  // 0x18
    unsigned long m_gpuAddress[3];  // 0x20
    CGLibMemType m_mem;  // 0x38, the three buffers
};

}  // namespace grlib

#endif
