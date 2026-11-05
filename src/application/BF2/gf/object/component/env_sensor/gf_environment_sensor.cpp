#include "gf/FileStaticVec3.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gf/GfComBehaviorEvent.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "mm/mtl/Delegate.h"
#include "mm/Col4.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "fw/Message.h"
#include "fw/ColiDamage.h"
#include "gf/CallBackCache.h"
#include "gf/PluginManager.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComPropertyEvent.h"
#include "classes/gf/GfObj.h"
#include "fw/ColiCheck.h"
#include "algorithm"

namespace gf {

EnviromentSensor::EnviromentSensor() : m_checkFlags(0), m_flags(0) {
    pad_290 = 1.0f;
}

// searchVertical's std::sort order for the hits: nearest first along the search direction (the name is the
// original's, from the sort's template arguments; the member's is not)
struct ContactLess {
    bool operator()(const fw::ContactInfo& a, const fw::ContactInfo& b) const {
        return m_dir->dot(a.m_position) < m_dir->dot(b.m_position);
    }
    const mm::Vec3* m_dir;
};

GfComBehaviorEvent::GfComBehaviorEvent() : m_flags(0) {}

void GfComBehaviorEvent::setup() {
    if (GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2)) {
        evtAnim->m_asm.m_callbacks[0].name = "system";
        evtAnim->m_asm.m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this),
                                                   &GfComBehavior::callbackAnimForEvent);
    }
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(FootIkControllerPlugin::PLUGIN_ID, &FootIkControllerPlugin::create, true);
    m_pluginManager.endSetup();
    if (FootIkControllerPlugin* footIk = getPlugin<FootIkControllerPlugin>(FootIkControllerPlugin::PLUGIN_ID)) {
        footIk->setActivate(true);
    }
}

void GfComBehaviorEvent::cleanup() {
    m_pluginManager.cleanup();
}

void GfComBehaviorEvent::update(const fw::UpdateInfo& info) {
    m_pluginManager.update(info);
    if (!(m_flags & 1)) {
        setFootIK(true);
        m_flags |= 1;
    }
    m_turnCmd.update(info.m_deltaTime);
}

void GfComBehaviorEvent::setFootIK(bool enable) {
    if (m_owner->getComponent<GfComIK>(3) != nullptr) {
        GfComEvtAnim* evtAnim = m_owner->getComponent<GfComEvtAnim>(2);
        if (evtAnim != nullptr && evtAnim->m_asm.m_control != nullptr) {
            if (FootIkControllerPlugin* footIk = getPlugin<FootIkControllerPlugin>(FootIkControllerPlugin::PLUGIN_ID)) {
                footIk->m_enableDownIK = enable;
            }
        }
    }
}

GfComBehaviorEvent::~GfComBehaviorEvent() {}

template <typename T>
void TFieldExecCmd<T>::create(const CreateInfo& info) {
    m_executed = false;
    clear();
    m_info = info;
}

// TFieldExecCmdTurn<GfComEvtAnim>::create's (not written yet)
template void TFieldExecCmd<GfComEvtAnim>::create(const CreateInfo& info);

mm::mtl::RTTI GfComBehaviorEvent::m_rtti("GfComBehaviorEvent", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf

// searchVertical's std::sort (not written yet) instantiates the libc++ sort core for the hits.
template void std::__sort<gf::ContactLess&, fw::ContactInfo*>(fw::ContactInfo*, fw::ContactInfo*, gf::ContactLess&);
