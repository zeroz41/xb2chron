#ifndef CLASSES_FW_REFERENCEFRAME_H
#define CLASSES_FW_REFERENCEFRAME_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "fw/Transform.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/Mat44.h"

namespace fw {
// table 0x7100B418F8; counted (its constructor clears the count at 8; WindProbe holds one by IntrusivePtr). Its
// IntrusiveListNodeBase base at 0x10 links it into its parent's m_children (addChild links &child+0x10; unlinkChild
// walks the list back from the nodes by that offset, the list's own node taken as an element at 0xa0).
class ReferenceFrame : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNodeBase {
public:
    ReferenceFrame();
    virtual ~ReferenceFrame();  // slot 0
    // child linked under this frame (GfComTransform::setup links its child frame so)
    void addChild(ReferenceFrame& child);
    // child taken out from under this frame (GfComModel::removeBoneReferenceFrame)
    void removeChild(ReferenceFrame& child);
    // frame taken out of its parent's children (GfComTransform::cleanup)
    static void unlinkParent(ReferenceFrame& frame);
    // frame's children taken out from under it (GfComTransform::cleanup)
    static void unlinkChild(ReferenceFrame& frame);
    void syncLocalTransform();
    void syncWorldTransform();
    // m_worldMatrix, rebuilt from the synced world transform when bit 2 of m_syncFlags is clear
    const mm::Mat44& getSyncedWorldMatrix();
    // m_worldMatrix rebuilt from the synced world transform when bit 2 of m_syncFlags is clear (1.0.0's name;
    // inline: TransformUpdater::resolveWorldTrasform inlines it, gf_com_effect_caster emits a copy)
    inline void syncWorldMatrix() {
        if ((m_syncFlags & 4) == 0) {
            syncWorldTransform();
            const mm::Quat& q = m_worldTransform.rotation;
            const float x2 = q.x + q.x;
            const float y2 = q.y + q.y;
            const float z2 = q.z + q.z;
            const float xx = q.x * x2;
            const float xz = q.x * z2;
            const float yy = q.y * y2;
            const float xy = q.x * y2;
            const float wx = x2 * q.w;
            const float wy = y2 * q.w;
            const float wz = q.w * z2;
            const float zz = q.z * z2;
            const float yz = q.y * z2;
            m_worldMatrix.m[0][0] = 1.0f - (yy + zz);
            m_worldMatrix.m[0][1] = xy + wz;
            m_worldMatrix.m[0][2] = xz - wy;
            m_worldMatrix.m[0][3] = 0.0f;
            m_worldMatrix.m[1][0] = xy - wz;
            m_worldMatrix.m[1][1] = 1.0f - (xx + zz);
            m_worldMatrix.m[1][2] = yz + wx;
            m_worldMatrix.m[1][3] = 0.0f;
            m_worldMatrix.m[2][0] = xz + wy;
            m_worldMatrix.m[2][1] = yz - wx;
            m_worldMatrix.m[2][2] = 1.0f - (xx + yy);
            m_worldMatrix.m[2][3] = 0.0f;
            m_worldMatrix.m[3][0] = 0.0f;
            m_worldMatrix.m[3][1] = 0.0f;
            m_worldMatrix.m[3][2] = 0.0f;
            m_worldMatrix.m[3][3] = 1.0f;
            const mm::Vec3 pos = m_worldTransform.position;
            m_worldMatrix.m[3][0] = pos.x;
            m_worldMatrix.m[3][1] = pos.y;
            m_worldMatrix.m[3][2] = pos.z;
            m_syncFlags |= 4;
        }
    }
    // m_worldTransform, synced first (inline: the name is not the original's; its callers read the transform
    // through the frame pointer they synced, with no second null check; same body as getSyncedWorldTransform below,
    // the original's name for it: its callers can move to that one)
    const Transform& getWorldTransform() {
        syncWorldTransform();
        return m_worldTransform;
    }
    // m_worldTransform, synced first (inline: GfComEnvSensor::resolveTransform inlines it into a tail call of
    // syncWorldTransform; ReferenceFrame.cpp emits the out-of-line copy after syncLocalTransform, its first caller,
    // with syncWorldTransform inlined, so that copy and syncWorldTransform call it for the parent)
    // the world transform becomes the current one and the local transform stale, the matrix's bit kept (inline: the
    // name is not the original's; GfObjUtil::attachGfObj and dettachGfObject after re-parenting a frame)
    void setWorldTransformCurrent() {
        m_syncFlags = (m_syncFlags & ~3u) | 2;
    }
    const Transform& getSyncedWorldTransform() {
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

    Transform m_localTransform;  // syncWorldTransform copies it to m_worldTransform without a parent
    // syncWorldTransform computes it: the parent's world transform times m_localTransform
    Transform m_worldTransform;
    mm::Mat44 m_worldMatrix;  // the constructor's is Mat44::identity
    // which of the three is current: bit 0 the local transform (syncLocalTransform sets it), bit 1 the world
    // transform (syncWorldTransform sets it and clears bit 2), bit 2 the world matrix; the constructor
    // sets all three
    unsigned int m_syncFlags;
    unsigned char pad_a4[0x4];
    // the frame it hangs under: syncLocalTransform computes m_localTransform against its world transform, without
    // one it copies (GfComPropertyPc::writeBack syncs the local transform only with one; the name is not the
    // original's)
    ReferenceFrame* m_parent;
    // the frames linked under this one (addChild/removeChild; unlinkChild empties it; the name is not the
    // original's)
    mm::mtl::IntrusiveList<ReferenceFrame> m_children;
    // the bone's scale AnimPoseModifier copies with the bone's transform (apply; bindReferenceFrameToBone sets
    // 1.0f); the constructor clears them (the names are not the original's)
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    unsigned int pad_d4;  // the constructor clears it
    unsigned char pad_d8[0x8];  // to 0xe0, the size GfComTransform::setup allocates
};
}  // namespace fw

#endif
