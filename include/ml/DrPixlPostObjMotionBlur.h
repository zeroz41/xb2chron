#ifndef ML_DRPIXLPOSTOBJMOTIONBLUR_H
#define ML_DRPIXLPOSTOBJMOTIONBLUR_H

#include "ml/DrPixlPostObj.h"
#include "grlib/CGLibDblUniformBlock.h"

namespace ml { class DrPixlRenderTarget; }

namespace ml {
// the motion blur pass (no table: the destructor is the only one, D1). Only what render and the destructor use is
// declared; the field names are not the original's.
class DrPixlPostObjMotionBlur : public DrPixlPostObj {
public:
    ~DrPixlPostObjMotionBlur();
    void calcBludBuffColorBuff();
    void update();
    void render();
    void calcBlurWork();
    void calcVelocityBlur();
    void renderCalcBlur();
    void lastRender();

    unsigned char pad_18[0x8];
    // 0x20, calcBludBuffColorBuff sets it up at 0.4 of the view size with DrPixlFormat::s_BlurOutFormat
    DrPixlRenderTarget* m_blurOut;
    // 0x28, calcBludBuffColorBuff sets both up at a quarter of the view size with DrPixlFormat::s_BlurVelFormat;
    // render invalidates [0] after DrMan::blurCallBackRender
    DrPixlRenderTarget* m_blurVel[2];
    grlib::CGLibDblUniformBlock m_uniform;  // 0x38
};
}  // namespace ml

#endif
