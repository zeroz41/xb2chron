#ifndef CLASSES_ML_DRPIXLSHADOWOBJDIR_H
#define CLASSES_ML_DRPIXLSHADOWOBJDIR_H

#include "classes/ml/DrPixlShadowObj.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "mm/Plane.h"
#include "mm/Vec3.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7CE78
class DrPixlShadowObjDir : public ::ml::DrPixlShadowObj {
public:
    virtual ~DrPixlShadowObjDir();  // slot 0
    virtual void update();  // slot 2
    virtual bool dispChk();  // slot 4
    virtual bool clipChk(mm::Vec3 const&, float, bool);  // slot 5
    virtual int clipTypeChk(mm::Vec3 const&, float);  // slot 6
    virtual void debugInfo();  // slot 10

    bool setAddObjPos(mm::Vec3 const& pos, float radius);

    DrCalcClipWorkPlane m_clip;  // 0x1A0 (the name is not the original's)
    // 0x270: DrPixlShadowMan::clipDirShadowChk keeps only spheres wholly behind it (the name is not the original's)
    mm::Plane m_shadowPlane;
    unsigned char pad_290[0x70];
    // 0x300: the shadow direction clipDirShadowChk tests along (the name is not the original's)
    mm::Vec3 m_shadowDir;
    unsigned char pad_310[0x28];
    float m_typeClipRange;  // 0x338: clipTypeChk tests only spheres smaller than it (the name is not the original's)
};
}  // namespace ml

#endif
