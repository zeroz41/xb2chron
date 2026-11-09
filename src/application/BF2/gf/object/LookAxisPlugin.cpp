#include "classes/fw/ParamList.h"
#include "classes/gf/pc/LookAxisPlugin.h"
#include "classes/fw/ParamManager.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Quat.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/pc/TargetIKPlugin.h"
#include "math.h"

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

// the PC's front in its own space: unit z turned about y by the yaw in degrees; the look solvers and the target
// plugin take it
void LookAxisPlugin::setYaw(float yaw) {
    m_yaw = yaw;
    mm::Vec3 front = mm::Vec3::unitZ;
    float rad = yaw * 0.0174532924f;
    if (::fabsf(yaw) > 1.1920929e-07f) {
        float half = rad * 0.5f;
        float s = ::sinf(half);
        float c = ::cosf(half);
        mm::Quat rotation(0.0f, s, 0.0f, c);
        front = rotation.rotate(front);
    }
    if (GfComIK* ik = m_behavior->m_owner->getComponent<GfComIK>(3)) {
        if (fw::LookIkSolver* look = ik->getSolver<fw::LookIkSolver>(3)) {
            look->setFrontMS(front);
        } else if (fw::LookAtIkSolver* lookAt = ik->getSolver<fw::LookAtIkSolver>(5)) {
            lookAt->m_limit.limitAxisMS = front;
        }
    }
    if (TargetIKPlugin* target = m_behavior->getPlugin<TargetIKPlugin>(6)) {
        target->m_front = front;
    }
}

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
