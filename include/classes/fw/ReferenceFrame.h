#ifndef CLASSES_FW_REFERENCEFRAME_H
#define CLASSES_FW_REFERENCEFRAME_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "fw/Transform.h"

namespace fw {
// table 0x7100B418F8; counted (its constructor clears the count at 8; WindProbe holds one by IntrusivePtr)
class ReferenceFrame : public mm::mtl::ReferenceObject {
public:
    virtual ~ReferenceFrame();  // slot 0
    void syncLocalTransform();
    void syncWorldTransform();
    // m_worldTransform, synced first (inline: the name is not the original's; its callers read the transform
    // through the frame pointer they synced, with no second null check)
    const Transform& getWorldTransform() {
        syncWorldTransform();
        return m_worldTransform;
    }

    unsigned char pad_10[0x10];
    Transform m_localTransform;  // getSyncedWorldTransform copies it to m_worldTransform without a parent
    // getSyncedWorldTransform's result: the parent's world transform times m_localTransform
    Transform m_worldTransform;
};
}  // namespace fw

#endif
