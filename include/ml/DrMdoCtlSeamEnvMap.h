#ifndef ML_DRMDOCTLSEAMENVMAP_H
#define ML_DRMDOCTLSEAMENVMAP_H

#include "ml/DrMdoCtlSeamLowMap.h"

namespace ml { class DrResMdoSeamWrkEnv; }

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamEnvMap : public ::ml::DrMdoCtlSeamLowMap {
public:
    // inline: DrMdoCtlSeamAll's constructor calls DrMdoCtlSeam(int) directly
    explicit DrMdoCtlSeamEnvMap(int viewNum) : DrMdoCtlSeamLowMap(viewNum) {}
    void initEnvMapParts(DrResMdoSeamWrkEnv* wrk);
    void releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv* wrk);
    void readEnvMapCheck();
    void callRenderSeamEnvMap();
    void callGBuffRenderSeamEnvMap();
    void callLightPrePassRenderSeamEnvMap();
    void callAlphaRenderSeamEnvMap();
    void callSpAlphaRenderSeamEnvMap();
    void callRefractionRenderSeamEnvMap();
};
}  // namespace ml

#endif
