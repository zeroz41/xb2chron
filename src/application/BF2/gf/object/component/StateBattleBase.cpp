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

StateBattleBase::StateBattleBase() : m_owner(nullptr) {}

bool StateBattleBase::Enter(GfComBehaviorEnemy*, ai::State*) { return true; }

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter* chara, GfComBehaviorEnemy*, const fw::UpdateInfo& info) {
    chara->BeforeUpdate(info);
}

void StateBattleBase::BeforeUpdate(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

void StateBattleBase::Update(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

void StateBattleBase::AfterUpdate(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

// an animation annotation the enemy's state machine reached goes to its battle character
bool StateBattleActionBase::recieveMessage(void* owner, fw::MessageObject*, fw::Message& msg) {
    if (msg.m_id != 0x1000042) {
        return false;
    }
    m_owner = owner;
    GfComBehaviorEnemy* behavior = static_cast<GfComBehaviorEnemy*>(owner);
    GfComPropertyEnemy* property = behavior->m_owner->findComponent<GfComPropertyEnemy>(5);
    int index = property->m_battleProperty.m_characterIndex;
    btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
    chara->AsmCallback(static_cast<MsgObjectNotifyAsmCallback&>(msg));
    m_owner = nullptr;
    return true;
}

void StateBattleBase::Leave(GfComBehaviorEnemy*, ai::State*) {}

}  // namespace enemy

bool GfStateBase::onEvent(void* owner, void* event) {
    MessageEvent* message = static_cast<MessageEvent*>(event);
    return recieveMessage(owner, message->from, *message->msg);
}
namespace enemy {

const char* StateBattle::getName() const { return "StateBattle"; }

void StateBattle::onEnter(void* owner, ai::State* prev) {
    m_owner = owner;
    m_entered = Enter(static_cast<GfComBehaviorEnemy*>(owner), prev);
    m_owner = nullptr;
}

void StateBattle::onLeave(void* owner, ai::State* next) {
    m_owner = owner;
    Leave(static_cast<GfComBehaviorEnemy*>(owner), next);
    m_owner = nullptr;
}

void StateBattle::onStep(void* owner, const void* arg) {
    if (m_entered) {
        m_owner = owner;
        GfComBehaviorEnemy* behavior = static_cast<GfComBehaviorEnemy*>(owner);
        GfComPropertyEnemy* property = behavior->m_owner->findComponent<GfComPropertyEnemy>(5);
        int index = property->m_battleProperty.m_characterIndex;
        btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
        const fw::UpdateInfo& info = *static_cast<const fw::UpdateInfo*>(arg);
        BeforeUpdate(chara, behavior, info);
        Update(chara, behavior, info);
        AfterUpdate(chara, behavior, info);
        m_owner = nullptr;
    }
}

}  // namespace enemy

bool GfStateBase::recieveMessage(void*, fw::MessageObject*, fw::Message&) { return false; }

}  // namespace gf
