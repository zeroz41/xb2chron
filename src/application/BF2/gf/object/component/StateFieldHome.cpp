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
#include "ml/MtRand.h"

namespace gf {

void GfComBehaviorEnemy::callbackField(GfComAsm*, const CallBackCache&) {}

namespace enemy {

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
    if (owner.pad_545c) {
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

StateFieldHome::StateFieldHome() : m_seq(nullptr), pad_60(false), pad_64(0) {}

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

void StateFieldHome::seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.pad_545c) {
        owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(1), owner);
        m_seq = &StateFieldHome::seqMoveToHomePos;
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
    }
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
