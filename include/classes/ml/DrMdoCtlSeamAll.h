#ifndef CLASSES_ML_DRMDOCTLSEAMALL_H
#define CLASSES_ML_DRMDOCTLSEAMALL_H

#include "ml/DrMdoCtlSeamRead.h"

namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table 0x7100B7BAA8
class DrMdoCtlSeamAll : public ::ml::DrMdoCtlSeamRead {
public:
    DrMdoCtlSeamAll(const void* data, const char* name, DrMan* drMan, int viewNum);  // DrMdlMan::createMdl news it
    virtual ~DrMdoCtlSeamAll();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void noOffScreenUpdate();  // slot 4
    virtual void resourceInit();  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int);  // slot 8
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    void releaseSeamAll();
    // false once the seam's resources are released (dispOffUpdate ignores it; the meaning is inferred)
    bool callDeleteUpdate();
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

    unsigned char pad_14C0[0x120];  // sizeof 0x15E0 (DrMdlMan::createMdl news that much); not recovered
};
}  // namespace ml

#endif
