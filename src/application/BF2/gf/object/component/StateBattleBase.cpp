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
#include "btl/Misc.h"
#include "btl/siren_battle_manager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/UIManager.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatRsc.h"
#include "gf/GfEnemyBattleProperty.h"
#include "gf/GfObjAcc.h"
#include "gf/SDataEnemy.h"

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

bool StateBattle::Enter(GfComBehaviorEnemy* behavior, ai::State*) {
    GfComBehaviorEnemy* owner = static_cast<GfComBehaviorEnemy*>(m_owner);
    GfComPropertyEnemy* enemy = owner->m_owner->findComponent<GfComPropertyEnemy>(5);
    int index = enemy->m_battleProperty.m_characterIndex;
    btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
    chara->NotifyBattleStart(false);
    chara->SetAction(btl::BattleCharacter::ACTION_ID(2), false, true, 0, 0.0f);
    GfComPropertyEnemy* property =
        static_cast<GfComBehaviorEnemy*>(m_owner)->m_owner->getComponent<GfComPropertyEnemy>(5);
    {
        mm::Vec3 pos;
        btl::Misc::GetObjectTransform(chara->GetObject(), pos, btl::Misc::TRANS_TYPE_POS);
        property->m_battleProperty.pad_0 = pos;
    }
    {
        DataParamAcc acc(static_cast<GfObj*>(behavior->m_owner)->m_handle);
        const SDataEnemy* data = acc.getSDataEnemy();
        unsigned short id = data->m_id;
        GfBdatChrEnArrange* arrange = GfBdatChrEnArrange::sys();
        property->m_battleProperty.m_batAreaType = arrange->getChrEnArrangeBatAreaType(id);
        unsigned int area = arrange->getChrEnArrangeBatArea(id);
        property->m_battleProperty.m_returnHomeDistance = area == 0 ? 60.0f : area;
        unsigned int interval = arrange->getChrEnArrangeBatInterval(id);
        property->m_battleProperty.m_returnHomeCharacterDistance = interval == 0 ? 40.0f : interval;
        if (btl::BattleGlobal::sys()->m_challengeAnySuccess) {
            btl::SirenBattleManager* siren = btl::SirenBattleManager::sys();
            if (siren->m_params[0].m_arrangeID == id || siren->m_params[1].m_arrangeID == id) {
                property->m_battleProperty.m_batAreaType = 1;
                property->m_battleProperty.m_returnHomeDistance = 100000.0f;
                property->m_battleProperty.m_returnHomeCharacterDistance = 100000.0f;
            }
        }
        property->m_battleProperty.m_actType = GfBdatRsc::sys()->getRscEnActType(data->m_rscId);
    }
    GfObjAcc objAcc(static_cast<GfObj*>(behavior->m_owner)->m_handle);
    if (objAcc.getBdatId() == 0xC0) {
        static_cast<GfObj*>(behavior->m_owner)->pad_110 &= ~4u;
    }
    m_messageTimer = 0.0f;
    return true;
}

void StateBattle::Leave(GfComBehaviorEnemy* behavior, ai::State*) {
    GfComBehaviorEnemy* owner = static_cast<GfComBehaviorEnemy*>(m_owner);
    GfComPropertyEnemy* enemy = owner->m_owner->findComponent<GfComPropertyEnemy>(5);
    int index = enemy->m_battleProperty.m_characterIndex;
    btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
    chara->NotifyBattleEnd();
    GfObjAcc acc(static_cast<GfObj*>(behavior->m_owner));
    acc.setFlag(0x17, true);
}

void StateBattleBase::Leave(GfComBehaviorEnemy*, ai::State*) {}

void StateBattle::Update(btl::BattleCharacter* chara, GfComBehaviorEnemy* behavior, const fw::UpdateInfo& info) {
    chara->Update();
    if (CheckReturnHome(chara, behavior)) {
        if (chara->IsDriver(false)) {
            btl::CharacterParameter* param = chara->GetCharacterParameterConst(true);
            if (param != nullptr) {
                btl::BattleCharacter* driver = btl::CharacterManager::sys()->GetCharacterConst(param->m_driverHandle);
                if (driver != nullptr) {
                    driver->StartBackHome();
                }
            }
        }
        return;
    }
    if (chara->m_bdatID != 0x51C) {
        return;
    }
    if (!btl::DataManager::sys()->IsSpecialEffects(2)) {
        m_messageTimer = 0.0f;
        return;
    }
    if (btl::BattleGlobal::sys()->m_elementalCombo.m_camera || btl::SpAttackManager::sys()->m_camera ||
        btl::ChainAttackManager::sys()->IsProc(true)) {
        return;
    }
    m_messageTimer -= info.m_deltaTime;
    if (m_messageTimer <= 0.0f) {
        m_messageTimer += 4.0f;
        btl::UIManager::sys()->DispSystemMessageUI(chara, 7, true);
    }
}

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
