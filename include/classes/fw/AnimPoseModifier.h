#ifndef CLASSES_FW_ANIMPOSEMODIFIER_H
#define CLASSES_FW_ANIMPOSEMODIFIER_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/AnimationManager.h"

namespace anm { class Pose; }
namespace anm { class ExtraTruckBuffer; }

namespace fw {
class ModelObject;
class ReferenceFrame;
// table 0x7100B40C80
// AnimationManager::addPoseModifier keeps it (GfComModel::setup passes its own, no adjustment)
class AnimPoseModifier : public AnimPoseModifierInterface {
public:
    // a reference frame bound to a bone of the pose (the symbols name the type: FixedVector<BoneBindInfo, 256>::erase;
    // its fields follow bindReferenceFrameToBone, which pushes the frame then the bone; the field names are not the
    // original's)
    struct BoneBindInfo {
        mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;
        unsigned short m_bone;
    };
    // makes frame follow the pose's bone (GfComModel::createBoneReferenceFrameImpl)
    void bindReferenceFrameToBone(unsigned short bone, mm::mtl::IntrusivePtr<ReferenceFrame>& frame);
    // frame unbound from its bone (GfComModel::destroyBoneReferenceFrameImpl)
    void unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame>& frame);
    AnimPoseModifier();
    virtual ~AnimPoseModifier();  // slot 0
    virtual void apply();  // slot 2
    // binds the pose, the model and the extra truck buffer, the bone and truck maps from allocator (GfComModel::setup)
    void bind(anm::Pose* pose, ModelObject* model, anm::ExtraTruckBuffer* extra, mm::mtl::IAllocator* allocator);
    // undoes bind (GfComModel::cleanup)
    void unbind();
    // whether bind gave it a pose and a model (GfComModel::cleanup; the name is not the original's)
    bool isBound() const { return m_pose != nullptr && m_model != nullptr; }
    anm::Pose* m_pose;        // bind's first argument (the name is not the original's)
    ModelObject* m_model;     // bind's second argument (the name is not the original's)
    // per bone of the model, the index of the pose's bone of its name, 0xFFFF for none (bind; apply copies those
    // bones' model-space matrices to the model's; the name is not the original's)
    mm::mtl::Vector<short> m_boneIndices;
    // the frames bindReferenceFrameToBone bound (unbindReferenceFrame erases one; the name is not the original's)
    mm::mtl::FixedVector<BoneBindInfo, 256> m_boneBinds;  // 0x50, count at 0x1050
    anm::ExtraTruckBuffer* m_extra;  // bind's third argument (the name is not the original's)
    // per etc parameter of the model, the index of the extra truck of its name, -1 for none (bind; apply copies
    // those trucks' values to the parameters; the name is not the original's)
    mm::mtl::Vector<short> m_extraTruckIDs;  // 0x1088 bytes: GfComModel holds one at 0x40, its volume fade follows at 0x10c8
};
}  // namespace fw

#endif
