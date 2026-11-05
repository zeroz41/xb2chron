#ifndef ML_MDLVTXPARTICLE_H
#define ML_MDLVTXPARTICLE_H

namespace ml {
// a model's vertex particle parameters: ScnObjAccMdlParticle::setParams copies them to the model's vertex mesh
// (0x100-0x130). The field names are not the original's.
struct MdlVtxParticle {
    // the particle's parameters (GfObjUtil::setDeadParticle copies them from EffectManager's table)
    unsigned char pad_0[0x30];
    float m_alpha;  // GfObjUtil::setDeadParticle's alpha
};
}  // namespace ml

#endif
