#ifndef GRLIB_CGLIBPIXLCOUNTER_H
#define GRLIB_CGLIBPIXLCOUNTER_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {

// a samples-passed counter the GPU reports into a uniform block (0x18 bytes; the field names are not the original's)
class CGLibPixlCounter {
public:
    CGLibPixlCounter();
    // inline: cloud::CloudObjReduction's destructor releases each counter again after its own releases
    ~CGLibPixlCounter() { release(); }
    void release();
    void beginCounter();
    void endCounter();
    void setUniformBlock(unsigned int location);

    unsigned long m_gpuAddress;  // 0x00: the report's uniform block, 0 until endCounter allocates it
    CGLibMemType m_mem;          // 0x08
};

}  // namespace grlib

#endif
