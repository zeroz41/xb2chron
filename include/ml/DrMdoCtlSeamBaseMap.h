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

    // The fields below sit in the base-most part because the part that owns them is not proven (their names
    // are not the original's).
    unsigned char pad_6D8[0x5A4];
    // 0xC7C: DrMdoCtlSeamRead::wait*Stream set bit 16 when a stream ends without its data (and bit 10 while
    // DrMan::m_seamReadErrMode >= 1); DrMdoCtlSeamAll::callRenderSeamAll tests bit 3
    unsigned int m_seamFlags;
    unsigned char pad_C80[0x98];
    // 0xD18: a bit per _wkSeamReadCall::m_readIdx, cleared when that stream is in (DrMdoCtlSeamRead::wait*Stream)
    unsigned short m_readWaitBits;
};
}  // namespace ml

#endif
