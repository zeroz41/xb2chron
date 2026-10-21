#ifndef FW_UPDATEINFO_H
#define FW_UPDATEINFO_H

namespace fw {

// what an update passes down to the objects it updates
class UpdateInfo {
public:
    unsigned char pad_0[0x4];
    float m_deltaTime;  // the time this update advances: timers add it each update
};

}  // namespace fw

#endif
