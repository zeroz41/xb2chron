#include "classes/btl/BladeArtsManager.h"
#include "btl/Utility.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/BladeArtsManager.h"
#include "btl/Utility.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/SpAttackManager.h"
#include "gf/GfObjUtil.h"
#include "btl/challenge_battle_manager.h"
#include "classes/fw/Camera.h"
#include "btl/siren_battle_manager.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/GfAllocator.h"

namespace btl {

BladeArtsManager::BladeArtsManager() {
    m_procNum = 0;
}

BladeArtsManager::~BladeArtsManager() {}

void BladeArtsManager::Create() {
#line 54
    BladeArtsManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeArtsManager;
    manager->NotifyMapChange();
}

void BladeArtsManager::Destroy() {
    delete get();
}

void BladeArtsManager::NotifyMapChange() {
    for (int i = 0; i < 10; i++) {
        m_procs[i].clear();
    }
    m_procNum = 0;
}

void BladeArtsManager::PreUpdate(const fw::UpdateInfo& info) {}

void BladeArtsManager::FinishBladeArts(gf::GF_OBJ_HANDLE* handle) {
    int num = m_procNum;
    for (int i = 0; i < num; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            m_procs[i].m_step = 7;
        }
    }
}

bool BladeArtsManager::RegisterBladeArts(gf::GF_OBJ_HANDLE* driver, gf::GF_OBJ_HANDLE* blade, gf::GF_OBJ_HANDLE* target,
                                         int arts, bool flag, bool forced) {
    if (!forced && !BattleGlobal::get()->IsEnableBattle()) {
        return false;
    }
    if (gf::GfObjUtil::getObj(driver) == nullptr || gf::GfObjUtil::getObj(blade) == nullptr ||
        gf::GfObjUtil::getObj(target) == nullptr) {
        return false;
    }
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == driver || m_procs[i].m_blade == driver || m_procs[i].m_driver == blade ||
            m_procs[i].m_blade == blade) {
            return false;
        }
    }
    if (!forced && (BladeChangeManager::get()->IsRegister(driver) || BladeChangeManager::get()->IsRegister(blade))) {
        if (!CharacterManager::get()->GetCharacterConst(driver)->pad_11B3_1) {
            return false;
        }
    }
    if (SpAttackManager::get()->IsRegister(driver) || SpAttackManager::get()->IsRegister(blade)) {
        return false;
    }
    int slot = CharacterManager::get()->GetCharacterConst(blade)->IsActBladeArts(arts, flag);
    if (slot < 0 || m_procNum >= 10) {
        return false;
    }
    PROC_DATA& data = m_procs[m_procNum];
    data.m_driver = driver;
    data.m_blade = blade;
    data.m_target = target;
    data.m_arts = slot;
    data.m_step = 0;
    data.m_challengeId = 0;
    data.m_isForced = forced;
    m_procNum++;
    return true;
}

bool BladeArtsManager::NotifyProgress(gf::GF_OBJ_HANDLE* handle, PROGRESS_ID id) {
    bool result = true;
    int num = m_procNum;
    for (int i = 0; i < num; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            if (id == 0) {
                m_procs[i].m_step = m_procs[i].m_step == 2 ? 3 : 6;
                break;
            }
            result = false;
        }
    }
    return result;
}

unsigned int BladeArtsManager::GetButtonChallengeID(gf::GF_OBJ_HANDLE* handle) const {
    const PROC_DATA* data = find(handle);
    if (data == nullptr) {
        return 0;
    }
    return data->m_challengeId;
}

gf::GF_OBJ_HANDLE* BladeArtsManager::GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const {
    const PROC_DATA* data = find(handle);
    if (data == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return data->m_target;
}

bool BladeArtsManager::IsRegister(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            return true;
        }
    }
    return false;
}

bool BladeArtsManager::IsBladeStart(gf::GF_OBJ_HANDLE* handle) const {
    bool found = false;
    bool result;
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            result = m_procs[i].m_step > 3;
            found = true;
            break;
        }
    }
    return found && result;
}

bool BladeArtsManager::IsBladeAttack(gf::GF_OBJ_HANDLE* handle) const {
    bool found = false;
    bool result;
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            result = m_procs[i].m_step == 4;
            found = true;
            break;
        }
    }
    return found && result;
}

}  // namespace btl
