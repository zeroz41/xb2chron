#ifndef CLASSES_ML_DRENVIRONMENTOBJ_H
#define CLASSES_ML_DRENVIRONMENTOBJ_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrFogMan;
class DrLightMan;
class DrMan;

// a 16-byte record of the light resource: DrEnvironmentObjLgt::setFrame clamps the frame to its m_endFrame (the
// type and field names are not the original's)
struct EnvFrameRange {
    unsigned char pad_0[0xC];
    float m_endFrame;  // 0xC
};

// the weather blend state of a light object (0x30 bytes at DrEnvironmentObj+0xA8); DrEnvironmentObjLgt::update passes
// it to setWeatherNum (the field names are not the original's)
class DrEnvironmentTime {
public:
    void setWeatherNum(DrMan* drMan, bool changed, int);

    // DrEnvironmentObjLgt's constructor clears 0x0..0x17; no reader of 0x0..0x13 found yet
    unsigned long m_reserve[2];  // 0x0
    int m_reserve2;              // 0x10
    int m_hour;                  // 0x14, DrEnvironmentObjLgt::update copies DrMan's +0x1CAC
    float m_blendRate;        // 0x18, setWeatherNum stores 1 / m_weatherFrame
    float m_blendRate2;       // 0x1C, setWeatherNum stores the same value
    float m_weatherFrame;     // 0x20, setWeatherNum counts it down by DrMan's frame step
    float m_weatherFrameMax;  // 0x24, DrPixlPostParm::getWeatherFrame
    unsigned char m_flag;     // 0x28
    unsigned char m_weather;  // 0x29, setWeatherNum toggles it to follow DrPixlPostParm's +0x1080
    int m_weatherNum;         // 0x2C, DrPixlPostParm's +0x1084
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

    // 1.0.0 has it out of line (DrEnvironmentObj(DrMan*, DrLightMan*, DrFogMan*), stores up to 0x90 only); 3.0.1
    // inlines it into DrEnvironmentMan::createObj, where the stores 0x98..0x110 come before DrEnvironmentObjLgt's
    // table store, so they are written here (their order reproduces createObj's; the original split between the
    // two constructors is not known)
    DrEnvironmentObj(DrMan* drMan, DrLightMan* lightMan, DrFogMan* fogMan)
        : m_prev(nullptr), m_next(nullptr), m_drMan(drMan), m_lightMan(lightMan), m_fogMan(fogMan) {
        m_offsetPos.x = 0.0f;
        m_offsetPos.y = 0.0f;
        m_offsetPos.z = 0.0f;
        m_frame = 0.0f;
        m_frameSpd = 1.0f;
        m_maxFrame = 0.0f;
        m_flags = 0;
        m_group = 0;
        m_ofsMatrix = mm::Mat44::identity;
        m_texBuf = nullptr;
        m_time.m_weatherFrame = 0.0f;
        m_texBufNum = 0;
        m_time.m_reserve[1] = 0;
        m_time.m_reserve2 = 0;
        m_time.m_hour = 0;
        m_time.m_reserve[0] = 0;
        m_time.m_blendRate = 0.06f;
        m_time.m_blendRate2 = 0.2f;
        m_time.m_weatherNum = 0;
        m_time.m_flag = 0;
        m_time.m_weather = 0;
        m_time.m_weatherFrameMax = 0.0f;
        m_rangeFrame = nullptr;
        m_rangeNum = 0;
    }
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
    // DrEnvironmentMan's object list links (createObj appends at the tail; the names are not the original's)
    DrEnvironmentObj* m_prev;  // 0x8
    DrEnvironmentObj* m_next;  // 0x10
    // the DrEnvironmentMan's managers (DrEnvironmentObjLgt::update reads DrMan's view; names not the original's)
    DrMan* m_drMan;            // 0x18
    DrLightMan* m_lightMan;    // 0x20
    DrFogMan* m_fogMan;        // 0x28
    // 0x30, ScnObjLightDrSys::apply copies the light's world matrix here (the name is not the original's)
    mm::Mat44 m_ofsMatrix;
    mm::Vec3 m_offsetPos;  // 0x70
    float m_frame;  // 0x80, getFrame (the name is not the original's)
    float m_frameSpd;  // 0x84, getFrameSpd / setFrameSpd (the name is not the original's)
    float m_maxFrame;  // 0x88, getMaxFrame (the name is not the original's)
    // 0x8C, release sets FLAG_RELEASE shifted by DrMan::s_nDblStockIdx (the names are not the original's)
    unsigned int m_flags;
    int m_group;  // 0x90
    unsigned char pad_94[0x4];
    // DrEnvironmentObjLgt's (its inlined constructor clears them; the names are not the original's)
    grlib::CGLibTextureBuffer* m_texBuf;  // 0x98, releaseLgt releases each (0x70 bytes apart)
    int m_texBufNum;                      // 0xA0
    unsigned char pad_a4[0x4];
    DrEnvironmentTime m_time;             // 0xA8
    unsigned char pad_d8[0x8];
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
    unsigned char pad_154[0x4];
    const void* m_resource;  // 0x158, createObj's resource
    void* m_work[5];         // 0x160; releaseLgt deallocates m_work[4] (the names are not the original's)
    unsigned char pad_188[0x8];
    void* m_work2;           // 0x190
    unsigned char pad_198[0x18];
    // light object arrays by type and their counts (releaseLgt destroys each element through its table; elements
    // 0x40, 0xA0, 0xC0, 0xF0, 0x250 and 0x68 bytes; the names are not the original's)
    void* m_lgtArray[6];     // 0x1B0
    int m_renderLgtNum;  // 0x1E0, renderLgt's light count
    unsigned char pad_1e4[0x4];
    int m_lgtArrayNum[5];    // 0x1E8
    int m_lgtNum;  // 0x1FC, setupLgt reads it from the resource; debugRenderLgt2D's light count
    int m_lgtArray5Num;      // 0x200, m_lgtArray[5]'s count
    int m_updateReq;         // 0x204, the constructor sets 1, update clears it (the name is not the original's)
    int m_weatherNum;        // 0x208, update compares DrPixlPostParm's +0x107C with it
    unsigned char pad_20c[0x30];
    // 0x23C, ScnObjLightDrSys::setFromCaptureTool sets 2 (the name is not the original's)
    unsigned char m_captureMode;
};
}  // namespace ml

#endif
