#include "mm/mtl/Map.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkEnemyInsts.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkBattleLock.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gf/GfSmnEnemyManager.h"
#include "classes/gf/GfRelSmnEnemy.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "classes/fw/FrameworkMemory.h"
#include "fw/Transform.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "mm/Vec3.h"

namespace gf {

void GfGameInsideBattleLock::build(const GfSetupParam& param) {
#line 35
    GfGameInsideBattleLock* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameInsideBattleLock();
    self->m_infos.setAllocator(fw::FrameworkMemory::getAllocator(5));
}

void GfGameInsideBattleLock::destroy() {
    delete get();
}

void GfGameInsideBattleLock::update(const fw::UpdateInfo& info) {
    GfGameInsideBattleLock* self = get();
    if (self == nullptr || gmk::GmkManager::get() == nullptr) {
        return;
    }
    self->updateInfos();
    self->m_hasLock = false;
    auto f = [self](const gmk::AGmkBase& gmk) {
        const gmk::GmkBattleLock& lock = static_cast<const gmk::GmkBattleLock&>(gmk);
        if (lock.m_collision.m_coliObject != nullptr) {
            self->m_hasLock = true;
        }
    };
    gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBattleLock::TYPE, f);
}

void GfGameInsideBattleLock::updateInfos() {
    m_infos.clear();
    updateInfoByGmk<gmk::GmkEnemy>();
    updateInfoByGmk<gmk::GmkRoutedEnemy>();
    GfSmnEnemyManager* manager = GfSmnEnemyManager::get();
    if (manager == nullptr) {
        return;
    }
    unsigned int num = manager->getRelSmnEnemyNum();
    for (unsigned int i = 0; i < num; ++i) {
        const GfRelSmnEnemy* rel = GfSmnEnemyManager::get()->getRelSmnEnemy(i);
        if (rel == nullptr) {
            continue;
        }
        unsigned int enemyNum = rel->getEnemyNum();
        for (unsigned int j = 0; j < enemyNum; ++j) {
            GF_OBJ_HANDLE* handle = rel->getEnemy(j);
            m_infos[handle] = isInsideBattleLock(handle);
        }
    }
}

void GfGameInsideBattleLock::updateInfo(GF_OBJ_HANDLE* handle) {
    get()->m_infos[handle] = get()->isInsideBattleLock(handle);
}

bool GfGameInsideBattleLock::isInsideBattleLock(GF_OBJ_HANDLE* handle) const {
    GfObjAcc acc(handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    if (obj->m_type != 5) {
        return false;
    }
    mm::Vec3 pos;
    if (acc.isValidTransform()) {
        pos = acc.getWorldTransform().position;
    } else {
        pos = GfObjUtil::getObjSetup(handle)->m_initialPos;
    }
    return isInside(pos);
}

bool GfGameInsideBattleLock::isInside(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    return get()->m_infos[handle];
}

bool GfGameInsideBattleLock::isInside(const mm::Vec3& pos) {
    bool inside = false;
    auto f = [&inside, pos](const gmk::AGmkBase& gmk) {
        const gmk::GmkBattleLock& lock = static_cast<const gmk::GmkBattleLock&>(gmk);
        if (lock.m_collision.m_coliObject != nullptr) {
            inside = lock.isInsideShape(pos, 0.0f);
        }
    };
    if (!gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBattleLock::TYPE, f)) {
        return false;
    }
    return inside;
}

GfGameInsideBattleLock::~GfGameInsideBattleLock() {}

template <typename T>
void GfGameInsideBattleLock::updateInfoByGmk() {
    auto f = [this](const gmk::AGmkBase& gmk) {
        const T& enemy = static_cast<const T&>(gmk);
        if (!enemy.isValid()) {
            return;
        }
        unsigned int num = enemy.m_insts.m_popInfo.getGobInstNum();
        for (unsigned int i = 0; i < num; ++i) {
            GF_OBJ_HANDLE* handle = enemy.m_insts.getGobInst(i);
            m_infos[handle] = isInsideBattleLock(handle);
        }
    };
    gmk::GmkManager::get()->traverseGmkInst(T::TYPE, f);
}

}  // namespace gf
