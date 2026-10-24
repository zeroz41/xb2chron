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
    if (property.m_inputFlags.m_actions & 2) {
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
        const MsgObjectDamage* damage = static_cast<MsgUnk_100003A&>(msg).m_damage;
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

void StateFieldStart::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
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

bool StateFieldPrepareBigJump::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    if (msg.m_id == 0x1000011) {
        procMsgPcFieldNotifyBigJump(static_cast<GfComBehaviorPc*>(owner), from, static_cast<MsgPcFieldNotifyBigJump&>(msg));
        return true;
    }
    return false;
}

void StateFieldLure::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setEnableLure(*behavior, false);
}

bool StateFieldRideOn::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    if (msg.m_id == 0x1000025) {
        procMsgPcFieldNotifyRiderEvent(static_cast<GfComBehaviorPc*>(owner), from,
                                       static_cast<MsgPcFieldNotifyRiderEvent&>(msg));
        return true;
    }
    return false;
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

void StateFieldAlive::enter(GfComBehaviorPc* behavior, ai::State* prev) {}

void StateFieldAlive::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldExtraControl::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtil::setEnableDownIK(*behavior, false);
}

}}  // namespace gf::pc
