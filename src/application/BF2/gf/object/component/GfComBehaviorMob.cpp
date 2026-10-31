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
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfComCollider.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/gmk/Lvlb.h"
#include "mm/mtl/FixStr.h"

namespace gf {

void GfComBehaviorMob::BdatInfo::create(const CBdatWrapper& bdat, int row) {
    unsigned short range = Bdat::getValCheckU16(bdat.m_fp, "ReactionRange", row);
    m_reactionRangeSq = range * range;
    m_reactionPercent = Bdat::getValCheck(bdat.m_fp, "ReactionPercent", row, 2);
    m_reactionMot = Bdat::getValCheck(bdat.m_fp, "ReactionMot", row, 2);
    m_battleReaction = Bdat::getValCheck(bdat.m_fp, "BattleReaction", row, 2);
    if (Bdat::getMember(bdat.m_fp, "BattleMot")) {
        m_battleMot = Bdat::getValCheck(bdat.m_fp, "BattleMot", row, 2);
    }
    if (GfGameManager::fn_71002A9E68()) {
        unsigned short close = Bdat::getValCheckU16(bdat.m_fp, "CloseRange", row);
        m_approachDistSq = close * close;
    }
}

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

bool GfComBehaviorMob::isMove() const {
    if (m_turnCmd.m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_turnCmd.m_info.pad_c >= 0.0f &&
        m_turnCmd.m_info.pad_c <= 3.14159274f && m_turnCmd.m_info.pad_10 >= 0.0f &&
        m_turnCmd.m_info.pad_10 <= 3.14159274f && m_turnCmd.m_info.pad_14 > 0.0f && !m_turnCmd.pad_6c) {
        return false;
    }
    fw::ColiMoveObject* coli = getColiObject();
    if (coli == nullptr || coli->m_followType == 0) {
        return false;
    }
    gmk::AGmkBase* gmk = getBindedGmkInst();
    if (pad_b8 != nullptr || isSquadMember()) {
        return true;
    }
    return gmk != nullptr && gmk->m_info->m_shape != 1;
}

fw::ColiMoveObject* GfComBehaviorMob::getColiObject() const {
    const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
    if (collider != nullptr) {
        fw::ColiObject* coli = collider->m_coliObjects[0];
        if (coli != nullptr) {
            return coli->getRTTI()->isKindOf(&fw::ColiMoveObject::m_rtti) ? static_cast<fw::ColiMoveObject*>(coli)
                                                                         : nullptr;
        }
    }
    return nullptr;
}

bool GfComBehaviorMob::isSquadMember() const {
    return m_squadNavi.isInSquad() && m_squadNavi.m_index != 0;
}

void GfComBehaviorMob::updateNaviMeshObj(float deltaTime) {
    if (pad_a8 != nullptr && (pad_a8->m_flags & 2) && m_moveSpeed.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        const mm::Vec3& pos = getPos();
        pad_a8->setBeginPos(pos);
        pad_a8->setEndPos(pad_110);
        GfObjSetup* setup = GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup;
        const GfObjSetupMob* mob =
            setup->getRTTI()->isKindOf(&GfObjSetupMob::m_rtti) ? static_cast<GfObjSetupMob*>(setup) : nullptr;
        float speed = m_moveSpeed.m_speed * 0.2777778f * mob->m_initialScale.x;
        pad_a8->setMoveSpd(speed * deltaTime);
        ++pad_b0;
    }
}

void GfComBehaviorMob::init(bool moving) {
    if (fw::ColiMoveObject* coli = getColiObject()) {
        coli->setState(static_cast<fw::ColiState>(1));
        if (moving) {
            coli->setColiType(static_cast<fw::ColiType>(1));
            coli->setPriority(100);
            coli->setState(static_cast<fw::ColiState>(0));
        } else {
            coli->setColiType(static_cast<fw::ColiType>(0));
            coli->setPriority(800);
            coli->clearState(static_cast<fw::ColiState>(0));
        }
        if (coli->m_shape.get() != nullptr && coli->m_shape->m_kind == 5) {
            coli->setPriority(800);
        }
    }
    if (pad_a8 != nullptr) {
        if (moving) {
            pad_a8->m_flags |= 2;
        } else {
            pad_a8->m_flags &= ~2;
        }
    }
}

void GfComBehaviorMob::execTurnCmdToGoal() {
    mm::Vec3 pos;
    if (getMoveVec(pos, pad_a8)) {
        pos += getPos();
    } else {
        pos = pad_110;
    }
    execTurnCmdToPos(pos);
}

void GfComBehaviorMob::execTurnCmdToPos(const mm::Vec3& pos) {
    const mm::Vec3& cur = getPos();
    float angle = atan2f(pos.x - cur.x, pos.z - cur.z);
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, angle + steer);
    m_turnCmd.create(info);
}

bool GfComBehaviorMob::isArrivedToGoal() const {
    if (m_localSteer.isTimeOutCollide()) {
        return true;
    }
    fw::ColiMoveObject* coli = getColiObject();
    if (coli == nullptr) {
        return false;
    }
    float height;
    float radius;
    const fw::ColiShape* shape = coli->m_shape.get();
    if (shape != nullptr && shape->m_kind == 3) {
        height = static_cast<const fw::ColiShapeCharacter*>(shape)->m_height;
        radius = static_cast<const fw::ColiShapeCharacter*>(shape)->m_radius;
    } else {
        mm::Vec3 min;
        mm::Vec3 max;
        coli->getAABB(min, max);
        float dx = max.x - min.x;
        float dz = max.z - min.z;
        radius = sqrtf(dx * dx + dz * dz) * 0.5f;
        height = max.y - min.y;
    }
    const mm::Vec3& pos = getPos();
    if (height < pad_110.y - pos.y) {
        return false;
    }
    mm::Vec3 diff(pad_110.x - pos.x, 0.0f, pad_110.z - pos.z);
    float distSq = diff.dot(diff);
    return !(radius * radius < distSq);
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
        Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_reactionMot, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
}

template <typename T>
void StateReaction<T>::seqUpdateMove(T& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_done) {
        if (gmk::isPlayerExist() && owner.m_bdatInfo.m_reactionRangeSq > 0.0f && owner.m_bdatInfo.m_reactionMot != 0 && owner.m_bdatInfo.m_reactionPercent != 0 &&
            !(owner.m_bdatInfo.m_reactionRangeSq < owner.pad_53d0) && !(owner.pad_53d4 > 4.0f)) {
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
