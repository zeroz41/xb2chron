#ifndef CLASSES_FW_ANIMEVENTASMPOSESAMPLER_H
#define CLASSES_FW_ANIMEVENTASMPOSESAMPLER_H

#include "classes/fw/AnimSinglePoseSamper.h"
namespace anm { class ASMControl; }
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }

namespace fw {
// samples one anm::ASMControl into one anm::Pose (GfComEvtAnim::Asm's)
class AnimEventAsmPoseSampler : public ::fw::AnimPoseSamplerInterface {
public:
    AnimEventAsmPoseSampler();
    virtual ~AnimEventAsmPoseSampler();  // slot 0
    virtual void samplePose();  // slot 2
    void bind(anm::ASMControl* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra);
    void unbind();
    // whether a control and a pose are bound (inline: the name is not the original's)
    bool isBind() const { return m_control != nullptr && m_pose != nullptr; }

    anm::ASMControl* m_control;  // bind's (the names are not the original's)
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extra;
    unsigned short m_extraIndex;  // bind's slot index of the extra truck buffer (the name is not the original's)
    // samplePose skips sampling while it is set (the name is not the original's)
    bool m_pause;
    bool m_sampleFlag;  // set from the owner's setup info before bind (the name is not the original's)
};
}  // namespace fw

#endif
