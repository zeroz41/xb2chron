#ifndef CLASSES_ML_DRMDOCTLPOS_H
#define CLASSES_ML_DRMDOCTLPOS_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"

namespace ml { class DrPixlShadowCacheObj; }
namespace ml { class DrResMdoInstMdlInfo; }
namespace ml { class DrCalcCpPlaneObj; }

namespace ml {
// table 0x7100B7B8E0
class DrMdoCtlPos : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlPos();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int);  // slot 8
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    virtual void setDeleteCall(int);  // slot 16
    void releasePos();
    void callZpreePassRenderPosAll();
    void callThicknessRenderFirstPosAll();
    void callThicknessRenderSecondPosAll();
    void callRenderPosAll();
    void callGBuffRenderPosAll();
    void callAlphaRenderPosAll();
    void callSpAlphaRenderPosAll();
    void callLightPrePassRenderPosAll();
    void callRefractionRenderPosAll();
    void callPosRender(unsigned int pass);
    void createZBuffRenderDisplayList();
    void createThicknessRenderDisplayListSub(bool first);

    // the names are not the original's
    unsigned char pad_18C[0x5C];
    DrResMdoInstAnmObj m_instAnm;  // 0x1E8: releasePos releases it; ScnObjAccSeamPos reads it (m_mdlType 1)
    unsigned char pad_218[0x40];
    // 0x258: setDeleteCall calls its releaseCall (the name is not the original's)
    DrResMdoInstMdlInfo* m_instMdlInfo;
    unsigned char pad_260[0xF8];
    // 0x358: setDeleteCall releases and clears it (the name is not the original's)
    DrCalcCpPlaneObj* m_cpPlane;
    unsigned char pad_360[0x8];
    // 0x368: callShadowCacheUpdate clears the bits it is given; when any of them is in 0x370, it clears 0x370 and
    // 0x378 too (the names are not the original's)
    unsigned long m_shadowCacheBits;
    unsigned long m_shadowCacheReq;
    unsigned int m_shadowCacheCount;
};
}  // namespace ml

#endif
