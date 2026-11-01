#ifndef ML_DRPIXLPOSTOBJMOTIONBLUR2_H
#define ML_DRPIXLPOSTOBJMOTIONBLUR2_H

#include "ml/DrPixlPostObj.h"

namespace ml {

// a motion blur post object. Its fields are mostly not declared yet (the constructor makes six DrPixlRenderTargets at
// 0x20..0x48 and two CGLibVtxVertex at 0x50/0x58).
class DrPixlPostObjMotionBlur2 : public DrPixlPostObj {
public:
    DrPixlPostObjMotionBlur2(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjMotionBlur2();
    void resetColorBuff();
    void update();
    void calcBludBuffColorBuff();
    void render();
    void calcBlurWork();
    void calcVelocityBlur();
    void calcMaxVelocityPerTile();
    void calcBlurMask();
    void renderCalcBlur();
    void lastRender();

    unsigned char pad_18[0x4C];
    bool m_blurOn;  // 0x64: render runs renderCalcBlur and lastRender while it is set (the name is not the original's)
};

}  // namespace ml

#endif
