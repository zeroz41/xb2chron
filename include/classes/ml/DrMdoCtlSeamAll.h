#ifndef CLASSES_ML_DRMDOCTLSEAMALL_H
#define CLASSES_ML_DRMDOCTLSEAMALL_H

#include "classes/ml/DrMdoCtlSeam.h"

namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table 0x7100B7BAA8
class DrMdoCtlSeamAll : public ::ml::DrMdoCtlSeam {
public:
    virtual ~DrMdoCtlSeamAll();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void noOffScreenUpdate();  // slot 4
    virtual void resourceInit();  // slot 5
    virtual void shadowRender();  // slot 6
    virtual void shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int);  // slot 8
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    virtual void setDeleteCall(int);  // slot 16
    virtual void debugRender();  // slot 17
    void callZPrePassSeamAll();
    void callThicknessFirstSeamAll();
    void callThicknessSecondSeamAll();
    void callRenderSeamAll();
    void callGBuffRenderSeamAll();
    void callLightPrePassRenderSeamAll();
    void callAlphaRenderSeamAll();
    void callSpAlphaRenderSeamAll();
    void callRefractionRenderSeamAll();
    void callRenderSeamEnvMap();
    void callGBuffRenderSeamEnvMap();
    void callLightPrePassRenderSeamEnvMap();
    void callAlphaRenderSeamEnvMap();
    void callSpAlphaRenderSeamEnvMap();
    void callRefractionRenderSeamEnvMap();
};
}  // namespace ml

#endif
