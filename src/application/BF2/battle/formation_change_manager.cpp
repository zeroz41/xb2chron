#include "btl/formation_change_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameParty.h"
#include "fw/UpdateInfo.h"

namespace btl {

TUnk_B3BC20::TUnk_B3BC20() : m_count(0), m_serial(0) {}

TUnk_B3BC20::~TUnk_B3BC20() {}

void fn_710009D7B8() {
#line 83
    TUnk_B3BC20* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B3BC20;
    manager->fn_710009D92C();
}

void fn_710009D90C() {
    delete TUnk_B3BC20::get();
}

void TUnk_B3BC20::fn_710009D92C() {
    m_serial = 1;
    for (int i = 0; i < 10; i++) {
        m_requests[i].clear();
    }
    m_count = 0;
}

void TUnk_B3BC20::fn_710009DA40(const fw::UpdateInfo& info) {}

void TUnk_B3BC20::fn_710009DA44(const fw::UpdateInfo& info) {
    get()->fn_710009DA5C(info);
}

bool TUnk_B3BC20::fn_710009E940(gf::GF_OBJ_HANDLE* handle, bool flag) {
    BattleGlobal* global = BattleGlobal::get();
    if (!global->m_challengeAnySuccess || !global->IsEnableBattle()) {
        return false;
    }
    BattleCharacter* character = CharacterManager::get()->GetCharacterConst(handle);
    if (character == nullptr || !character->IsBattle() || character->m_isRunHold) {
        return false;
    }
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_handle[0] == handle || m_requests[i].m_handle[1] == handle) {
            return false;
        }
    }
    if (m_count >= 10) {
        return false;
    }
    Request& request = m_requests[m_count];
    request.clear();
    request.m_pos = character->m_pos;
    request.m_handle[0] = handle;
    request.m_serial = m_serial;
    request.m_type = 2;
    request.m_groupIndex = character->GetGroupIndex();
    request.m_flag29 = character->fn_710002F1F8();
    request.m_flag2a = flag;
    m_serial = m_serial == 0xFFFFFFFF ? 1 : m_serial + 1;
    m_count++;
    return true;
}

void TUnk_B3BC20::fn_710009EAD0(gf::GF_OBJ_HANDLE* handle) {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_handle[0] == handle || m_requests[i].m_handle[1] == handle) {
            m_requests[i].m_end = true;
            return;
        }
    }
}

TUnk_B3BC20::Request* TUnk_B3BC20::fn_710009EB1C(gf::GF_OBJ_HANDLE* handle) {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_handle[0] == handle || m_requests[i].m_handle[1] == handle) {
            return &m_requests[i];
        }
    }
    return nullptr;
}

bool TUnk_B3BC20::fn_710009EB70(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_handle[0] == handle || m_requests[i].m_handle[1] == handle) {
            return true;
        }
    }
    return false;
}

bool TUnk_B3BC20::fn_710009EBC4(int group) const {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_groupIndex == group) {
            return true;
        }
    }
    return false;
}

bool TUnk_B3BC20::fn_710009EC0C(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_type == 2) {
            if (m_requests[i].m_handle[0] == handle) {
                return true;
            }
            if (m_requests[i].m_handle[1] == handle) {
                return true;
            }
        }
    }
    return false;
}

bool TUnk_B3BC20::fn_710009EC6C(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_type == 1) {
            if (m_requests[i].m_handle[0] == handle) {
                return true;
            }
            if (m_requests[i].m_handle[1] == handle) {
                return true;
            }
        }
    }
    return false;
}

void TUnk_B3BC20::fn_710009ECCC(gf::GF_OBJ_HANDLE* handle) {
    for (int i = 0; i < m_count; i++) {
        if (m_requests[i].m_handle[0] == handle || m_requests[i].m_handle[1] == handle) {
            m_requests[i].m_flag32 = true;
            return;
        }
    }
}

bool TUnk_B3BC20::fn_710009ED18(gf::GF_OBJ_HANDLE* handle) {
    Request* request = fn_710009EB1C(handle);
    bool flag;
    if (request != nullptr) {
        if (request->m_flag32) {
            flag = true;
        } else {
            BattleCharacter* character = CharacterManager::get()->GetCharacterConst(handle);
            flag = character->fn_710002F1F8() && character->IsControlCharacterGroup() && character->pad_11B3_1;
        }
    }
    return request == nullptr || flag;
}

}  // namespace btl
