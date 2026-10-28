#ifndef ML_DRMDOCTLSEAMMPFMAP_H
#define ML_DRMDOCTLSEAMMPFMAP_H

#include "ml/DrMdoCtlSeamInstMap.h"

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamMpfMap : public ::ml::DrMdoCtlSeamInstMap {
public:
    void createMpfZPrePassDisplayList();
    void createMpfMapDisplayList();
};
}  // namespace ml

#endif
