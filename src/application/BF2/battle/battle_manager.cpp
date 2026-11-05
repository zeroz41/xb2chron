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
#include "classes/gf/GfObj.h"
#include "classes/btl/BattleCharacter.h"
#include "gf/GfObjUtil.h"
#include "gf/GfTargetProperty.h"
#include "gf/MsgPcBattleStart.h"
#include "gf/GfPlayFactory.h"
#include "btl/Utility.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/fw/Framework.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfGameParty.h"

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

void BattleManager::update(const fw::UpdateInfo& info) {
    fw::UpdateInfo battleInfo = info;
    BattleGlobal* global = mm::mtl::PtrSingleton<BattleGlobal>::sys();
    if (!global->pad_bit43 && !global->pad_bit44 && !global->pad_bit45 &&
        mm::mtl::PtrSingleton<ChainAttackManager>::sys()->m_startStep == 0 &&
        !mm::mtl::PtrSingleton<SpAttackManager>::sys()->IsMovie()) {
        float speed = fw::Framework::getLayerUpdateSpeed(4);
        battleInfo.m_deltaTime *= speed;
        battleInfo.m_speed *= speed;
    } else {
        battleInfo.m_deltaTime = 0.0f;
        battleInfo.m_speed = 0.0f;
    }
    mm::mtl::PtrSingleton<BattleManager>::sys()->Update(battleInfo);
    DataManager::PreUpdate(battleInfo);
    UIManager::PreUpdate(battleInfo);
    BattleGlobal::PreUpdate(battleInfo);
    CharacterManager::PreUpdate(battleInfo);
    ChallengeBattleManager::PreUpdate(battleInfo);
    BladeArtsManager::PreUpdate(battleInfo);
    BladeChangeManager::PreUpdate(battleInfo);
    FormationChangeManager::PreUpdate(battleInfo);
    SpAttackManager::PreUpdate(battleInfo);
    ChainAttackManager::PreUpdate(battleInfo);
    HateRingManager::PreUpdate(battleInfo);
    EffectManager::PreUpdate(battleInfo);
    TalkManager::PreUpdate(battleInfo);
    SirenBattleManager::PreUpdate(battleInfo);
    DataManager::Update(battleInfo);
    UIManager::Update(battleInfo);
    BattleGlobal::Update(battleInfo);
    CharacterManager::Update(battleInfo);
    ChallengeBattleManager::Update(battleInfo);
    BladeArtsManager::Update(battleInfo);
    BladeChangeManager::Update(battleInfo);
    FormationChangeManager::Update(battleInfo);
    SpAttackManager::Update(battleInfo);
    ChainAttackManager::Update(battleInfo);
    HateRingManager::Update(battleInfo);
    EffectManager::Update(battleInfo);
    TalkManager::Update(battleInfo);
    SirenBattleManager::Update(battleInfo);
    mm::mtl::Singleton<ai::AiManager>::getPtr()->update(battleInfo);
}

void BattleManager::Update(const fw::UpdateInfo& info) {
    if (!pad_15) {
        return;
    }
    bool gameOver = CheckGameOver(info);
    if (gameOver) {
        if (!pad_17) {
            mm::mtl::PtrSingleton<CharacterManager>::sys()->PlayEnemyWinVoice();
            pad_17 = true;
        }
        pad_16 = true;
        if (Utility::IsEnableDeadSequence()) {
            gf::GfPlayFactory::createPlayerDead(static_cast<gf::GfPlayerDead>(1));
            pad_16 = false;
        }
    } else {
        pad_16 = false;
        pad_17 = false;
    }
    BattleGlobal* global = mm::mtl::PtrSingleton<BattleGlobal>::sys();
    float rate = pad_10 * (1.0f / 15.0f);
    global->m_gameOver = gameOver;
    global->pad_aa4 = rate;
    CheckBattle();
    bool battleTarget = false;
    if (gf::GfGameManager::isEnableFieldBattleTarget()) {
        if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->pad_bit1) {
            battleTarget = true;
        } else {
            gf::GF_OBJ_HANDLE* leader = Utility::GetLeader();
            BattleCharacter* chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(leader);
            if (chr != nullptr) {
                CharacterParameter* param = chr->GetCharacterParameterConst(true);
                if (param != nullptr) {
                    battleTarget = param->m_hasHateTarget;
                }
            }
        }
    }
    if (gf::GfGameTarget* target = mm::mtl::PtrSingleton<gf::GfGameTarget>::sys()) {
        target->changeBattleTarget(battleTarget);
    }
    CheckInBattle();
}

void BattleManager::CheckInBattleCharacter(gf::GF_OBJ_HANDLE* handle, bool force) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    BattleCharacter* chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(handle);
    if (chr == nullptr || chr->IsBattle()) {
        return;
    }
    gf::GfObj* obj = chr->GetObject();
    if (obj == nullptr) {
        return;
    }
    if (!force) {
        gf::GfObjProperty* property = gf::GfObjUtil::getProperty(handle);
        if (property == nullptr || property->m_target->m_state != 0 || !property->m_target->m_gmkTutorialOK ||
            chr->IsOnSlide()) {
            return;
        }
    }
    if (mm::mtl::PtrSingleton<BladeChangeManager>::sys()->IsRegister(handle) ||
        mm::mtl::PtrSingleton<ChainAttackManager>::sys()->IsProc(false)) {
        return;
    }
    gf::MsgPcBattleStart msg(0);
    static_cast<fw::MessageObject*>(obj)->recieveMessage(obj, msg);
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

void BattleManager::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (static_cast<int>(gev) == 2) {
        if (DataManager* manager = mm::mtl::PtrSingleton<DataManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (BattleGlobal* manager = mm::mtl::PtrSingleton<BattleGlobal>::sys()) {
            manager->NotifyMapChange();
        }
        if (BladeArtsManager* manager = mm::mtl::PtrSingleton<BladeArtsManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (BladeChangeManager* manager = mm::mtl::PtrSingleton<BladeChangeManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (FormationChangeManager* manager = mm::mtl::PtrSingleton<FormationChangeManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (SpAttackManager* manager = mm::mtl::PtrSingleton<SpAttackManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (EffectManager* manager = mm::mtl::PtrSingleton<EffectManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (TalkManager* manager = mm::mtl::PtrSingleton<TalkManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (UIManager* manager = mm::mtl::PtrSingleton<UIManager>::sys()) {
            manager->NotifyMapChange();
        }
        if (SirenBattleManager* manager = mm::mtl::PtrSingleton<SirenBattleManager>::sys()) {
            manager->NotifyMapChange();
        }
    }
    pad_15 = static_cast<int>(gev) == 7;
}

void BattleManager::NotifyQuestTask(unsigned int id) {
    BattleManager* manager = mm::mtl::PtrSingleton<BattleManager>::sys();
    if (manager != nullptr) {
        manager->QuestTaskProc(id);
    }
}

void BattleManager::QuestTaskProc(unsigned int id) {
    if (!mm::mtl::PtrSingleton<BattleGlobal>::sys()->pad_bit1) {
        return;
    }
    CharacterManager* manager = mm::mtl::PtrSingleton<CharacterManager>::sys();
    unsigned char* fp = gf::GfDataBdat::getFP(0xCA);
    unsigned short enemyHp = Bdat::getValCheckU16(fp, "ReduceEnemyHP", id);
    if (enemyHp != 0) {
        unsigned int enemyId = Bdat::getValCheckU16(fp, "EnemyID", id);
        unsigned short groupId = Bdat::getValCheckU16(fp, "EnemyGroupID", id);
        if (enemyId != 0) {
            for (int i = 20; i < 90; i++) {
                BattleCharacter* chr = manager->GetCharacterConst(i);
                if (chr != nullptr && chr->m_bdatID == enemyId) {
                    chr->SetLimitHP(enemyHp);
                    break;
                }
            }
        } else {
            for (int i = 20; i < 90; i++) {
                BattleCharacter* chr = manager->GetCharacterConst(i);
                if (chr != nullptr) {
                    int bdatId = chr->m_bdatID;
                    gf::GfBdatChrEnParam* enParam = mm::mtl::PtrSingleton<gf::GfBdatChrEnParam>::sys();
                    for (unsigned int slot = 0; slot < 12; slot++) {
                        if (bdatId == enParam->getEnemyGroupEnemyID(groupId, slot)) {
                            chr->SetLimitHP(enemyHp);
                            break;
                        }
                    }
                }
            }
        }
    }
    unsigned short pcHp = Bdat::getValCheckU16(fp, "ReducePCHP", id);
    if (pcHp != 0) {
        for (int i = 0; i < 20; i++) {
            BattleCharacter* chr = manager->GetCharacterConst(i);
            if (chr != nullptr) {
                if (chr->IsControlCharacter()) {
                    chr->SetLimitHP(pcHp);
                } else {
                    chr->SetLimitHP(0);
                }
            }
        }
    }
}

bool BattleManager::isInitialized() {
    BattleManager* manager = mm::mtl::PtrSingleton<BattleManager>::sys();
    if (manager != nullptr) {
        return manager->m_initialized;
    }
    return false;
}

}  // namespace btl
