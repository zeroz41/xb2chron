#ifndef ML_MDSMATTOPHEADER_H
#define ML_MDSMATTOPHEADER_H

namespace ml {

// A model's material top header; the type name is from DrMdoMat::setupAvatarTbl's mangling. Only the fields
// setupAvatarTbl reads are known; their names are not the original's.
struct MdsMatTopHeader {
    unsigned char pad_0[0x40];
    unsigned char m_flags;  // 0x40, bit 2: the header carries the first avatar colour at m_avatarColorOfs
    unsigned char pad_41[0x7];
    unsigned int m_avatarColorOfs;  // 0x48, from the header's start
};
}  // namespace ml

#endif
