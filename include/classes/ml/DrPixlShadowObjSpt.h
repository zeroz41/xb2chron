#ifndef CLASSES_ML_DRPIXLSHADOWOBJSPT_H
#define CLASSES_ML_DRPIXLSHADOWOBJSPT_H

#include "classes/ml/DrPixlShadowObj.h"
#include "classes/ml/DrCalcClipWorkCone.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7CEE8
class DrPixlShadowObjSpt : public ::ml::DrPixlShadowObj {
public:
    virtual ~DrPixlShadowObjSpt();  // slot 0
    virtual void update();  // slot 2
    virtual void afterUpdate();  // slot 3
    virtual bool dispChk();  // slot 4
    virtual bool clipChk(mm::Vec3 const&, float, bool);  // slot 5
    virtual int clipTypeChk(mm::Vec3 const&, float);  // slot 6
    virtual bool setSptCalcPos(mm::Vec3 const&, float);  // slot 7
    virtual void renderLight();  // slot 8
    virtual void stockTile();  // slot 9
    // inline: the original emits it weak among DrPixlShadowObj's inline slots
    virtual const float* getParmTbl() const { return m_sptParmTbl; }  // slot 11

    DrCalcClipWorkCone m_clip;  // 0x1A0 (the name is not the original's)
    unsigned char pad_1b0[0x50];
    float m_sptParmTbl[0xC];  // 0x200: what getParmTbl returns (the name and element type are not the original's)
    float m_clipRange;  // 0x230: clipChk/clipTypeChk reject spheres larger than it (the name is not the original's)
};
}  // namespace ml

#endif
