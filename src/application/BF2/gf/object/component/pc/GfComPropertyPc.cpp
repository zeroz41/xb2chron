#include "gf/FileStaticVec3.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Message.h"
#include "gf/MsgObjectGetVelocity.h"
#include "gf/MsgPcFieldNotifyChangePlayerID.h"
#include "anm/QsTransform.h"
#include "mm/Math.h"

namespace gf {

inline GfComPropertyPc::~GfComPropertyPc() {}

GfComPropertyPc::GfComPropertyPc()
    : m_setupKind(-1), m_battleStartKind(0), m_headColiHeight(0.0f), m_headColiPos(mm::Vec3::zero), m_inputDir(),
      m_inputFlags(), m_prevInputDir(), m_prevInputFlags(), m_velocity(mm::Vec3::zero), m_moveVec2(0.0f, 0.0f),
      m_moveSpeed(0.0f), pad_d0(mm::Vec3::zero), pad_e0(mm::Vec3::zero), pad_f0(0.0f), m_colVel(mm::Vec3::zero),
      m_stateFlags(0), m_waterLevel(0), pad_118(0.0f), m_waterDepth(0.0f), m_wallJumpState(0), m_warpType(0),
      m_frontDir(mm::Vec3::zero), m_frontDirInv(mm::Vec3::zero), m_moveDir(mm::Vec3::zero),
      m_moveDirInv(mm::Vec3::zero), m_sideDir(mm::Vec3::zero), m_sideDirInv(mm::Vec3::zero),
      m_viewPos(mm::Vec3::zero), m_viewUp(mm::Vec3::zero), m_viewDown(mm::Vec3::zero), m_viewFront(mm::Vec3::zero),
      m_viewBack(mm::Vec3::zero), m_viewRight(mm::Vec3::zero), m_viewLeft(mm::Vec3::zero),
      m_stickFrontDir(mm::Vec3::zero), m_stickFrontDirInv(mm::Vec3::zero), m_groundFrontDir(mm::Vec3::zero),
      m_groundFrontDirInv(mm::Vec3::zero), m_stickSideDir(mm::Vec3::zero), m_stickSideDirInv(mm::Vec3::zero),
      m_chestHeight(0.0f), m_waistHeight(0.0f), m_waterLeaveDepth(0.0f) {
    m_locomotion.m_translation = mm::Vec3::zero;
    m_locomotion.m_rotation = mm::Quat::identity;
}

void GfComPropertyPc::resetParams() {
    fw::ParamManager* manager = fw::ParamManager::get();
    m_paramList = manager->m_paramLists[13];
    if (m_stateFlags & 0x400) {
        m_field.m_paramList = manager->m_paramLists[14];
    } else {
        m_field.m_paramList = manager->m_paramLists[15];
    }
}

void GfComPropertyPc::cleanup() {
    m_battle.cleanup(*this);
    m_field.cleanup(*this);
    m_field.m_paramList = nullptr;
    m_paramList = nullptr;
    m_setupKind = -1;
    m_battleStartKind = 0;
}

void GfComPropertyPc::writeBack() {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    fw::Transform& world = transform->m_frame->getWorldTransformForWrite();
    world.position = m_pos;
    world.rotation = m_rot;
    if (transform->m_frame->m_parent != nullptr) {
        transform->m_frame->syncLocalTransform();
    }
    if (transform->m_childFrame) {
        transform->m_childFrame->getLocalTransformForWrite();
        transform->m_childFrame->syncWorldTransform();
    }
    m_prevPos = m_lastPos;
    m_prevRot = m_lastRot;
}

void GfComPropertyPc::setPadControl(bool on) {
    if (on) {
        m_stateFlags |= 0x400;
    } else {
        m_stateFlags &= ~0x400;
    }
    resetParams();
    m_field.resetStatus(*this);
}

bool GfComPropertyPc::existInputXY() const {
    const float* threshold = getParam<float>(0);
    if (mm::fabs(m_inputDir.x) < *threshold && mm::fabs(m_inputDir.y) < *threshold) {
        return false;
    }
    return true;
}

const GfComPropertyPc::Locomotion* GfComPropertyPc::getLocomotion() const {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAC3B0, guard lbl_7100EAC3D0)
    static const Locomotion s_none = {mm::Vec3::zero, mm::Quat::identity};
    return (m_stateFlags & 4) ? &m_locomotion : &s_none;
}

void GfComPropertyPc::setLocomotion(const anm::QsTransform& locomotion) {
    m_locomotion.m_translation = mm::Vec3(locomotion.m_translation.x, locomotion.m_translation.y,
                                          locomotion.m_translation.z);
    m_locomotion.m_rotation = locomotion.m_rotation;
    m_stateFlags |= 4;
}

float GfComPropertyPc::getGravity() const {
    if (!(m_stateFlags & 8)) {
        return 0.0f;
    }
    return -*getParam<float>(1);
}

const EnviromentSensor* GfComPropertyPc::getEnvSensor() const {
    GfComEnvSensor* sensor = m_owner->getComponent<GfComEnvSensor>(11);
    return &sensor->getSensor();
}

void GfComPropertyPc::setEnvSensorCheckFlags(unsigned int flags, bool on) {
    GfComEnvSensor* sensor = m_owner->getComponent<GfComEnvSensor>(11);
    if (on) {
        sensor->m_sensor.m_checkFlags |= flags;
    } else {
        sensor->m_sensor.m_checkFlags &= ~flags;
    }
}

bool GfComPropertyPc::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x100003E) {
        procMsgObjectFlushProperty(sender, reinterpret_cast<MsgObjectFlushProperty&>(msg));
        return true;
    }
    if (msg.m_id == 0x1000049) {
        procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity&>(msg));
        return true;
    }
    if (msg.m_id == 0x100001D) {
        procMsgPcFieldNotifyChangePlayerID(sender, static_cast<MsgPcFieldNotifyChangePlayerID&>(msg));
        return true;
    }
    if (msg.m_id == 0x1000003) {
        procMsgActivateComponentDebugWindow(sender, reinterpret_cast<MsgDebugActivateComponentWindow&>(msg));
        return true;
    }
    if (m_stateFlags & 1) {
        if (m_field.recieveMessage(*this, sender, msg)) {
            return true;
        }
    }
    if (m_stateFlags & 2) {
        pc::GfPropertyPcInterface& battle = m_battle;
        if (battle.recieveMessage(*this, sender, msg)) {
            return true;
        }
    }
    return GfComProperty::recieveMessage(sender, msg);
}

void GfComPropertyPc::procMsgActivateComponentDebugWindow(fw::MessageObject* sender,
                                                          MsgDebugActivateComponentWindow& msg) {}

void GfComPropertyPc::procMsgPcFieldNotifyChangePlayerID(fw::MessageObject* sender,
                                                         MsgPcFieldNotifyChangePlayerID& msg) {
    m_setupKind = msg.m_playerID;
}

void GfComPropertyPc::procMsgObjectGetVelocity(fw::MessageObject* sender, MsgObjectGetVelocity& msg) {
    msg.m_velocity = m_moveVec2.x * mm::Vec3::unitY + m_velocity;
}

mm::mtl::RTTI GfComPropertyPc::m_rtti("GfComPropertyPc", &GfComProperty::m_rtti, nullptr);

}  // namespace gf
