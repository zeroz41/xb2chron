#ifndef ML_DRPIXLPOSTOBJRAINDROP_H
#define ML_DRPIXLPOSTOBJRAINDROP_H

#include "ml/DrPixlPostObj.h"

namespace ml { class DrPixlRenderTarget; }

namespace ml {
// a post-process object: rain drops on the screen (the field names are not the original's)
class DrPixlPostObjRainDrop : public DrPixlPostObj {
public:
    DrPixlPostObjRainDrop(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjRainDrop();
    void resetColorBuff();
    void update();
    void render();
    void requestUseLoadedDepth();

    unsigned int m_flags;          // 0x18: requestUseLoadedDepth clears bit 2
    unsigned char pad_1C[0x4];
    DrPixlRenderTarget* m_target;  // 0x20: 0x3D0 bytes, made by the constructor
    float m_param0;                // 0x28: 0.0 at first
    float m_param1;                // 0x2C: 0.1 at first
    float m_param2;                // 0x30: 0.2 at first
};
}  // namespace ml

#endif
