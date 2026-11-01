#ifndef ML_DRMDOMORPHING_H
#define ML_DRMDOMORPHING_H

namespace ml {
struct MdoWrkMatRes;
class DrResMdoMorpObj;
class DrResEtcPamObj;

// A model's morphing state (no table: its constructor stores none). Field names are not the original's.
class DrMdoMorphing {
public:
    DrMdoMorphing(MdoWrkMatRes* wrkMatRes, DrResMdoMorpObj* morpObj, DrResEtcPamObj* pamObj);
    ~DrMdoMorphing();
    // 0: no target weight; 1: weights changing from zero only; 2: a weight is changing while another is set, or
    // changing away from a non-zero value (the meaning of the values is inferred)
    int isBlendCheck() const;
    void parmsUpdate();
    void updateParms();
    void resetDefVertex();
    void blendVertex();
    void oldPosVertex();

    MdoWrkMatRes* m_pWrkMatRes;    // 0x0
    DrResMdoMorpObj* m_pMorpObj;   // 0x8
    DrResEtcPamObj* m_pPamObj;     // 0x10
    unsigned char pad_18[0x4];     // sizeof 0x40: DrResMdoMorpObj::update's stack copy
    // 0x1C: updateParms sets it to -1 before it reads the weights (no reader known; the name is not the original's)
    int m_parmsState;
    unsigned char pad_20[0x20];
};
}  // namespace ml

#endif
