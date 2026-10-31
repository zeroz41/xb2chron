#ifndef ML_DRPIXLPOSTOBJBLOOM_H
#define ML_DRPIXLPOSTOBJBLOOM_H

#include "ml/DrPixlPostObj.h"

namespace ml { class DrPixlRenderTarget; }

namespace ml {
// the bloom pass (no table). Only what calculateGaussBlur uses is declared; the field names are not the original's.
class DrPixlPostObjBloom : public DrPixlPostObj {
public:
    void calculateGaussBlur();
    void calculateGaussBlurImplPS();
    void calculateFlareBuff();
    void calculateLensFlare();

    // 0x18, the constructor creates them; createBloomTexture sets them up with DrPixlFormat::s_BloomFormat.
    // calculateGaussBlur scales [3] into m_compositeBuff
    DrPixlRenderTarget* m_bloomBuff[4];
    unsigned char pad_38[0x10];
    DrPixlRenderTarget* m_compositeBuff;  // 0x48, calculateGaussBlur adds m_bloomBuff[3] into it
};
}  // namespace ml

#endif
