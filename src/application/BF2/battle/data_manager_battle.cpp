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
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "ml/MTRand.h"
#include "btl/Misc.h"
#include "classes/btl/EnemyParameter.h"
#include "mm/mtl/FixStr.h"

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

void DataManager::ClearCache() {
    ml::CS lock(m_criticalSection);
    m_artsCacheIDs.clear();
    m_artsCacheIDs1.clear();
    m_artsCacheIDs2.clear();
    m_artsCacheIDs3.clear();
    for (int i = 0; i < 100; i++) {
        m_artsCache[i].pad_0_0 = 0;
    }
    for (int i = 0; i < 45; i++) {
        m_artsCache1[i].pad_0_0 = 0;
    }
    for (int i = 0; i < 30; i++) {
        m_artsCache2[i].pad_0_0 = 0;
    }
    for (int i = 0; i < 30; i++) {
        m_artsCache3[i].pad_0_0 = 0;
    }
    pad_15CF0 = 0;
}

int DataManager::RegisterCharacterParameter(gf::GF_OBJ_HANDLE* handle) {
    if (Misc::GetPartyID(handle) != -1) {
        CharacterParameter* parameter = SearchCharacterParameterConst(handle, false);
        if (parameter != nullptr) {
            int id = parameter->m_registeredID;
            parameter->Initialize(handle);
            parameter->m_registeredID = id;
            return id;
        }
        for (int i = 0; i < 18; i++) {
            if (m_playerParameters[i].m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                parameter = &m_playerParameters[i];
                parameter->Initialize(handle);
                parameter->m_registeredID = i;
                return i;
            }
        }
        return -1;
    }
    for (int i = 0; i < 70; i++) {
        if (m_enemyParameters[i] == nullptr) {
#line 241
            CharacterParameter* parameter = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) EnemyParameter;
            m_enemyParameters[i] = parameter;
            parameter->Initialize(handle);
            int id = i + 1000;
            parameter->m_registeredID = id;
            return id;
        }
    }
    return -1;
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

// the used entry for type and id: a binary search of the type's cache indices, kept sorted by the entries' ids
ARTS_DATA* DataManager::GetCacheArtsDataConst(ARTS_DATA::DATA_TYPE type, int id) const {
    switch (type) {
    case 0: {
        int num = m_artsCacheIDs.size();
        int lo = 0;
        int hi = num - 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            const ARTS_DATA& entry = m_artsCache[m_artsCacheIDs[mid]];
            int key = entry.pad_0_0;
            if (key == id) {
                return const_cast<ARTS_DATA*>(&entry);
            }
            if (key > id) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        break;
    }
    case 1: {
        int num = m_artsCacheIDs1.size();
        int lo = 0;
        int hi = num - 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            const ARTS_DATA& entry = m_artsCache1[m_artsCacheIDs1[mid]];
            int key = entry.pad_0_0;
            if (key == id) {
                return const_cast<ARTS_DATA*>(&entry);
            }
            if (key > id) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        break;
    }
    case 2: {
        int num = m_artsCacheIDs2.size();
        int lo = 0;
        int hi = num - 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            const ARTS_DATA& entry = m_artsCache2[m_artsCacheIDs2[mid]];
            int key = entry.pad_0_0;
            if (key == id) {
                return const_cast<ARTS_DATA*>(&entry);
            }
            if (key > id) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        break;
    }
    case 3: {
        int num = m_artsCacheIDs3.size();
        int lo = 0;
        int hi = num - 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            const ARTS_DATA& entry = m_artsCache3[m_artsCacheIDs3[mid]];
            int key = entry.pad_0_0;
            if (key == id) {
                return const_cast<ARTS_DATA*>(&entry);
            }
            if (key > id) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        break;
    }
    }
    return nullptr;
}

void DataManager::UpdateCacheID(const ARTS_DATA* data) const {
    if (data == nullptr) {
        return;
    }
    unsigned char age = data->m_cacheAge;
    switch (data->pad_0_22) {
    case 3:
        UpdateAge(m_artsCacheIDs3, m_artsCache3, data, age);
        break;
    case 1:
        UpdateAge(m_artsCacheIDs1, m_artsCache1, data, age);
        break;
    case 2:
        UpdateAge(m_artsCacheIDs2, m_artsCache2, data, age);
        break;
    default:
        UpdateAge(m_artsCacheIDs, m_artsCache, data, age);
        break;
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

void DataManager::SetElementalEffect(int effect, int chr) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        return;
    }
    if (effect == 0) {
        m_elementalEffectID = 0;
        return;
    }
    CharacterManager* manager = CharacterManager::sys();
    BattleCharacter* chara = manager->GetCharacterConst(chr);
    if (chara == nullptr || chara->m_isPlayer) {
        return;
    }
    float rate = chara->GetFriendEnhanceRate(0xA0, false, false);
    if (rate > 0.0f && ml::mtRandf1() <= rate) {
        m_elementalEffectID = 0;
        return;
    }
    m_elementalEffectID = effect;
    unsigned char* bdat = gf::GfDataBdat::getFP(0x24);
    mm::mtl::FixedVector<unsigned char, 90> list;
    Utility::GetCharacterList(list, chara->m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(1), 0x23);
    bool created = false;
    for (unsigned char id : list) {
        BattleCharacter* target = manager->GetCharacterConst(id);
        if (target == nullptr) {
            continue;
        }
        target->CreateElementalEffect(effect);
        created = true;
        unsigned char name = Bdat::getValCheckU8(bdat, "Name", effect);
        if (name == 0) {
            continue;
        }
        gf::GfMenuObjDamageBuff::OpenParam param;
        param.m_type = 1;
        param.m_resist = false;
        param.m_bdat = gf::GfDataBdat::getFP(0x199);
        param.m_nameId = name;
        param.m_pos = target->m_pos;
        param.m_pos.y += target->GetCharacterParameterConst(true)->pad_38;
        gf::GfMenuObjDamageBuff::open(param);
    }
    if (created) {
        chara->PlaySE(static_cast<BTL_SE>(1), Bdat::getValCheckU8(bdat, "SE", effect), nullptr, true);
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

void DataManager::NotifyMapChange() {
    ClearCache();
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

// what GetEnhanceData makes of an enhance effect (the EnhanceEffect of BDAT table 0x2C, 1-0x10D): the
// ENHANCE_EFFECT_DATA's m_effect before the row's parameters are added, how they are added (m_valueType 1, 2: Param1,
// Param2; 3, 4: 10 - Param1 / 10, rounded up for 3), the row's float column Param<m_valueParam> as the value and
// Param<m_param2Param> as pad_2 (0: none; else 999999 and the row's Param of table 0x2D), and m_flags (bits 0-2: pad_4, 3, 4: pad_6_3, pad_6_4, 5: only when asked
// for). The type's and the field names are not the original's
struct ENHANCE_EFFECT_INFO {
    unsigned short m_effect;
    unsigned short m_valueType : 3;
    unsigned short m_valueParam : 4;
    unsigned short m_param2Param : 3;
    unsigned short m_flags : 6;
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009B75A2)
static const ENHANCE_EFFECT_INFO s_enhanceEffectInfo[0x10D] = {
    {0, 0, 1, 0, 0x20},  // 1
    {1, 0, 1, 0, 0x20},  // 2
    {2, 0, 1, 0, 0x20},  // 3
    {3, 0, 1, 0, 0x20},  // 4
    {4, 0, 1, 0, 0x20},  // 5
    {5, 0, 1, 0, 0x20},  // 6
    {6, 0, 1, 0, 0x20},  // 7
    {7, 0, 1, 0, 0x20},  // 8
    {8, 0, 1, 0, 0x20},  // 9
    {9, 0, 1, 0, 0x20},  // 10
    {10, 0, 1, 0, 0x21},  // 11
    {11, 0, 1, 0, 0x21},  // 12
    {12, 0, 1, 0, 0x21},  // 13
    {13, 0, 1, 0, 0x21},  // 14
    {14, 0, 1, 0, 0x21},  // 15
    {15, 0, 1, 0, 0x21},  // 16
    {16, 0, 1, 0, 0x21},  // 17
    {17, 0, 1, 0, 0x21},  // 18
    {18, 0, 1, 0, 0x21},  // 19
    {19, 0, 1, 0, 0x21},  // 20
    {20, 1, 2, 0, 0x00},  // 21
    {29, 1, 2, 0, 0x00},  // 22
    {38, 0, 1, 0, 0x00},  // 23
    {39, 0, 1, 0, 0x01},  // 24
    {40, 0, 1, 0, 0x00},  // 25
    {41, 0, 1, 0, 0x00},  // 26
    {42, 0, 1, 0, 0x00},  // 27
    {43, 0, 1, 0, 0x00},  // 28
    {44, 0, 1, 0, 0x00},  // 29
    {45, 0, 1, 0, 0x00},  // 30
    {46, 0, 1, 0, 0x00},  // 31
    {47, 0, 1, 0, 0x00},  // 32
    {48, 0, 1, 0, 0x00},  // 33
    {49, 0, 1, 0, 0x00},  // 34
    {50, 0, 1, 0, 0x00},  // 35
    {51, 0, 1, 0, 0x00},  // 36
    {52, 0, 1, 0, 0x00},  // 37
    {53, 0, 1, 0, 0x00},  // 38
    {54, 0, 1, 0, 0x01},  // 39
    {55, 0, 1, 0, 0x00},  // 40
    {56, 0, 1, 0, 0x00},  // 41
    {57, 0, 1, 0, 0x00},  // 42
    {58, 0, 1, 0, 0x00},  // 43
    {59, 3, 2, 0, 0x00},  // 44
    {69, 0, 1, 0, 0x00},  // 45
    {70, 0, 1, 0, 0x00},  // 46
    {71, 0, 1, 0, 0x00},  // 47
    {72, 0, 1, 0, 0x00},  // 48
    {73, 0, 1, 0, 0x00},  // 49
    {74, 0, 1, 0, 0x00},  // 50
    {75, 0, 1, 0, 0x00},  // 51
    {76, 0, 1, 0, 0x00},  // 52
    {77, 0, 1, 0, 0x00},  // 53
    {78, 0, 1, 0, 0x00},  // 54
    {79, 0, 1, 0, 0x00},  // 55
    {80, 0, 1, 0, 0x00},  // 56
    {81, 0, 1, 0, 0x00},  // 57
    {82, 1, 2, 0, 0x00},  // 58
    {91, 0, 1, 0, 0x00},  // 59
    {92, 1, 0, 0, 0x02},  // 60
    {101, 1, 0, 0, 0x02},  // 61
    {110, 3, 2, 0, 0x00},  // 62
    {120, 0, 1, 0, 0x00},  // 63
    {121, 3, 2, 0, 0x00},  // 64
    {131, 0, 1, 0, 0x00},  // 65
    {132, 3, 2, 0, 0x00},  // 66
    {142, 4, 2, 0, 0x00},  // 67
    {152, 0, 1, 0, 0x00},  // 68
    {153, 0, 1, 0, 0x00},  // 69
    {154, 0, 1, 0, 0x00},  // 70
    {155, 0, 1, 0, 0x00},  // 71
    {156, 0, 1, 0, 0x00},  // 72
    {157, 0, 1, 0, 0x00},  // 73
    {158, 0, 1, 0, 0x00},  // 74
    {159, 0, 1, 0, 0x00},  // 75
    {160, 0, 1, 0, 0x00},  // 76
    {161, 0, 1, 0, 0x00},  // 77
    {162, 0, 1, 0, 0x00},  // 78
    {163, 0, 1, 0, 0x00},  // 79
    {164, 0, 1, 0, 0x00},  // 80
    {165, 0, 1, 0, 0x00},  // 81
    {166, 0, 1, 0, 0x01},  // 82
    {167, 0, 1, 0, 0x01},  // 83
    {168, 0, 1, 0, 0x00},  // 84
    {169, 0, 1, 0, 0x00},  // 85
    {170, 0, 1, 0, 0x00},  // 86
    {171, 0, 1, 0, 0x00},  // 87
    {172, 0, 1, 0, 0x00},  // 88
    {173, 0, 1, 0, 0x00},  // 89
    {174, 0, 1, 0, 0x00},  // 90
    {175, 0, 1, 0, 0x00},  // 91
    {176, 0, 1, 0, 0x00},  // 92
    {177, 0, 1, 0, 0x00},  // 93
    {178, 0, 1, 0, 0x00},  // 94
    {179, 0, 1, 0, 0x00},  // 95
    {180, 0, 1, 0, 0x00},  // 96
    {181, 0, 1, 0, 0x00},  // 97
    {182, 0, 1, 0, 0x00},  // 98
    {183, 0, 1, 0, 0x00},  // 99
    {184, 0, 1, 0, 0x00},  // 100
    {185, 0, 1, 0, 0x01},  // 101
    {186, 0, 1, 0, 0x01},  // 102
    {187, 0, 1, 0, 0x01},  // 103
    {188, 0, 1, 0, 0x00},  // 104
    {189, 0, 1, 0, 0x00},  // 105
    {190, 0, 1, 0, 0x01},  // 106
    {191, 0, 1, 0, 0x00},  // 107
    {192, 0, 1, 0, 0x00},  // 108
    {193, 0, 0, 0, 0x02},  // 109
    {194, 0, 1, 0, 0x01},  // 110
    {195, 0, 1, 0, 0x01},  // 111
    {196, 0, 1, 0, 0x00},  // 112
    {197, 1, 0, 0, 0x02},  // 113
    {213, 0, 1, 0, 0x00},  // 114
    {214, 0, 1, 0, 0x00},  // 115
    {215, 0, 0, 0, 0x02},  // 116
    {216, 0, 1, 0, 0x00},  // 117
    {217, 0, 1, 0, 0x00},  // 118
    {218, 1, 2, 0, 0x00},  // 119
    {218, 0, 1, 0, 0x00},  // 120
    {268, 0, 0, 0, 0x02},  // 121
    {269, 0, 1, 0, 0x00},  // 122
    {270, 0, 1, 0, 0x01},  // 123
    {271, 0, 1, 0, 0x01},  // 124
    {272, 0, 1, 0, 0x00},  // 125
    {273, 0, 1, 0, 0x00},  // 126
    {274, 0, 1, 0, 0x00},  // 127
    {275, 0, 1, 0, 0x00},  // 128
    {276, 0, 1, 0, 0x00},  // 129
    {277, 0, 1, 0, 0x01},  // 130
    {278, 0, 1, 0, 0x01},  // 131
    {279, 0, 1, 0, 0x00},  // 132
    {280, 0, 1, 0, 0x00},  // 133
    {281, 0, 1, 0, 0x01},  // 134
    {281, 1, 2, 0, 0x00},  // 135
    {286, 0, 1, 0, 0x00},  // 136
    {287, 0, 1, 0, 0x00},  // 137
    {288, 3, 2, 1, 0x00},  // 138
    {298, 0, 1, 0, 0x00},  // 139
    {299, 0, 1, 0, 0x00},  // 140
    {300, 0, 1, 0, 0x00},  // 141
    {301, 0, 1, 0, 0x00},  // 142
    {302, 0, 1, 0, 0x00},  // 143
    {303, 0, 1, 0, 0x00},  // 144
    {304, 0, 1, 0, 0x00},  // 145
    {305, 0, 1, 0, 0x00},  // 146
    {306, 0, 1, 0, 0x00},  // 147
    {307, 0, 1, 0, 0x00},  // 148
    {308, 0, 1, 0, 0x01},  // 149
    {309, 0, 1, 0, 0x00},  // 150
    {310, 0, 1, 0, 0x00},  // 151
    {311, 0, 1, 0, 0x00},  // 152
    {312, 0, 1, 0, 0x00},  // 153
    {313, 0, 1, 0, 0x00},  // 154
    {314, 0, 1, 0, 0x00},  // 155
    {315, 0, 2, 1, 0x08},  // 156
    {316, 0, 1, 2, 0x00},  // 157
    {317, 0, 1, 2, 0x08},  // 158
    {318, 0, 1, 0, 0x01},  // 159
    {319, 0, 1, 0, 0x00},  // 160
    {320, 0, 1, 0, 0x00},  // 161
    {321, 0, 1, 2, 0x01},  // 162
    {322, 0, 1, 0, 0x00},  // 163
    {323, 0, 1, 0, 0x00},  // 164
    {324, 0, 1, 0, 0x00},  // 165
    {325, 0, 1, 0, 0x00},  // 166
    {326, 0, 1, 0, 0x00},  // 167
    {327, 0, 1, 2, 0x08},  // 168
    {328, 0, 1, 0, 0x00},  // 169
    {329, 0, 1, 0, 0x00},  // 170
    {330, 0, 1, 0, 0x00},  // 171
    {331, 0, 1, 2, 0x00},  // 172
    {332, 0, 1, 0, 0x00},  // 173
    {333, 0, 1, 0, 0x00},  // 174
    {334, 0, 1, 2, 0x00},  // 175
    {335, 0, 1, 0, 0x00},  // 176
    {336, 0, 1, 0, 0x00},  // 177
    {337, 0, 1, 0, 0x00},  // 178
    {338, 0, 1, 0, 0x01},  // 179
    {339, 0, 1, 0, 0x00},  // 180
    {340, 0, 1, 0, 0x00},  // 181
    {341, 0, 1, 0, 0x00},  // 182
    {342, 0, 1, 2, 0x00},  // 183
    {343, 0, 1, 0, 0x00},  // 184
    {344, 0, 1, 0, 0x01},  // 185
    {345, 0, 1, 0, 0x00},  // 186
    {346, 0, 1, 2, 0x00},  // 187
    {347, 0, 1, 0, 0x00},  // 188
    {348, 0, 1, 0, 0x01},  // 189
    {349, 0, 0, 0, 0x02},  // 190
    {350, 0, 1, 0, 0x00},  // 191
    {351, 0, 1, 0, 0x00},  // 192
    {352, 0, 1, 0, 0x00},  // 193
    {353, 0, 1, 0, 0x00},  // 194
    {354, 0, 1, 2, 0x00},  // 195
    {355, 0, 1, 0, 0x02},  // 196
    {356, 0, 1, 0, 0x00},  // 197
    {357, 0, 1, 0, 0x00},  // 198
    {358, 0, 1, 0, 0x00},  // 199
    {359, 0, 1, 0, 0x00},  // 200
    {360, 0, 1, 0, 0x00},  // 201
    {361, 0, 1, 0, 0x00},  // 202
    {362, 0, 1, 0, 0x00},  // 203
    {363, 0, 1, 0, 0x00},  // 204
    {364, 0, 1, 0, 0x00},  // 205
    {365, 0, 1, 0, 0x00},  // 206
    {366, 0, 1, 0, 0x01},  // 207
    {367, 0, 0, 0, 0x02},  // 208
    {368, 0, 1, 0, 0x00},  // 209
    {369, 0, 2, 1, 0x01},  // 210
    {370, 0, 1, 0, 0x00},  // 211
    {371, 0, 1, 0, 0x00},  // 212
    {372, 0, 1, 0, 0x01},  // 213
    {373, 0, 1, 0, 0x00},  // 214
    {374, 0, 1, 0, 0x01},  // 215
    {375, 0, 0, 0, 0x02},  // 216
    {376, 0, 1, 0, 0x00},  // 217
    {377, 0, 1, 0, 0x00},  // 218
    {378, 0, 1, 0, 0x00},  // 219
    {379, 0, 1, 0, 0x00},  // 220
    {380, 0, 1, 0, 0x00},  // 221
    {381, 0, 0, 0, 0x02},  // 222
    {382, 0, 1, 0, 0x00},  // 223
    {383, 0, 1, 0, 0x00},  // 224
    {384, 0, 1, 0, 0x00},  // 225
    {385, 0, 0, 0, 0x02},  // 226
    {386, 0, 1, 0, 0x00},  // 227
    {387, 0, 0, 0, 0x02},  // 228
    {388, 0, 1, 0, 0x00},  // 229
    {389, 0, 0, 0, 0x02},  // 230
    {390, 0, 1, 0, 0x00},  // 231
    {391, 0, 1, 0, 0x00},  // 232
    {392, 0, 0, 0, 0x02},  // 233
    {393, 0, 1, 0, 0x00},  // 234
    {394, 0, 1, 0, 0x00},  // 235
    {395, 0, 0, 0, 0x02},  // 236
    {396, 0, 1, 0, 0x01},  // 237
    {397, 0, 1, 0, 0x00},  // 238
    {398, 0, 1, 0, 0x00},  // 239
    {399, 0, 1, 2, 0x00},  // 240
    {400, 0, 1, 0, 0x00},  // 241
    {401, 0, 1, 0, 0x11},  // 242
    {402, 0, 1, 0, 0x00},  // 243
    {403, 0, 1, 0, 0x00},  // 244
    {404, 0, 1, 0, 0x00},  // 245
    {405, 0, 1, 0, 0x00},  // 246
    {406, 0, 1, 0, 0x00},  // 247
    {407, 0, 1, 0, 0x01},  // 248
    {408, 0, 1, 0, 0x00},  // 249
    {409, 0, 1, 0, 0x00},  // 250
    {410, 0, 1, 0, 0x00},  // 251
    {411, 0, 1, 0, 0x00},  // 252
    {412, 0, 1, 0, 0x00},  // 253
    {413, 0, 1, 0, 0x00},  // 254
    {414, 0, 1, 2, 0x00},  // 255
    {415, 0, 1, 2, 0x00},  // 256
    {416, 0, 1, 0, 0x00},  // 257
    {417, 0, 1, 0, 0x00},  // 258
    {418, 0, 1, 0, 0x00},  // 259
    {419, 0, 1, 0, 0x01},  // 260
    {420, 0, 1, 0, 0x00},  // 261
    {421, 0, 1, 0, 0x01},  // 262
    {422, 0, 1, 2, 0x00},  // 263
    {423, 0, 1, 0, 0x01},  // 264
    {424, 0, 1, 0, 0x00},  // 265
    {425, 0, 1, 0, 0x00},  // 266
    {426, 0, 1, 0, 0x00},  // 267
    {427, 0, 1, 0, 0x00},  // 268
    {428, 0, 1, 2, 0x00},  // 269
};

bool DataManager::GetEnhanceData(int enhance, ENHANCE_EFFECT_DATA& data, bool all) {
    if (enhance < 0x106) {
        return false;
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x2C);
    unsigned short effect = Bdat::getValCheckU16(fp, "EnhanceEffect", enhance);
    if (!(effect >= 1 && effect <= 0x10D)) {
        return false;
    }
    const ENHANCE_EFFECT_INFO& info = s_enhanceEffectInfo[effect - 1];
    if ((info.m_flags & 0x20) && !all) {
        return false;
    }
    int value = info.m_effect;
    switch (info.m_valueType) {
    case 1: {
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, "Param1", enhance, 8);
        value += static_cast<int>(param.real);
        break;
    }
    case 2: {
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, "Param2", enhance, 8);
        value += static_cast<int>(param.real);
        break;
    }
    case 3: {
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, "Param1", enhance, 8);
        value += 10 - (static_cast<int>(param.real) + 9) / 10;
        break;
    }
    case 4: {
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, "Param1", enhance, 8);
        value += 10 - static_cast<int>(param.real) / 10;
        break;
    }
    }
    data.m_effect = value;
    unsigned short valueParam = info.m_valueParam;
    if (valueParam != 0) {
        mm::mtl::FixStr<32> column;
        column.format("Param%d", valueParam);
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, column.m_str, enhance, 8);
        data.pad_8 = param.real;
    } else {
        data.pad_8 = 999999.0f;
    }
    unsigned char* effectFp = gf::GfDataBdat::getFP(0x2D);
    data.pad_5 = Bdat::getValCheck(effectFp, "Name", effect, 2);
    data.pad_6_0 = Bdat::getValCheckU8(effectFp, "Direct", effect) == 0;
    data.pad_6_1 = Bdat::getFlagVal(effectFp, "Flag", effect, "UI") != 0;
    data.pad_6_2 = Bdat::getFlagVal(effectFp, "Flag", effect, "PG") != 0;
    unsigned short param2Param = info.m_param2Param;
    if (param2Param != 0) {
        mm::mtl::FixStr<32> column;
        column.format("Param%d", param2Param);
        Bdat::uVal param;
        param.ulong = Bdat::getValCheck(fp, column.m_str, enhance, 8);
        data.pad_2 = static_cast<int>(param.real);
    } else {
        data.pad_2 = Bdat::getValCheck(effectFp, "Param", effect, 2);
    }
    data.pad_4 = info.m_flags & 7;
    data.pad_6_3 = info.m_flags >> 3;
    data.pad_6_4 = info.m_flags >> 4;
    return true;
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
