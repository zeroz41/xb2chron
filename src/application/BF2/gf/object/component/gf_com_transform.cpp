#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/TransformManager.h"
#include "classes/fw/TransformUpdater.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Message.h"

#include <algorithm>

namespace gf {

bool GfComTransform::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

GfComTransform::GfComTransform() : m_pViewer(nullptr), m_listener(this) {}

GfComTransform::~GfComTransform() {}

void GfComTransform::setup(const SetupInfo& setup_info) {
#line 46
    MM_ASSERT(setup_info.frame_max!=0);
#line 48
    m_frame = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) fw::ReferenceFrame;
    fw::Transform& transform = m_frame.get()->getWorldTransformForWrite();
    transform.position = setup_info.position;
    transform.rotation = setup_info.rotation;
    m_frame->syncLocalTransform();
    if (setup_info.childFrame) {
#line 62
        m_childFrame = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) fw::ReferenceFrame;
        m_frame->addChild(*m_childFrame.get());
        m_childFrame->getLocalTransformForWrite();
        m_childFrame->syncWorldTransform();
    }
    m_updater.m_referenceFrames.setAllocator(getAllocator(ALLOCATOR(0)));
    m_updater.m_referenceFrames.reserve(setup_info.frame_max);
    m_updater.m_afterReferenceFrames.setAllocator(getAllocator(ALLOCATOR(0)));
    m_updater.m_afterReferenceFrames.reserve(setup_info.frame_max);
    {
        mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = m_frame;
        m_updater.m_referenceFrames.push_back(frame);
    }
    if (m_childFrame) {
        mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = m_childFrame;
        m_updater.m_referenceFrames.push_back(frame);
    }
    fw::TransformManager::get()->addUpdater(getLayer(), &m_updater);
}

void GfComTransform::cleanup() {
    if (fw::ReferenceFrame* child = m_childFrame.get()) {
        fw::ReferenceFrame::unlinkParent(*child);
        fw::ReferenceFrame::unlinkChild(*child);
    }
    fw::ReferenceFrame* frame = m_frame.get();
    fw::ReferenceFrame::unlinkParent(*frame);
    fw::ReferenceFrame::unlinkChild(*frame);
    fw::TransformManager::get()->removeUpdater(getLayer(), &m_updater);
    if (m_updater.m_referenceFrames.capacity() != 0) {
        m_updater.m_referenceFrames.clear();
        m_updater.m_referenceFrames.destroy();
    }
    if (m_updater.m_afterReferenceFrames.capacity() != 0) {
        m_updater.m_afterReferenceFrames.clear();
        m_updater.m_afterReferenceFrames.destroy();
    }
}

void GfComTransform::addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    m_updater.m_referenceFrames.push_back(frame);
}

void GfComTransform::removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>* it =
        std::find(m_updater.m_referenceFrames.begin(), m_updater.m_referenceFrames.end(), frame);
    if (it != m_updater.m_referenceFrames.end()) {
        m_updater.m_referenceFrames.erase(it);
    }
}

void GfComTransform::addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    m_updater.m_afterReferenceFrames.push_back(frame);
}

void GfComTransform::removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>* it =
        std::find(m_updater.m_afterReferenceFrames.begin(), m_updater.m_afterReferenceFrames.end(), frame);
    if (it != m_updater.m_afterReferenceFrames.end()) {
        m_updater.m_afterReferenceFrames.erase(it);
    }
}

void GfComTransform::setPosition(const mm::Vec3& position) {
    m_frame.get()->getWorldTransformForWrite().position = position;
}

const mm::Vec3& GfComTransform::getPosition() const {
    return m_frame.get()->m_worldTransform.position;
}

void GfComTransform::setRotation(const mm::Quat& rotation) {
    m_frame.get()->getWorldTransformForWrite().rotation = rotation;
}

const mm::Quat& GfComTransform::getRotation() const {
    return m_frame.get()->m_worldTransform.rotation;
}

void GfComTransform::syncFrame() {
    if (m_frame) {
        m_frame->syncLocalTransform();
    }
    if (m_childFrame) {
        m_childFrame->getLocalTransformForWrite();
        m_childFrame->syncWorldTransform();
    }
}

void GfComTransform::changeLayer(unsigned int oldLayer, unsigned int newLayer) {
    fw::TransformManager::get()->removeUpdater(getLayer(), &m_updater);
    fw::TransformManager::get()->addUpdater(newLayer, &m_updater);
}

void GfComTransform::Listener::onWkStandbyLogout() {
    m_pOwner->m_pViewer = nullptr;
}

mm::mtl::RTTI GfComTransform::m_rtti("GfComTransform", &GfComponent::m_rtti, nullptr);

}  // namespace gf
