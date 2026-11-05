#include "classes/btl/DataManager.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "btl/Utility.h"
#include "btl/siren_battle_manager.h"
#include "btl/challenge_battle_manager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "gf/OwnerBonus.h"
#include "plugin/Bdat.h"

namespace btl {

DataManager::~DataManager() {}

void DataManager::Create() {
#line 109
    DataManager* manager = new (gf::getAllocator(gf::ALLOCATOR(1)), __FILE__, __LINE__, 8) DataManager;
    manager->ClearCache();
}

void DataManager::Destroy() {
    DataManager* manager = sys();
    if (manager->m_comboRequestContext != nullptr) {
        manager->m_comboRequestContext->release();
        manager->m_comboRequestContext = nullptr;
    }
    if (manager != nullptr) {
        delete manager;
    }
}

void DataManager::UnregisterCharacterParameter(int id) {
    if (!(id >= 1000)) {
        PlayerParameter& parameter = m_playerParameters[id];
        if (Utility::IsThirdCharacter(parameter.m_handle) ||
            (parameter.IsBlade(true) && gf::GfDataBlade::isDummyBlade(m_playerParameters[id].m_enArrangeID))) {
            parameter.Reset();
        } else {
            m_playerParameters[id].m_flags622_0 = false;
        }
        return;
    }
    int index = id - 1000;
    if (index >= 0 && index < 70) {
        CharacterParameter*& parameter = m_enemyParameters[index];
        if (parameter != nullptr) {
            delete parameter;
            parameter = nullptr;
        }
    }
}

// The negated test is the original's form: written as `id >= 1000` (or `id < 1000`) clang puts the enemy block
// first and compares against 1000 instead of 999.
CharacterParameter* DataManager::GetCharacterParameterConst(int id) const {
    if (!(id >= 1000)) {
        return const_cast<PlayerParameter*>(&m_playerParameters[id]);
    }
    return m_enemyParameters[id - 1000];
}

void DataManager::InitializeComboRequestUI() {
    if (m_comboRequestContext == nullptr) {
        m_comboRequestContext = gf::GfMenuCallContext::create();
        if (m_comboRequestContext != nullptr) {
            gf::GfMenuObjPartyStatus::attachComboRequest(m_comboRequestContext);
        }
    }
}

CharacterParameter* DataManager::SearchCharacterParameterConst(gf::GF_OBJ_HANDLE* handle, bool) const {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return nullptr;
    }
    for (const PlayerParameter& parameter : m_playerParameters) {
        if (parameter.m_handle == handle) {
            return const_cast<PlayerParameter*>(&parameter);
        }
    }
    for (int i = 0; i < 70; i++) {
        CharacterParameter* parameter = m_enemyParameters[i];
        if (parameter != nullptr && parameter->m_handle == handle) {
            return parameter;
        }
    }
    return nullptr;
}

void DataManager::RegisterUpdateAttackParam(bool players, bool enemies) {
    if (players) {
        for (int i = 0; i < 18; i++) {
            CharacterParameter& parameter = m_playerParameters[i];
            if (parameter.m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                parameter.pad_f0_7 = true;
            }
        }
    }
    if (enemies) {
        for (int i = 0; i < 70; i++) {
            CharacterParameter* parameter = m_enemyParameters[i];
            if (parameter != nullptr && parameter->m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                parameter->pad_f0_7 = true;
            }
        }
    }
}

void DataManager::FluctuatePartyGauge(int id, int groupIndex) {
    float value;
    bool flag;
    if (id < 10000) {
        value = static_cast<short>(Bdat::getValCheck(gf::GfDataBdat::getFP(0x37), "Param", id, 5));
        if (id == 5) {
            float rate = gf::GfGameManager::getOwnerBonus().m_values[12] * 0.01f;
            if (rate < 0.0f) {
                rate = 0.0f;
            } else if (rate > 1.0f) {
                rate = 1.0f;
            }
            value *= 1.0f / (rate + 1.0f);
            flag = false;
        } else {
            flag = true;
        }
    } else {
        switch (id) {
        case 10000:
            value = -100.0f;
            break;
        case 10001:
            value = -300.0f;
            break;
        case 10002:
            value = 300.0f;
            break;
        case 10003:
            value = 300.0f;
            break;
        default:
            value = -300.0f;
            break;
        }
        flag = false;
    }
    AddPartyGauge(value, groupIndex, flag);
}

int DataManager::GetPartyGauge() const {
    return gf::GfGameParty::getPartyGauge();
}

float DataManager::GetPouchBuffParam(int param, int groupIndex) const {
    if (groupIndex > 2) {
        return 0.0f;
    }
    return m_pouchBuffs[groupIndex].m_params[param];
}

bool DataManager::IsPouchBuffTiming(int groupIndex) const {
    if (groupIndex > 2) {
        return false;
    }
    return m_pouchBuffs[groupIndex].m_isTiming != 0;
}

int DataManager::RegisterEnemyGroup(gf::GF_OBJ_HANDLE* first, gf::GF_OBJ_HANDLE* second) {
    if (first == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || second == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return -1;
    }
    for (long i = 0; i < 35; i++) {
        if (m_enemyGroups[i].m_first == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            m_enemyGroups[i].m_first = first;
            m_enemyGroups[i].m_second = second;
            return i + 3;
        }
    }
    return -1;
}

void DataManager::ReleaseEnemyGroup(gf::GF_OBJ_HANDLE* handle) {
    int index = GetEnemyGroupIndex(handle);
    if (index < 0) {
        return;
    }
    ENEMY_GROUP& group = m_enemyGroups[index - 3];
    if (group.m_first == handle) {
        group.m_firstReleased = true;
    } else if (group.m_second == handle) {
        group.m_secondReleased = true;
    }
    if (group.m_firstReleased && group.m_secondReleased) {
        group.m_second = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        group.m_first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        group.m_firstReleased = false;
        group.m_secondReleased = false;
        m_groups[index].m_isValid = false;
    }
}

int DataManager::GetEnemyGroupIndex(gf::GF_OBJ_HANDLE* handle) const {
    int index = -1;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        for (int i = 0; i < 35; i++) {
            if (m_enemyGroups[i].m_first == handle || m_enemyGroups[i].m_second == handle) {
                index = i + 3;
                break;
            }
        }
    }
    return index;
}

void DataManager::PreUpdate(const fw::UpdateInfo& info) {
    DataManager* manager = sys();
    if (manager == nullptr) {
        return;
    }
    for (long i = 0; i < 18; i++) {
        CharacterParameter& parameter = manager->m_playerParameters[i];
        if (parameter.m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            parameter.PreUpdate(info);
        }
    }
    for (int i = 0; i < 70; i++) {
        CharacterParameter* parameter = manager->m_enemyParameters[i];
        if (parameter != nullptr && parameter->m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            parameter->PreUpdate(info);
        }
    }
}

void DataManager::Update(const fw::UpdateInfo& info) {
    if (sys() != nullptr) {
        sys()->UpdateProc(info);
    }
}

void DataManager::SetSpecialEffects(int effect, bool enable) {
    m_specialEffects[effect] = enable;
}

void DataManager::UpdatePouchBuff(float dt) {
    if (!BattleGlobal::sys()->pad_bit1) {
        for (int i = 0; i < 3; i++) {
            m_pouchBuffs[i].m_params[12] = 0.0f;
            m_pouchBuffs[i].m_isTiming = false;
        }
        return;
    }
    for (int i = 0; i < 3; i++) {
        POUCH_BUFF& buff = m_pouchBuffs[i];
        if (buff.m_params[4] <= 0.0f && buff.m_params[9] <= 0.0f) {
            buff.m_params[12] = 0.0f;
            buff.m_isTiming = false;
        } else {
            float time = buff.m_params[12] + dt;
            if (time < 30.0f) {
                buff.m_isTiming = false;
            } else {
                time -= 30.0f;
                buff.m_isTiming = true;
            }
            buff.m_params[12] = time;
        }
    }
}

bool DataManager::IsExistRequestPermit() const {
    if (pad_15D10 >= 0) {
        return true;
    }
    for (int i = 0; i < 3; i++) {
        const GROUP_DATA& group = m_groups[i];
        if (group.m_needPermit && (group.m_requestPermit & 1) && group.m_isValid) {
            return true;
        }
    }
    return false;
}

void DataManager::RequestPermit(int group, gf::GF_OBJ_HANDLE* handle) {
    if (!m_groups[group].pad_bit0) {
        return;
    }
    bool flag = false;
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        gf::GF_OBJ_HANDLE* bladeHandle = gf::GfGameParty::getHandleBlade(group, -1);
        BattleCharacter* blade = CharacterManager::sys()->GetCharacterConst(bladeHandle);
        if (blade != nullptr) {
            if (blade->CheckInvalidSpAttack()) {
                return;
            }
            flag = blade->m_bdatID == 1003;
        }
    }
    pad_15D10 = group;
    gf::DataParamAcc acc(gf::GfGameParty::getHandleDriver(group, gf::PTPOS(0)));
    int attribute = acc.getAttribute(-1, false);
    int id = CharacterManager::sys()->GetCharacterConst(handle)->m_elementalCombo.GetNextElementalComboID(attribute, false, flag);
    pad_15D11 = id;
    pad_15D12 = BattleGlobal::sys()->GetElementalComboStage(id);
    pad_15D08 = handle;
    m_specialEffects[3] = false;
}

void DataManager::PostUpdate(const fw::UpdateInfo& info) {
    DataManager* manager = sys();
    for (long i = 0; i < 18; i++) {
        CharacterParameter& parameter = manager->m_playerParameters[i];
        if (parameter.m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            parameter.PostUpdate(info);
        }
    }
    for (int i = 0; i < 70; i++) {
        CharacterParameter* parameter = manager->m_enemyParameters[i];
        if (parameter != nullptr && parameter->m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            parameter->PostUpdate(info);
        }
    }
}

bool DataManager::IsSpecialEffects(int effect) const {
    return m_specialEffects[effect];
}

bool DataManager::IsValidDeadEnhance(int enhance) {
    switch (enhance) {
    case 168:
    case 193:
    case 196:
    case 268:
    case 358:
    case 394:
        return true;
    default:
        return false;
    }
}

}  // namespace btl
