#ifndef ML_DRPIXLPOSTOBJTSSAO_H
#define ML_DRPIXLPOSTOBJTSSAO_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// a post-process object (screen-space ambient occlusion): ten DrPixlRenderTargets at 0x20..0x68. The field names are
// not the original's (they follow resetColorBuff's DrPixlMemMan slots and formats).
class DrPixlPostObjTSSAO : public DrPixlPostObj {
public:
    // the blur pass directions (the enumerator names are not the original's: render_beforeTemporal passes 1, then 2)
    enum BlurAxis {
        BLUR_AXIS_1 = 1,
        BLUR_AXIS_2 = 2,
    };

    DrPixlPostObjTSSAO(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjTSSAO();
    void resetColorBuff(bool force);
    void update();
    void render_beforeTemporal();
    void passQuaterNormal();
    void passSSAO();
    void passTemporalFiltering();
    void render_afterTemporal();
    void passUpScaleToMiddle();
    void passBlur_Sub(BlurAxis axis, float blur, DrPixlRenderTarget* src, DrPixlRenderTarget* dst, bool);

    unsigned int m_flags;  // 0x18, resetColorBuff sets bit 1 when it rebuilds the double buffers
    unsigned char pad_1c[0x4];
    DrPixlRenderTarget* m_workBuff;  // 0x20, the first the constructor makes
    DrPixlRenderTarget* m_ssaoBuff[2];  // 0x28, by DrMan::s_nDblIdx
    DrPixlRenderTarget* m_blurBuffA;  // 0x38
    DrPixlRenderTarget* m_outBuff;  // 0x40, DrPixlFormat::s_SSAOOutFormat
    DrPixlRenderTarget* m_blurBuffB;  // 0x48
    DrPixlRenderTarget* m_historyBuff[2];  // 0x50, by DrMan::s_nDblIdx
    DrPixlRenderTarget* m_extraBuff[2];  // 0x60, the constructor clears them
    unsigned int m_frame;  // 0x70, resetColorBuff clears it
};
}  // namespace ml

#endif
