#ifndef GRLIB_CGLIBETCUNIFORMBLOCK_H
#define GRLIB_CGLIBETCUNIFORMBLOCK_H

namespace grlib {

// a uniform block (0x18 bytes): its buffer filled through getBuff, sent by updateData, bound by setUniformBlock
class CGLibEtcUniformBlock {
public:
    CGLibEtcUniformBlock();
    ~CGLibEtcUniformBlock();
    void setMoveMem(unsigned int size);
    void* getBuff();
    void updateData(unsigned int size);
    void setUniformBlock(unsigned int location);

    unsigned char pad_0[0x18];
};

}  // namespace grlib

#endif
