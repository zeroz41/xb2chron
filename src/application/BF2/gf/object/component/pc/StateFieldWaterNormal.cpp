#include "classes/gf/pc/StateFieldWaterNormal.h"
#include "classes/gf/pc/StateFieldWaterDive.h"
#include "classes/gf/pc/StateFieldWaterPrepareWarp.h"
#include "classes/gf/pc/StateFieldWaterDead.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "gf/MsgPcFieldNotifyWarp.h"
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

void StateFieldWaterIdle::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setIdleStatus(*property, true);
}

void StateFieldWaterIdle::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setIdleStatus(*behavior->m_owner->getComponent<GfComPropertyPc>(5), false);
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

void StateFieldWaterIdleTurn::leave(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldWaterWarpDive::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setSpecialActStatus(*behavior, false);
}

}  // namespace pc
}  // namespace gf
