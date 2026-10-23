#ifndef CLASSES_FW_ANIMCOLPOSEMODIFIER_H
#define CLASSES_FW_ANIMCOLPOSEMODIFIER_H

#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/AnimAfterModifierInterface.h"
#include "classes/fw/ColiObject.h"

namespace fw { class ModelObject; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40B20; poses a collision object from a model's animation (GfComCollider adds it to the
// AnimationManager as an after-modifier)
class AnimColPoseModifier : public ::fw::AnimAfterModifierInterface {
public:
    AnimColPoseModifier();
    virtual ~AnimColPoseModifier();  // slot 0
    virtual void apply();  // slot 2
    void bind(fw::ModelObject* model, fw::ColiObject* coli, mm::mtl::IAllocator* allocator);
    void unbind();
    // whether bind gave it both (inline: the name is not the original's)
    bool isBound() const { return m_model.get() != nullptr && m_coli.get() != nullptr; }

    mm::mtl::IntrusivePtr<fw::ModelObject> m_model;  // bind's; unbind releases it (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::ColiObject> m_coli;    // bind's; unbind releases it (the name is not the original's)
    unsigned char pad_28[0x28];
};
}  // namespace fw

#endif
