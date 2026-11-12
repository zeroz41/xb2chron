#ifndef ML_DRMDOCTLSEAMMPFMAP_H
#define ML_DRMDOCTLSEAMMPFMAP_H

#include "ml/DrMdoCtlSeamInstMap.h"

namespace ml {
class DrResMdoSeamWrkMpf;
// One part of the seam model control: the DrMdoCtlSeam* classes have no table of their own and DrMdoCtlSeamAll's
// methods call each part's methods on the same object (this unchanged), so they form one chain of bases between
// DrMdoCtlSeam and DrMdoCtlSeamAll. The order of the chain is not proven (every part sits at offset 0).
class DrMdoCtlSeamMpfMap : public ::ml::DrMdoCtlSeamInstMap {
public:
    // inline: DrMdoCtlSeamAll's constructor calls DrMdoCtlSeam(int) directly
    explicit DrMdoCtlSeamMpfMap(int viewNum) : DrMdoCtlSeamInstMap(viewNum) {}
    void createMpfZPrePassDisplayList();
    void createMpfMapDisplayList();
    void releaseFreeSeamMpf(DrResMdoSeamWrkMpf* wrk);
    // stocks every mpf model whose box (40 around it) holds pos and that is not in yet; false when it stocked one
    void readMpfMapCheck();
    bool readMpfModelCheck(const mm::Vec3& pos);
    void updateMpfMapRenderList();
};
}  // namespace ml

#endif
