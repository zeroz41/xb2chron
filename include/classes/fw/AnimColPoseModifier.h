#ifndef CLASSES_FW_ANIMCOLPOSEMODIFIER_H
#define CLASSES_FW_ANIMCOLPOSEMODIFIER_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
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
    bool isBound() const { return m_model != nullptr && m_coli != nullptr; }

    // bind's, referenced; unbind releases them. Plain pointers: the destructor does not release them (the names
    // are not the original's)
    fw::ModelObject* m_model;
    fw::ColiObject* m_coli;
    // per bone of the collision object, bind resizes it to the bone count filled with 0xffff; unbind clears it
    // (the name is not the original's)
    mm::mtl::Vector<short> m_boneIndices;
};
}  // namespace fw

#endif
