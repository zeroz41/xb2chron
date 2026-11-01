#ifndef ML_DRMDOCTLSEAMLOWMAP_H
#define ML_DRMDOCTLSEAMLOWMAP_H

#include "ml/DrMdoCtlSeamMpfMap.h"

namespace ml { class DrResMdoSeamWrkLow; }

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamLowMap : public ::ml::DrMdoCtlSeamMpfMap {
public:
    void initLowMapParts(DrResMdoSeamWrkLow* wrk);
    void releaseFreeSeamLow(DrResMdoSeamWrkLow* wrk);
    void createLowZPrePassDisplayList();
    void renderSeamLowMap(int pass);
};
}  // namespace ml

#endif
