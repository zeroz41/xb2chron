#ifndef ML_MDSMPFMATTOPHEADER_H
#define ML_MDSMPFMATTOPHEADER_H

namespace ml {
// The head of an MPF material resource (DrShdUniformBlockMan::createUniformMpfMaterialObj makes a material uniform
// block per material). Only the material count is known; its name is not the original's.
struct MdsMpfMatTopHeader {
    unsigned char pad_0[0x14];
    unsigned int m_matNum;  // 0x14
};
}  // namespace ml

#endif
