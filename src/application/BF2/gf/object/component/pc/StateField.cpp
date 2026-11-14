#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/StateFieldExtraControl.h"
#include "gf/MsgPcGetElvLift.h"
#include "gf/MsgPcFieldElvWarp.h"
#include "gf/MsgPcGetElvLift.h"
#include "gf/MsgPcFieldElvWarp.h"
#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/MsgObjectDamage.h"
#include "gf/MsgPcFieldNotifyAction.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/StateField.h"
#include "classes/gf/pc/StateFieldTalk.h"
#include "classes/gf/pc/StateFieldPrepareBigJump.h"
#include "classes/gf/pc/StateFieldRideOn.h"
#include "classes/gf/pc/StateFieldDead.h"
#include "gf/MsgPcBattleStart.h"
#include "gf/MsgPcFieldNotifyBigJump.h"
#include "gf/MsgPcFieldNotifyRiderEvent.h"
#include "anm/StringPtr.h"
#include "gf/MsgGameTalkAction.h"
#include "gf/MsgGameLipAction.h"
#include "gf/MsgUnk_1000030.h"
#include "gf/MsgObjectNotifyHealHp.h"
#include "gf/MsgPcFieldRelaySurvive.h"
#include "gf/MsgUnk_100003A.h"
#include "gf/MsgUnk_100001A.h"
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
#include "classes/gf/pc/StateFieldStart.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/LipSyncPlugin.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/btl/BladeChangeManager.h"
#include "gf/MsgUnk_1000026.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/MsgUnk_1000044.h"
#include "gf/MsgPcFieldNotifyHighJump.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"

namespace gf { namespace pc {

// the field states' slots: inline (their tables have no key function; registerFieldStates makes the states, so their
// tables and slots are emitted here), handing the owner and the step argument to the state's own functions
// the states' own functions the original defines inline (no out-of-line copy: their slots carry their code); the
// names enter/leave/update are inferred from the other states' slots (not the original's)
inline void StateFieldPrepareBigJump::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    if (!GfGameManager::isPlayerPause()) {
        requestState(3);
    }
}

inline const char* StateField::getName() const {
    return "StateField";
}
inline void StateField::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateField::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateField::onStep(void* owner, const void* arg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    GfComPropertyPc& property = *behavior->m_owner->findComponent<GfComPropertyPc>(5);
    if (property.m_inputFlags[1]) {
        StateUtilField::flipAutoRun(property);
    }
    if (StateUtilField::isInputInverseDirAutoRun(property)) {
        StateUtilField::setAutoRun(property, false);
    }
    if (StateUtilField::testAutoRun(property)) {
        StateUtilField::setAutoRunInput(property);
    }
}

inline const char* StateFieldRideOn::getName() const {
    return "StateFieldRideOn";
}
inline void StateFieldRideOn::onEnter(void* owner, ai::State* prev) {
    static_cast<GfComBehaviorPc*>(owner)->m_owner->findComponent<GfComPropertyPc>(5)->m_stateFlags |= 1;
}
inline void StateFieldRideOn::onLeave(void* owner, ai::State* next) {
    static_cast<GfComBehaviorPc*>(owner)->m_owner->findComponent<GfComPropertyPc>(5)->m_stateFlags &= ~1u;
}
inline void StateFieldRideOn::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldDead::getName() const {
    return "StateFieldDead";
}
inline void StateFieldDead::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldDead::onLeave(void* owner, ai::State* next) {}
inline void StateFieldDead::onStep(void* owner, const void* arg) {
    if (m_waitAnimEnd) {
        GfComAsm* com = static_cast<GfComBehaviorPc*>(owner)->m_owner->getComponent<GfComAsm>(2);
        if (com->isEnd(AnimLayer(0)) && StateUtilField::execAsmCmd(*com, static_cast<ASM_CMD_ID_FIELD>(0x20))) {
            m_waitAnimEnd = false;
        }
    }
}

inline const char* StateFieldTalk::getName() const {
    return "StateFieldTalk";
}
inline void StateFieldTalk::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldTalk::onLeave(void* owner, ai::State* next) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    if (GfObj* obj = GfObjUtil::getObj(m_target)) {
        MsgPcFieldNotifyAction action(1);
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(obj, action);
    }
    StateUtilField::setSpecialActStatus(*behavior, false);
    MsgUnk_100001A end;
    StateUtil::broadcastPlayer(*behavior, end);
    StateUtil::setEnableDownIK(*behavior, false);
}
inline void StateFieldTalk::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldPrepareBigJump::getName() const {
    return "StateFieldPrepareBigJump";
}
inline void StateFieldPrepareBigJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldPrepareBigJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldPrepareBigJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}


void StateField::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfObjUtil::setEnableEyeBlink(static_cast<GfObj*>(behavior->m_owner)->m_handle, true);
    StateUtilField::setLookAtFlag(*behavior, true);
    StateUtil::setEnableLookIK(*behavior, true);
    StateUtil::setEnableAgentField(*behavior, true);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::switchPlacementIK(*behavior, true);
    StateUtil::setEnableHeadDetectForSwitcher(*behavior, true);
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_stateFlags |= 1;
    StateUtil::setEnvSensor(*behavior, 0xD0, true);
    StateUtil::setFallDamageDisable(*behavior, false);
    StateUtil::setEnableSpineIK(*behavior, true);
    StateUtil::setEnableAttach(*behavior, true);
    StateUtil::setEnableTimer(*behavior, true);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
}

void StateField::leave(GfComBehaviorPc* behavior, ai::State* next) {
    GfObjUtil::setEnableEyeBlink(static_cast<GfObj*>(behavior->m_owner)->m_handle, false);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    StateUtilField::setAutoRun(*property, false);
    StateUtilField::setLookAtFlag(*behavior, false);
    StateUtil::setEnableAgentField(*behavior, false);
    property->m_stateFlags &= ~1u;
    StateUtil::setEnvSensor(*behavior, 0xD0, false);
    StateUtil::setEnableHeadDetectForSwitcher(*behavior, false);
    StateUtil::setEnableSpineIK(*behavior, false);
    StateUtil::switchPlacementIK(*behavior, false);
    StateUtil::setEnableAttach(*behavior, false);
    StateUtil::setEnableTimer(*behavior, false);
}

void StateField::onDead(GfComBehaviorPc* behavior, MsgObjectNotifyDead& msg) {
    if (!btl::BladeChangeManager::sys()->IsEnableFieldDead(static_cast<GfObj*>(behavior->m_owner)->m_handle)) {
        return;
    }
    StateUtil::notifyDead(*behavior, msg, true);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (msg.m_deadType == 4) {
        if (strcmp(com->getStateName(AnimLayer(0)), "S_fall") != 0) {
            com->setState("S_fall", AnimLayer(0));
        }
        com->execCmd("C_falldead", AnimLayer(0));
        StateUtil::setFallDamageDisable(*behavior, true);
        MsgUnk_1000026 notify;
        StateUtil::sendMessageToBuddy(*behavior, notify);
    } else {
        unsigned int flags = property->m_stateFlags;
        com->setState("S_idle", AnimLayer(0));
        if (flags & 0x10) {
            StateUtilField::execAsmCmd(*com, static_cast<ASM_CMD_ID_FIELD>(0x1D));
            requestState(0x3A);
        } else {
            if (!StateUtilField::execAsmCmd(*com, static_cast<ASM_CMD_ID_FIELD>(0x1E))) {
                StateUtilField::execAsmCmd(*com, static_cast<ASM_CMD_ID_FIELD>(0x1D));
            }
            requestState(0x3C);
        }
    }
}

bool StateField::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100000A: {
        GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
        property->m_battle.SetStartCondition(static_cast<MsgPcBattleStart&>(msg));
        requestState(0x3F);
        return true;
    }
    case 0x100001F: {
        fw::Message* inner = static_cast<MsgPcFieldRelaySurvive&>(msg).m_msg;
        if (inner != nullptr && inner->m_id == 0x100003B) {
            onDead(behavior, static_cast<MsgObjectNotifyDead&>(*inner));
        }
        return true;
    }
    case 0x100003A: {
        const MsgObjectDamage* damage = static_cast<MsgObjectNotifyDamage&>(msg).m_damage;
        if (damage != nullptr && damage->m_type == 0) {
            unsigned char type = damage->m_battleStartType;
            if (type != 0) {
                MsgPcBattleStart start(3);
                start.m_param0 = type;
                start.m_param1 = damage->m_battleStartParam;
                GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
                property->m_battle.SetStartCondition(start);
                requestState(0x3F);
            }
        }
        return true;
    }
    case 0x100003B:
        procMsgObjectNotifyDead(behavior, from, static_cast<MsgObjectNotifyDead&>(msg));
        return true;
    }
    return false;
}

void StateField::procMsgObjectNotifyDead(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgObjectNotifyDead& msg) {
    const fw::Message* cause = msg.m_cause;
    if (cause != nullptr && cause->m_id == 0x1000035 && static_cast<const MsgObjectDamage*>(cause)->m_type == 0) {
        GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
        property->m_velocity = mm::Vec3::zero;
        property->m_moveVec2.x = 0.0f;
        property->m_moveVec2.y = 0.0f;
        MsgPcBattleStart start(2);
        property->m_battle.SetStartCondition(start);
        requestState(0x3F);
        return;
    }
    onDead(behavior, msg);
    if (msg.m_deadType != 4) {
        MsgPcFieldRelaySurvive relay(&msg);
        StateUtil::sendMessageToBuddy(*behavior, relay);
    }
}

void StateFieldStart::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtilField::setSpecialActStatus(*behavior, true);
    if (!(behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_stateFlags & 0x400)) {
        StateUtil::setTarget(*behavior, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    }
}

void StateFieldStart::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
}

void StateFieldStart::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (property->m_waterLevel == 3) {
        if (property->m_stateFlags & 0x800) {
            if (StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_WATERDEAD)) {
                requestState(0x23);
            }
        } else if (StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_WATERIDLE)) {
            requestState(0x19);
        }
    } else if (property->m_stateFlags & 0x10) {
        const char* state = com->getStateName(AnimLayer(0));
        if (state != nullptr && strcmp(state, "S_idle") == 0) {
            requestState(3);
        }
    } else if (StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_FALL)) {
        requestState(0xF);
    }
}

void StateFieldAccess::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (GfObj* target = StateUtilField::getAccessTarget(*behavior)) {
        if (property->m_stateFlags & 0x400) {
            MsgPcGetElvLift lift;
            static_cast<fw::MessageObject*>(target)->recieveMessage(&static_cast<fw::MessageObject&>(*static_cast<GfObj*>(behavior->m_owner)), lift);
            if (lift.m_isLiftSwitch) {
                MsgPcFieldElvWarp warp(&lift, target->m_handle);
                StateUtil::broadcastPlayer(*behavior, warp);
            }
        }
        m_target = target->m_handle;
        MsgPcFieldNotifyAction action(0);
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(target, action);
    }
    StateUtilField::setAccessFlag(*behavior, false);
    StateUtilField::setSpecialActStatus(*behavior, true);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    StateUtil::setEnableDownIK(*behavior, true);
    GfObjUtil::setInvincible(static_cast<GfObj*>(behavior->m_owner)->m_handle, true, false);
}

void StateFieldAccess::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    if (strcmp(behavior->m_owner->getComponent<GfComAsm>(2)->getStateName(AnimLayer(0)), "S_idle") == 0 &&
        !GfGameManager::isPlayerPause()) {
        requestState(3);
    }
}

// the talk's motions by MsgGameTalkAction's action: the states (proposed name, not the original's: the symbols leave it
// unnamed, lbl_7100B68048) and the commands tried first (proposed name, not the original's: lbl_7100B68068)
static const char* const sTalkStateNames[4] = {"S_talkA_00", "S_talkA_01", "S_talkA_02", "S_idle"};
static const char* const sTalkCmdNames[4] = {"C_talkA_00", nullptr, "C_talkA_02", nullptr};

void StateFieldTalk::procMsgGameTalkAction(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgGameTalkAction& msg) {
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (msg.m_setState) {
        msg.m_result = com->setState(sTalkStateNames[msg.m_action], AnimLayer(0));
        return;
    }
    if (sTalkCmdNames[msg.m_action] != nullptr) {
        msg.m_result = com->execCmd(sTalkCmdNames[msg.m_action], AnimLayer(0));
    }
    if (!msg.m_result && sTalkCmdNames[msg.m_action] != nullptr) {
        msg.m_result = com->setState(sTalkStateNames[msg.m_action], AnimLayer(0));
    }
}

bool StateFieldTalk::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100002E:
        procMsgGameTalkAction(behavior, from, static_cast<MsgGameTalkAction&>(msg));
        return true;
    case 0x100002F:
        procMsgGameLipAction(behavior, from, static_cast<MsgGameLipAction&>(msg));
        return true;
    case 0x1000030:
        if (LipSyncPlugin* lipSync = behavior->getPlugin<LipSyncPlugin>(2)) {
            lipSync->setWeight(static_cast<MsgUnk_1000030&>(msg).m_weight);
        }
        return true;
    }
    return false;
}

void StateFieldTalk::procMsgGameLipAction(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgGameLipAction& msg) {
    if (msg.m_action == 0) {
        if (LipSyncPlugin* lipSync = behavior->getPlugin<LipSyncPlugin>(2)) {
            lipSync->m_forcePlay = true;
        }
    } else if (msg.m_action == 1) {
        if (LipSyncPlugin* lipSync = behavior->getPlugin<LipSyncPlugin>(2)) {
            lipSync->m_forcePlay = false;
        }
    }
}

void StateFieldTalk::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    if (GfObj* target = StateUtilField::getAccessTarget(*behavior)) {
        m_target = target->m_handle;
        MsgPcFieldNotifyAction action(0);
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(target, action);
    }
    StateUtilField::setAccessFlag(*behavior, false);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setSpecialActStatus(*behavior, true);
    StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), ASM_CMD_ID_FIELD_IDLE);
    StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldTalk::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    if (GfGameManager::isPlayerPause()) {
        return;
    }
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    const char* state = com->getStateName(AnimLayer(0));
    bool done = strcmp(state, "S_idle") == 0;
    done |= strcmp(state, "S_talkA_02") == 0;
    if (done || StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_IDLE)) {
        requestState(3);
    }
}

void StateFieldPrepareBigJump::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    if (GfObj* target = StateUtilField::getAccessTarget(*behavior)) {
        MsgPcFieldNotifyAction action(0);
        static_cast<GfObj*>(behavior->m_owner)->sendMessage(target, action);
    }
    StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), ASM_CMD_ID_FIELD_IDLE);
    StateUtilField::setAccessFlag(*behavior, false);
    StateUtilField::setSpecialActStatus(*behavior, true);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldPrepareBigJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
    if (LipSyncPlugin* lipSync = behavior->getPlugin<LipSyncPlugin>(2)) {
        lipSync->setWeight(1.0f);
    }
}

bool StateFieldPrepareBigJump::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    if (msg.m_id == 0x1000011) {
        procMsgPcFieldNotifyBigJump(static_cast<GfComBehaviorPc*>(owner), from, static_cast<MsgPcFieldNotifyBigJump&>(msg));
        return true;
    }
    return false;
}

void StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                                           MsgPcFieldNotifyBigJump& msg) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_field.setBigJumpInfo(&msg);
    MsgPcFieldNotifyHighJump notify(&msg);
    StateUtil::broadcastPlayer(*behavior, notify);
    if (from != nullptr) {
        GfObj* obj = from->getRTTI()->isKindOf(&GfObj::m_rtti) ? static_cast<GfObj*>(from) : nullptr;
        if (obj != nullptr) {
            property->m_field.m_noticeSender = obj->m_handle;
        }
    }
    requestState(0x11);
}

void StateFieldBigJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::notifySkillAct(*behavior, false);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (const MsgPcFieldNotifyBigJump* info = property->m_field.getBigJumpInfo()) {
        if (property->m_stateFlags & 0x400) {
            SCOM_QUEST_GIMMICK::createJump(info->m_gmkId, 0.0f);
        }
        property->m_field.setBigJumpInfo(nullptr);
    }
    StateUtil::setEnableGravity(*behavior, true);
    StateUtilField::setSpecialActStatus(*behavior, false);
}

void StateFieldLure::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    m_target = StateUtilField::getLureTargetHandle(*behavior);
}

void StateFieldLure::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setEnableLure(*behavior, false);
}

void StateFieldLure::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (com->isEnd(AnimLayer(0)) && StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_IDLE)) {
        if (GfObj* obj = GfObjUtil::getObj(m_target)) {
            MsgUnk_1000044 msg;
            static_cast<GfObj*>(behavior->m_owner)->sendMessage(obj, msg);
        }
        requestState(3);
    }
}

void StateFieldRideOn::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    syncMotion(behavior);
    while (!m_cmdQueue.empty()) {
        GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
        mm::mtl::FixStr<32> cmd = m_cmdQueue.first();
        com->execCmd(cmd.m_str, AnimLayer(0));
        m_cmdQueue.pop_front();
    }
}

unsigned int StateFieldRideOn::getVehicleMotType(GfComAsm& com) const {
    const char* state = com.getStateName(AnimLayer(0));
    if (state == nullptr) {
        return 13;
    }
    if (strcmp(state, "S_move") == 0) {
        return 0;
    }
    if (strcmp(state, "S_uplanding_00") == 0) {
        return 1;
    }
    if (strcmp(state, "S_uplanding_01") == 0) {
        return 2;
    }
    if (strcmp(state, "S_downlanding_00") == 0) {
        return 3;
    }
    if (strcmp(state, "S_downlanding_01") == 0) {
        return 4;
    }
    if (strcmp(state, "S_jump_00") == 0 || strcmp(state, "S_jump_01") == 0) {
        return 5;
    }
    if (strcmp(state, "S_jump_02") == 0) {
        return 6;
    }
    if (strcmp(state, "S_jumpdmg") == 0) {
        return 7;
    }
    if (strcmp(state, "S_highjump_00") == 0) {
        return 8;
    }
    if (strcmp(state, "S_highjump_01") == 0) {
        return 9;
    }
    if (strcmp(state, "S_fall") == 0) {
        return 10;
    }
    if (strcmp(state, "S_waterhole_00") == 0) {
        return 11;
    }
    if (strcmp(state, "S_waterhole_01") == 0) {
        return 12;
    }
    return 13;
}

unsigned int StateFieldRideOn::getRiderMotType(GfComAsm& com) const {
    const char* state = com.getStateName(AnimLayer(0));
    if (state == nullptr) {
        return 13;
    }
    if (strcmp(state, "S_move_ride") == 0) {
        return 0;
    }
    if (strcmp(state, "S_rideup_00") == 0) {
        return 1;
    }
    if (strcmp(state, "S_rideup_01") == 0) {
        return 2;
    }
    if (strcmp(state, "S_ridedown_00") == 0) {
        return 3;
    }
    if (strcmp(state, "S_ridedown_01") == 0) {
        return 4;
    }
    if (strcmp(state, "S_ridejump_00") == 0 || strcmp(state, "S_ridejump_01") == 0) {
        return 5;
    }
    if (strcmp(state, "S_ridejump_02") == 0) {
        return 6;
    }
    if (strcmp(state, "S_ridejumpdmg") == 0) {
        return 7;
    }
    if (strcmp(state, "S_ridehigjump_00") == 0) {
        return 8;
    }
    if (strcmp(state, "S_ridehigjump_01") == 0) {
        return 9;
    }
    if (strcmp(state, "S_ridefall") == 0) {
        return 10;
    }
    if (strcmp(state, "S_ridewaterhole_00") == 0) {
        return 11;
    }
    if (strcmp(state, "S_ridewaterhole_01") == 0) {
        return 12;
    }
    return 13;
}

bool StateFieldRideOn::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    if (msg.m_id == 0x1000025) {
        procMsgPcFieldNotifyRiderEvent(static_cast<GfComBehaviorPc*>(owner), from,
                                       static_cast<MsgPcFieldNotifyRiderEvent&>(msg));
        return true;
    }
    return false;
}

void StateFieldRideOn::procMsgPcFieldNotifyRiderEvent(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                                      MsgPcFieldNotifyRiderEvent& msg) {
    if (msg.m_event == 2) {
        m_cmdQueue.clear();
        behavior->m_owner->getComponent<GfComAsm>(2)->setState("S_ride", AnimLayer(0));
        return;
    }
    // the asm command each rider event runs (proposed name, not the original's: the symbols leave it unnamed,
    // lbl_7100EAC318, guard lbl_7100EAC310). Its guarded initialization says the element type has a constructor;
    // anm::StringPtr is inferred
    static const anm::StringPtr s_cmdNames[3] = {"C_rideclimbidle", "C_ride", nullptr};
    mm::mtl::FixStr<32> cmd(s_cmdNames[msg.m_event].m_str);
    m_cmdQueue.push_back(cmd);
}

void StateFieldDead::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_waitAnimEnd = strcmp(behavior->m_owner->getComponent<GfComAsm>(2)->getStateName(AnimLayer(0)), "S_downpose") != 0;
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
}

bool StateFieldDead::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100003C:
        procMsgObjectNotifyHealHp(behavior, from, static_cast<MsgObjectNotifyHealHp&>(msg));
        return true;
    case 0x100001F: {
        fw::Message* inner = static_cast<MsgPcFieldRelaySurvive&>(msg).m_msg;
        if (inner != nullptr && inner->m_id == 0x100003C && static_cast<MsgObjectNotifyHealHp*>(inner)->m_healType == 0) {
            StateUtil::notifyRevival(*behavior, static_cast<MsgObjectNotifyHealHp&>(*inner));
            StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), static_cast<ASM_CMD_ID_FIELD>(0x21));
            requestState(0x3B);
        }
        return true;
    }
    }
    return false;
}

void StateFieldDead::procMsgObjectNotifyHealHp(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                               MsgObjectNotifyHealHp& msg) {
    if (msg.m_healType == 0) {
        StateUtil::notifyRevival(*behavior, msg);
        StateUtilField::execAsmCmd(*behavior->m_owner->getComponent<GfComAsm>(2), static_cast<ASM_CMD_ID_FIELD>(0x21));
        requestState(0x3B);
        MsgPcFieldRelaySurvive relay(&msg);
        StateUtil::sendMessageToBuddy(*behavior, relay);
    }
}

void StateFieldAlive::enter(GfComBehaviorPc* behavior, ai::State* prev) {}

void StateFieldAlive::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldAlive::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (com->isEnd(AnimLayer(0)) && StateUtilField::execAsmCmd(*com, ASM_CMD_ID_FIELD_IDLE)) {
        requestState(3);
    }
}

void StateFieldExtraControl::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_mode = -1;
    GfComAsm* com = behavior->m_owner->getComponent<GfComAsm>(2);
    if (const char* state = com->getStateName(AnimLayer(0))) {
        if (strcmp(state, "S_idle") == 0) {
            if (m_mode != 2) {
                GfGameManager::setGmkTutorialMoverOK(true);
                StateUtil::setEnableDownIK(*behavior, true);
                StateUtil::setEnableDownIK(*behavior, true);
                m_mode = 2;
            }
        } else if (strcmp(state, "S_move") == 0) {
            if (m_mode != 0) {
                m_mode = 0;
            }
        } else if (strcmp(state, "S_walkendL") == 0 || strcmp(state, "S_walkendR") == 0) {
            if (m_mode != 1) {
                m_mode = 1;
            }
        } else if (strcmp(state, "S_talkA_02") == 0) {
            if (m_mode != 3) {
                StateUtil::setEnableDownIK(*behavior, true);
                m_mode = 3;
            }
        }
    }
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.y = 0.0f;
}

void StateFieldExtraControl::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtil::setEnableDownIK(*behavior, false);
}

}}  // namespace gf::pc
