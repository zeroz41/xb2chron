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
    // inline (no symbol): DrPixlShadowMan::createDirCacheShadow builds it in place
    DrPixlShadowObjDir(DrMan* drMan) : DrPixlShadowObj(drMan, 0) {
        pad_2B0 = 1.0f;
        m_shadowDir.x = 0.0f;
        m_shadowDir.y = 0.0f;
        m_shadowDir.z = 0.0f;
        m_typeClipRange = 5.0f;
        pad_33C = 30.0f;
        pad_340 = 1.0f;
    }
    virtual ~DrPixlShadowObjDir();  // slot 0
    virtual void update();  // slot 2
    virtual bool dispChk();  // slot 4
    virtual bool clipChk(mm::Vec3 const&, float, bool);  // slot 5
    virtual int clipTypeChk(mm::Vec3 const&, float);  // slot 6
    virtual void debugInfo();  // slot 10

    bool setAddObjPos(mm::Vec3 const& pos, float radius);
    void calcLgtMat();

    DrCalcClipWorkPlane m_clip;  // 0x1A0 (the name is not the original's)
    // 0x270: DrPixlShadowMan::clipDirShadowChk keeps only spheres wholly behind it (the name is not the original's)
    mm::Plane m_shadowPlane;
    // 0x290: setAddObjPos measures each added sphere's depth along it (the name is not the original's)
    mm::Plane m_depthPlane;
    float pad_2B0;  // the constructor sets 1.0f
    unsigned char pad_2B4[0x4C];
    // 0x300: the shadow direction clipDirShadowChk tests along (the name is not the original's)
    mm::Vec3 m_shadowDir;
    // 0x310/0x320: the box setAddObjPos grows around each added sphere (the names are not the original's)
    mm::Vec3 m_addMax;
    mm::Vec3 m_addMin;
    // 0x330/0x334: the depth range setAddObjPos grows (the names are not the original's)
    float m_depthNear;
    float m_depthFar;
    float m_typeClipRange;  // 0x338: clipTypeChk tests only spheres smaller than it (the name is not the original's)
    float pad_33C;  // the constructor sets 30.0f; update reads it
    float pad_340;  // the constructor sets 1.0f; update and calcLgtMat store it
    // 0x344: setAddObjPos sets one bit per unit of depth from (int)m_depthNear (the name is not the original's)
    unsigned int m_depthBits;
};
}  // namespace ml

#endif
