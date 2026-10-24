#ifndef CLASSES_FW_ANIMASMPOSESAMPLER_H
#define CLASSES_FW_ANIMASMPOSESAMPLER_H

#include "classes/fw/AnimSinglePoseSamper.h"

namespace anm { class ASMControl; }
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }

namespace fw {
// table 0x7100B40CF8: samples one anm::ASMControl into one anm::Pose (AnimationManager::addPoseSampler keeps it)
class AnimAsmPoseSampler : public ::fw::AnimPoseSamplerInterface {
public:
    AnimAsmPoseSampler();
    virtual ~AnimAsmPoseSampler();  // slot 0
    virtual void samplePose();  // slot 2
    void bind(anm::ASMControl* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra);
    void unbind();
    // whether a control and a pose are bound (inline: the name is not the original's)
    bool isBind() const { return m_control != nullptr && m_pose != nullptr; }

    anm::ASMControl* m_control;
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extra;
    unsigned short m_extraIndex;  // bind's slot index of the extra truck buffer (the name is not the original's)
    // set from the owner's setup info before bind, as AnimSinglePoseSamper's (the name is not the original's)
    bool m_sampleFlag;
};
}  // namespace fw

#endif
