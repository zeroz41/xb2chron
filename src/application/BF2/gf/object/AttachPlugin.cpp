#include "gf/FileStaticVec3.h"
#include "gf/EnviromentSensor.h"
#include "gf/GfObjUtil.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/pc/AttachPlugin.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf { namespace pc {

AttachPlugin::AttachPlugin() : m_flags(0), m_attachObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_behavior(nullptr) {
    m_attachTransform.position = mm::Vec3::zero;
    m_attachTransform.rotation = mm::Quat::identity;
}

AttachPlugin::~AttachPlugin() {}

bool AttachPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_behavior = &behavior;
    return true;
}

void AttachPlugin::cleanup(gf::GfComBehaviorPc&) {
    m_flags &= ~FLAG_ATTACH;
    m_behavior = nullptr;
}

void AttachPlugin::onActivate() {}

inline void AttachPlugin::dettachObj() {
    if (m_attachObj != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        GfObjUtil::dettachGfObject(m_attachObj, static_cast<GfObj*>(m_behavior->m_owner)->m_handle);
        m_attachObj = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        GfComDynamics* dynamics = m_behavior->m_owner->getComponent<GfComDynamics>(8);
        if (dynamics != nullptr) {
            fw::Transform movement;
            movement.position = mm::Vec3::zero;
            movement.rotation = mm::Quat::identity;
            dynamics->m_updater.m_prevTransform = movement;
            notifyExcludeMovementRider(movement);
        }
    }
}

void AttachPlugin::onDeactivate() {
    dettachObj();
}

// update (0x7100517544) is not matched yet: written as the attach/notify/detach flow (getComponent<GfComPropertyPc>,
// the ground's object from the env sensor's bit 0, attachObj when the field status has bit 4, else notifyMovement and
// a re-attach while the ground info is within 3 below the PC) it differs in 4 words: the original tests the state
// flags' bit 4 on a word load (ldr, not ldrb) and checks the ground info for none before the ground's object

void AttachPlugin::attachObj(gf::GF_OBJ_HANDLE* obj) {
    GfObjUtil::attachGfObj(obj, static_cast<GfObj*>(m_behavior->m_owner)->m_handle);
    m_attachObj = obj;
    GfObj* attached = GfObjUtil::getObj(obj);
    if (attached != nullptr) {
        GfComTransform* transform = attached->getComponent<GfComTransform>(0);
        if (transform != nullptr) {
            m_attachTransform = transform->getFrame()->getWorldTransform();
        }
        GfComDynamics* dynamics = m_behavior->m_owner->getComponent<GfComDynamics>(8);
        if (dynamics != nullptr) {
            fw::Transform movement;
            movement.position = mm::Vec3::zero;
            movement.rotation = mm::Quat::identity;
            dynamics->m_updater.m_prevTransform = movement;
            notifyExcludeMovementRider(movement);
        }
    }
}

// notifyMovement (0x7100517900) is not matched yet: written as
//     fw::Transform world = transform->getFrame()->getWorldTransform();
//     movement.position = world.position - m_attachTransform.position;
//     m_attachTransform.rotation = mm::Quat::inverse(m_attachTransform.rotation);
//     movement.rotation = world.rotation * m_attachTransform.rotation;
//     dynamics->m_updater.m_prevTransform = movement; notifyExcludeMovementRider(movement); m_attachTransform = world;
// its data flow is the original's; register allocation differs (the original rematerializes the pointer to
// m_attachTransform.rotation.y in its second validity check)

void AttachPlugin::notifyExcludeMovementRider(const fw::Transform& movement) {
    if (GfGameRide::get() == nullptr ||
        !GfGameRide::isVehicle(static_cast<GfObj*>(m_behavior->m_owner)->m_handle)) {
        return;
    }
    GfObj* buddy = GfObjUtil::getObj(StateUtil::getBuddyHandle(*m_behavior));
    if (buddy == nullptr) {
        return;
    }
    GfComPropertyPc* property = buddy->getComponent<GfComPropertyPc>(5);
    GfComDynamics* dynamics = buddy->getComponent<GfComDynamics>(8);
    if ((property->m_stateFlags & 0x200) && dynamics != nullptr) {
        dynamics->m_updater.m_prevTransform = movement;
    }
}

void AttachPlugin::changeWallMode(bool wall) {
    if (wall == ((m_flags & FLAG_WALL_MODE) != 0)) {
        return;
    }
    if (wall) {
        GfComPropertyPc* property = m_behavior->m_owner->getComponent<GfComPropertyPc>(5);
        const EnviromentSensor* sensor = property->getEnvSensor();
        if (sensor->m_flags & 2) {
            gf::GF_OBJ_HANDLE* wallObj = sensor->m_wallObj;
            if (wallObj != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                dettachObj();
                attachObj(wallObj);
            }
        }
        m_flags |= FLAG_WALL_MODE;
    } else {
        dettachObj();
        m_flags &= ~FLAG_WALL_MODE;
    }
}

mm::mtl::RTTI AttachPlugin::m_rtti("AttachPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
