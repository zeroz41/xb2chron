#ifndef ML_DRMDOCTLSEAMBASEMAP_H
#define ML_DRMDOCTLSEAMBASEMAP_H

#include "classes/ml/DrMdoCtlSeam.h"

namespace ml { class DrResMdoSeamWrkBase; }

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamBaseMap : public ::ml::DrMdoCtlSeam {
public:
    void initBaseMapParts(DrResMdoSeamWrkBase* wrk);
    void createBaseZPrePassDisplayList();
    void createBaseThicknesPassDisplayList(bool first);
    void renderSeamBaseMap(int pass);

    // The seam fields are DrMdoCtlSeam's: its destructor destroys members up to 0xD30 (DrResMdoSeamMemMan at
    // 0x6E0, DrResMdoSeamRead at 0xCD0, DrResMdoSeamParmRead at 0xD30).
};
}  // namespace ml

#endif
