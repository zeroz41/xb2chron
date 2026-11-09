#ifndef ML_DRMDOCTLSEAMINSTMAP_H
#define ML_DRMDOCTLSEAMINSTMAP_H

#include "ml/DrMdoCtlSeamBaseMap.h"

namespace ml { class DrResMdoSeamWrkInst; }
namespace ml { struct MdsMdlTopHeader; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamInstMap : public ::ml::DrMdoCtlSeamBaseMap {
public:
    // inline: DrMdoCtlSeamAll's constructor calls DrMdoCtlSeam(int) directly
    explicit DrMdoCtlSeamInstMap(int viewNum) : DrMdoCtlSeamBaseMap(viewNum) {}
    void initInstMapParts(DrResMdoSeamWrkInst* wrk, DrResMdoSeamWrkInst* wrk2);
    void releaseFreeSeamInst(DrResMdoSeamWrkInst* wrk);
    void readInstMapCheck();
    bool readInstModelCheck(const mm::Vec3& pos, bool, bool);
    void createInstZPrePassDisplayList();
    void createInstThicknessPassDisplayList(bool first);
    void renderSeamInstMap(int pass);
    void beginResAll(MdoWrkMatRes* res);
    void endResAll();
    void callInstShadowCacheAddRender(int idx);
    void renderInstShadowCacheRender(DrResMdoSeamWrkInst* wrk, const mm::Mat44& mtx, unsigned int vtxNo,
                                     const MdsMdlTopHeader* top);
};
}  // namespace ml

#endif
