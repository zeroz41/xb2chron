#include "classes/btl/DataManager.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjPartyStatus.h"

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

int DataManager::GetEnemyGroupIndex(gf::GF_OBJ_HANDLE* handle) {
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
