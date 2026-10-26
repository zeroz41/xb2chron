#ifndef FW_UPDATESTATE_H
#define FW_UPDATESTATE_H

namespace fw {
// what the launcher hands the framework's frame functions (beginFrame, endFrame, tail); only its first byte is read
class UpdateState {
public:
    // set: beginFrame stops time (speeds and deltas 0), tail skips the updates (the name is not the original's)
    bool m_pause;
};
}  // namespace fw

#endif
