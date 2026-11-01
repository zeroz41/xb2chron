#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/TalkManager.h"
#include "gf/GfQuestUtil.h"

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

BattleCharacter* CharacterManager::fn_710007B5DC(bool isPlayer, int bdatID) const {
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

int CharacterManager::GetAliveBossNum() const {
    int num = 0;
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr == nullptr) continue;
        CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param != nullptr && param->m_hasHateTarget && !param->fn_7100085314(false) && !chr->IsDead(0)) {
            num += param->IsBoss();
        }
    }
    return num;
}

void CharacterManager::fn_710007C020(int count) {
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

void CharacterManager::fn_710007C1E0() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        if (m_slots[i].m_isUsed) {
            m_slots[i].m_chr.fn_710002B868();
        }
    }
}

bool CharacterManager::fn_710007C240() const {
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

bool CharacterManager::fn_710007C36C(bool battleOnly) const {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && (!battleOnly || chr->IsBattle()) && !chr->IsBlade() && !chr->IsDead(0)) {
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

void CharacterManager::fn_710007D594() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        BattleCharacter* chr = GetCharacterConst(i);
        if (chr != nullptr && chr->IsDead(0) && !chr->pad_F06_1) {
            chr->pad_F06_1 = 1;
        }
    }
}

}  // namespace btl
