#ifndef ML_DRMDOCTLSEAMBASEMAP_H
#define ML_DRMDOCTLSEAMBASEMAP_H

#include "classes/ml/DrMdoCtlSeam.h"

namespace ml { class DrResMdoSeamWrkBase; }
namespace ml { class DrPixlShadowObj; }

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
    void callShadowMapRenderSeamBaseMap(DrPixlShadowObj* shadow);
    void changeMemBaseMapParts(DrResMdoSeamWrkBase* wrk);
    void releaseFreeSeamBase(DrResMdoSeamWrkBase* wrk);
    // reads in the base maps whose box (widened by the read range) holds pos and that are not in yet; found is set
    // when one is; false when one was found (the parameter names are not the original's)
    void readBaseMapCheck();
    bool readBaseModelCheck(bool& found, const mm::Vec3& pos, bool check);

    static float SEAM_BASEMAP_READ_DEN_CHECK;
    static float SEAM_BASEMAP_READ_IN_CHECK;

    // The seam fields are DrMdoCtlSeam's: its destructor destroys members up to 0xD30 (DrResMdoSeamMemMan at
    // 0x6E0, DrResMdoSeamRead at 0xCD0, DrResMdoSeamParmRead at 0xD30).
};
}  // namespace ml

#endif
