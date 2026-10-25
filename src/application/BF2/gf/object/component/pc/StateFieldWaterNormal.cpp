#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/pc/StateFieldWaterDeadSink.h"
#include "classes/gf/pc/StateFieldWaterWarpDive.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/StateFieldWaterBrake.h"
#include "gf/MsgObjectNotifyHealHp.h"
#include "gf/MsgPcFieldNotifyWaterWarpBuddy.h"
#include "classes/gf/pc/StateFieldWaterSwim.h"
#include "classes/gf/pc/StateFieldWaterNormal.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/GfGamePlayerCamera.h"
#include <math.h>
#include "classes/gf/pc/FadePlugin.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/pc/StateFieldWaterDive.h"
#include "classes/gf/pc/StateFieldWaterPrepareWarp.h"
#include "classes/gf/pc/StateFieldWaterDead.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "gf/MsgPcFieldNotifyWarp.h"
#include "gf/MsgPcFieldNotifyAction.h"
#include "gf/MsgPcFieldNotifyWaterWarp.h"
#include "gf/MsgPcFieldRelaySurvive.h"
#include "gf/MsgObjectNotifyHealHp.h"
#include "gf/MsgPcGetState.h"
#include "classes/gf/pc/StateFieldWaterSink.h"
#include "classes/gf/pc/StateFieldWaterSwimSink.h"
#include "ai/Hfsm.h"
#include "classes/gf/pc/StateField.h"
#include "classes/gf/pc/StateFieldAccess.h"
#include "classes/gf/pc/StateFieldAir.h"
#include "classes/gf/pc/StateFieldAirDead.h"
#include "classes/gf/pc/StateFieldAlive.h"
#include "classes/gf/pc/StateFieldBigJump.h"
#include "classes/gf/pc/StateFieldDead.h"
#include "classes/gf/pc/StateFieldExtraControl.h"
#include "classes/gf/pc/StateFieldFall.h"
#include "classes/gf/pc/StateFieldIdle.h"
#include "classes/gf/pc/StateFieldIdleTurn.h"
#include "classes/gf/pc/StateFieldJump.h"
#include "classes/gf/pc/StateFieldLand.h"
#include "classes/gf/pc/StateFieldLandBig.h"
#include "classes/gf/pc/StateFieldLure.h"
#include "classes/gf/pc/StateFieldMove.h"
#include "classes/gf/pc/StateFieldMoveCommon.h"
#include "classes/gf/pc/StateFieldOnGround.h"
#include "classes/gf/pc/StateFieldOnWall.h"
#include "classes/gf/pc/StateFieldPrepareBigJump.h"
#include "classes/gf/pc/StateFieldRideOn.h"
#include "classes/gf/pc/StateFieldSlide.h"
#include "classes/gf/pc/StateFieldSlideLandBrake.h"
#include "classes/gf/pc/StateFieldSlideMove.h"
#include "classes/gf/pc/StateFieldStart.h"
#include "classes/gf/pc/StateFieldStopBrake.h"
#include "classes/gf/pc/StateFieldTalk.h"
#include "classes/gf/pc/StateFieldTurn.h"
#include "classes/gf/pc/StateFieldWall.h"
#include "classes/gf/pc/StateFieldWallAdsorptionAir.h"
#include "classes/gf/pc/StateFieldWallAdsorptionGround.h"
#include "classes/gf/pc/StateFieldWallAdsorptionUnderGround.h"
#include "classes/gf/pc/StateFieldWallClimbEnd.h"
#include "classes/gf/pc/StateFieldWallIdle.h"
#include "classes/gf/pc/StateFieldWallJump.h"
#include "classes/gf/pc/StateFieldWallJumpEnd.h"
#include "classes/gf/pc/StateFieldWallJumpMove.h"
#include "classes/gf/pc/StateFieldWallJumpStart.h"
#include "classes/gf/pc/StateFieldWallLand.h"
#include "classes/gf/pc/StateFieldWallMove.h"
#include "classes/gf/pc/StateFieldWallPerformance.h"
#include "classes/gf/pc/StateFieldWallPrepareJump.h"
#include "classes/gf/pc/StateFieldWater.h"
#include "classes/gf/pc/StateFieldWaterBrake.h"
#include "classes/gf/pc/StateFieldWaterDead.h"
#include "classes/gf/pc/StateFieldWaterDeadDive.h"
#include "classes/gf/pc/StateFieldWaterDeadIdle.h"
#include "classes/gf/pc/StateFieldWaterDeadRise.h"
#include "classes/gf/pc/StateFieldWaterDeadSink.h"
#include "classes/gf/pc/StateFieldWaterDive.h"
#include "classes/gf/pc/StateFieldWaterIdle.h"
#include "classes/gf/pc/StateFieldWaterIdleTurn.h"
#include "classes/gf/pc/StateFieldWaterNormal.h"
#include "classes/gf/pc/StateFieldWaterPrepareWarp.h"
#include "classes/gf/pc/StateFieldWaterRise.h"
#include "classes/gf/pc/StateFieldWaterSink.h"
#include "classes/gf/pc/StateFieldWaterSwim.h"
#include "classes/gf/pc/StateFieldWaterSwimRise.h"
#include "classes/gf/pc/StateFieldWaterSwimSink.h"
#include "classes/gf/pc/StateFieldWaterWarpDive.h"
#include "classes/gf/pc/StateFieldWaterWarpRise.h"
#include "classes/gf/pc/StateFieldWaterWarpRiseBuddy.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfGameManager.h"
#include "gf/pc/StateUtilField.h"
#include "gf/pc/StateUtil.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/MsgPcFieldWaterWarp.h"
#include "gf/MsgPcFieldWaterWarpBuddy.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfObj.h"
#include "mm/Vec3.h"
#include "classes/gf/pc/AccessPlugin.h"
#include <string.h>

namespace gf {
namespace pc {

inline void StateFieldWaterPrepareWarp::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
}

inline const char* StateFieldWaterNormal::getName() const {
    return "StateFieldWaterNormal";
}

inline void StateFieldWaterNormal::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldWaterNormal::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldWaterNormal::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDive::getName() const {
    return "StateFieldWaterDive";
}

inline void StateFieldWaterDive::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldWaterDive::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldWaterDive::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterPrepareWarp::getName() const {
    return "StateFieldWaterPrepareWarp";
}

inline void StateFieldWaterPrepareWarp::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldWaterPrepareWarp::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldWaterPrepareWarp::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDead::getName() const {
    return "StateFieldWaterDead";
}

inline void StateFieldWaterDead::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldWaterDead::onLeave(void* owner, ai::State* next) {}

inline void StateFieldWaterDead::onStep(void* owner, const void* arg) {}

// StateFieldWaterNormal: the PC swimming at the surface

void StateFieldWaterNormal::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setAccessFlag(*behavior, true);
    if (AccessPlugin* plugin = behavior->getPlugin<AccessPlugin>(4)) {
        plugin->m_accessKinds = 0x10;
    }
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.x = 0.0f;
}

void StateFieldWaterNormal::leave(GfComBehaviorPc* behavior, ai::State* next) {
    if (next != nullptr && next->m_stateID != 0x1D) {
        StateUtilField::setAccessFlag(*behavior, false);
    }
    if (AccessPlugin* plugin = behavior->getPlugin<AccessPlugin>(4)) {
        plugin->m_accessKinds = 0;
    }
}

void StateFieldWaterNormal::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfObj* target = StateUtilField::getAccessTarget(*behavior);
    if (target != nullptr && (property->m_inputFlags.m_actions & 1) != 0) {
        MsgPcFieldGetAccessType msg;
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(target, msg);
        if (msg.m_type == 4) {
            requestState(0x1D);
        }
    }
}

void StateFieldWaterNormal::onDead(GfComBehaviorPc* behavior, MsgObjectNotifyDead& msg) {
    StateUtil::notifyDead(*behavior, msg, true);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    comAsm->execCmd("C_waterdead", static_cast<AnimLayer>(0));
    requestState(0x23);
}

bool StateFieldWaterNormal::recieveMessage(void* owner, fw::MessageObject* sender, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x1000018:
        procMsgPcFieldWaterWarp(behavior, sender, static_cast<MsgPcFieldWaterWarp&>(msg));
        return true;
    case 0x1000021:
        procMsgPcFieldWaterWarpBuddy(behavior, sender, static_cast<MsgPcFieldWaterWarpBuddy&>(msg));
        return true;
    case 0x100003B:
        procMsgObjectNotifyDead(behavior, sender, static_cast<MsgObjectNotifyDead&>(msg));
        return true;
    case 0x100001F:
        procMsgPcFieldRelaySurvive(behavior, sender, static_cast<MsgPcFieldRelaySurvive&>(msg));
        return true;
    }
    return false;
}

void StateFieldWaterNormal::procMsgPcFieldWaterWarp(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                    MsgPcFieldWaterWarp& msg) {
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    MsgPcGetState getState;
    behavior->recieveMessage(static_cast<GfObj*>(behavior->m_owner), getState);
    if (getState.m_state == 0x14 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERHOLE_00)) {
        msg.m_accepted = true;
        requestState(0x1E);
    }
}

void StateFieldWaterNormal::procMsgPcFieldWaterWarpBuddy(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                         MsgPcFieldWaterWarpBuddy& msg) {
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    msg.m_accepted = true;
    requestState(0x20);
}

void StateFieldWaterNormal::procMsgObjectNotifyDead(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                    MsgObjectNotifyDead& msg) {
    onDead(behavior, msg);
    if (msg.m_deadType != 3) {
        MsgPcFieldRelaySurvive relay(&msg);
        StateUtil::sendMessageToBuddy(*behavior, relay);
    }
}

void StateFieldWaterNormal::procMsgPcFieldRelaySurvive(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                       MsgPcFieldRelaySurvive& msg) {
    fw::Message* relayed = msg.m_msg;
    if (relayed != nullptr && relayed->m_id == 0x100003B) {
        onDead(behavior, static_cast<MsgObjectNotifyDead&>(*relayed));
    }
}

// StateFieldWaterDive

void StateFieldWaterDive::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setWaterDiveMove(*property, true);
    StateUtil::setFallDamageDisable(*behavior, true);
}

void StateFieldWaterDive::leave(GfComBehaviorPc* behavior, ai::State* next) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (next == nullptr || next->m_stateID != 0x23) {
        StateUtilField::setWaterDiveMove(*property, false);
        property->m_moveVec2.x = 0.0f;
    }
    StateUtil::setFallDamageDisable(*behavior, false);
}

void StateFieldWaterDive::update(GfComBehaviorPc*, const fw::UpdateInfo&) {}

void StateFieldWaterDive::onDead(GfComBehaviorPc* behavior, MsgObjectNotifyDead& msg) {
    StateUtil::notifyDead(*behavior, msg, true);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    comAsm->execCmd("C_waterdead", static_cast<AnimLayer>(0));
    requestState(0x23);
}

bool StateFieldWaterDive::recieveMessage(void* owner, fw::MessageObject* sender, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100003B:
        procMsgObjectNotifyDead(behavior, sender, static_cast<MsgObjectNotifyDead&>(msg));
        return true;
    case 0x100001F:
        procMsgPcFieldRelaySurvive(behavior, sender, static_cast<MsgPcFieldRelaySurvive&>(msg));
        return true;
    }
    return false;
}

void StateFieldWaterDive::procMsgObjectNotifyDead(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                  MsgObjectNotifyDead& msg) {
    onDead(behavior, msg);
    if (msg.m_deadType != 3) {
        MsgPcFieldRelaySurvive relay(&msg);
        StateUtil::sendMessageToBuddy(*behavior, relay);
    }
}

void StateFieldWaterDive::procMsgPcFieldRelaySurvive(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                     MsgPcFieldRelaySurvive& msg) {
    fw::Message* relayed = msg.m_msg;
    if (relayed != nullptr && relayed->m_id == 0x100003B) {
        onDead(behavior, static_cast<MsgObjectNotifyDead&>(*relayed));
    }
}

// StateFieldWaterPrepareWarp

void StateFieldWaterPrepareWarp::enter(GfComBehaviorPc* behavior, ai::State*) {
    if (GfObj* target = StateUtilField::getAccessTarget(*behavior)) {
        MsgPcFieldNotifyAction msg(0);
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(target, msg);
    }
    StateUtilField::setAccessFlag(*behavior, false);
    StateUtilField::setSpecialActStatus(*behavior, true);
    StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), ASM_CMD_ID_FIELD_SWIM_01);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
    m_warpNotified = false;
}

void StateFieldWaterPrepareWarp::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (m_warpNotified) {
        if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERHOLE_00)) {
            GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
            MsgPcFieldNotifyWaterWarp msg(property->m_field.getWarpInfo());
            StateUtil::broadcastMainChar(*behavior, msg);
            requestState(0x1E);
        }
    } else if (!GfGameManager::isPlayerPause()) {
        requestState(0x14);
    }
}

bool StateFieldWaterPrepareWarp::recieveMessage(void* owner, fw::MessageObject* sender, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    if (msg.m_id == 0x1000014) {
        procMsgPcFieldNotifyWarp(behavior, sender, static_cast<MsgPcFieldNotifyWarp&>(msg));
        return true;
    }
    return false;
}

void StateFieldWaterPrepareWarp::procMsgPcFieldNotifyWarp(GfComBehaviorPc* behavior, fw::MessageObject* sender,
                                                          MsgPcFieldNotifyWarp& msg) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_field.setWarpInfo(&msg);
    if (sender != nullptr) {
        GfObj* obj = sender->getRTTI()->isKindOf(&GfObj::m_rtti) ? static_cast<GfObj*>(sender) : nullptr;
        if (obj != nullptr) {
            property->m_field.m_noticeSender = obj->m_handle;
        }
    }
    m_warpNotified = true;
}

// StateFieldWaterDead

void StateFieldWaterDead::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldWaterDead::onAlive(GfComBehaviorPc* behavior, MsgObjectNotifyHealHp& msg) {
    StateUtil::notifyRevival(*behavior, msg);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        requestState(0x14);
    }
}

bool StateFieldWaterDead::recieveMessage(void* owner, fw::MessageObject* sender, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100003C:
        procMsgObjectNotifyHealHp(behavior, sender, static_cast<MsgObjectNotifyHealHp&>(msg));
        return true;
    case 0x100001F:
        procMsgPcFieldRelaySurvive(behavior, sender, static_cast<MsgPcFieldRelaySurvive&>(msg));
        return true;
    }
    return false;
}

void StateFieldWaterDead::procMsgObjectNotifyHealHp(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                    MsgObjectNotifyHealHp& msg) {
    if (msg.m_healType == 0) {
        onAlive(behavior, msg);
        MsgPcFieldRelaySurvive relay(&msg);
        StateUtil::sendMessageToBuddy(*behavior, relay);
    }
}

void StateFieldWaterDead::procMsgPcFieldRelaySurvive(GfComBehaviorPc* behavior, fw::MessageObject*,
                                                     MsgPcFieldRelaySurvive& msg) {
    fw::Message* relayed = msg.m_msg;
    if (relayed != nullptr && relayed->m_id == 0x100003C &&
        static_cast<MsgObjectNotifyHealHp*>(relayed)->m_healType == 0) {
        onAlive(behavior, *static_cast<MsgObjectNotifyHealHp*>(relayed));
    }
}

// StateFieldWater: the PC in water (the parent of the water states)

void StateFieldWater::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setWaterMode(*behavior, true);
    StateUtil::setEnableLookIK(*behavior, false);
    StateUtilField::setLookAtFlag(*behavior, false);
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveSpeed = 0.0f;
}

void StateFieldWater::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setWaterMode(*behavior, false);
    StateUtil::setEnableLookIK(*behavior, true);
    StateUtilField::setLookAtFlag(*behavior, true);
}

void StateFieldWater::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    if (property->m_waterDepth <= property->m_waterLeaveDepth || StateUtilField::isInterruptionWater(*property)) {
        GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
        if (property->existInputXY()) {
            if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
                requestState(7);
            }
        } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
            requestState(3);
        }
    }
}

void StateFieldWaterIdle::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setIdleStatus(*property, true);
}

void StateFieldWaterIdle::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setIdleStatus(*behavior->m_owner->getComponent<GfComPropertyPc>(5), false);
}

void StateFieldWaterIdle::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (property->existInputXY()) {
        GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
        if (StateUtilField::isInputInverseDir(*property)) {
            requestState(0x15);
        } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
            requestState(0x16);
        }
    }
}

void StateFieldWaterSwim::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterBrake::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterSink::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    m_time = 0.0f;
}

void StateFieldWaterSink::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterRise::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.x = 0.0f;
}

void StateFieldWaterRise::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterSwimSink::enter(GfComBehaviorPc*, ai::State*) {
    m_time = 0.0f;
}

void StateFieldWaterSwimSink::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterSwimRise::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.x = 0.0f;
}

void StateFieldWaterSwimRise::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterIdleTurn::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    m_dir = property->m_inputDir.y * property->m_groundFrontDir + property->m_inputDir.x * property->m_stickSideDir;
    if (m_dir.isZero()) {
        m_dir = property->m_moveDirInv;
    } else {
        float length = m_dir.length();
        if (length <= 1e-6f) {
            m_dir = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            m_dir.x = scale * m_dir.x;
            m_dir.y = scale * m_dir.y;
            m_dir.z = scale * m_dir.z;
        }
    }
    StateUtilField::notifyTurn(*behavior);
}

void StateFieldWaterIdleTurn::leave(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldWaterIdleTurn::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (StateUtilField::isTurnEndRangeCacheInput(*property, m_dir)) {
        GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
        if (!property->existInputXY()) {
            requestState(0x14);
            return;
        }
        if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
            requestState(0x16);
            return;
        }
    }
    MoveUtilField::updateMoveWaterTurn(info, *property, m_dir);
}

void StateFieldWaterWarpDive::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setSpecialActStatus(*behavior, false);
}

void StateFieldWaterSwim::enter(GfComBehaviorPc* behavior, ai::State*) {
    MoveUtilField::enterMoveSwim(*behavior->m_owner->getComponent<GfComPropertyPc>(5));
}

void StateFieldWaterSwim::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (StateUtilField::isTurnRange(*property, m_inputQueue) &&
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_01)) {
        requestState(0x15);
    } else if (property->existInputXY()) {
        MoveUtilField::updateMoveSwim(info, *property);
        StateUtilField::setAsmSpeedSwim(*property);
    } else {
        requestState(0x17);
    }
}

void StateFieldWaterBrake::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.y = 0.0f;
    m_slowCmdRun = false;
}

void StateFieldWaterBrake::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (property->existInputXY()) {
        if (StateUtilField::isInputInverseDir(*property)) {
            StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_01);
            requestState(0x15);
        } else {
            StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00);
            requestState(0x16);
        }
        return;
    }
    const GfPropertyField::MoveParam* param =
        property->m_field.m_paramList->getAdapter(0).get<GfPropertyField::MoveParam>();
    MoveUtilField::updateBrake(info, *property);
    float speed = property->m_velocity.length();
    if (speed <= 0.0f && strcmp(comAsm->getStateName(static_cast<AnimLayer>(0)), "S_wateridle") == 0) {
        requestState(0x14);
    }
    if (!m_slowCmdRun && speed <= param->m_brakeSlowSpeed) {
        if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_01)) {
            m_slowCmdRun = true;
        }
    }
}

void StateFieldWaterSink::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    const GfPropertyField::WaterParam* param =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    m_time += info.m_deltaTime;
    if ((property->m_stateFlags & 0x10) != 0 || m_time >= param->m_sinkTime) {
        requestState(0x1A);
    } else if (StateUtilField::getChildFrameHeight(*behavior) <= -param->m_sinkDepth) {
        property->m_moveVec2.x = 0.0f;
    } else {
        MoveUtilField::updateMoveWaterSink(info, *property);
    }
}

void StateFieldWaterSwimSink::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    const GfPropertyField::WaterParam* param =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    m_time += info.m_deltaTime;
    if (m_time >= param->m_swimSinkTime &&
        StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), ASM_CMD_ID_FIELD_SWIM_00)) {
        requestState(0x1C);
        return;
    }
    MoveUtilField::updateMoveSwim(info, *property);
    if (StateUtilField::getChildFrameHeight(*behavior) <= -param->m_sinkDepth) {
        property->m_moveVec2.x = 0.0f;
    } else {
        MoveUtilField::updateMoveWaterSink(info, *property);
    }
}

void StateFieldWaterRise::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    MoveUtilField::updateMoveWaterRise(info, *property);
    float move = info.m_deltaTime * property->m_moveVec2.x;
    if (StateUtilField::getChildFrameHeight(*behavior) + move >= 0.0f) {
        requestState(0x14);
    }
}

void StateFieldWaterSwimRise::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    MoveUtilField::updateMoveSwim(info, *property);
    MoveUtilField::updateMoveWaterRise(info, *property);
    float move = info.m_deltaTime * property->m_moveVec2.x;
    if (StateUtilField::getChildFrameHeight(*behavior) + move >= 0.0f) {
        requestState(0x16);
    }
}

void StateFieldWaterWarpDive::enter(GfComBehaviorPc* behavior, ai::State*) {
    m_time = 0.0f;
    m_fadeStarted = false;
    StateUtilField::setSpecialActStatus(*behavior, true);
    StateUtilField::notifySkillAct(*behavior, true);
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    const GfPropertyField::WaterParam* water =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    const FadePlugin::Param* fade = property->m_field.m_paramList->getAdapter(18).get<FadePlugin::Param>();
    m_fadeStartTime = water->m_warpDiveTime - fade->m_fadeOutWait;
    property->m_moveVec2.x = 0.0f;
}

void StateFieldWaterWarpDive::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    m_time += info.m_deltaTime;
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    property->setLocomotion(*comAsm->getLocomotion());
    if (!m_fadeStarted && m_time >= m_fadeStartTime && property->m_setupKind == 0) {
        StateUtilField::startWaterWarpFade(*behavior);
        m_fadeStarted = true;
    }
    const GfPropertyField::WaterParam* water =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    if (m_time > water->m_warpDiveTime && comAsm->setState("S_waterhole_01", static_cast<AnimLayer>(0))) {
        const MsgPcFieldNotifyWarp* warp = property->m_field.getWarpInfo();
        MsgPcFieldNotifyWaterWarpBuddy notify(warp);
        StateUtil::sendMessageToBuddy(*behavior, notify);
        mm::Vec3 pos = warp->m_pos;
        pos.y -= property->m_chestHeight;
        property->m_pos = pos;
        float half = warp->m_param * 0.5f;
        property->m_rot = mm::Quat(0.0f, sinf(half), 0.0f, cosf(half));
        property->syncDirection();
        StateUtilField::setChildFrameHeight(*behavior, -property->m_field.m_warpRiseDepth);
        if (GfComDynamics* dynamics = behavior->m_owner->getComponent<GfComDynamics>(8)) {
            dynamics->resetMovement();
        }
    if (property->m_setupKind == 0) {
            GfGamePlayerCamera::requestResetCamera();
        }
        property->m_field.m_statusFlags &= ~0x40;
        requestState(0x1F);
    }
}

void StateFieldWaterWarpRise::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setSpecialActStatus(*behavior, true);
}

void StateFieldWaterWarpRise::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setSpecialActStatus(*behavior, false);
    StateUtilField::notifySkillAct(*behavior, false);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfPropertyField& field = property->m_field;
    if (const MsgPcFieldNotifyWarp* warp = field.getWarpInfo()) {
        if ((property->m_stateFlags & 0x400) != 0) {
            SCOM_QUEST_GIMMICK::createWarp(warp->m_gmkId, 0.0f);
        }
        field.setBigJumpInfo(nullptr);
    }
}

void StateFieldWaterWarpRise::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    property->setLocomotion(*comAsm->getLocomotion());
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        requestState(0x14);
    }
}

void StateFieldWaterWarpRiseBuddy::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    const MsgPcFieldNotifyWarp* warp = property->m_field.getWarpInfo();
    mm::Vec3 pos = warp->m_pos;
    pos.y -= property->m_chestHeight;
    property->m_pos = pos;
    float half = warp->m_param * 0.5f;
    property->m_rot = mm::Quat(0.0f, sinf(half), 0.0f, cosf(half));
    property->syncDirection();
    StateUtilField::setChildFrameHeight(*behavior, -property->m_field.m_warpRiseDepth);
    if (GfComDynamics* dynamics = behavior->m_owner->getComponent<GfComDynamics>(8)) {
        dynamics->resetMovement();
    }
}

void StateFieldWaterWarpRiseBuddy::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterWarpRiseBuddy::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    MoveUtilField::updateMoveWaterHoleRise(info, *property);
    float move = info.m_deltaTime * property->m_moveVec2.x;
    if (StateUtilField::getChildFrameHeight(*behavior) + move >= 0.0f) {
        requestState(0x14);
    }
}

// StateFieldWaterDeadDive, DeadSink, DeadRise, DeadIdle: the dead PC in water

void StateFieldWaterDeadDive::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    if (property->m_wallJumpState == 1) {
        return;
    }
    StateUtilField::setWaterDiveMove(*property, true);
}

void StateFieldWaterDeadDive::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setWaterDiveMove(*behavior->m_owner->getComponent<GfComPropertyPc>(5), false);
}

void StateFieldWaterDeadDive::update(GfComBehaviorPc*, const fw::UpdateInfo&) {}

void StateFieldWaterDeadSink::enter(GfComBehaviorPc* behavior, ai::State*) {
    m_time = 0.0f;
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    const GfPropertyField::WaterParam* param =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    float speed = property->m_moveVec2.x;
    float limit = -param->m_maxSinkSpeed;
    property->m_moveVec2.x = speed < limit ? speed : limit;
}

void StateFieldWaterDeadSink::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterDeadSink::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    const GfPropertyField::WaterParam* param =
        property->m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    m_time += info.m_deltaTime;
    if ((property->m_stateFlags & 0x10) != 0 || m_time >= param->m_sinkTime) {
        requestState(0x24);
    } else if (StateUtilField::getChildFrameHeight(*behavior) <= -param->m_sinkDepth) {
        property->m_moveVec2.x = 0.0f;
    } else {
        MoveUtilField::updateMoveWaterSink(info, *property);
    }
}

void StateFieldWaterDeadRise::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.x = 0.0f;
}

void StateFieldWaterDeadRise::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterDeadRise::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    MoveUtilField::updateMoveWaterRise(info, *property);
    float move = info.m_deltaTime * property->m_moveVec2.x;
    if (StateUtilField::getChildFrameHeight(*behavior) + move >= 0.0f) {
        requestState(0x25);
    }
}

void StateFieldWaterDeadIdle::enter(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterDeadIdle::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWaterDeadIdle::fn_7100507984(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    if (property->m_status.get()->m_hp != 0) {
        MsgObjectNotifyHealHp msg;
        GfObj* obj = static_cast<GfObj*>(behavior->m_owner);
        obj->sendMessage(obj, msg);
    }
}

}  // namespace pc
}  // namespace gf
