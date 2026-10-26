#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gf/GfAllocator.h"

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

BattleCharacter* CharacterManager::GetCharacterConst(int index) const {
    if (index >= 0 && index < CHARACTER_NUM) {
        return m_slots[index].m_isUsed ? const_cast<BattleCharacter*>(&m_slots[index].m_chr) : nullptr;
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

void CharacterManager::fn_710007C020(int count) {
    int total = m_enhanceCount + count;
    m_enhanceCount = total < 0xFF ? total : 0xFF;
}

void CharacterManager::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

void CharacterManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void CharacterManager::PostUpdate(const fw::UpdateInfo& info) {
    sys()->PostUpdateProc(info);
}

void CharacterManager::fn_710007C1E0() {
    for (int i = PLAYER_NUM; i < CHARACTER_NUM; i++) {
        if (m_slots[i].m_isUsed) {
            m_slots[i].m_chr.fn_710002B868();
        }
    }
}

}  // namespace btl
