#ifndef ML_MDSMATVALSHADERCATE_H
#define ML_MDSMATVALSHADERCATE_H

namespace ml {
// A material's shader value category (resource data). Only the flag DrMdoSetup's uniformBlock_Cluster*
// callbacks test is known; the field name is not the original's.
struct MdsMatValShaderCate {
    unsigned char pad_0[0x3];
    unsigned char m_flags;  // 0x3, bit 0: bind the light lists as storage buffers, not uniform blocks
};
}  // namespace ml

#endif
