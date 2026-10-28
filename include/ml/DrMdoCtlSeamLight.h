#ifndef ML_DRMDOCTLSEAMLIGHT_H
#define ML_DRMDOCTLSEAMLIGHT_H

#include "ml/DrMdoCtlSeamEnvMap.h"

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamLight : public ::ml::DrMdoCtlSeamEnvMap {
public:
};
}  // namespace ml

#endif
