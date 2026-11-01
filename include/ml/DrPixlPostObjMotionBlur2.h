#ifndef ML_DRPIXLPOSTOBJMOTIONBLUR2_H
#define ML_DRPIXLPOSTOBJMOTIONBLUR2_H

#include "ml/DrPixlPostObj.h"

namespace grlib { class CGLibVtxVertex; }

namespace ml {

// a motion blur post object: six DrPixlRenderTargets at 0x20..0x48 and two CGLibVtxVertex at 0x50/0x58, all made by
// the constructor. The field names are not the original's (they follow calcBludBuffColorBuff's formats).
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

    unsigned long m_state;  // 0x18, the constructor clears it after calcBludBuffColorBuff
    DrPixlRenderTarget* m_blurOut;  // 0x20, DrPixlFormat::s_BlurOutFormat
    DrPixlRenderTarget* m_velocityBuff[2];  // 0x28, DrPixlFormat::s_BlurVelFormat
    DrPixlRenderTarget* m_workOutA;  // 0x38, DrPixlFormat::s_BlurOutFormat
    DrPixlRenderTarget* m_workOutB;  // 0x40, DrPixlFormat::s_BlurOutFormat
    DrPixlRenderTarget* m_maskBuff;  // 0x48, DrPixlFormat::s_BlurMaskFormat
    grlib::CGLibVtxVertex* m_vertex[2];  // 0x50, calcBludBuffColorBuff flips m_vertexIdx and rebuilds that one
    unsigned int m_vertexIdx;  // 0x60
    bool m_blurOn;  // 0x64: render runs renderCalcBlur and lastRender while it is set (the name is not the original's)
};

}  // namespace ml

#endif
