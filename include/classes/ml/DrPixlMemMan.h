#ifndef CLASSES_ML_DRPIXLMEMMAN_H
#define CLASSES_ML_DRPIXLMEMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/DrMan.h"

namespace ml { class DrPixlMemMan; }

namespace ml {
// table 0x7100B7CDE0
class DrPixlMemMan : public ::mm::mtl::PtrSingleton< ::ml::DrPixlMemMan> {
public:
    DrPixlMemMan();
    virtual ~DrPixlMemMan();  // slot 0
    void setupMemBuff();

    // one record per view of the memory pool offsets setupMemBuff lays out for the render targets (the type and
    // field names are not the original's); the users index it by DrMan::getIns()->m_postParmIdx (and the double-buffer ones by an unsigned index)
    struct ViewMem {
        unsigned char pad_0[0x98];
        // 0x98: DrPixlPostObjTMAA::resetColorBuff's targets: [i * 2] m_colorBuff[i], [i * 2 + 1] m_bloomBuff[i]
        unsigned int m_tmaaOfs[4];
        unsigned char pad_A8[0x40];
        // 0xE8: DrPixlDeferred's shadow targets: [0] the single one, [1 + i] m_shadowTargetDbl[i]
        unsigned int m_dirShadowOfs[3];
        unsigned char pad_F4[0x5C];
        // 0x150: DrPixlPostObjVolume::calcColorBuff's m_volumeBuff[0..2] (name inferred)
        unsigned int m_volumeOfs[3];
        unsigned char pad_15C[0x30];
        // 0x18C: DrPixlPostObjSSR::resetColorBuff's targets: [i] m_reflectionBuff[i], [2] m_buffFirst, [3] m_buffLast
        unsigned int m_ssrOfs[4];
        unsigned char pad_19C[0x18];
        // 0x1B4: DrPixlPostObjTSSAO::resetColorBuff's targets: [i] m_ssaoBuff[i], [2 + i] m_historyBuff[i],
        // [4] m_workBuff, [5] m_blurBuffA, [6] m_blurBuffB, [7] m_outBuff
        unsigned int m_ssaoOfs[8];
        unsigned char pad_1D4[0x3C];
    };
    unsigned char pad_8[0x8];
    ViewMem m_viewMem[2];  // 0x10
    unsigned int m_captureOfs;  // 0x430, DrPixlMan::resetColorBuff's capture target (name inferred)

    // the current view's offset i of a post object's targets (m_viewMem[DrMan::getIns()->m_postParmIdx]). Inline in
    // the original: its callers load the instance, then compute i (unsigned), then call DrMan::getIns(). The names are
    // not the original's.
    unsigned int getTMAAOfs(unsigned int i) const { return m_viewMem[DrMan::getIns()->m_postParmIdx].m_tmaaOfs[i]; }
    unsigned int getSSROfs(unsigned int i) const { return m_viewMem[DrMan::getIns()->m_postParmIdx].m_ssrOfs[i]; }
    unsigned int getSSAOOfs(unsigned int i) const { return m_viewMem[DrMan::getIns()->m_postParmIdx].m_ssaoOfs[i]; }
};
}  // namespace ml

#endif
