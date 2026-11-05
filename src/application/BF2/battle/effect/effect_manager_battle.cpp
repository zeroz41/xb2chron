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

inline void EffectManager::Initialize() {
    memset(m_rates, 0, sizeof(m_rates));
    m_ratesDirty = false;
}

void EffectManager::Create() {
#line 58
    EffectManager* manager = new (gf::getAllocator(gf::ALLOCATOR(1)), __FILE__, __LINE__, 8) EffectManager;
    manager->Initialize();
}


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

void EffectManager::UpdateProc(const fw::UpdateInfo& info) {
    fw::UpdateInfo update = info;
    if (BattleGlobal::sys()->IsPause(-1)) {
        update.m_deltaTime = 0.0f;
        update.m_speed = 0.0f;
    }
    if (m_ratesDirty) {
        memset(m_rates, 0, sizeof(m_rates));
        m_ratesDirty = false;
    }
    for (mm::mtl::FixedList<PROC_DATA, 90>::iterator it = m_procList.begin(); it != m_procList.end();) {
        int index = (*it).m_index;
        EffectObject& obj = m_effects[index].m_obj;
        obj.Update(update);
        if (obj.IsEnd()) {
            m_effects[index].m_used = false;
            obj.Initialize(0);
            it = m_procList.erase(it);
        } else {
            ++it;
        }
    }
    for (mm::mtl::FixedList<REGISTER_PROC_DATA, 30>::iterator it = m_registerList.begin();
         it != m_registerList.end();) {
        REGISTER_DATA& reg = m_registers[(*it).m_index];
        reg.m_timer -= update.m_deltaTime;
        while (reg.m_created < reg.m_count && reg.m_timer <= 0.0f) {
            for (int i = 0; i < reg.m_num; i++) {
                unsigned int id = CreateEffect(EXCLUSION_TYPE_NONE);
                if (id == 0) {
                    break;
                }
                EffectObject* obj = GetEffect(id);
                if (obj == nullptr) {
                    break;
                }
                obj->SetObject(reg.m_effectPacks, reg.m_name.m_str, reg.m_pos, nullptr, &reg.m_scale);
                gf::GF_OBJ_HANDLE* owner = reg.m_owner;
                gf::GF_OBJ_HANDLE* handle50 = reg.pad_50;
                obj->m_owner = owner;
                obj->pad_50 = handle50;
                obj->SetArtsData(reg.m_artsSlot, reg.m_artsKind, reg.m_artsParam);
                obj->pad_58 = reg.pad_58;
                obj->SetOneShotHitData(0.0f, true);
            }
            reg.m_timer += reg.m_interval;
            reg.m_created++;
        }
        if (reg.m_created < reg.m_count) {
            ++it;
        } else {
            reg.m_used = false;
            it = m_registerList.erase(it);
        }
    }
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

bool EffectManager::IsExistChrCircle(gf::GF_OBJ_HANDLE* handle) const {
    for (mm::mtl::FixedList<PROC_DATA, 90>::const_iterator it = m_procList.begin(); it != m_procList.end();
         ++it) {
        const EFFECT_DATA& data = m_effects[(*it).m_index];
        if (data.m_used && data.m_obj.m_owner == handle && data.m_obj.m_bit3) {
            return true;
        }
    }
    return false;
}

bool EffectManager::IsExistChrHitEffect(gf::GF_OBJ_HANDLE* handle, bool flag) const {
    for (mm::mtl::FixedList<PROC_DATA, 90>::const_iterator it = m_procList.begin(); it != m_procList.end();
         ++it) {
        const EFFECT_DATA& data = m_effects[(*it).m_index];
        if (data.m_used && data.m_obj.m_owner == handle && data.m_obj.m_hitKind != EffectObject::HIT_KIND_NONE &&
            (!flag || !data.m_obj.m_bit3)) {
            return true;
        }
    }
    for (mm::mtl::FixedList<REGISTER_PROC_DATA, 30>::const_iterator it = m_registerList.begin();
         it != m_registerList.end(); ++it) {
        const REGISTER_DATA& reg = m_registers[(*it).m_index];
        if (reg.m_used && reg.m_owner == handle) {
            return true;
        }
    }
    return false;
}

float EffectManager::GetCircleDamageBonusRate(int index) const {
    return m_rates[index] * 0.01f;
}
}  // namespace btl

// instantiated for btl::EffectManager::~EffectManager (not written yet)
template mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::~FixedList();

namespace btl {


}  // namespace btl
