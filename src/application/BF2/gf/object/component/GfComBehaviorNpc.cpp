#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/npc/StateIdle.h"
#include "classes/gf/npc/StateWalk.h"
#include "classes/gf/npc/StateAreaMove.h"
#include "classes/gf/npc/StateApproachPc.h"
#include "classes/gf/npc/StateReaction.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/npc/StateTalk.h"
#include "classes/gf/GfComBehaviorNpc/Listener.h"
#include "classes/gf/GfComBehaviorNpc/LocalSteerIsTargetNotPlayer.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "plugin/Bdat.h"
#include "math.h"
#include "ml/MTRand.h"

namespace gf {

float GfComBehaviorNpc::BdatInfo::getDistYThreshold() {
    return 2.0f;
}

bool GfComBehaviorNpc::BdatInfo::isIconTalkBonus() const {
    if (!pad_1a) {
        return false;
    }
    unsigned char* fp = GfDataBdat::getFP(0xeb);
    return !GfDataBlade::fn_710024D890(m_talkEventId + 41878 - Bdat::getIdTop(fp));
}

void GfComBehaviorNpc::BdatInfo::setTalkBonusFlag() const {
    unsigned char* fp = GfDataBdat::getFP(0xeb);
    GfDataBlade::fn_710024D86C(m_talkEventId + 41878 - Bdat::getIdTop(fp), 1);
}

bool GfComBehaviorNpc::LocalSteerIsTargetNotPlayer::operator()(const GfFieldLocalSteer& steer,
                                                                GF_OBJ_HANDLE* target) const {
    return GfGameManager::getPartyLeader() != target;
}

gmk::AGmkBase* GfComBehaviorNpc::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

void GfComBehaviorNpc::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 7, 1);
    m_hfsm.registerState<npc::StateIdle>(0, -1);
    m_hfsm.registerState<npc::StateWalk>(1, -1);
    m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorNpc> >(2, -1);
    m_hfsm.registerState<npc::StateApproachPc>(3, -1);
    m_hfsm.registerState<npc::StateReaction<GfComBehaviorNpc> >(4, -1);
    m_hfsm.registerState<npc::StateBattle<GfComBehaviorNpc> >(5, -1);
    m_hfsm.registerState<npc::StateTalk>(6, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

GfComAsm* GfComBehaviorNpc::getComAsm() const {
    return m_owner->getComponent<GfComAsm>(2);
}

void GfComBehaviorNpc::setGoalPos(const mm::Vec3& pos) {
    m_goalPos = pos;
}

const mm::Vec3& GfComBehaviorNpc::getPos() const {
    return m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransform().position;
}

void GfComBehaviorNpc::execTurnCmd(float rotY) {
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, steer + rotY);
    m_turnCmd.create(info);
}

void GfComBehaviorNpc::execTurnCmdToPos(const mm::Vec3& pos) {
    const mm::Vec3& cur = getPos();
    float angle = atan2f(pos.x - cur.x, pos.z - cur.z);
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, angle + steer);
    m_turnCmd.create(info);
}

void GfComBehaviorNpc::Listener::onWkStandbyLogout() {
    m_owner->pad_198 = nullptr;
}

namespace npc {

template <typename T>
void StateReaction<T>::seqTurnToPc(T& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        owner.init(false);
        owner.execTurnCmdToPos(gmk::getPlayerPos());
        m_seq = &StateReaction::seqWaitTurnToPcEnd;
    }
}

template <typename T>
void StateReaction<T>::seqWaitTurnToPcEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        beginReaction(owner);
        m_seq = &StateReaction::seqUpdateMove;
    }
}

template <typename T>
void StateReaction<T>::beginReaction(const T& owner) {
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_reactionMot, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
}

template <typename T>
void StateReaction<T>::seqUpdateMove(T& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_done) {
        if (gmk::isPlayerExist() && owner.m_bdatInfo.m_reactionRangeSq > 0.0f &&
            owner.m_bdatInfo.m_reactionMot != 0 && owner.m_bdatInfo.m_reactionPercent != 0 &&
            !(owner.m_bdatInfo.m_reactionRangeSq < owner.m_playerDistSq) && !(owner.m_playerDistYSq > 4.0f)) {
            return;
        }
        endReaction(owner);
        m_seq = &StateReaction::seqTurnToPrev;
    }
}

// the reaction's closing motion: the row's command name with its last character made '2'
template <typename T>
void StateReaction<T>::endReaction(const T& owner) {
    mm::mtl::FixStr<32> name(reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_reactionMot, 7)));
    name.m_str[name.length() - 1] = '2';
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name.m_str));
}

template <typename T>
void StateReaction<T>::seqWaitTurnToPrevEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        requestState(0);
    }
}

template <typename T>
void StateBattle<T>::onEnter(void* p, ai::State*) {
    T& owner = *static_cast<T*>(p);
    owner.init(true);
    unsigned short mot = owner.m_bdatInfo.m_battleMot;
    m_seq = mot != 0 ? &StateBattle::seqApplyBattleMot : &StateBattle::seqTurnPc;
    if (mot != 0 && owner.m_bdatInfo.m_battleReaction != 2) {
        owner.getBindedGmkInst();
    }
    pad_60 = 0;
}

template <typename T>
void StateBattle<T>::seqApplyBattleMot(T& owner, const fw::UpdateInfo&) {
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_battleMot, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
    m_seq = &StateBattle::seqUpdateBattleMot;
}

template <typename T>
void StateBattle<T>::seqTurnPc(T& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        mm::Vec3 pos;
        if (findGoalPos(pos, owner)) {
            owner.setGoalPos(pos);
            owner.execTurnCmdToPos(pos);
            m_seq = &StateBattle::seqWaitTurnEnd;
        }
    }
}

template <typename T>
void StateBattle<T>::seqUpdateBattleMot(T&, const fw::UpdateInfo&) {
    if (!GfGameManager::isBattle()) {
        requestState(0);
    }
}

template <typename T>
void StateBattle<T>::seqWaitTurnEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateBattle::seqUpdateMove;
    }
}

template <typename T>
void StateBattle<T>::seqUpdateMove(T& owner, const fw::UpdateInfo& info) {
    if (m_execCmd.m_done) {
        if (m_execCmd.m_executed) {
            owner.m_moveSpeed.setSpeedKmph(owner.m_moveSpeed.m_speedMax, 1.0f);
            owner.init(true);
        }
        if (!GfGameManager::isBattle()) {
            requestState(1);
            owner.m_moveSpeed.setSpeedKmph(owner.m_moveSpeed.m_speedMin, 1.0f);
            return;
        }
        if (owner.m_bdatInfo.m_battleReaction == 0) {
            mm::Vec3 goal;
            if (findGoalPos(goal, owner)) {
                owner.setGoalPos(goal);
            }
            owner.moveToGoal(info.m_deltaTime);
            pad_60 += info.m_deltaTime;
            if (pad_60 > 2.0f) {
                SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj*>(owner.m_owner)->m_handle, 1.0f, 0);
            }
        }
    }
}
}  // namespace npc
}  // namespace gf
