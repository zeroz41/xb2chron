#ifndef GRLIB_CGLIBDBLUNIFORMBLOCK_H
#define GRLIB_CGLIBDBLUNIFORMBLOCK_H

namespace grlib {

// a double-buffered uniform block (0x38 bytes: DrShdLgtClustered keeps six of them 0x38 apart)
class CGLibDblUniformBlock {
public:
    void setUniformBlock(unsigned int location);
    void setStorageBuffer(unsigned int location);

    unsigned char pad_0[0x38];
};

}  // namespace grlib

#endif
