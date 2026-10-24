#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/LurePlugin.h"
#include "classes/gf/GfGameManager.h"
#include "gf/AccessParam.h"
#include "gf/OwnerBonus.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/pc/StateUtil.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Transform.h"

namespace gf { namespace pc {

LurePlugin::LurePlugin() : m_target(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_behavior(nullptr) {}

bool LurePlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_paramList = fw::ParamManager::get()->m_paramLists[7];
    m_behavior = &behavior;
    return true;
}

void LurePlugin::cleanup(gf::GfComBehaviorPc&) {}

void LurePlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo&) {
    gf::GF_OBJ_HANDLE* target = StateUtil::getTarget(behavior);
    if (target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const AccessParam* param = m_paramList->getAdapter(0).get<AccessParam>();
        GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
        if (!isActiveRangeLure(*property, *param, target)) {
            target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    } else {
        target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    if (m_target != target) {
        m_target = target;
    }
}

bool isActiveRangeLure(gf::GfComPropertyPc& property, const gf::AccessParam& param, gf::GF_OBJ_HANDLE* handle) {
    gf::GfObj* obj = GfObjUtil::getObj(handle);
    if (obj == nullptr || GfObjUtil::getObjType(handle) != 5) {
        return false;
    }
    GfObjAcc acc(obj);
    const fw::Transform& transform = acc.getWorldTransform();
    mm::Vec3 center = property.m_pos + property.m_rot.rotate(mm::Vec3::unitZ * param.offsetFront);
    mm::Vec3 diff = transform.position - center;
    float upper = param.accessUpper;
    float down = -param.accessDown;
    bool inHeight = (diff.y <= upper) & (down <= diff.y);
    const OwnerBonus* bonus = &GfGameManager::getOwnerBonus();
    float radius = param.accessRadius;
    int value = bonus->m_values[11];
    float extra = value >= 0 ? static_cast<float>(value > 9 ? 10 : value) : 0.0f;
    float range = radius + extra;
    float distance = mm::Vec3(diff.x, 0.0f, diff.z).length();
    return inHeight & (distance < range);
}

// drawDebug (0x710051BF40) is not matched yet: with [2][2] and [2][3] set last it is identical but for the order of
// two stores (the original stores the merged [2][2]/[2][3] word before [3][3]); candidate in the worker's notes

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

mm::mtl::RTTI LurePlugin::m_rtti("LurePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
