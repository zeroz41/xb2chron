#ifndef CLASSES_ML_DRPIXLSHADOWOBJSPT_H
#define CLASSES_ML_DRPIXLSHADOWOBJSPT_H

#include "classes/ml/DrPixlShadowObj.h"
#include "classes/ml/DrCalcClipWorkCone.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7CEE8
class DrPixlShadowObjSpt : public ::ml::DrPixlShadowObj {
public:
    // inline (no symbol): DrPixlShadowMan::createSptShadow builds it in place
    DrPixlShadowObjSpt(DrMan* drMan) : DrPixlShadowObj(drMan, 1) {
        m_sptParmTbl[3] = 1.0f;
        m_sptParmTbl[2] = 1.0f;
        m_sptParmTbl[1] = 1.0f;
        m_sptParmTbl[0] = 1.0f;
        m_calcMax[0] = 1.0f;
        m_calcMax[1] = 1.0f;
        m_calcMin[0] = -1.0f;
        m_calcMin[1] = -1.0f;
        m_clipRange = 4.0f;
    }
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
    // 0x200: what getParmTbl returns; afterUpdate fills and sends the 8 floats (the name and element type are not
    // the original's)
    float m_sptParmTbl[8];
    // 0x220: the view rectangle of the spheres setSptCalcPos accepted this frame (max x, y then min x, y), clamped
    // to -1..1 by afterUpdate (the names are not the original's)
    float m_calcMax[2];
    float m_calcMin[2];
    float m_clipRange;  // 0x230: clipChk/clipTypeChk reject spheres larger than it (the name is not the original's)
};
}  // namespace ml

#endif
