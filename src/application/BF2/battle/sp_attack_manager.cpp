#include "classes/btl/BattleCharacter.h"
#include "classes/btl/SpAttackManager.h"
#include "btl/Utility.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfArtsMovie.h"
#include "classes/gf/GfTrinityAttack.h"

namespace btl {

inline void SpAttackManager::PROC_DATA::Reset() {
    if (m_artsMovie) {
        gf::GfArtsMovie::destroy();
        m_artsMovie = nullptr;
    }
    if (m_trinityAttack) {
        gf::GfTrinityAttack::destroy();
        m_trinityAttack = nullptr;
    }
    m_attacker = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    m_partner = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    pad_28 = 0;
    pad_30 = 0;
    pad_38 = 0;
    m_state = 0;
    pad_44 = 0;
    pad_48 = 0;
    pad_50 = 0;
    pad_5C_0 = 0;
    m_isUpdateAttackData = 0;
    m_progressPair = 0;
    m_progressThird = 0;
    m_isDispThirdChr = 0;
    m_info54 = Info54();
    m_pair51 = Pair51();
    m_phase = 0;
}
SpAttackManager::~SpAttackManager() {}

void SpAttackManager::Create() {
#line 152
    SpAttackManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) SpAttackManager;
    manager->NotifyMapChange();
}

void SpAttackManager::Destroy() {
    delete get();
}

void SpAttackManager::NotifyMapChange() {
    for (int i = 0; i < 5; i++) {
        m_procs[i].Reset();
    }
    m_procCount = 0;
}

void SpAttackManager::DeleteCamera(bool interpolate) {
    if (m_camera) {
        float time = interpolate ? m_cameraFrames * (1.0f / 30.0f) : 0.0f;
        fw::CameraManager::get()->m_layers[0].pop(m_camera, time);
        m_camera = nullptr;
        m_cameraState = 0;
    }
    for (int i = 0; i < 3; i++) {
        gf::GF_OBJ_HANDLE* handle = m_cameraCharas[i];
        BattleCharacter* chara = CharacterManager::get()->GetCharacterConst(handle);
        if (chara) {
            chara->m_spAttackCamera = 0;
        }
        m_cameraCharas[i] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void SpAttackManager::Update(const fw::UpdateInfo& info) {
    get()->UpdateProc(info);
}

inline bool SpAttackManager::PROC_DATA::IsMember(gf::GF_OBJ_HANDLE* handle) const {
    return m_attacker == handle || m_partner == handle || (m_trinityAttack && Utility::IsThirdCharacter(handle));
}

bool SpAttackManager::IsRegister(gf::GF_OBJ_HANDLE* handle) const {
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        if (m_procs[i].IsMember(handle)) {
            return true;
        }
    }
    return false;
}

void SpAttackManager::NotifyProgress(gf::GF_OBJ_HANDLE* handle, PROGRESS_ID id) {
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        PROC_DATA& data = m_procs[i];
        if (data.IsMember(handle)) {
            switch (id) {
            case 0:
                if (!data.m_trinityAttack) {
                    data.m_progressPair = 1;
                } else {
                    if (Utility::IsThirdCharacter(handle)) {
                        data.m_progressThird = 1;
                    } else {
                        data.m_progressPair = 1;
                    }
                    if (!data.m_progressPair || !data.m_progressThird) {
                        return;
                    }
                }
                data.m_state = 4;
                break;
            case 2:
                data.m_state = 5;
                break;
            case 3:
                data.m_state = 7;
                break;
            }
            return;
        }
    }
}

void SpAttackManager::FinishUpdateAttackData(gf::GF_OBJ_HANDLE* handle) {
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        if (m_procs[i].IsMember(handle)) {
            m_procs[i].m_isUpdateAttackData = 0;
            return;
        }
    }
}

unsigned char SpAttackManager::GetSpAttackSlot(gf::GF_OBJ_HANDLE* handle) const {
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        if (m_procs[i].IsMember(handle)) {
            return m_procs[i].m_info54.m_slot;
        }
    }
    return 0xf;
}

gf::GF_OBJ_HANDLE* SpAttackManager::GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const {
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        if (m_procs[i].IsMember(handle)) {
            return m_procs[i].m_target;
        }
    }
    return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool SpAttackManager::IsLastAttackDriver(gf::GF_OBJ_HANDLE* handle) const {
    bool found = false;
    bool flag;
    int count = m_procCount;
    for (int i = 0; i < count; i++) {
        if (m_procs[i].IsMember(handle)) {
            flag = m_procs[i].m_isLastAttackDriver;
            found = true;
            break;
        }
    }
    return found & flag;
}

bool SpAttackManager::IsDispThirdChr() const {
    bool found = false;
    bool flag;
    for (int i = 0; i < m_procCount; i++) {
        if (m_procs[i].m_trinityAttack) {
            flag = m_procs[i].m_isDispThirdChr;
            found = true;
            break;
        }
    }
    return found && flag;
}

bool SpAttackManager::IsMovie() const {
    for (int i = 0; i < m_procCount; i++) {
        if (m_procs[i].m_phase == 3 || m_procs[i].m_phase == 4) {
            return true;
        }
    }
    return false;
}

}  // namespace btl
