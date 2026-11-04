#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFobjDropitem.h"
#include "mm/mtl/Vector.h"

namespace btl {

ChainAttackManager::~ChainAttackManager() {}

void ChainAttackManager::Create() {
#line 98
    ChainAttackManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ChainAttackManager;
    manager->Reset(0);
}

void ChainAttackManager::Destroy() {
    if (sys() != nullptr) {
        delete sys();
    }
}

void ChainAttackManager::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

void ChainAttackManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

bool ChainAttackManager::IsStartDirectionAfterFadeOut() const {
    return m_startStep > 1;
}

unsigned char ChainAttackManager::GetSpAttackLevel(int index) const {
    return m_spAttacks[index].level;
}

int ChainAttackManager::GetOrderAttr(int index) const {
    if (static_cast<unsigned int>(index) <= 8) {
        return m_orderAttrs[index];
    }
    return 0;
}

bool ChainAttackManager::IsProc(bool excludeStartWait) const {
    if (m_procState == 0) {
        return false;
    }
    if (IsStartWait() && excludeStartWait) {
        return false;
    }
    return true;
}

bool ChainAttackManager::IsResult() const {
    return m_procState > 50;
}

float ChainAttackManager::GetDamageRate() const {
    if (m_procState < 4) {
        return 1.0f;
    }
    // the rate's bits stepped up by one (1.0.0's GetDamageRate and GetBonusRate do the same)
    union {
        float f;
        int i;
    } rate;
    rate.f = (m_damageRate - 1683) * 0.01f;
    rate.i += 1;
    return rate.f;
}

void ChainAttackManager::AddCriticalBonus(float value) {
    if (m_procState >= 1 && m_procState <= 50) {
        m_addedValue += value;
    }
}

float ChainAttackManager::GetCriticalBonus() const {
    if (m_procState != 0) {
        return m_addedValue;
    }
    return 0.0f;
}

void ChainAttackManager::AddTotalDamage(unsigned int damage) {
    if (m_procState >= 1 && m_procState <= 50) {
        m_totalDamage += damage;
    }
}

int ChainAttackManager::GetGroupIndex() const {
    if (m_groupSlot > 2) {
        return -1;
    }
    int group = m_groups[m_groupSlot];
    if (group > 2) {
        return -1;
    }
    return group;
}

bool ChainAttackManager::IsStartWait() const {
    return m_procState >= 1 && m_procState <= 3;
}

bool ChainAttackManager::IsSelectAction() const {
    return m_procState == 9;
}

bool ChainAttackManager::IsStopTime() const {
    return m_procState == 9;
}

}  // namespace btl

// the drop item vector's growth (its user is not written yet)
template void mm::mtl::Vector<gf::GfDropitemInfo>::expand(size_t, size_t);
