#ifndef ML_DRPIXLPOSTOBJTMAA_H
#define ML_DRPIXLPOSTOBJTMAA_H

#include "ml/DrPixlPostObj.h"
#include "ml/DrPixlRenderTarget.h"

namespace ml {

// the temporal anti-aliasing post object. The constructor makes four DrPixlRenderTargets at 0x20..0x38; the field
// names are not the original's.
class DrPixlPostObjTMAA : public DrPixlPostObj {
public:
    // the enumerator names are not the original's (renderSharpness passes 1, 2 and 4)
    enum SHARPNESS_TYPE {
        SHARPNESS_TYPE_1 = 1,
        SHARPNESS_TYPE_2 = 2,
        SHARPNESS_TYPE_4 = 4,
    };

    DrPixlPostObjTMAA(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjTMAA();
    void resetColorBuff();
    void render();
    void renderTMAA();
    // the current frame's bloom buffer (DrPixlPostObjBloom::calculateDownScaleImpl reads it)
    DrPixlRenderTarget* getBloomTexture();
    void renderSharpness();
    void renderSharpnessImpl(SHARPNESS_TYPE type);

    unsigned int m_flags;  // 0x18, the constructor clears it; renderSharpness tests 4
    unsigned char pad_1c[0x4];
    DrPixlRenderTarget* m_colorBuff[2];  // 0x20, made and deleted in turn with m_bloomBuff
    DrPixlRenderTarget* m_bloomBuff[2];  // 0x30, by DrMan::s_nDblIdx
};

}  // namespace ml

#endif
