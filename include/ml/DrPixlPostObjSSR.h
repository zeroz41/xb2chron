#ifndef ML_DRPIXLPOSTOBJSSR_H
#define ML_DRPIXLPOSTOBJSSR_H

#include "ml/DrPixlPostObj.h"
#include "ml/DrPixlRenderTarget.h"

namespace ml {

// the screen-space reflection post object. The constructor makes four DrPixlRenderTargets at 0x20..0x38;
// the field names are not the original's.
class DrPixlPostObjSSR : public DrPixlPostObj {
public:
    DrPixlPostObjSSR(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    void resetColorBuff();
    ~DrPixlPostObjSSR();
    void update();
    void render();
    void raymarch2();
    void temporalSuperSampling2();
    // the current frame's reflection buffer (DrShdLgtGlobalIBL::renderByLinkList reads it)
    DrPixlRenderTarget* getReflectionTexture() const;
    // the buffer scales (DrPixlMan reads them too): m_buffFirst/m_buffLast and m_reflectionBuff
    static const float RAYMARCH_BUFFER_SCALE;
    static const float TEMPORAL_BUFFER_SCALE;

    unsigned int m_flags;  // 0x18, the constructor clears it
    unsigned char pad_1c[0x4];
    DrPixlRenderTarget* m_buffFirst;  // 0x20, the first the constructor makes
    DrPixlRenderTarget* m_reflectionBuff[2];  // 0x28, by DrMan::s_nDblIdx
    DrPixlRenderTarget* m_buffLast;  // 0x38, the last the constructor makes
};

}  // namespace ml

#endif
