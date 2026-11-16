#include "classes/gf/GfStateBase.h"
#include "classes/gf/enemy/StateBattleBase.h"
#include "classes/gf/enemy/StateBattleActionBase.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/GfObj.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfBehaviorEnemyField.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatRsc.h"
#include "gf/SDataEnemy.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "fw/Transform.h"
#include "fw/ColiCheck.h"
#include "ml/MTRand.h"

namespace gf {

void GfComBehaviorEnemy::callbackField(GfComAsm*, const CallBackCache&) {}

namespace enemy {

bool StateFieldAreaWalk::getGoalPosWater(mm::Vec3& pos, const GfComBehaviorEnemy& owner) const {
    if (!getGoalPosRandom(pos, owner)) {
        return false;
    }
    fw::TColiCheckResult<256> result;
    result.clear();
    mm::Vec3 start = pos;
    start.y += 5.0f;
    mm::Vec3 end = pos;
    end.y -= 5.0f;
    fw::ColiCheckConfig config;
    config.m_mask = ~0u;
    config.m_flags = 9;
    config.m_mode = 1;
    config.m_option = false;
    if (!fw::ColiCheck::testLineChara(result, start, end, config)) {
        return false;
    }
    // the water surface the line hit (material 1)
    if (result.getMaterial(0).m_id != 1) {
        return false;
    }
    pos = result.getPosition(0);
    return true;
}

void StateFieldAreaWalk::enter(GfComBehaviorEnemy* owner, ai::State*) {
    if (owner->m_field.getGmkRouteNavi() != nullptr || owner->getBindedGmkInst() == nullptr) {
        requestState(1);
        return;
    }
    if (owner->isFlyInsect()) {
        pad_18 = 2;
    } else if (owner->isFlyCircle()) {
        pad_18 = 3;
        pad_1c = ml::mtRandf1() > 0.5f;
    } else if (owner->isWater()) {
        pad_18 = 4;
    } else {
        pad_18 = 1;
    }
    owner->m_field.applyFieldMoveSpeed(static_cast<STATE_ID>(m_stateID), *owner);
    m_seq = &StateFieldAreaWalk::seqInitGoalPos;
}

void StateFieldAreaWalk::leave(GfComBehaviorEnemy*, ai::State*) {}

void StateFieldAreaWalk::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateFieldAreaWalk::seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        pad_68 = 0;
        m_seq = &StateFieldAreaWalk::seqMoveToGoal;
    }
}

}  // namespace enemy

template <typename T>
void TFieldExecCmd<T>::create(const CreateInfo& info) {
    m_executed = false;
    clear();
    m_info = info;
}

template <typename T>
bool TFieldExecCmd<T>::execCmd(T& com, const char* name) const {
    bool result = false;
    if (com.getStateName(AnimLayer(0)) != nullptr) {
        // the command "C_xxx" plays the state "S_xxx": it runs already when the names match after the prefix
        mm::mtl::FixStr<32> state(com.getStateName(AnimLayer(0)));
        if (strcmp(name + 1, state.m_str + 1) == 0) {
            result = true;
        } else {
            result = com.execCmd(name, AnimLayer(0));
        }
    }
    return result;
}

// update's (not identical yet)
template bool TFieldExecCmd<GfComAsm>::execCmd(GfComAsm& com, const char* name) const;

namespace enemy {

void StateFieldAreaWalk::seqMoveToGoal(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (!m_execCmd.m_done) {
        return;
    }
    bool fly = owner.isFly();
    if (!fly && !canGetMoveVec(owner.m_field.pad_40)) {
        requestState(1);
        return;
    }
    pad_68 += info.m_deltaTime;
    if (owner.m_field.isArrivedToGoal() || pad_68 > 5.0f) {
        if (!fly) {
            owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(1), owner);
            m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_walkend"));
            m_seq = &StateFieldAreaWalk::seqWaitMoveEnd;
        } else if (pad_18 == 3) {
            m_seq = &StateFieldAreaWalk::seqInitGoalPos;
        } else {
            m_seq = &StateFieldAreaWalk::seqChangeState;
        }
    }
    owner.m_field.moveToGoal(info.m_deltaTime);
}

void StateFieldAreaWalk::seqWaitMoveEnd(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        m_seq = &StateFieldAreaWalk::seqChangeState;
    }
}

void StateFieldAreaWalk::seqChangeState(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    STATE_ID next = owner.getNextFieldStateId();
    if (owner.isStateCondMatch(next)) {
        requestState(next);
    } else {
        requestState(1);
    }
}

bool StateFieldAreaWalk::isCondMatch(const GfComBehaviorEnemy& owner) {
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr || gmk->getGmkType() != 0) {
        return false;
    }
    // a type 0 gimmick's data starts with a float the enemy's arrival distance is compared with
    if (*reinterpret_cast<const float*>(gmk->m_createInfo.m_data) <= owner.m_field.pad_18) {
        return false;
    }
    return true;
}

void StateFieldBlade::enter(GfComBehaviorEnemy* owner, ai::State*) {
    owner->m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(0), *owner);
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, "C_idle"));
    m_seq = &StateFieldBlade::seqWaitIdle;
}

void StateFieldBlade::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldBlade::seqIdle;
    }
}

void StateFieldBlade::leave(GfComBehaviorEnemy*, ai::State*) {}

void StateFieldBlade::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    if (owner->isStateCondMatch(static_cast<STATE_ID>(1)) && owner->m_field.isArrivedToGoal()) {
    }
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

// the position of the driver the blade is mounted to; false while it has no valid transform (inline, no symbol;
// the name is not the original's)
static inline bool getDriverPos(const GfComBehaviorEnemy& owner, mm::Vec3& pos) {
    GfObjAcc driver(GfMountManager::getHandle(static_cast<GfObj*>(owner.m_owner)->m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2)));
    if (!driver.isValidTransform()) {
        return false;
    }
    pos = driver.getWorldTransform().position;
    return true;
}

void StateFieldBlade::seqIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    mm::Vec3 driverPos;
    {
        GfObjAcc driver(GfMountManager::getHandle(static_cast<GfObj*>(owner.m_owner)->m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2)));
        if (!driver.isValidTransform()) {
            return;
        }
        driverPos = driver.getWorldTransform().position;
    }
    mm::Vec3 diff = driverPos - owner.getTransform().position;
    float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    float radius;
    {
        DataParamAcc acc(static_cast<GfObj*>(owner.m_owner)->m_handle);
        const SDataEnemy* data = acc.getSDataEnemy();
        radius = mm::mtl::PtrSingleton<GfBdatRsc>::sys()->getRscEnEnRadius(data->m_rscId);
    }
    float range = radius + 4.0f;
    if (distSq < range * range) {
        return;
    }
    owner.m_field.m_goalPos = driverPos;
    owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(1), owner);
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
    m_seq = &StateFieldBlade::seqMoveToDriver;
}

void StateFieldBlade::seqMoveToDriver(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (!m_execCmd.m_done) {
        return;
    }
    const float dt = info.m_deltaTime;
    owner.m_field.moveToGoal(dt);
    mm::Vec3 driverPos;
    if (getDriverPos(owner, driverPos)) {
        owner.m_field.m_goalPos = driverPos;
        mm::Vec3 diff = driverPos - owner.getTransform().position;
        float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
        float radius;
        {
            DataParamAcc acc(static_cast<GfObj*>(owner.m_owner)->m_handle);
            const SDataEnemy* data = acc.getSDataEnemy();
            radius = mm::mtl::PtrSingleton<GfBdatRsc>::sys()->getRscEnEnRadius(data->m_rscId);
        }
        float range = radius + 1.0f;
        if (range * range < distSq) {
            return;
        }
    }
    owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(0), owner);
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_walkend"));
    m_seq = &StateFieldBlade::seqWaitIdle;
}

StateFieldHome::StateFieldHome() : m_seq(nullptr), pad_60(false), pad_64(0) {}

void StateFieldHome::enter(GfComBehaviorEnemy* owner, ai::State*) {
    GfObjAcc acc(static_cast<GfObj*>(owner->m_owner)->m_handle);
    if (acc.isEnemyBlade()) {
        requestState(15);
        return;
    }
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(owner->m_owner)->m_handle);
    if (gmk != nullptr && gmk->getGmkType() == gmk::GmkSalvageLocator::TYPE) {
        gmk::GmkSalvageLocator* locator = static_cast<gmk::GmkSalvageLocator*>(gmk);
        if (GfGameManager::isEnemyChangeBattleOK()) {
            locator->syncDepopTboxes();
        } else {
            locator->onEnemyHomeToPlayerAccess(static_cast<GfObj*>(owner->m_owner)->m_handle);
        }
    }
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, "C_idle"));
    m_seq = &StateFieldHome::seqWaitIdle;
    pad_60 = false;
    pad_64 = 0;
}

void StateFieldHome::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldHome::seqInitHomePos;
    }
}

void StateFieldHome::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    if (!pad_60) {
        pad_64 += info.m_deltaTime;
        if (pad_64 > 10.0f) {
            pad_60 = true;
            SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj*>(owner->m_owner)->m_handle, 1.0f, 0);
        }
    }
    if (owner->isStateCondMatch(static_cast<STATE_ID>(1)) && owner->m_field.isArrivedToGoal() && !pad_60) {
        pad_60 = true;
        SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj*>(owner->m_owner)->m_handle, 1.0f, 0);
    }
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateFieldHome::seqInitHomePos(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    mm::Vec3 home;
    if (gmk::GmkRouteNavi* navi = owner.m_field.getGmkRouteNavi()) {
        if (!navi->isValid()) {
            return;
        }
        const mm::Vec3& pos = owner.getTransform().position;
        gmk::GmkRouteNavi::UpdateInfo naviInfo;
        naviInfo.m_pos.x = pos.x;
        naviInfo.m_pos.y = pos.y;
        naviInfo.m_pos.z = pos.z;
        navi->update(naviInfo);
        if (!navi->pad_80) {
            return;
        }
        home = navi->pad_90;
    } else {
        GfObjSetupEnemy* setup =
            mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(owner.m_owner)->m_handle)->m_setup);
        home = setup->m_initialPos;
    }
    owner.m_field.m_goalPos = home;
    owner.execTurnCmdToGoal();
    m_seq = &StateFieldHome::seqWaitTurnEnd;
}

void StateFieldHome::seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(1), owner);
        m_seq = &StateFieldHome::seqMoveToHomePos;
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
    }
}

void StateFieldHome::seqMoveToHomePos(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (!m_execCmd.m_done) {
        return;
    }
    const float dt = info.m_deltaTime;
    owner.m_field.moveToGoal(dt);
}

bool StateFieldHome::isCondMatch(const GfComBehaviorEnemy&) { return gmk::isPlayerExist(); }

StateFieldHome::~StateFieldHome() {}

const char* StateFieldHome::getName() const { return "StateFieldHome"; }

void StateFieldHome::onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }

void StateFieldHome::onLeave(void*, ai::State*) {}

void StateFieldHome::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace enemy
}  // namespace gf
