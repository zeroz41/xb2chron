#include "classes/btl/BattleManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/DataManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/BladeArtsManager.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/HateRingManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/btl/UIManager.h"
#include "classes/btl/EffectManager.h"
#include "btl/challenge_battle_manager.h"
#include "btl/formation_change_manager.h"
#include "btl/siren_battle_manager.h"
#include "classes/ai/AiManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAllocator.h"

namespace btl {

void BattleManager::Initialize(const gf::GfSetupParam& param) {
    gf::GfEvent::addEventCallback(this);
    BattleGlobal::Create();
    BtlSystemBalanceAccess::Create();
    CharacterManager::Create();
    DataManager::Create();
    ChallengeBattleManager::Create();
    BladeArtsManager::Create();
    BladeChangeManager::Create();
    FormationChangeManager::Create();
    SpAttackManager::Create();
    ChainAttackManager::Create();
    HateRingManager::Create();
    EffectManager::Create();
    TalkManager::Create();
    UIManager::Create();
    SirenBattleManager::Create();
    mm::mtl::Singleton<ai::AiManager>::getPtr()->init();
    m_initialized = true;
    pad_15 = true;
}

BattleManager::~BattleManager() {
    ;
}

void BattleManager::build(const gf::GfSetupParam& param) {
    BattleManager* manager =
#line 112
        new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) BattleManager;
    manager->Initialize(param);
}

void BattleManager::destroy() {
    BattleManager* manager = mm::mtl::PtrSingleton<BattleManager>::sys();
    manager->Finalize();
    delete manager;
}

void BattleManager::Finalize() {
    mm::mtl::Singleton<ai::AiManager>::getPtr()->destroy();
    SirenBattleManager::Destroy();
    UIManager::Destroy();
    TalkManager::Destroy();
    EffectManager::Destroy();
    HateRingManager::Destroy();
    ChainAttackManager::Destroy();
    SpAttackManager::Destroy();
    FormationChangeManager::Destroy();
    BladeChangeManager::Destroy();
    BladeArtsManager::Destroy();
    ChallengeBattleManager::Destroy();
    DataManager::Destroy();
    CharacterManager::Destroy();
    BtlSystemBalanceAccess::Destroy();
    BattleGlobal::Destroy();
    gf::GfEvent::removeEventCallback(this);
    m_initialized = false;
}

void BattleManager::postUpdate(const fw::UpdateInfo& info) {
    if (m_initialized) {
        DataManager::PostUpdate(info);
        BattleGlobal::PostUpdate(info);
        CharacterManager::PostUpdate(info);
    }
}

void BattleManager::gevBattleStart() {}

void BattleManager::gevBattleEnd() {}

bool BattleManager::isInitialized() {
    BattleManager* manager = mm::mtl::PtrSingleton<BattleManager>::sys();
    if (manager != nullptr) {
        return manager->m_initialized;
    }
    return false;
}

}  // namespace btl
