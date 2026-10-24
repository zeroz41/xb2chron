#ifndef CLASSES_FW_ANIMPOSESAMPER_H
#define CLASSES_FW_ANIMPOSESAMPER_H

#include "classes/fw/AnimSinglePoseSamper.h"
namespace anm { class Blender; }
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }

namespace fw {
// samples one anm::Blender into one anm::Pose
class AnimPoseSamper : public ::fw::AnimPoseSamplerInterface {
public:
    // inline: AnimEventMotPoseSamper's constructor has it inlined, and the symbols name no copy of its own
    AnimPoseSamper() : m_blender(nullptr), m_pose(nullptr), m_extra(nullptr), m_enable(true), m_sampleFlag(true) {}
    virtual ~AnimPoseSamper();  // slot 0
    virtual void samplePose();  // slot 2
    void bind(anm::Blender* blender, anm::Pose* pose, anm::ExtraTruckBuffer* extra);
    void unbind();
    // whether a blender and a pose are bound (inline: the name is not the original's)
    bool isBind() const { return m_blender != nullptr && m_pose != nullptr; }

    anm::Blender* m_blender;  // bind's (the names are not the original's)
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extra;
    unsigned short m_extraIndex;  // bind's slot index of the extra truck buffer (the name is not the original's)
    // samplePose samples only while it is set; the constructor's true (the name is not the original's)
    bool m_enable;
    bool m_sampleFlag;  // samplePose: set, in local space; clear, in model space  // set from the owner's setup info before bind (the name is not the original's)
};
}  // namespace fw

#endif
