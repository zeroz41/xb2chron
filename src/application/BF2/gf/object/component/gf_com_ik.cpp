#include "fw/IkResolver.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComIK/FootGround.h"
#include "classes/gf/GfComIK/Ground.h"
#include "classes/gf/GfComIK/ViewerListener.h"
#include "classes/fw/AnimationManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Message.h"

namespace gf {

bool GfComIK::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

GfComIK::GfComIK() : m_footCount(0), m_pViewer(nullptr) {
    m_solvers.setAllocator(getAllocator(ALLOCATOR(0)));
    m_viewerListener.m_pOwner = this;
}

GfComIK::~GfComIK() {}

void GfComIK::cleanup() {
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->removeIkResolver(getLayer(), *this);
    }
    m_solvers.clear();
    m_ground.reset();
}

void GfComIK::changeLayer(unsigned int oldLayer, unsigned int newLayer) {
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->removeIkResolver(getLayer(), *this);
        manager->addIkResolver(newLayer, *this);
    }
}

void GfComIK::ViewerListener::onWkStandbyLogout() {
    if (m_pOwner != nullptr) {
        m_pOwner->m_pViewer = nullptr;
    }
}

fw::IKFootGroundInterface* GfComIK::Ground::getFootGround(fw::IKFootIndex index) {
    return &m_feet[index];
}

GfComIK::Ground::~Ground() {}

mm::mtl::RTTI GfComIK::m_rtti("GfComIK", &GfComponent::m_rtti, nullptr);

}  // namespace gf
