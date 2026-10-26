#ifndef CLASSES_ML_DRMDOCTLPOS_H
#define CLASSES_ML_DRMDOCTLPOS_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"

namespace ml { class DrPixlShadowCacheObj; }

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
    void callZpreePassRenderPosAll();
    void callThicknessRenderFirstPosAll();
    void callThicknessRenderSecondPosAll();
    void callRenderPosAll();
    void callGBuffRenderPosAll();
    void callAlphaRenderPosAll();
    void callSpAlphaRenderPosAll();
    void callLightPrePassRenderPosAll();
    void callRefractionRenderPosAll();
    void createZBuffRenderDisplayList();
    void createThicknessRenderDisplayListSub(bool first);

    // the names are not the original's
    unsigned char pad_182[0x66];
    DrResMdoInstAnmObj m_instAnm;  // 0x1E8: releasePos releases it; ScnObjAccSeamPos reads it (m_mdlType 1)
};
}  // namespace ml

#endif
