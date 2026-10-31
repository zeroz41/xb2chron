#include "gf/FileStaticVec3.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/mob/StateIdle.h"
#include "classes/gf/mob/StateMove.h"
#include "classes/gf/mob/StateSquadMember.h"
#include "classes/gf/mob/StateApproachPc.h"
#include "classes/gf/npc/StateAreaMove.h"
#include "classes/gf/npc/StateReaction.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/GfComBehaviorMob/Listener.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "plugin/Bdat.h"
#include "math.h"
#include "ml/MTRand.h"
#include "classes/fw/NaviManager.h"
#include "classes/gmk/GmkSquad.h"

namespace gf {

mm::mtl::RTTI GfComBehaviorMob::m_rtti("GfComBehaviorMob", &GfComBehavior::m_rtti, nullptr);

GfComBehaviorMob::~GfComBehaviorMob() {
    cleanup();
}

void GfComBehaviorMob::cleanup() {
    pad_b8 = nullptr;
    fw::NaviManager::sys()->releaseObject(pad_a8);
    pad_a8 = nullptr;
    disposeFsm();
    m_pluginManager.cleanup();
}

gmk::AGmkBase* GfComBehaviorMob::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

void GfComBehaviorMob::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 7, 1);
    m_hfsm.registerState<mob::StateIdle>(0, -1);
    m_hfsm.registerState<mob::StateMove>(1, -1);
    m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorMob> >(2, -1);
    m_hfsm.registerState<mob::StateSquadMember>(3, -1);
    m_hfsm.registerState<npc::StateReaction<GfComBehaviorMob> >(4, -1);
    m_hfsm.registerState<npc::StateBattle<GfComBehaviorMob> >(5, -1);
    m_hfsm.registerState<mob::StateApproachPc>(6, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

const mm::Vec3& GfComBehaviorMob::getPos() const {
    return m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransform().position;
}

const mm::Quat& GfComBehaviorMob::getRot() const {
    return m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransform().rotation;
}

void GfComBehaviorMob::execTurnCmdToPos(const mm::Vec3& pos) {
    const mm::Vec3& cur = getPos();
    float angle = atan2f(pos.x - cur.x, pos.z - cur.z);
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, angle + steer);
    m_turnCmd.create(info);
}

void GfComBehaviorMob::Listener::onWkStandbyLogout() {
    m_owner->pad_53b8 = nullptr;
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
    const char* name = reinterpret_cast<const char*>(
        Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.pad_9e, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
}

template <typename T>
void StateReaction<T>::seqUpdateMove(T& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_done) {
        if (gmk::isPlayerExist() && owner.pad_98 > 0.0f && owner.pad_9e != 0 && owner.pad_9c != 0 &&
            !(owner.pad_98 < owner.pad_53d0) && !(owner.pad_53d4 > 4.0f)) {
            return;
        }
        endReaction(owner);
        m_seq = &StateReaction::seqTurnToPrev;
    }
}

template <typename T>
void StateReaction<T>::seqWaitTurnToPrevEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        requestState(0);
    }
}

// StateAreaMove's sequences below are emitted once onEnter (which starts the chain) is written; each was compared
// identical through a stub onEnter (wip/test_stubs.cpp), and seqWaitTurnToPrevEnd through a stub seqTurnToPrev.
template <typename T>
void StateAreaMove<T>::seqWaitTurnEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateAreaMove::seqMoveToGoal;
    }
}
template <typename T>
void StateAreaMove<T>::seqWaitMoveEnd(T& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        pad_60 = ml::mtRandf1(3.0f, 5.0f);
        pad_64 = 0.0f;
        owner.init(false);
        m_seq = &StateAreaMove::seqIdle;
    }
}
template <typename T>
void StateAreaMove<T>::seqIdle(T&, const fw::UpdateInfo& info) {
    pad_64 += info.m_deltaTime;
    if (!(pad_64 < pad_60)) {
        m_seq = &StateAreaMove::seqInitGoalPos;
    }
}
}  // namespace npc
}  // namespace gf
