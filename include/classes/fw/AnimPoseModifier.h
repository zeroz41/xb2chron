#ifndef CLASSES_FW_ANIMPOSEMODIFIER_H
#define CLASSES_FW_ANIMPOSEMODIFIER_H

#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/AnimationManager.h"

namespace anm { class Pose; }

namespace fw {
class ModelObject;
class ReferenceFrame;
// table 0x7100B40C80
// AnimationManager::addPoseModifier keeps it (GfComModel::setup passes its own, no adjustment)
class AnimPoseModifier : public AnimPoseModifierInterface {
public:
    // makes frame follow the pose's bone (GfComModel::createBoneReferenceFrameImpl)
    void bindReferenceFrameToBone(unsigned short bone, mm::mtl::IntrusivePtr<ReferenceFrame>& frame);
    // frame unbound from its bone (GfComModel::destroyBoneReferenceFrameImpl)
    void unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame>& frame);
    AnimPoseModifier();
    virtual ~AnimPoseModifier();  // slot 0
    virtual void apply();  // slot 2
    // undoes bind (GfComModel::cleanup)
    void unbind();
    // whether bind gave it a pose and a model (GfComModel::cleanup; the name is not the original's)
    bool isBound() const { return m_pose != nullptr && m_model != nullptr; }
    anm::Pose* m_pose;        // bind's first argument (the name is not the original's)
    ModelObject* m_model;     // bind's second argument (the name is not the original's)
    unsigned char pad_28[0x1060];  // 0x1088 bytes: GfComModel holds one at 0x40, its volume fade follows at 0x10c8
};
}  // namespace fw

#endif
