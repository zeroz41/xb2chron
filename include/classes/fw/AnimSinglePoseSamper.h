#ifndef CLASSES_FW_ANIMSINGLEPOSESAMPER_H
#define CLASSES_FW_ANIMSINGLEPOSESAMPER_H

#include "mm/mtl/IntrusiveList.h"

namespace anm { class Control; }
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }

namespace fw {
// what AnimationManager::addPoseSampler/removePoseSampler keep (AnimSinglePoseSamper is one, at its start)
class AnimPoseSamplerInterface {
public:
    virtual ~AnimPoseSamplerInterface() {}
    virtual void samplePose() = 0;
};

// table 0x7100B40CA8: samples one anm::Control into one anm::Pose
class AnimSinglePoseSamper : public ::fw::AnimPoseSamplerInterface {
public:
    AnimSinglePoseSamper();
    virtual ~AnimSinglePoseSamper();  // slot 0
    virtual void samplePose();  // slot 2
    // binds the control and the pose when they have as many bones, and the extra truck buffer's track
    void bind(anm::Control* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra);
    void unbind();
    // whether a control and a pose are bound (inline: the name is not the original's)
    bool isBind() const { return m_control != nullptr && m_pose != nullptr; }

    mm::mtl::IntrusiveListNodeBase m_node;  // the constructor links it to itself
    anm::Control* m_control;
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extra;
    unsigned short m_extraIndex;  // 0xFFFF until bind finds the extra track (the name is not the original's)
    // samplePose hands it to anm::Util::samplePoseSmartFromControl as its bool; true until set (the name is not
    // the original's)
    bool m_sampleFlag;
};
}  // namespace fw

#endif
