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

void StateFieldSpawn::enter(GfComBehaviorEnemy* owner, ai::State*) { owner->disposeMenuObj(); }

void StateFieldSpawn::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->createMenuObj(); }

StateFieldSquadMember::StateFieldSquadMember() : m_seq(nullptr), pad_60(false), pad_64(0) {}

StateFieldSquadMember::~StateFieldSquadMember() {}

const char* StateFieldSquadMember::getName() const { return "StateFieldSquadMember"; }

void StateFieldSquadMember::onEnter(void* owner, ai::State*) {
    TFieldExecCmd<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(static_cast<GfComBehaviorEnemy*>(owner)->m_owner)->m_handle;
    info.cmdName = "C_idle";
    info.timeout = 5.0f;
    m_execCmd.create(info);
    m_seq = &StateFieldSquadMember::seqUpdateIdle;
}

void StateFieldSquadMember::onLeave(void*, ai::State*) {}

void StateFieldSquadMember::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace enemy
}  // namespace gf
