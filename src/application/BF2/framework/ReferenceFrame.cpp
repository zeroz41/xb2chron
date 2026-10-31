#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/TransformManager.h"
#include "classes/fw/TransformUpdater.h"

namespace fw {

ReferenceFrame::ReferenceFrame() : m_syncFlags(0), m_parent(nullptr) {
    m_localTransform.position = mm::Vec3::zero;
    m_localTransform.rotation = mm::Quat::identity;
    m_worldTransform.position = mm::Vec3::zero;
    m_worldTransform.rotation = mm::Quat::identity;
    m_worldMatrix = mm::Mat44::identity;
    m_syncFlags |= 7;
    pad_c8 = nullptr;
    pad_d0 = nullptr;
}

// the body stores the table (an empty one would not): a statement the build compiles away
ReferenceFrame::~ReferenceFrame() {
    ;
}

void ReferenceFrame::addChild(ReferenceFrame& child) {
    m_children.push_back(&child);
    child.m_parent = this;
}

void ReferenceFrame::removeChild(ReferenceFrame& child) {
    m_children.remove(&child);
    child.m_parent = nullptr;
}

void ReferenceFrame::syncLocalTransform() {
    if ((m_syncFlags & 1) == 0) {
        if (m_parent != nullptr) {
            Transform::mulInverse(m_parent->getSyncedWorldTransform(), m_worldTransform, &m_localTransform);
        } else {
            m_localTransform = m_worldTransform;
        }
        m_syncFlags |= 1;
    }
}

void ReferenceFrame::syncWorldTransform() {
    if ((m_syncFlags & 2) == 0) {
        if (m_parent == nullptr) {
            m_worldTransform = m_localTransform;
        } else {
            Transform::mul(m_parent->getSyncedWorldTransform(), m_localTransform, &m_worldTransform);
        }
        m_syncFlags = (m_syncFlags & ~6u) | 2;
    }
}

void Transform::mul(const Transform& lhs, const Transform& rhs, Transform* pOut) {
    pOut->position = lhs.position + lhs.rotation.rotate(rhs.position);
    pOut->rotation = rhs.rotation * lhs.rotation;
}

void ReferenceFrame::unlinkParent(ReferenceFrame& frame) {
    if (frame.m_parent != nullptr) {
        frame.m_parent->removeChild(frame);
    }
}

void ReferenceFrame::unlinkChild(ReferenceFrame& frame) {
    const Transform& world = frame.getSyncedWorldTransform();
    for (mm::mtl::IntrusiveList<ReferenceFrame>::iterator it = frame.m_children.begin(); it != frame.m_children.end();
         ++it) {
        ReferenceFrame& child = *it;
        if (child.m_parent == &frame) {
            Transform& local = child.getLocalTransformForWrite();
            local.position += world.position;
            local.rotation = world.rotation * local.rotation;
            child.m_parent = nullptr;
        }
    }
    frame.m_children.clear();
}

}  // namespace fw
