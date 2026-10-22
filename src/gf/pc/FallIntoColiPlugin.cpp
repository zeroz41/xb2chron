#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfGameSearchObj.h"

namespace gf { namespace pc {

FallIntoColiPlugin::FallIntoColiPlugin() : m_activeTime(0.0f), m_stillTime(0.0f) {}

FallIntoColiPlugin::~FallIntoColiPlugin() {}

void FallIntoColiPlugin::cleanup(gf::GfComBehaviorPc&) {
    if (m_searchObj != reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1)) {
        gf::GfGameSearchObj::destroyObj(m_searchObj);
        m_searchObj = reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1);
    }
}

void FallIntoColiPlugin::onActivate() {
    m_activeTime = 0.0f;
    m_stillTime = 0.0f;
}

void FallIntoColiPlugin::onDeactivate() {
    gf::GfGameSearchObj::setEnable(m_searchObj, false);
}

float FallIntoColiPlugin::getHeight(gf::GfComBehaviorPc& behavior) const {
    GfComTransform* transform = behavior.m_owner->getComponent<GfComTransform>(0);
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = transform->getFrame();
    return frame->getWorldTransform().position.y;
}

mm::mtl::RTTI FallIntoColiPlugin::m_rtti("FallIntoColiPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
