#include "classes/btl/HateRingManager.h"
#include "btl/Misc.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameParty.h"
#include "fw/UpdateInfo.h"
#include "mm/Col4.h"
#include "mm/Math.h"
#include <math.h>

namespace btl {

inline void HateRingManager::RING_DATA::Reset() {
    m_handle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    m_target = -1;
    m_arrowTime = 0.0f;
    if (m_ringEffect != 0) {
        fw::EffectManager::sys()->destroyHateRingVec(m_ringEffect);
    }
    if (m_arrowEffect != 0) {
        fw::EffectManager::sys()->destroyHateArrow(m_arrowEffect);
    }
    m_ringEffect = 0;
    m_arrowEffect = 0;
    m_pos = mm::Vec3::zero;
}

HateRingManager::~HateRingManager() {}

void HateRingManager::Create() {
#line 93
    new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) HateRingManager;
}

void HateRingManager::Destroy() {
    HateRingManager* manager = get();
    int i = 0;
    RING_DATA* ring = manager->m_rings;
    do {
        ring->Reset();
        ring++;
        i++;
    } while (i < 90);
    delete manager;
}

void HateRingManager::PreUpdate(const fw::UpdateInfo&) {}

void HateRingManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void HateRingManager::UpdateProc(const fw::UpdateInfo& info) {
    for (int i = 0; i < 3; i++) {
        m_hateEnemyNum[i] = 0;
    }
    if (BattleGlobal::sys()->IsEnableBattle()) {
        RING_DATA* ring = m_rings;
        for (int i = 0; i < 90; i++, ring++) {
            if (ring->m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                continue;
            }
            BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
            if (chr == nullptr || chr->IsDead(0)) {
                ring->Reset();
            } else {
                m_hateEnemyNum[ring->m_target]++;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (m_hateEnemyNum[i] == 0 && m_ringEffects[i] != 0) {
                fw::EffectManager::sys()->destroyHateRing(m_ringEffects[i]);
                m_ringEffects[i] = 0;
            }
        }
    }
    RING_DATA* ring = m_rings;
    for (int i = 0; i < 90; i++, ring++) {
        UpdateArrow(i, *ring, info.m_deltaTime);
    }
}

void HateRingManager::UpdateArrow(int index, RING_DATA& ring, float deltaTime) {
    if (ring.m_arrowEffect == 0) {
        return;
    }
    float time = ring.m_arrowTime;
    if (time < 0.0f) {
        return;
    }
    float rate;
    if (time < 15.0f) {
        rate = time * (1.0f / 15.0f);
        float step = deltaTime * 30.0f;
        ring.m_arrowTime = time + step;
    } else {
        rate = 1.0f;
        ring.m_arrowTime = -1.0f;
    }
    mm::Vec3 pos;
    Misc::GetObjectTransform(ring.m_handle, pos, Misc::TRANS_TYPE_POS);
    pos.y += CharacterManager::sys()->GetCharacterConst(index)->GetCharacterParameterConst(true)->pad_30 + 0.2f;
    mm::Vec3 target;
    if (!ring.m_pos.isZero()) {
        target = ring.m_pos;
    } else {
        target = m_partyPos[ring.m_target];
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(ring.m_target, static_cast<gf::PTPOS>(0));
        target.y += CharacterManager::sys()->GetCharacterConst(driver)->GetCharacterParameterConst(true)->pad_30 * 0.82f;
        ring.m_pos = target;
    }
    mm::Vec3 dir = target - pos;
    mm::Vec3 arrow(rate * dir.x + pos.x, rate * dir.y + pos.y, rate * dir.z + pos.z);
    arrow.y += sinf(rate * 3.1415927f) * mm::clamp(Misc::CalcLengthXZ(dir) * 0.25f, 2.0f, 4.0f);
    fw::EffectManager::sys()->updateHateArrow(ring.m_arrowEffect, arrow, 0.0f, 1.0f, mm::Col4::white);
}

void HateRingManager::UpdateRing(int index, mm::Vec3 pos, mm::Vec3 dir) {
    m_partyPos[index] = pos;
    fw::EffectManager* effect = fw::EffectManager::sys();
    unsigned int handle = m_ringEffects[index];
    if (m_hateEnemyNum[index] != 0) {
        if (handle == 0) {
            handle = effect->createHateRing();
        }
        if (handle != 0) {
            float angle = Misc::CalcRotY(dir);
            effect->updateHateRing(m_ringEffects[index], pos, angle, true, 1.0f);
        }
    } else if (handle != 0) {
        effect->destroyHateRing(handle);
        handle = 0;
    }
    m_ringEffects[index] = handle;
}

void HateRingManager::SetData(int index, gf::GF_OBJ_HANDLE* handle, int target) {
    RING_DATA& ring = m_rings[index];
    if (target < 0) {
        if (ring.m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            return;
        }
        ring.Reset();
        return;
    }
    ring.m_handle = handle;
    fw::EffectManager* effect = fw::EffectManager::sys();
    if (ring.m_target != target) {
        if (ring.m_target >= 0) {
            gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(ring.m_target, static_cast<gf::PTPOS>(0));
            BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
            if (chr != nullptr) {
                chr->NotifyLostHateTarget(index);
            }
            gf::GF_OBJ_HANDLE* blade = gf::GfGameParty::getHandleBlade(ring.m_target, -1);
            chr = CharacterManager::sys()->GetCharacterConst(blade);
            if (chr != nullptr) {
                chr->NotifyLostHateTarget(index);
            }
        }
        if (target >= 0) {
            int prev = ring.m_target;
            gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(target, static_cast<gf::PTPOS>(0));
            BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
            if (chr != nullptr) {
                chr->NotifyGetHateTarget(index, prev < 0);
            }
            gf::GF_OBJ_HANDLE* blade = gf::GfGameParty::getHandleBlade(target, -1);
            chr = CharacterManager::sys()->GetCharacterConst(blade);
            if (chr != nullptr) {
                chr->NotifyGetHateTarget(index, prev < 0);
            }
        }
        ring.m_target = target;
        ring.m_arrowTime = 0.0f;
        if (ring.m_arrowEffect != 0) {
            effect->destroyHateArrow(ring.m_arrowEffect);
            ring.m_arrowEffect = 0;
        }
        ring.m_pos = mm::Vec3::zero;
    }
    if (m_ringEffects[target] == 0) {
        if (ring.m_ringEffect != 0) {
            effect->destroyHateRingVec(ring.m_ringEffect);
            ring.m_ringEffect = 0;
        }
        if (ring.m_arrowEffect != 0) {
            effect->destroyHateArrow(ring.m_arrowEffect);
            ring.m_arrowEffect = 0;
        }
        ring.m_pos = mm::Vec3::zero;
        return;
    }
    if (ring.m_ringEffect == 0) {
        ring.m_ringEffect = effect->createHateRingVec();
    }
    if (ring.m_ringEffect != 0) {
        mm::Vec3 pos;
        Misc::GetObjectTransform(handle, pos, Misc::TRANS_TYPE_POS);
        mm::Vec3 dir;
        Misc::CalcDirectionXZ(m_partyPos[target], pos, dir);
        float angle = Misc::CalcRotY(dir);
        effect->updateHateRingVec(ring.m_ringEffect, m_partyPos[target], angle, 1.0f, mm::Col4::white);
    }
    if (ring.m_arrowEffect == 0) {
        ring.m_arrowEffect = effect->createHateArrow();
        ring.m_arrowTime = 0.0f;
        ring.m_pos = mm::Vec3::zero;
        UpdateArrow(index, ring, 0.0f);
    }
}

gf::GF_OBJ_HANDLE* HateRingManager::GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const {
    return gf::GfGameParty::getHandleDriver(GetTarget(handle), static_cast<gf::PTPOS>(0));
}

unsigned char HateRingManager::GetHateEnemyNum(int index) const {
    return m_hateEnemyNum[index];
}

unsigned int HateRingManager::GetHateEnemyNumAll() const {
    unsigned int packed = 0;
    for (int i = 0; i < 3; i++) {
        packed |= m_hateEnemyNum[i] << (i * 10);
    }
    return packed;
}

}  // namespace btl
