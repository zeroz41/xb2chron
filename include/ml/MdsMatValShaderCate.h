#ifndef ML_MDSMATVALSHADERCATE_H
#define ML_MDSMATVALSHADERCATE_H

namespace ml {
// A material's shader value category (resource data). Only the flag DrMdoSetup's uniformBlock_Cluster*
// callbacks test is known; the field name is not the original's.
struct MdsMatValShaderCate {
    // 0x0: the entry's block id, its DrMdoSetup::s_pUniBkMat index (DrMdoSetup::setShader; name inferred)
    unsigned short m_blockId;
    unsigned char pad_2[0x1];
    unsigned char m_flags;  // 0x3, bit 0: bind the light lists as storage buffers, not uniform blocks
};
}  // namespace ml

#endif
