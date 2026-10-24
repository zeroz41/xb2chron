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

namespace gf {
namespace enemy {

void StateFieldAreaWalk::leave(GfComBehaviorEnemy*, ai::State*) {}

void StateFieldAreaWalk::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
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

void StateFieldBlade::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldBlade::seqIdle;
    }
}

void StateFieldBlade::leave(GfComBehaviorEnemy*, ai::State*) {}

StateFieldHome::StateFieldHome() : m_seq(nullptr), pad_60(false), pad_64(0) {}

void StateFieldHome::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldHome::seqInitHomePos;
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
