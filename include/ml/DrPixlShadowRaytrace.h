#ifndef ML_DRPIXLSHADOWRAYTRACE_H
#define ML_DRPIXLSHADOWRAYTRACE_H

#include "ml/DrPixlRenderTarget.h"

namespace ml { class DrMan; }

namespace ml {

// the ray-traced screen-space shadow. The constructor keeps its DrMan and makes five DrPixlRenderTargets at
// 0x18..0x38; the field names are not the original's.
class DrPixlShadowRaytrace {
public:
    // the blur pass directions (the enumerator names are not the original's: render_beforeTemporal passes 1, then 2)
    enum BlurAxis {
        BLUR_AXIS_1 = 1,
        BLUR_AXIS_2 = 2,
    };

    DrPixlShadowRaytrace(DrMan* drMan);
    ~DrPixlShadowRaytrace();
    void render_beforeTemporal();
    void raytracePass();
    void blurPassSub(BlurAxis axis, DrPixlRenderTarget* src, DrPixlRenderTarget* dst);
    void temporalFiltering();
    // the shadow texture of the current frame's temporal buffer (DrPixlDeferred and the light renderers read it)
    grlib::CGLibTextureBuffer* getScreenSpaceShadow() const;
    // the temporal buffer of the current frame (s_nDblIdx) and of the stocked one (s_nDblStockIdx)
    DrPixlRenderTarget* getTemporalOutputTexture();
    DrPixlRenderTarget* getTemporalHistoryTexture();

    DrMan* m_drMan;  // 0x0
    unsigned char pad_8[0x8];
    bool m_blurOn;  // 0x10, the constructor sets it; render_beforeTemporal blurs while it is set
    unsigned char pad_11[0x7];
    DrPixlRenderTarget* m_buffFirst;  // 0x18, the first the constructor makes
    DrPixlRenderTarget* m_temporalBuff[2];  // 0x20
    DrPixlRenderTarget* m_buffFourth;  // 0x30
    DrPixlRenderTarget* m_buffLast;  // 0x38, the last the constructor makes
};

}  // namespace ml

#endif
