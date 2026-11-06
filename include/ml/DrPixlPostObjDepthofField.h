#ifndef ML_DRPIXLPOSTOBJDEPTHOFFIELD_H
#define ML_DRPIXLPOSTOBJDEPTHOFFIELD_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// the depth-of-field post object DrPixlPostMan::setDepthField creates (0xC0 bytes); its fields are not declared yet
class DrPixlPostObjDepthofField : public DrPixlPostObj {
public:
    DrPixlPostObjDepthofField(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjDepthofField();
    void resetColorBuff();
    void update();
    void renderDepthSample();
    void renderDepthAllSample();
    void renderDofScaleDown();
    void renderDofPass();
    void renderCalc();

    // 0x18-0x48: the constructor creates the seven; resetColorBuff sets them up with these DrPixlFormat formats
    // (the names are not the original's)
    DrPixlRenderTarget* m_calcBuff[3];  // 0x18: s_DofCalcFormat
    DrPixlRenderTarget* m_lastBuff;     // 0x30: s_DofLastFormat
    DrPixlRenderTarget* m_autoBuff;     // 0x38: s_DofAutoFormat
    DrPixlRenderTarget* m_float2Buff;   // 0x40: the constructor gives it DrAPCache::TEXTYPE_FLOAT_X2
    DrPixlRenderTarget* m_calcSampBuff; // 0x48: s_DofCalcSampFormat
    int m_pixlLv;      // 0x50: update copies the post parameter's level here (name inferred)
    float m_pixlScale; // 0x54: 1, 2 or 4 by m_pixlLv (name inferred)
    bool m_needClear;  // 0x58: the constructor sets it; renderDepthAllSample clears m_float2Buff once (name inferred)
    bool m_filterOn;   // 0x59: update sets it from DrPixlPostParm::m_colorFilterDof (name inferred)
    unsigned char pad_5a[0x2];
    // 0x5C: twelve sample positions; renderDepthSample copies them into its "sapl" vectors (name inferred)
    float m_samplePos[12][2];
    unsigned char pad_bc[0x4];
};
}  // namespace ml

#endif
