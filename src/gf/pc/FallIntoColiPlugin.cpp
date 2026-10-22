#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfGameSearchObj.h"
#include "fw/UpdateInfo.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/pc/StateUtil.h"
#include "mm/Math.h"

namespace gf { namespace pc {

FallIntoColiPlugin::FallIntoColiPlugin() : m_activeTime(0.0f), m_stillTime(0.0f) {}

FallIntoColiPlugin::~FallIntoColiPlugin() {}

// setup (0x71005193D8) is not matched yet: its GfSearchParam's stack initialization schedules differently (the
// candidate is in the worker's notes)

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

void FallIntoColiPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo& info) {
    m_activeTime = info.m_deltaTime + m_activeTime;
    if (m_activeTime >= 10.0f) {
        if (!gf::GfGameSearchObj::isEnable(m_searchObj)) {
            gf::GfGameSearchObj::setEnable(m_searchObj, true);
            m_height = getHeight(behavior);
        }
        if (mm::fabs(getHeight(behavior) - m_height) <= 1.0f) {
            // stuck in place with something found around the PC for 5 seconds: a death by a fall into a collision
            m_stillTime = info.m_deltaTime + m_stillTime;
            if (m_stillTime >= 5.0f && gf::GfGameSearchObj::getObj(m_searchObj)->m_num_nodes != 0) {
                MsgObjectNotifyDead msg;
                msg.m_deadType = 7;
                StateUtil::notifyDead(behavior, msg, true);
            }
        } else {
            m_height = getHeight(behavior);
            m_stillTime = 0.0f;
        }
    }
}

float FallIntoColiPlugin::getHeight(gf::GfComBehaviorPc& behavior) const {
    GfComTransform* transform = behavior.m_owner->getComponent<GfComTransform>(0);
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = transform->getFrame();
    return frame->getWorldTransform().position.y;
}

mm::mtl::RTTI FallIntoColiPlugin::m_rtti("FallIntoColiPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
