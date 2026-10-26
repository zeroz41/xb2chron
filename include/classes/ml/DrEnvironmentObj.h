#ifndef CLASSES_ML_DRENVIRONMENTOBJ_H
#define CLASSES_ML_DRENVIRONMENTOBJ_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7B1F8
class DrEnvironmentObj {
public:
    enum {
        // ScnObjLightDrSys::apply's (the names are not the original's)
        FLAG_HIDE = 0x1,          // the light is not displayed
        FLAG_BIT2 = 0x4,          // apply clears it when the light has no offset matrix
        FLAG_OFS_MATRIX = 0x8,    // m_ofsMatrix holds the light's world matrix
        FLAG_DEBUG_DISP_2D = 0x100000,  // setDeugDisp2D
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
    // ScnObjLightDrSys::apply's copy of the light's world matrix (inline: the name is not the original's)
    void setOfsMatrix(const mm::Mat44& mat) { m_ofsMatrix = mat; }

    // ScnObjLightDrSys::getOffsetPos / getGroup read these (the names are not the original's)
    unsigned char pad_8[0x28];
    // 0x30, ScnObjLightDrSys::apply copies the light's world matrix here (the name is not the original's)
    mm::Mat44 m_ofsMatrix;
    mm::Vec3 m_offsetPos;  // 0x70
    float m_frame;  // 0x80, getFrame (the name is not the original's)
    float m_frameSpd;  // 0x84, getFrameSpd / setFrameSpd (the name is not the original's)
    float m_maxFrame;  // 0x88, getMaxFrame (the name is not the original's)
    // 0x8C, release sets FLAG_RELEASE shifted by DrMan::s_nDblStockIdx (the names are not the original's)
    unsigned int m_flags;
    int m_group;  // 0x90
    unsigned char pad_94[0x1A8];
    // 0x23C, ScnObjLightDrSys::setFromCaptureTool sets 2 (the name is not the original's)
    unsigned char m_captureMode;
};
}  // namespace ml

#endif
