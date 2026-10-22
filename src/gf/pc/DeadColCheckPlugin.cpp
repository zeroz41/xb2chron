#include "gf/MsgObjectDamage.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComCollider.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfStatusProperty.h"
#include "gf/EnviromentSensor.h"
#include "gf/MsgObjectDamage.h"
#include "gf/MsgUnk_1000046.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/pc/DeadColCheckPlugin.h"

namespace gf { namespace pc {

DeadColCheckPlugin::DeadColCheckPlugin() {}

bool DeadColCheckPlugin::setup(gf::GfComBehaviorPc&) {
    return true;
}

void DeadColCheckPlugin::cleanup(gf::GfComBehaviorPc&) {}

void DeadColCheckPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo&) {
    if (!testDead(behavior)) {
        return;
    }
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    GfObj* obj = static_cast<GfObj*>(property->m_owner);
    unsigned int hp = property->m_status.get()->m_hp;
    if (property->m_stateFlags & 0x400) {
        // a dead plane that kills outright
        if (hp != 0) {
            MsgObjectDamage msg(hp, 4);
            obj->sendMessage(obj, msg);
        }
    } else {
        // all the hit points but one
        unsigned int damage = hp - 1;
        if (damage != 0) {
            MsgObjectDamage msg(damage, 4);
            obj->sendMessage(obj, msg);
        }
        MsgUnk_1000046 msg(true);
        obj->sendMessage(obj, msg);
    }
}

bool DeadColCheckPlugin::testDead(gf::GfComBehaviorPc& behavior) const {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    const EnviromentSensor::DeadPlaneInfo* deadPlane = StateUtil::getDeadPlaneInfo(behavior);
    if (deadPlane != nullptr) {
        // a fall from above the plane to it
        bool wasAbove = property->m_prevPos.y > deadPlane->m_height;
        bool isBelow = property->m_pos.y <= deadPlane->m_height;
        return wasAbove && isBelow;
    }
    if (property->m_stateFlags & 0x400) {
        // the collider: the component in slot 4 when it is one
        fw::ComponentObject* component = behavior.m_owner->m_components[4];
        if (component != nullptr && !component->getRTTI()->isKindOf(&GfComCollider::m_rtti)) {
            component = nullptr;
        }
        const GfComCollider* collider = static_cast<GfComCollider*>(component);
        return collider->m_coliObjects[0]->testAttribute(static_cast<fw::ColiAtrr>(1));
    }
    return false;
}

void DeadColCheckPlugin::onActivate() {}

void DeadColCheckPlugin::onDeactivate() {}

mm::mtl::RTTI DeadColCheckPlugin::m_rtti("DeadColCheckPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
