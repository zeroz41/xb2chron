#ifndef ML_DRPIXLPOSTOBJBLOOM_H
#define ML_DRPIXLPOSTOBJBLOOM_H

#include "ml/DrPixlPostObj.h"

namespace ml { class DrPixlRenderTarget; }

namespace ml {
// the bloom pass (no table). Only what the defined functions use is declared; the field and enumerator names are not
// the original's.
class DrPixlPostObjBloom : public DrPixlPostObj {
public:
    enum DownScaleType { DownScale_Normal = 0, DownScale_2PassFirst = 1, DownScale_2PassSecond = 2 };

    static float BLOOMTEX_SCALE;

    DrPixlPostObjBloom(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjBloom() { releaseBloomTexture(); }
    void resetColorBuff(bool all);
    void releaseBloomTexture();
    void releaseColorBuff(bool all);
    void createBloomTexture(float width, float height, bool all);
    void calcRender();
    void calculateDownScaleImpl(DownScaleType type);
    void calculateGaussBlur();
    void calculateGaussBlurImplPS();
    void calculateFlareBuff();
    void calculateLensFlare();

    // 0x18, the constructor creates them; createBloomTexture sets them up with DrPixlFormat::s_BloomFormat.
    // calculateGaussBlur scales [3] into m_compositeBuff
    DrPixlRenderTarget* m_bloomBuff[4];
    // 0x38 and 0x60: releaseColorBuff frees them pairwise; calculateGaussBlur adds m_bloomBuff[3] into
    // m_scaleBuff[2]
    DrPixlRenderTarget* m_scaleBuff[5];
    DrPixlRenderTarget* m_scaleWorkBuff[5];
    unsigned char pad_88[0x8];
    unsigned int m_perFrame;  // 0x90, DrPixlPostMan::update clears it each frame (name inferred)
    unsigned int m_flags;  // 0x94, calcRender sets bit 0 after rebuilding the buffers
    // 0x98, by DrMan::s_nDblIdx: releaseColorBuff frees both when all or DrPixlPostParm::m_iblColorMode is 3
    DrPixlRenderTarget* m_dblBuff[2];
    int m_bloomType;  // 0xA8, the DrPixlPostParm::m_bloomType the buffers were made for
};
}  // namespace ml

#endif
