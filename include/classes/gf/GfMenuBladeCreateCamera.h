#ifndef CLASSES_GF_GFMENUBLADECREATECAMERA_H
#define CLASSES_GF_GFMENUBLADECREATECAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5FFE8
class GfMenuBladeCreateCamera : public ::fw::Camera {
public:
    // 1.0.0 has it out of line (0x71003FDD00); 3.0.1 inlines it into GfMenuObjBladeCreate's constructor
    GfMenuBladeCreateCamera()
        : ::fw::Camera(::fw::CAMERA_PRIO(0x37)), m_rotTime(0.0f), m_rotTimer(0.0f), m_rotOffsetY(0.0f), m_rotY(0.0f),
          m_rotYEnd(0.0f), m_rotYStart(0.0f), m_rotDir(0) {}
    virtual ~GfMenuBladeCreateCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 8
    static mm::mtl::RTTI m_rtti;

    // 1.0.0 has it out of line; 3.0.1 inlines it (DriverSelectListener::reciveEvent): turns to y over time, wrapped
    // by 2 pi toward the direction (0 or 1)
    void setRotY(float y, unsigned int dir, float time) {
        float rotY = m_rotY;
        if (dir == 0 && y - rotY > 0.0f) {
            y -= 6.2831855f;
        } else if (dir == 1 && y - rotY < 0.0f) {
            if (rotY + y < 6.2831855f) {
                y = 6.2831855f - y;
            } else {
                y += 6.2831855f;
            }
        }
        m_rotYEnd = y;
        m_rotDir = dir;
        m_rotTime = time;
        m_rotTimer = 0.0f;
        m_rotYStart = rotY;
    }

    // field names are not the original's: 1.0.0's setDefault/getDefault (0xB0, 0xC0), getCurrent (0xD0, 0xE0),
    // setRotOffsetY (0xF8) and setRotY(float y, unsigned int dir, float time) (0xF0..0x108) use them
    mm::Vec3 m_defaultEye;
    mm::Vec3 m_defaultTarget;
    mm::Vec3 m_currentEye;
    mm::Vec3 m_currentTarget;
    float m_rotTime;     // setRotY's time (0: at once)
    float m_rotTimer;    // setRotY clears it
    float m_rotOffsetY;
    float m_rotY;        // where the rotation starts (setRotY sets it to the end at once when the time is 0)
    float m_rotYEnd;     // setRotY's y, wrapped by 2 pi toward the direction
    float m_rotYStart;   // m_rotY when setRotY was called
    unsigned int m_rotDir;  // setRotY's direction (0 or 1)
};
}  // namespace gf

#endif
