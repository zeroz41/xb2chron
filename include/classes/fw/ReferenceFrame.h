#ifndef CLASSES_FW_REFERENCEFRAME_H
#define CLASSES_FW_REFERENCEFRAME_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "fw/Transform.h"
#include "mm/Mat44.h"

namespace fw {
// table 0x7100B418F8; counted (its constructor clears the count at 8; WindProbe holds one by IntrusivePtr)
class ReferenceFrame : public mm::mtl::ReferenceObject {
public:
    ReferenceFrame();
    virtual ~ReferenceFrame();  // slot 0
    // child linked under this frame (GfComTransform::setup links its child frame so)
    void addChild(ReferenceFrame& child);
    // frame taken out of its parent's children (GfComTransform::cleanup)
    static void unlinkParent(ReferenceFrame& frame);
    // frame's children taken out from under it (GfComTransform::cleanup)
    static void unlinkChild(ReferenceFrame& frame);
    void syncLocalTransform();
    void syncWorldTransform();
    // m_worldMatrix, rebuilt from the synced world transform when bit 2 of m_syncFlags is clear
    const mm::Mat44& getSyncedWorldMatrix();
    // m_worldTransform, synced first (inline: the name is not the original's; its callers read the transform
    // through the frame pointer they synced, with no second null check)
    const Transform& getWorldTransform() {
        syncWorldTransform();
        return m_worldTransform;
    }
    // m_localTransform to write: it becomes the current one, the world transform and matrix stale (inline: the
    // name is not the original's; GfMenuModelView::getObjectTransformLocal)
    Transform& getLocalTransformForWrite() {
        m_syncFlags = (m_syncFlags & ~7u) | 1;
        return m_localTransform;
    }
    // m_worldTransform to write: it becomes the current one, the local transform and matrix stale (inline: the
    // name is not the original's; GfMenuModelView::getObjectTransform)
    Transform& getWorldTransformForWrite() {
        m_syncFlags = (m_syncFlags & ~7u) | 2;
        return m_worldTransform;
    }

    unsigned char pad_10[0x10];
    Transform m_localTransform;  // getSyncedWorldTransform copies it to m_worldTransform without a parent
    // getSyncedWorldTransform's result: the parent's world transform times m_localTransform
    Transform m_worldTransform;
    mm::Mat44 m_worldMatrix;  // the constructor's is Mat44::identity
    // which of the three is current: bit 0 the local transform (syncLocalTransform sets it), bit 1 the world
    // transform (getSyncedWorldTransform sets it and clears bit 2), bit 2 the world matrix; the constructor
    // sets all three
    unsigned int m_syncFlags;
    unsigned char pad_a4[0x3c];  // to 0xe0, the size GfComTransform::setup allocates
};
}  // namespace fw

#endif
