#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_ACCESS_TARGET.h"
#include "gf/AccessParam.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/pc/StateUtil.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfObj.h"

namespace gf { namespace pc {

AccessPlugin::AccessPlugin()
    : m_target(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_behavior(nullptr), m_accessKinds(-1) {}

bool AccessPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_paramList = fw::ParamManager::get()->m_paramLists[5];
    m_behavior = &behavior;
    return true;
}

void AccessPlugin::cleanup(gf::GfComBehaviorPc&) {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        SCOM_ACCESS_TARGET::create(m_target);
    }
}

void AccessPlugin::onDeactivate() {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        SCOM_ACCESS_TARGET::create(m_target);
    }
}

void AccessPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo&) {
    gf::GF_OBJ_HANDLE* target = StateUtil::getTarget(behavior);
    if (target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
        bool flag = (property->m_stateFlags & 0x80000000) != 0;
        unsigned int bit = (property->m_field.m_statusFlags >> 4) & 1;
        unsigned int index = flag ? (bit | 2) : bit;
        const AccessParam* param = m_paramList->getAdapter(index).get<AccessParam>();
        if (!isActiveRange(*property, *param, target)) {
            target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    } else {
        target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    if (m_target != target) {
        MsgPcFieldGetAccessType msg;
        GfObj* obj = GfObjUtil::getObj(target);
        if (obj == nullptr) {
            target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        } else {
            static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
            if (m_accessKinds != 0) {
                m_target = target;
            } else {
                target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            }
        }
        SCOM_ACCESS_TARGET::create(target);
    }
}

bool isActiveRange(gf::GfComPropertyPc& property, const gf::AccessParam& param, gf::GF_OBJ_HANDLE* handle) {
    gf::GfObj* obj = GfObjUtil::getObj(handle);
    if (obj == nullptr || (obj->pad_110 & 1) == 0 || !GfGameManager::isEnableFieldAccess()) {
        return false;
    }
    MsgPcFieldGetAccessType msg;
    static_cast<GfObj*>(property.m_owner)->sendMessage(obj, msg);
    if (!msg.m_enable) {
        return false;
    }
    GfObjAcc acc(obj);
    const fw::Transform& transform = acc.getWorldTransform();
    mm::Vec3 center = property.m_pos + property.m_rot.rotate(mm::Vec3::unitZ * param.offsetFront);
    mm::Vec3 diff = transform.position - center;
    float upper = param.accessUpper;
    float down = -param.accessDown;
    bool inHeight = (diff.y <= upper) & (down <= diff.y);
    float distance = mm::Vec3(diff.x, 0.0f, diff.z).length();
    float range = param.accessRadius + acc.getTargetSearchOffset();
    return inHeight & (distance < range);
}

// drawDebug (0x7100516FD4) is not matched yet: it stores the matrix's [2][2] and [2][3] as one word

void AccessPlugin::onActivate() {}

mm::mtl::RTTI AccessPlugin::m_rtti("AccessPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
