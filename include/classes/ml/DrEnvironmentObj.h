#ifndef CLASSES_ML_DRENVIRONMENTOBJ_H
#define CLASSES_ML_DRENVIRONMENTOBJ_H

#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7B1F8
class DrEnvironmentObj {
public:
    enum {
        FLAG_RELEASE = 0x40000000,
    };

    virtual ~DrEnvironmentObj() {}  // slot 0
    virtual void resourceInit() {}  // slot 2
    virtual void update() {}  // slot 3
    virtual void renderLgt() {}  // slot 4
    virtual void debugRenderLgt() {}  // slot 5
    virtual void debugRenderLgt2D() {}  // slot 6
    virtual void setFrame(float) = 0;  // slot 7
    virtual void changeMemCall(void const*) = 0;  // slot 8

    float getFrame() const;
    float getMaxFrame() const;
    float getFrameSpd();
    void setFrameSpd(float spd);
    void release();

    // ScnObjLightDrSys::getOffsetPos / getGroup read these (the names are not the original's)
    unsigned char pad_8[0x68];
    mm::Vec3 m_offsetPos;  // 0x70
    float m_frame;  // 0x80, getFrame (the name is not the original's)
    float m_frameSpd;  // 0x84, getFrameSpd / setFrameSpd (the name is not the original's)
    float m_maxFrame;  // 0x88, getMaxFrame (the name is not the original's)
    // 0x8C, release sets FLAG_RELEASE shifted by DrMan::s_nDblStockIdx (the names are not the original's)
    unsigned int m_flags;
    int m_group;  // 0x90
};
}  // namespace ml

#endif
