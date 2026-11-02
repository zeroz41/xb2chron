#ifndef ML_DRPIXLPOSTOBJDEPTHOFFIELD_H
#define ML_DRPIXLPOSTOBJDEPTHOFFIELD_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// the depth-of-field post object DrPixlPostMan::setDepthField creates (0xC0 bytes); its fields are not declared yet
class DrPixlPostObjDepthofField : public DrPixlPostObj {
public:
    DrPixlPostObjDepthofField(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjDepthofField();

    // 0x18-0x48: the constructor creates the seven; resetColorBuff sets them up with these DrPixlFormat formats
    // (the names are not the original's)
    DrPixlRenderTarget* m_calcBuff[3];  // 0x18: s_DofCalcFormat
    DrPixlRenderTarget* m_lastBuff;     // 0x30: s_DofLastFormat
    DrPixlRenderTarget* m_autoBuff;     // 0x38: s_DofAutoFormat
    DrPixlRenderTarget* m_float2Buff;   // 0x40: the constructor gives it DrAPCache::TEXTYPE_FLOAT_X2
    DrPixlRenderTarget* m_calcSampBuff; // 0x48: s_DofCalcSampFormat
    unsigned char pad_50[0x70];
};
}  // namespace ml

#endif
