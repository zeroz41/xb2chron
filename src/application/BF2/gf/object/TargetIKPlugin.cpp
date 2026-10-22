#include "gf/FileStaticVec3.h"
#include "classes/fw/MessageObject.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/gf/pc/TargetIKPlugin.h"
#include "gf/GfObjAcc.h"
#include "gf/LookParam.h"
#include "gf/MsgGameChangeTarget.h"
#include "gf/MsgPcGetLookPoint.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/GfObjUtil.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"
#include "mm/Quat.h"

namespace gf { namespace pc {

TargetIKPlugin::TargetIKPlugin()
    : m_target(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_front(mm::Vec3::unitZ), m_upRatio(1.0f), m_downRatio(1.0f) {}

TargetIKPlugin::~TargetIKPlugin() {}

bool TargetIKPlugin::setup(gf::GfComBehaviorPc& behavior) {
    GfComIK* ik = behavior.m_owner->getComponent<GfComIK>(3);
    fw::LookIkSolver* solver = ik->getSolver<fw::LookIkSolver>(3);
    if (solver == nullptr) {
        return false;
    }
    m_solver = solver;
    mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::get()->m_paramLists[5];
    m_param = list->getAdapter(4);
    return true;
}

void TargetIKPlugin::cleanup(gf::GfComBehaviorPc&) {
    m_solver = nullptr;
}

void TargetIKPlugin::onActivate() {
    const LookParam* param = m_param.get<LookParam>();
    m_solver->fadeIn(param->targetMoveTime);
}

void TargetIKPlugin::onDeactivate() {
    const LookParam* param = m_param.get<LookParam>();
    m_solver->fadeOut(param->targetMoveTime);
    m_upRatio = 1.0f;
    m_downRatio = 1.0f;
    m_solver->setTargetUpRatio(m_upRatio);
    m_solver->setTargetDownRatio(m_downRatio);
}

void TargetIKPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo& info) {
    if (m_target == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    const LookParam* param = m_param.get<LookParam>();
    GfComAsm* asmCom = behavior.m_owner->getComponent<GfComAsm>(2);
    if (asmCom != nullptr) {
        unsigned long attribute = asmCom->getAttribute(AsmCategory(0), AnimLayer(0));
        float step = info.m_deltaTime / param->changeBehaviorTime;
        m_upRatio = mm::clamp(m_upRatio + ((attribute & 0x10) == 0 ? step : -step), 0.0f, 1.0f);
        m_solver->setTargetUpRatio(m_upRatio);
        float down = m_downRatio;
        m_downRatio = mm::clamp(((attribute & 0x20) == 0 ? step : -step) + down, 0.0f, 1.0f);
        m_solver->setTargetDownRatio(m_downRatio);
    }
    GfObj* target = GfObjUtil::getObj(m_target);
    if (target == nullptr) {
        return;
    }
    MsgPcGetLookPoint msg;
    bool taken = static_cast<GfObj*>(behavior.m_owner)->sendMessage(target, msg);
    if (!msg.m_found || !taken) {
        return;
    }
    m_solver->setTarget(msg.m_point);
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    GfObjAcc acc(target);
    unsigned int attribute = acc.getAttribute();
    bool outOfRange = !isActiveRange(*property, msg.m_point);
    bool lookAway = !(attribute & 2) || outOfRange;
    bool enable = m_solver->isEnable();
    if (lookAway) {
        if (enable || m_solver->getFadeType() == fw::IkFadeSolver::FADE_IN) {
            m_solver->fadeOut(param->targetMoveTime);
        }
    } else {
        if (!enable || m_solver->getFadeType() == fw::IkFadeSolver::FADE_OUT) {
            m_solver->fadeIn(param->targetMoveTime);
        }
    }
}

bool TargetIKPlugin::isActiveRange(gf::GfComPropertyPc& property, const mm::Vec3& pos) {
    const LookParam* param = m_param.get<LookParam>();
    mm::Vec3 dir(pos.x - property.m_pos.x, 0.0f, pos.z - property.m_pos.z);
    dir.normalize();
    float cos = mm::clamp(dir.dot(property.m_rot.rotate(m_front)), -1.0f, 1.0f);
    return mm::acos(cos) * (180.0f / 3.14159265f) <= param->lookAngle;
}

void TargetIKPlugin::procMsgGameChangeTarget(fw::MessageObject*, gf::MsgGameChangeTarget& msg) {
    if (msg.m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const LookParam* param = m_param.get<LookParam>();
        if (m_solver.get() != nullptr) {
            m_solver.get()->startTargetFade(param->targetMoveTime);
        }
    }
    m_target = msg.m_target;
}

mm::mtl::RTTI TargetIKPlugin::m_rtti("TargetIKPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
