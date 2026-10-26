#include "mm/mtl/Delegate.h"
#include "classes/gf/pc/PadField.h"
#include "btl/Utility.h"
#include "anm/AsmAnnotetion.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/gf/GfMoveRunControler.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/pc/PadField.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/GfMoveFallControler.h"
#include "classes/gf/GfMoveTurnControler.h"
#include "classes/gf/GfMoveBrakeControler.h"
#include "classes/gf/GfMoveWaterSinkControler.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/anm/ResASM.h"
#include "anm/AsmAnnotetion.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"
#include "btl/challenge_battle_manager.h"
#include "btl/Utility.h"

namespace gf { namespace pc {

void AgentUtilField::setIdleInput(GfComPropertyPc& property) {
    property.setInputDirPow(property.m_moveDir, 0.0f);
}

// the state machine's S_uniqueA state carries a "look" annotation: 0 entering it, 1 leaving it
void registerAsmCallbackField(GF_OBJ_HANDLE* obj, anm::ResASM* res) {
    anm::AsmAnnotetion annotation;
    annotation.m_name = "look";
    annotation.m_type = 0;
    annotation.m_value = 0;
    res->setEnterAnnotation(1, "S_uniqueA", annotation);
    annotation.m_name = "look";
    annotation.m_type = 0;
    annotation.m_value = 1;
    res->setLeaveAnnotation(1, "S_uniqueA", annotation);
    res->sortAnnotation(1);
}

void MoveUtilField::updateMoveRun(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveRunPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateBrake(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveBrakeControler controler;
    GfMoveBrakeControler::Packet packet;
    packet.m_velocity = property.m_velocity;
    packet.m_param = property.m_field.m_paramList->getAdapter(1);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
}

void MoveUtilField::updateMoveTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(4);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

void MoveUtilField::updateMoveWalkTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(5);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

void MoveUtilField::updateMoveJump(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveJumpControler controler;
    GfMoveJumpControler::Packet packet;
    setMoveJumpPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateFallDown(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveFallControler controler;
    GfMoveFallControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(8);
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

void MoveUtilField::updateMoveSwim(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveSwimPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateMoveWaterTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(11);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

void MoveUtilField::updateMoveWaterSink(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveWaterSinkControler controler;
    GfMoveWaterSinkControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(12);
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

}}  // namespace gf::pc

namespace gf {

void GfComBehaviorPc::callbackField(GfComAsm* asmCom, const CallBackCache& cache) {}

}  // namespace gf

namespace gf { namespace pc {

PadField::PadField() : m_property(nullptr) {}

void PadField::setup(int padNo, GfComPropertyPc& property) {
    m_relay.bind(padNo, 0, getAllocator(ALLOCATOR(0)));
    m_relay.bindAction("decide", this, &PadField::decideAction);
    m_relay.bindAction("jump", this, &PadField::jumpAction);
    m_relay.bindAction("lock", this, &PadField::lockAction);
    m_relay.bindAction("wall_release", this, &PadField::wallReleaseAction);
    m_relay.bindAction("lure", this, &PadField::lureAction);
    m_relay.bindAxis("move_front", this, &PadField::moveFront);
    m_relay.bindAxis("move_side", this, &PadField::moveSide);
}

void PadField::decideAction() const {
    if (btl::Utility::fn_710000FBC4() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(0));
}

void PadField::jumpAction() const {
    if (GfGameManager::isDisableJumpForRide()) {
        return;
    }
    if (btl::Utility::fn_710000FBC4() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(2));
}

void PadField::lockAction() const {
    if (GfGameManager::isDisableAutoRun()) {
        return;
    }
    if (btl::Utility::fn_710000FBC4() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(1));
}

void PadField::wallReleaseAction() const {
    if (btl::Utility::fn_710000FBC4() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(3));
}

void PadField::lureAction() const {
    if (btl::Utility::fn_710000FBC4() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    if (btl::TUnk_B3A9C8::sys()->fn_7100026A48()) {
        return;
    }
    setInput(InputID(4));
}

void PadField::moveFront(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 1)) {
        if (btl::Utility::fn_710000FBC4()) {
            m_property->m_inputDir.y = 0.0f;
        } else {
            m_property->m_inputDir.y = value;
        }
    }
}

void PadField::moveSide(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 1)) {
        if (btl::Utility::fn_710000FBC4()) {
            m_property->m_inputDir.x = 0.0f;
        } else {
            m_property->m_inputDir.x = value;
        }
    }
}

void PadField::cleanup(GfComPropertyPc& property) {
    m_relay.unbind();
}

void PadField::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    m_property = &property;
    m_relay.update();
    m_property = nullptr;
}

void PadField::setInput(InputID id) const {
    if (m_property != nullptr) {
        m_property->m_inputFlags.m_actions |= 1u << id;
    }
}

}}  // namespace gf::pc
