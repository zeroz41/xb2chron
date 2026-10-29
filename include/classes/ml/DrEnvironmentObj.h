#ifndef CLASSES_ML_DRENVIRONMENTOBJ_H
#define CLASSES_ML_DRENVIRONMENTOBJ_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// a 16-byte record of the light resource: DrEnvironmentObjLgt::setFrame clamps the frame to its m_endFrame (the
// type and field names are not the original's)
struct EnvFrameRange {
    unsigned char pad_0[0xC];
    float m_endFrame;  // 0xC
};

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
    unsigned char pad_94[0x4C];
    // setFrame clamps the frame to each range's end into m_rangeFrame (the names are not the original's)
    const EnvFrameRange* m_frameRange;  // 0xE0
    unsigned char pad_e8[0x20];
    int m_rangeNum;  // 0x108
    unsigned char pad_10c[0x4];
    float* m_rangeFrame;  // 0x110
    unsigned char pad_118[0x38];
    // DrEnvironmentObjLgt's (DrEnvironmentMan::createObj stores them in its inlined constructor; the names are
    // not the original's)
    int m_lgtArg;  // 0x150, DrEnvironmentMan's m_lgtArg; resourceInit passes it to setupLgt
    unsigned char pad_154[0x8C];
    int m_renderLgtNum;  // 0x1E0, renderLgt's light count
    unsigned char pad_1e4[0x18];
    int m_lgtNum;  // 0x1FC, setupLgt reads it from the resource; debugRenderLgt2D's light count
    unsigned char pad_200[0x3C];
    // 0x23C, ScnObjLightDrSys::setFromCaptureTool sets 2 (the name is not the original's)
    unsigned char m_captureMode;
};
}  // namespace ml

#endif
