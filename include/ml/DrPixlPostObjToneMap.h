#ifndef ML_DRPIXLPOSTOBJTONEMAP_H
#define ML_DRPIXLPOSTOBJTONEMAP_H

#include "ml/DrPixlPostObj.h"

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

    unsigned char pad_18[0x9C];
    unsigned char m_flags;  // 0xB4, DrPixlPostMan::update runs updateByCompute while bit 4 is set
    unsigned char pad_B5[0xB];
};
}  // namespace ml

#endif
