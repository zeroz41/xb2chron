#ifndef ML_DRPIXLPOSTOBJTONEMAP_H
#define ML_DRPIXLPOSTOBJTONEMAP_H

#include "ml/DrPixlPostObj.h"
#include "grlib/CGLibOneUniformBlock.h"

namespace ml {
// DrPixlPostMan::m_toneMap (0xC0 bytes). Only what DrPixlPostMan uses is declared; the field names are not the
// original's.
class DrPixlPostObjToneMap : public DrPixlPostObj {
public:
    DrPixlPostObjToneMap(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjToneMap();
    void updateByRenderTarget();
    void updateByCompute();
    void fastRender();
    void createSclDow();

    // 0x18: the constructor sizes them 128, 64, 32, 16, 8 and 4 pixels with DrPixlFormat::s_ToneMapFormat (name
    // inferred)
    DrPixlRenderTarget* m_sclDown[6];
    grlib::CGLibOneUniformBlock m_uniform[2];  // 0x48, the constructor sets both up with 16 bytes (name inferred)
    // 0x98: 1x1 TEXTYPE_HALF_X1 targets; the constructor points 0xA8 at [0] (name inferred)
    DrPixlRenderTarget* m_lumBuff[2];
    unsigned char pad_A8[0xC];
    unsigned char m_flags;  // 0xB4, DrPixlPostMan::update runs updateByCompute while bit 4 is set
    unsigned char pad_B5[0xB];
};
}  // namespace ml

#endif
