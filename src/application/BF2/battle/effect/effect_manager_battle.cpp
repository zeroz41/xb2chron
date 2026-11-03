#include "classes/btl/EffectManager.h"
#include <string.h>
#include "fw/UpdateInfo.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"

namespace btl {


inline void EffectManager::DeleteAllEffect() {
    for (mm::mtl::FixedList<PROC_DATA, 90>::iterator it = m_procList.begin(); it != m_procList.end();) {
        EFFECT_DATA& data = m_effects[(*it).m_index];
        data.m_used = false;
        data.m_obj.Initialize(0);
        it = m_procList.erase(it);
    }
}

inline void EffectManager::Finalize() {
    DeleteAllEffect();
}

EffectManager::EffectManager() : m_nextId(1) {}

void EffectManager::Destroy() {
    EffectManager* manager = sys();
    manager->Finalize();
    delete manager;
}

void EffectManager::NotifyMapChange() {
    DeleteAllEffect();
}

void EffectManager::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

void EffectManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

EffectObject* EffectManager::GetEffect(unsigned int id) {
    for (mm::mtl::FixedList<PROC_DATA, 90>::iterator it = m_procList.begin(); it != m_procList.end(); ++it) {
        if ((*it).m_id == id) {
            EffectObject* obj = &m_effects[(*it).m_index].m_obj;
            if (obj->m_id == id) {
                return obj;
            }
        }
    }
    return nullptr;
}
}  // namespace btl

// instantiated for btl::EffectManager::UpdateProc (not written yet)
template mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::iterator mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::erase(mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::iterator);

namespace btl {

bool EffectManager::IsExistChrHitEffect(gf::GF_OBJ_HANDLE* handle) const {
    for (mm::mtl::FixedList<PROC_DATA, 90>::const_iterator it = m_procList.begin(); it != m_procList.end();
         ++it) {
        const EFFECT_DATA& data = m_effects[(*it).m_index];
        if (data.m_used && data.m_obj.m_owner == handle && data.m_obj.m_bit3) {
            return true;
        }
    }
    return false;
}

float EffectManager::fn_7100099748(int index) const {
    return m_rates[index] * 0.01f;
}
}  // namespace btl

// instantiated for btl::EffectManager::~EffectManager (not written yet)
template mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::~FixedList();

namespace btl {


}  // namespace btl
