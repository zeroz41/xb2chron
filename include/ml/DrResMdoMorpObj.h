#ifndef ML_DRRESMDOMORPOBJ_H
#define ML_DRRESMDOMORPOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoMorpObj {
public:
    // one morph target's blend weight (0x20 bytes; names are not the original's): DrMdoMorphing::parmsUpdate
    // copies m_weight to m_prevWeight, isBlendCheck compares them
    struct Target {
        float m_weight;      // 0x0
        float m_prevWeight;  // 0x4
        unsigned char pad_8[0x18];
    };

    static void release(DrResMdoMorpObj*& obj);

    unsigned char pad_0[0x8];
    Target* m_pTarget;         // 0x8 (the name is not the original's)
    unsigned int m_targetNum;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
