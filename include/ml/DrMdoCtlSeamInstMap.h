#ifndef ML_DRMDOCTLSEAMINSTMAP_H
#define ML_DRMDOCTLSEAMINSTMAP_H

#include "ml/DrMdoCtlSeamBaseMap.h"

namespace ml { class DrResMdoSeamWrkInst; }

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamInstMap : public ::ml::DrMdoCtlSeamBaseMap {
public:
    void initInstMapParts(DrResMdoSeamWrkInst* wrk, DrResMdoSeamWrkInst* wrk2);
    void createInstZPrePassDisplayList();
    void createInstThicknessPassDisplayList(bool first);
    void renderSeamInstMap(int pass);
};
}  // namespace ml

#endif
