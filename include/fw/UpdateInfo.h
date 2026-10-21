#ifndef FW_UPDATEINFO_H
#define FW_UPDATEINFO_H

namespace fw {

// what an update is handed for one frame: three floats, passed by value in s0-s2
// (GfFieldMapSe::update forwards it so); Framework::beginFrame fills its own
class UpdateInfo {
public:
    float m_frameTime;  // one frame at the framework's frame rate: 1 / the rate
    float m_deltaTime;  // the frame's time step: m_frameTime scaled by m_speed
    float m_speed;      // the update speed (Framework::setUpdateSpeed, per layer setLayerUpdateSpeed)
};

}  // namespace fw

#endif
