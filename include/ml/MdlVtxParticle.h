#ifndef ML_MDLVTXPARTICLE_H
#define ML_MDLVTXPARTICLE_H

namespace ml {
// a model's vertex particle parameters: ScnObjAccMdlParticle::setParams copies them to the model's vertex mesh
// (0x100-0x130). The field names are not the original's.
struct MdlVtxParticle {
    // two floats setParams copies as one 8-byte block (the name is not the original's)
    struct Pair {
        float m_first;
        float m_second;
    };

    // the particle's parameters (GfObjUtil::setDeadParticle copies them from EffectManager's table)
    float m_val0;
    float m_val4;
    float m_val8;
    float m_valC;
    int m_val10;
    Pair m_val14;
    float m_val1C;
    float m_val20;
    float m_val24;  // clamped to 0..1 by setParams
    float m_val28;  // clamped to 0..1 by setParams
    float m_val2C;
    float m_alpha;  // 0x30: GfObjUtil::setDeadParticle's alpha
};
}  // namespace ml

#endif
