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

    MdoWrkMatRes* m_pWrkMatRes;    // 0x0
    DrResMdoMorpObj* m_pMorpObj;   // 0x8
    DrResEtcPamObj* m_pPamObj;     // 0x10
};
}  // namespace ml

#endif
