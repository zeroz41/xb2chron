#ifndef CLASSES_ML_DRPIXLSHADOWOBJ_H
#define CLASSES_ML_DRPIXLSHADOWOBJ_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibRenderTarget.h"
#include "ml/DrPixlShadowMan.h"
#include "mm/Mat44.h"

namespace mm { class Vec3; }

namespace ml {
class DrMan;
class DrLightObj;

// table 0x7100B7CE08
class DrPixlShadowObj {
public:
    // every slot is inline: the original emits them all weak after DrPixlMan.cpp's own functions
    virtual ~DrPixlShadowObj() {}  // slot 0
    virtual void update() {}  // slot 2
    virtual void afterUpdate() {}  // slot 3
    virtual bool dispChk() { return true; }  // slot 4
    virtual bool clipChk(mm::Vec3 const&, float, bool) { return true; }  // slot 5
    virtual int clipTypeChk(mm::Vec3 const&, float) { return 0; }  // slot 6
    virtual bool setSptCalcPos(mm::Vec3 const&, float) { return true; }  // slot 7
    virtual void renderLight() {}  // slot 8
    virtual void stockTile() {}  // slot 9
    virtual void debugInfo() {}  // slot 10
    virtual const float* getParmTbl() const { return m_parmTbl.m[0]; }  // slot 11

    // clears the depth target, begins the shadow pass (DrAPCache, DrAPGxType, the DrCalcViewWork with m_parmTbl)
    // once per frame: bit 0 of m_flags marks it done
    void renderSetup();
    bool renderEnd();
    void setInstSelMapShadow(bool enable);

    // 0x8, the destructor destroys it; DrPixlMan::setShadowObj keeps its address (the name is not the original's)
    grlib::CGLibDblUniformBlock m_uniform;
    // 0x40: the shadow depth target from DrPixlShadowMan's pool (create*Shadow set it up); renderEnd invalidates its
    // depth buffer (the name is not the original's)
    DrPixlShadowMan::TexWork* m_depthTarget;
    unsigned char pad_48[0x4];
    // 0x4C: DrPixlShadowMan::setSptCalcPos skips an object while it is 0 (the name is not the original's)
    unsigned short m_active;
    unsigned char pad_4E[0x2];
    // 0x50 flags (the name is not the original's): bit 0 set by renderSetup and tested by renderEnd, bit 1 tested by
    // the derived dispChk, bit 2 set by setInstSelMapShadow, bit 3 gates DrPixlShadowObjDir::clipTypeChk
    unsigned int m_flags;
    unsigned char pad_54[0xC];
    // 0x60: what getParmTbl returns; the uniform block is set up with 0x40 or 0x50 bytes, a 4x4 matrix plus a vector;
    // renderSetup passes the matrix to DrCalcViewWork::shadowBegin (the name is not the original's)
    mm::Mat44 m_parmTbl;
    // 0xA0: DrPixlShadowObjSpt::setSptCalcPos moves a sphere's centre into the shadow's view with it (the name is
    // not the original's)
    mm::Mat44 m_viewMtx;
    // 0xE0: setSptCalcPos scales the radius by its [0][0] and [1][1] (the name is not the original's)
    mm::Mat44 m_projMtx;
    // 0x120: DrPixlShadowObjSpt::afterUpdate sends it (transposed 3x4) to the uniform block (the name is not the
    // original's)
    mm::Mat44 m_viewProjMtx;
    unsigned char pad_160[0x10];
    float m_range;  // 0x170: DrPixlShadowObjSpt::afterUpdate sends 1 / it (the name is not the original's)
    unsigned char pad_174[0x4];
    DrMan* m_drMan;  // 0x178: renderEnd ends the shadow pass of its DrCalcMan (the name is not the original's)
    unsigned char pad_180[0x10];
    // 0x190: the next object of a chain (DrPixlShadowMan::shadowRender walks it); the derived destructors delete it
    // (the name is not the original's)
    DrPixlShadowObj* m_next;
    DrLightObj* m_lightObj;  // 0x198: the DrLightObj the object was created for (the name is not the original's)
};
}  // namespace ml

#endif
