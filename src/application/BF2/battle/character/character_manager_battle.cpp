#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/TalkManager.h"
#include "gf/GfQuestUtil.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "btl/siren_battle_manager.h"
#include "classes/gf/GfGameParty.h"

namespace btl {

CharacterManager::~CharacterManager() {}

void CharacterManager::Create() {
#line 77
    new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) CharacterManager;
}

void CharacterManager::Destroy() {
    CharacterManager* manager = sys();
    if (manager != nullptr) {
        delete manager;
    }
}

int CharacterManager::SearchCharacter(gf::GF_OBJ_HANDLE* handle) const {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        int low = 0;
        int high = static_cast<int>(m_sortedSlots.size()) - 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            int index = m_sortedSlots[mid];
            gf::GF_OBJ_HANDLE* found = m_slots[index].m_chr.m_handle;
            if (found == handle) {
                return index;
            }
            if (handle < found) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }
    return -1;
}

int CharacterManager::Register(gf::GF_OBJ_HANDLE* handle, bool isEnemy) {
    int found = SearchCharacter(handle);
    if (found >= 0) {
        return found;
    }
    for (int last = (isEnemy ? CHARACTER_NUM - 1 : PLAYER_NUM - 1), i = (isEnemy ? PLAYER_NUM : 0); i <= last;
         i++) {
        CHARACTER_SLOT& slot = m_slots[i];
        if (slot.m_isUsed) continue;
        slot.m_isUsed = true;
        bool inserted = false;
        for (mm::mtl::FixedVector<unsigned char, CHARACTER_NUM>::iterator it = m_sortedSlots.begin();
             it != m_sortedSlots.end(); ++it) {
            if (handle < GetCharacterConst(*it)->m_handle) {
                m_sortedSlots.insert(it, i);
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            m_sortedSlots.push_back(i);
        }
        slot.m_chr.Initialize(handle, i);
        return i;
    }
    return -1;
}

void CharacterManager::Release(int index, gf::GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && m_slots[index].m_chr.m_handle != handle) {
        return;
    }
    BattleCharacter* chr = &m_slots[index].m_chr;
    int aiChrID = chr->m_index;
    if (aiChrID >= 0) {
        chr->m_index = -1;
        if (chr->m_isPlayer) {
            m_aiChrTable.m_player[aiChrID] = 0xFF;
        } else {
            m_aiChrTable.m_enemy[aiChrID] = 0xFF;
        }
    }
    chr->Initialize(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1), -1);
    m_slots[index].m_isUsed = false;
    for (mm::mtl::FixedVector<unsigned char, CHARACTER_NUM>::iterator it = m_sortedSlots.begin();
         it != m_sortedSlots.end(); ++it) {
        if (*it == index) {
            m_sortedSlots.erase(it);
            return;
        }
    }
}

BattleCharacter* CharacterManager::GetCharacterConst(gf::GF_OBJ_HANDLE* handle) const {
    int index = SearchCharacter(handle);
    return index < 0 ? nullptr : const_cast<BattleCharacter*>(&m_slots[index].m_chr);
}

BattleCharacter* CharacterManager::GetCharacterConst(int index) const {
    if (index >= 0 && index < CHARACTER_NUM) {
        return m_slots[index].m_isUsed ? const_cast<BattleCharacter*>(&m_slots[index].m_chr) : nullptr;
    }
    return nullptr;
}

BattleCharacter* CharacterManager::GetCharacterByBdatIDConst(bool isPlayer, unsigned int bdatID) const {
    int begin = isPlayer ? 0 : PLAYER_NUM;
    int last = isPlayer ? PLAYER_NUM - 1 : CHARACTER_NUM - 1;
    for (int i = begin; i <= last; i++) {
        const CHARACTER_SLOT& slot = m_slots[i];
        if (!slot.m_isUsed) continue;
        bool found = slot.m_chr.m_bdatID == bdatID;
        if (found) return const_cast<BattleCharacter*>(&slot.m_chr);
    }
    return nullptr;
}

gf::GF_OBJ_HANDLE* CharacterManager::GetCharacterHandle(int index) const {
    if (index >= 0 && index < CHARACTER_NUM && m_slots[index].m_isUsed) {
        return m_slots[index].m_chr.m_handle;
    }
    return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

BattleCharacter* CharacterManager::GetControlCharacter() {
    int index = m_controlIndex;
    if (index >= CHARACTER_NUM) {
        return nullptr;
    }
    return m_slots[index].m_isUsed ? &m_slots[index].m_chr : nullptr;
}

bool CharacterManager::IsControlCharacter(gf::GF_OBJ_HANDLE* handle) {
    int index = m_controlIndex;
    if (index >= CHARACTER_NUM || !m_slots[index].m_isUsed) {
        return false;
    }
    return m_slots[index].m_chr.m_handle == handle;
}

BattleCharacter* CharacterManager::GetBattleEnemyCharacter(bool aliveOnly, bool skipFn28D0C) {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->IsBattle() && (!skipFn28D0C || !chr->fn_7100028D0C(false)) &&
            (!aliveOnly || !chr->IsDead(0))) {
            return chr;
        }
    }
    return nullptr;
}

int CharacterManager::GetAliveBossNum() const {
    int num = 0;
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param != nullptr && param->m_hasHateTarget && !param->IsBlade(false) && !chr->IsDead(0)) {
            num += param->IsBoss();
        }
    }
    return num;
}

void CharacterManager::AddPartyGaugeLimit(unsigned int count) {
    int total = m_enhanceCount + count;
    m_enhanceCount = total < 0xFF ? total : 0xFF;
}

bool CharacterManager::IsCharacterDead(gf::GF_OBJ_HANDLE* handle) const {
    const BattleCharacter* chr = GetCharacterConst(SearchCharacter(handle));
    if (chr == nullptr) {
        return true;
    }
    return chr->IsDead(0);
}

void CharacterManager::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

void CharacterManager::PreUpdateProc(const fw::UpdateInfo& info) {
    bool questEnemy = false;
    if (BattleGlobal::sys()->pad_bit6) {
        questEnemy = true;
    }
    for (unsigned char index : m_sortedSlots) {
        BattleCharacter* chr = &m_slots[index].m_chr;
        chr->PreManagerUpdate(info);
        if (!questEnemy && !chr->m_isPlayer && chr->IsBattle()) {
            questEnemy = !gf::GfQuestUtil::getCurrentEnemyWithEvent(chr->m_bdatID).empty();
        }
    }
    if (questEnemy) {
        BattleGlobal* global = BattleGlobal::sys();
        if (!global->pad_bit6) {
            global->pad_bit6 = true;
        }
    }
}

void CharacterManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void CharacterManager::UpdateProc(const fw::UpdateInfo& info) {
    m_enhanceCount = 0;
    AssignAiChrID();
    int control = -1;
    for (unsigned char index : m_sortedSlots) {
        BattleCharacter* chr = &m_slots[index].m_chr;
        chr->ManagerUpdate(info);
        if (control < 0 && chr->IsControlCharacter()) {
            control = index;
        }
    }
    m_controlIndex = control >= 0 ? control : CHARACTER_NUM;
    BattleGlobal* global = BattleGlobal::sys();
    if (global->m_challengeAnySuccess) {
        SirenBattleManager* siren = SirenBattleManager::sys();
        if (siren->pad_1cb && siren->m_sides[0].pad_12_0) {
            AddPartyGaugeLimit(3);
        }
    }
    int rest = 3 - m_enhanceCount;
    global->pad_83c9 = rest < 0 ? 0 : (rest > 3 ? 3 : rest);
}

void CharacterManager::AssignAiChrID() {
    bool inBattle = false;
    for (unsigned char index : m_sortedSlots) {
        if (m_slots[index].m_chr.IsBattle()) {
            inBattle = true;
            break;
        }
    }
    if (inBattle) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            BattleCharacter* chr = GetCharacterConst(i);
            if (chr == nullptr) continue;
            int aiChrID = chr->m_index;
            if (aiChrID >= 0) continue;
            const CharacterParameter* param = chr->GetCharacterParameterConst(true);
            if (param == nullptr) continue;
            if (BattleGlobal::sys()->m_challengeAnySuccess) {
                // the index the handle carries in its low byte
                aiChrID = static_cast<unsigned char>(reinterpret_cast<unsigned long>(chr->m_handle));
            } else {
                int group = param->m_groupIndex;
                if (param->IsBlade(false)) {
                    // a blade: 3 past five ids for each party member before its driver's
                    for (int blade = 0; blade < 5; blade++) {
                        if (gf::GfGameParty::getHandleBlade(group, blade) == chr->m_handle) {
                            aiChrID = group * 5 + blade + 3;
                            break;
                        }
                    }
                } else {
                    aiChrID = group;
                }
            }
            if (aiChrID >= 0) {
                chr->m_index = aiChrID;
                m_aiChrTable.m_player[aiChrID] = i;
            }
        }
    } else {
        for (int i = 0; i < PLAYER_NUM; i++) {
            BattleCharacter* chr = GetCharacterConst(i);
            if (chr != nullptr && chr->m_index >= 0) {
                int aiChrID = chr->m_index;
                chr->m_index = -1;
                m_aiChrTable.m_player[aiChrID] = 0xFF;
            }
        }
    }
    if (inBattle) {
        for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
            BattleCharacter* chr = GetCharacterConst(i);
            if (chr != nullptr && chr->m_index < 0) {
                chr->m_index = i - PLAYER_NUM;
                m_aiChrTable.m_enemy[i - PLAYER_NUM] = i;
            }
        }
    } else {
        for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
            BattleCharacter* chr = GetCharacterConst(i);
            if (chr != nullptr && chr->m_index >= 0) {
                int aiChrID = chr->m_index;
                chr->m_index = -1;
                m_aiChrTable.m_enemy[aiChrID] = 0xFF;
            }
        }
    }
}

void CharacterManager::PostUpdate(const fw::UpdateInfo& info) {
    sys()->PostUpdateProc(info);
}

void CharacterManager::PostUpdateProc(const fw::UpdateInfo& info) {
    bool isScout = false;
    for (unsigned char index : m_sortedSlots) {
        BattleCharacter* chr = &m_slots[index].m_chr;
        chr->PostManagerUpdate(info);
        if (chr->m_isPlayer) {
            chr->UpdateHateRingData();
        } else if (!isScout) {
            isScout = chr->IsScout();
        }
    }
    BattleGlobal::sys()->pad_bit29 = isScout;
    for (unsigned char index : m_sortedSlots) {
        BattleCharacter* chr = &m_slots[index].m_chr;
        if (!chr->m_isPlayer) {
            chr->UpdateHateRingData();
        }
    }
}

int CharacterManager::GetCharacterIDByAiChrID(int id, bool isPlayer) const {
    if (isPlayer) {
        if (m_aiChrTable.m_player[id] != 0xFF) {
            return m_aiChrTable.m_player[id];
        }
    } else {
        if (m_aiChrTable.m_enemy[id] != 0xFF) {
            return m_aiChrTable.m_enemy[id];
        }
    }
    return -1;
}

void CharacterManager::CheckTutorialEnemy() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        if (m_slots[i].m_isUsed) {
            m_slots[i].m_chr.CheckTutorialEnemy();
        }
    }
}

bool CharacterManager::IsExistSeriousBattleEnemy() const {
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        return false;
    }
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        bool found = chr->GetWeaponEffectCaster();
        if (found) return true;
    }
    return false;
}

bool CharacterManager::IsExistAlivePlayer() const {
    for (int i = 0; i < PLAYER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && !chr->IsBlade() && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistAliveEnemy(bool battleOnly) const {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && (!battleOnly || chr->IsBattle()) && !chr->IsBlade() && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistChallengeBattleEnemy() const {
    bool locked = gf::GfGameInsideBattleLock::sys()->m_hasLock;
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr || (locked && !chr->pad_F00_4)) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(false);
        if (param != nullptr && (param->IsChallengeTarget() || chr->IsBattle()) && param->m_isNotBlade && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

void CharacterManager::BattleEndInitialize() {
    for (unsigned char index : m_sortedSlots) {
        BattleCharacter* chr = &m_slots[index].m_chr;
        if (chr->fn_7100028D0C(true)) continue;
        if (chr->m_isPlayer || !chr->IsDead(0)) {
            chr->BattleEndInitialize();
        }
    }
}

bool CharacterManager::IsExistBattlePlayer() const {
    for (int i = 0; i < PLAYER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->IsBattle() && !chr->pad_F00_3) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistEnArrange(unsigned int bdatID) const {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->m_bdatID == bdatID && chr->IsBattle() && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistHikariSp() const {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(false);
        if (param != nullptr && param->IsInvalidHikariSp() && param->m_hasHateTarget && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistAlwaysKakusei() const {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(false);
        if (param != nullptr && param->IsAlwaysKakusei() && param->m_hasHateTarget && !chr->IsDead(0)) {
            return true;
        }
    }
    return false;
}

bool CharacterManager::IsExistHomuri() const {
    for (int i = 0; i < PLAYER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr || !chr->fn_7100028D0C(false)) continue;
        // 1003: the bdat id the name asks for (Homura)
        bool found = chr->m_bdatID == 1003;
        if (found) return true;
    }
    return false;
}

int CharacterManager::GetBattleEnemyMaxLevel(bool addNamed) const {
    int maxLevel = 0;
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(false);
        if (param != nullptr && param->m_hasHateTarget && !chr->IsDead(0)) {
            int level = param->GetLevel();
            if (addNamed && param->IsNamed()) {
                level += 15;
            }
            maxLevel = maxLevel > level ? maxLevel : level;
        }
    }
    return maxLevel;
}

void CharacterManager::PlayEnemyWinVoice() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->IsBattle() && !chr->fn_7100028D0C(false) && !chr->IsDead(0)) {
            if (mm::mtl::PtrSingleton<TalkManager>::sys()->NotifyTrigger(i, static_cast<TalkManager::TRIGGER>(23), 0, 0)) {
                return;
            }
        }
    }
}

void CharacterManager::SetupBGM(bool battleOnly, bool includeDead) {
    bool found = false;
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr || (battleOnly && !chr->IsBattle()) || chr->IsDead(0)) continue;
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param == nullptr) continue;
        if (!found) {
            BattleGlobal::sys()->ResetBGM();
        }
        param->SetupBGM();
        found = true;
    }
    if (!found && includeDead) {
        for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
            BattleCharacter* chr = GetCharacterConst(i);
            if (chr == nullptr || (battleOnly && !chr->IsBattle())) continue;
            CharacterParameter* param = chr->GetCharacterParameter(true);
            if (param == nullptr) continue;
            if (!found) {
                BattleGlobal::sys()->ResetBGM();
            }
            param->SetupBGM();
            found = true;
        }
    }
}

void CharacterManager::NotifyChallengeNextWave() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->IsDead(0) && !chr->pad_F06_1) {
            chr->pad_F06_1 = 1;
        }
    }
}

}  // namespace btl
