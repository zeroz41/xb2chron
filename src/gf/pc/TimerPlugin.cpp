#include "classes/gf/pc/TimerPlugin.h"
#include "fw/UpdateInfo.h"

namespace gf { namespace pc {

TimerPlugin::TimerPlugin() {
    for (int i = 0; i < TYPE_NUM; i++) {
        m_timers[i].m_activate = false;
        m_timers[i].m_time = 0.0f;
    }
}

void TimerPlugin::setActivateTimer(TYPE type, bool activate) {
    if (m_timers[type].m_activate != activate) {
        m_timers[type].m_activate = activate;
        m_timers[type].m_time = 0.0f;
    }
}

void TimerPlugin::update(gf::GfComBehaviorPc&, const fw::UpdateInfo& info) {
    for (int i = 0; i < TYPE_NUM; i++) {
        if (m_timers[i].m_activate) {
            m_timers[i].m_time += info.m_deltaTime;
        }
    }
}

mm::mtl::RTTI TimerPlugin::m_rtti("TimerPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
