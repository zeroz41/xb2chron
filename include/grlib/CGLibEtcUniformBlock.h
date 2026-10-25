#ifndef GRLIB_CGLIBETCUNIFORMBLOCK_H
#define GRLIB_CGLIBETCUNIFORMBLOCK_H

namespace grlib {

// a uniform block in the system context's global uniform memory (0x18 bytes): its buffer filled through
// getBuff, sent by updateData, bound by setUniformBlock. The field names are not the original's.
class CGLibEtcUniformBlock {
public:
    CGLibEtcUniformBlock();
    ~CGLibEtcUniformBlock();
    void setMoveMem(unsigned int size);
    void* getBuff();
    void updateData(unsigned int size);
    void Rebuilding();
    void setUniformBlock(unsigned int location);
    void setStorageBuffer(unsigned int location);

    unsigned char* m_pBuff;  // 0x0
    unsigned int m_size;  // 0x8
    unsigned long m_gpuAddress;  // 0x10
};

}  // namespace grlib

#endif
