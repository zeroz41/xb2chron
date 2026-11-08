#ifndef CLASSES_ML_DRPIXLMEMMAN_H
#define CLASSES_ML_DRPIXLMEMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DrPixlMemMan; }

namespace ml {
// table 0x7100B7CDE0
class DrPixlMemMan : public ::mm::mtl::PtrSingleton< ::ml::DrPixlMemMan> {
public:
    DrPixlMemMan();
    virtual ~DrPixlMemMan();  // slot 0
    void setupMemBuff();

    // one record per view of the memory pool offsets setupMemBuff lays out for the render targets (the type and
    // field names are not the original's); the users index it by DrMan::getIns()->m_postParmIdx
    struct ViewMem {
        unsigned char pad_0[0xE8];
        // 0xE8: DrPixlDeferred's shadow targets: [0] the single one, [1 + i] m_shadowTargetDbl[i]
        unsigned int m_dirShadowOfs[3];
        unsigned char pad_F4[0x11C];
    };
    unsigned char pad_8[0x8];
    ViewMem m_viewMem[2];  // 0x10
    unsigned int m_captureOfs;  // 0x430, DrPixlMan::resetColorBuff's capture target (name inferred)
};
}  // namespace ml

#endif
