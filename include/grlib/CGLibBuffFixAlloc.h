#ifndef GRLIB_CGLIBBUFFFIXALLOC_H
#define GRLIB_CGLIBBUFFFIXALLOC_H

namespace grlib {

// fixed-size slots handed out by id (the field names are not the original's; the size, 0x28, is the room
// CGLibSystemContext's constructor leaves its CGLibBuffOcclusion)
class CGLibBuffFixAlloc {
public:
    unsigned int allocID();
    void freeID(unsigned int id);

    unsigned char* m_pBuff;      // 0x00: the slots
    unsigned char pad_8[0x8];
    unsigned int m_elemSize;     // 0x10: the bytes of one slot
    unsigned char pad_14[0x14];
};

// the occlusion report slots (CGLibSystemContext::m_occlusion; that it derives from CGLibBuffFixAlloc is inferred:
// CGLibOcclusionQuery calls allocID/freeID on it at offset 0)
class CGLibBuffOcclusion : public CGLibBuffFixAlloc {
public:
    CGLibBuffOcclusion();
};

}  // namespace grlib

#endif
