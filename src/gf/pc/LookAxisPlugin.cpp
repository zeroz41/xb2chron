#include "classes/fw/ParamList.h"
#include "classes/gf/pc/LookAxisPlugin.h"
#include "classes/fw/ParamManager.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { namespace pc {

LookAxisPlugin::LookAxisPlugin()
    : m_behavior(nullptr), m_yaw(0.0f), m_startYaw(0.0f), m_targetYaw(0.0f), m_changeTime(0.0f),
      m_changing(false) {}

bool LookAxisPlugin::setup(gf::GfComBehaviorPc& behavior) {
    mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::get()->m_paramLists[5];
    m_param = list->getAdapter(4);
    m_behavior = &behavior;
    return true;
}

void LookAxisPlugin::cleanup(gf::GfComBehaviorPc&) {}

void LookAxisPlugin::onActivate() {}

void LookAxisPlugin::onDeactivate() {
    setYaw(0.0f);
    m_changing = false;
}

// setYaw (0x710051B72C) is not matched yet: 12 words of instruction scheduling and one register differ in its
// quaternion block (candidate in the worker's notes)

void LookAxisPlugin::update(gf::GfComBehaviorPc&, const fw::UpdateInfo& info) {
    if (m_changing) {
        const Param* param = m_param.get<Param>();
        m_changeTime += info.m_deltaTime;
        float t = mm::clamp(m_changeTime / param->m_changeDuration, 0.0f, 1.0f);
        setYaw(m_startYaw * (1.0f - t) + m_targetYaw * t);
        if (m_changeTime >= param->m_changeDuration) {
            m_changing = false;
        }
    }
}

void LookAxisPlugin::changeAxisYaw(float yaw) {
    m_startYaw = m_yaw;
    m_targetYaw = yaw;
    m_changeTime = 0.0f;
    m_changing = true;
}

mm::mtl::RTTI LookAxisPlugin::m_rtti("LookAxisPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
