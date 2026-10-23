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
    virtual ~AnimPoseSamper();  // slot 0
    virtual void samplePose();  // slot 2
    void bind(anm::Blender* blender, anm::Pose* pose, anm::ExtraTruckBuffer* extra);
    void unbind();
    // whether a blender and a pose are bound (inline: the name is not the original's)
    bool isBind() const { return m_blender != nullptr && m_pose != nullptr; }

    anm::Blender* m_blender;  // bind's (the names are not the original's)
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extra;
    unsigned char pad_30[0x3];
    bool m_sampleFlag;  // set from the owner's setup info before bind (the name is not the original's)
};
}  // namespace fw

#endif
