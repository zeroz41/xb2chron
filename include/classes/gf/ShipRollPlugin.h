#ifndef CLASSES_GF_SHIPROLLPLUGIN_H
#define CLASSES_GF_SHIPROLLPLUGIN_H

#include "classes/fw/CameraPlugin.h"

namespace fw { class Camera; }

namespace gf {
// table 0x7100B45EE8: rocks the player camera like a ship, rolling it and raising and lowering it, from the
// player camera's ship_* parameters. setEnable makes the one plugin and pushes it onto the camera layer.
// Field names are not the original's.
class ShipRollPlugin : public ::fw::CameraPlugin {
public:
    // a swing: back and forth, or along a sine (the names are not the original's)
    struct Swing {
        Swing() : m_angle(0.0f), m_amplitude(0.0f), m_back(false), m_enable(false) {}
        float m_angle;      // degrees along the sine (ship_curve)
        float m_amplitude;  // degrees
        bool m_back;        // sweeping towards the negative side (not ship_curve)
        bool m_enable;      // setEnable's (1.0.0's isRollEnable and isPitchEnable read them)
    };

    // out of line in 1.0.0, inline in setEnable in 3.0.1
    ShipRollPlugin() : m_roll(0.0f), m_pitch(0.0f) {}
    virtual ~ShipRollPlugin();  // slot 0
    virtual void update(fw::Camera*);  // slot 2
    static void setEnable(bool roll, bool pitch);

    float m_roll;   // radians: the camera's roll
    float m_pitch;  // added to the eye's and the target's height
    Swing m_rollSwing;
    Swing m_pitchSwing;
};
}  // namespace gf

#endif
