#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/fw/EffectManager.h"
#include "btl/Misc.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfAllocator.h"

namespace btl {

// the m_wait an entry of each kind must pass before IsReceiveLater holds (the name is not the original's)
static int getReceiveLimit(int kind) {
    switch (kind) {
    case 0:
        return 6;
    case 1:
        return 7;
    case 2:
        return -1;
    }
    return -1;
}

BladeChangeManager::~BladeChangeManager() {}

void BladeChangeManager::Create() {
#line 87
    BladeChangeManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeChangeManager;
    manager->NotifyMapChange();
}

void BladeChangeManager::Destroy() {
    delete get();
}

void BladeChangeManager::NotifyMapChange() {
    m_serial = 1;
    for (int i = 0; i < 10; i++) {
        m_procs[i].clear();
    }
    m_procNum = 0;
}

void BladeChangeManager::PreUpdate(const fw::UpdateInfo& info) {}

void BladeChangeManager::Update(const fw::UpdateInfo& info) {
    get()->UpdateProc(info);
}

void BladeChangeManager::UpdateProc(const fw::UpdateInfo& info) {
    int num = m_procNum;
    for (int i = 0; i < num; i++) {
        PROC_DATA& data = m_procs[i];
        bool end;
        if (data.m_kind == 1) {
            end = HomuraChangeProc(data, info.m_deltaTime);
        } else if (data.m_kind == 2) {
            end = ForceHikariProc(data, info.m_deltaTime);
        } else if (data.m_kind == 0) {
            end = BladeChangeProc(data, info.m_deltaTime);
        } else {
            end = true;
        }
        if (end) {
            num--;
            data = m_procs[num];
            m_procs[num].clear();
            i--;
            m_procNum--;
        } else if (data.m_effect != 0) {
            fw::EffectManager* effect = fw::EffectManager::get();
            if (!effect->isExist(data.m_effect)) {
                data.m_effect = 0;
            } else {
                mm::Vec3 pos;
                if (Misc::GetObjectTransform(data.m_blade, pos, Misc::TRANS_TYPE_POS)) {
                    effect->setParam(data.m_effect, pos, mm::Vec3::unit);
                }
            }
        }
    }
}

void BladeChangeManager::FinishBladeChange(gf::GF_OBJ_HANDLE* handle) {
    int num = m_procNum;
    for (int i = 0; i < num; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            m_procs[i].m_isFinished = true;
        }
    }
}

int BladeChangeManager::GetChangeBladeIndex(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            return m_procs[i].m_changeBladeIndex;
        }
    }
    return -1;
}

int BladeChangeManager::GetBaseBladeBdatID(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            return m_procs[i].m_baseBladeBdatId;
        }
    }
    return 0;
}

int BladeChangeManager::GetBladeChangeType(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            return m_procs[i].m_type;
        }
    }
    return -1;
}

bool BladeChangeManager::IsRegister(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle && !m_procs[i].m_isDriverDone) {
            return true;
        }
        if (m_procs[i].m_blade == handle) {
            return true;
        }
        if (m_procs[i].m_newBlade == handle && !m_procs[i].m_isNewBladeDone) {
            return true;
        }
    }
    return false;
}

bool BladeChangeManager::IsReceiveLater(gf::GF_OBJ_HANDLE* handle) const {
    bool found = false;
    bool later;
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
            found = true;
            int limit = getReceiveLimit(m_procs[i].m_kind);
            later = m_procs[i].m_wait > limit;
            break;
        }
    }
    return found & later;
}

bool BladeChangeManager::fn_710001903C(gf::GF_OBJ_HANDLE* handle) const {
    for (int i = 0; i < m_procNum; i++) {
        if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || m_procs[i].m_driver == handle ||
            m_procs[i].m_blade == handle) {
            if (!m_procs[i].m_isNotHomura) {
                return true;
            }
        }
    }
    return false;
}

bool BladeChangeManager::fn_71000190E0() const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_type == 1 && m_procs[i].m_changeBladeIndex == 4 && !m_procs[i].m_isNewBladeDone) {
            return true;
        }
    }
    return false;
}

bool BladeChangeManager::IsProcHomuriEnd() const {
    for (int i = 0; i < m_procNum; i++) {
        if (m_procs[i].m_type >= 3 && m_procs[i].m_type <= 5 && !m_procs[i].m_isNotHomura) {
            return true;
        }
    }
    return false;
}

bool BladeChangeManager::fn_7100019180(gf::GF_OBJ_HANDLE* handle) {
    for (int i = 0; i < m_procNum; i++) {
        if ((m_procs[i].m_driver == handle && !m_procs[i].m_isDriverDone) || m_procs[i].m_blade == handle ||
            (m_procs[i].m_newBlade == handle && !m_procs[i].m_isNewBladeDone)) {
            BattleCharacter* chara = CharacterManager::get()->GetCharacterConst(handle);
            if (chara == nullptr) {
                return true;
            }
            return !chara->fn_7100028D0C(false);
        }
    }
    return true;
}

}  // namespace btl
