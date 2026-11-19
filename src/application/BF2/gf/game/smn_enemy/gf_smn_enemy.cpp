#include "classes/gf/GfRelSmnEnemy.h"
#include "classes/gf/GfSmnEnemyManager.h"
#include "classes/gf/GfRelSmnEnemy.h"
#include "classes/gf/GfSmnEnemyManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkEnemyInsts.h"
#include "classes/gmk/GmkEnemyInsts.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/SDataEnemy.h"
#include "ml/MTRand.h"
#include "plugin/Bdat.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"
#include "fw/Transform.h"
#include "gf/GfGameUtil.h"
#include <math.h>

#include <algorithm>

namespace gf {

GfRelSmnEnemy::~GfRelSmnEnemy() {
    dispose();
    GfObjManager::removeListener(this);
}

unsigned int GfRelSmnEnemy::getEnemyNum() const {
    if (!isValid()) {
        return 0;
    }
    return m_enemies.size();
}

GF_OBJ_HANDLE* GfRelSmnEnemy::getEnemy(unsigned int index) const {
    if (!isValid()) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return m_enemies[index];
}

void GfRelSmnEnemy::disposeEnemies(bool fade) {
    disposeWaitEnemies();
    if (m_enemies.size() != 0) {
        for (GF_OBJ_HANDLE* enemy : m_enemies) {
            if (enemy != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (fade) {
                    SCOM_DESTROY_GAME_OBJ::create(enemy, 0.5f, 0);
                } else {
                    GfObjUtil::destroy(enemy);
                }
            }
        }
        m_enemies.destroy();
    }
}

void GfRelSmnEnemy::update(float dt) {
    if (!isValid()) {
        return;
    }
    GfObjAcc acc(m_info.handle);
    if (!acc.isDestroy() && !acc.testFlag(0x11) && acc.getObj() != nullptr) {
        updatePopEnemy();
        updateDepopEnemy();
        validatePopPos();
    } else {
        disposeWaitEnemies();
    }
}

void GfRelSmnEnemy::disposeWaitEnemies() {
    if (m_waitEnemies.size() != 0) {
        for (std::pair<PopInfo*, GF_OBJ_HANDLE*>& wait : m_waitEnemies) {
            if (wait.second != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfObjUtil::destroy(wait.second);
            }
        }
        m_waitEnemies.destroy();
    }
}

namespace {
// an enemy's setup when its object's info holds one of its own kind (5), as gf_game_obj's _gfgob::getEnemySetup
// (inline; the name is not the original's)
inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
}  // namespace

void GfRelSmnEnemy::updateDepopEnemy() {
    if (m_enemies.size() == 0) {
        return;
    }
    for (GF_OBJ_HANDLE*& handle : m_enemies) {
        GfObjSetupEnemy* setup = getEnemySetup(handle);
        if (m_depopCond.m_horizontalSq > 0.0f && m_depopCond.m_verticalSq > 0.0f &&
            !m_depopCond.isMatch(setup->m_initialPos)) {
            m_enemies.erase(&handle);
            SCOM_DESTROY_GAME_OBJ::create(handle, 0.5f, 0);
            return;
        }
    }
}

void GfRelSmnEnemy::validatePopPos() {
    if (m_enemies.size() != 0) {
        for (GF_OBJ_HANDLE* enemy : m_enemies) {
            if (!GfGameObj::isValidGameObj(enemy, true, nullptr)) {
                return;
            }
            if (GfGameUtil::isGameObjWait(enemy)) {
                return;
            }
        }
    }
    if (m_waitEnemies.size() == 0) {
        return;
    }
    size_t index = static_cast<size_t>(m_waitEnemies.size() * ml::mtRandf2());
    std::pair<PopInfo*, GF_OBJ_HANDLE*>& wait = m_waitEnemies.begin()[index];
    bool zero = wait.first->pos.isZero();
    GF_OBJ_HANDLE* handle = wait.second;
    GfObjAcc acc(handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    GfComBehaviorEnemy* behavior = obj->getComponent<GfComBehaviorEnemy>(6);
    if (behavior == nullptr) {
        return;
    }
    GfObjSetupEnemy* setup = getEnemySetup(handle);
    if (behavior->validatePopPos(setup->m_initialPos, setup->pad_30, false, zero)) {
        m_waitEnemies.erase(&wait);
        m_enemies.push_back(handle);
        behavior->onPopped();
        GfGameUtil::setGameObjWait(handle, false);
        return;
    }
    mm::Vec3 pos;
    if (!getPopPos(pos, *wait.first)) {
        return;
    }
    fw::Transform transform;
    transform.position = pos;
    mm::Vec3 half = mm::Vec3(setup->pad_30) * 0.5f;
    float sx = ::sinf(half.x);
    float cx = ::cosf(half.x);
    float sy = ::sinf(half.y);
    float cy = ::cosf(half.y);
    float sz = ::sinf(half.z);
    float cz = ::cosf(half.z);
    transform.rotation.x = sx * cy * cz - cx * sy * sz;
    transform.rotation.y = cx * sy * cz + sx * cy * sz;
    transform.rotation.z = cx * cy * sz - sx * sy * cz;
    transform.rotation.w = cx * cy * cz + sx * sy * sz;
    setup->setInitialTransform(transform);
}

void GfRelSmnEnemy::removeEnemy(GF_OBJ_HANDLE* handle) {
    if (m_waitEnemies.size() != 0) {
        for (std::pair<PopInfo*, GF_OBJ_HANDLE*>& wait : m_waitEnemies) {
            if (wait.second == handle) {
                m_waitEnemies.erase(&wait);
                return;
            }
        }
    }
    if (m_enemies.size() != 0) {
        GF_OBJ_HANDLE** it = std::find(m_enemies.begin(), m_enemies.end(), handle);
        if (it != m_enemies.end()) {
            m_enemies.erase(it);
        }
    }
}

void GfRelSmnEnemy::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int) {
    if (evt != OBJEVT(3)) {
        return;
    }
    removeEnemy(handle);
    if (!isValid()) {
        return;
    }
    bool popped = true;
    for (PopInfo& info : m_popInfos) {
        EnemyInfo enemy = info.enemy;
        if (enemy.isValid()) {
            popped &= info.popped != 0;
            if (!info.popped) {
                break;
            }
        }
    }
    if (popped && m_waitEnemies.size() == 0 && m_enemies.size() == 0) {
        dispose();
    }
}

GfSmnEnemyManager::GfSmnEnemyManager() {
    m_relSmnEnemies.setAllocator(getAllocator(ALLOCATOR(0)));
    m_relSmnEnemies.reserve(40);
}

GfSmnEnemyManager::~GfSmnEnemyManager() {
    clearSmnEnemies();
    get()->m_relSmnEnemies.destroy();
}

void GfSmnEnemyManager::clearSmnEnemies() {
    if (get() == nullptr) {
        return;
    }
    if (get()->m_relSmnEnemies.size() != 0) {
        for (GfRelSmnEnemy* rel : get()->m_relSmnEnemies) {
            delete rel;
        }
        get()->m_relSmnEnemies.clear();
    }
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        GF_OBJ_HANDLE* handle = *it;
        gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
        if (gmk != nullptr && gmk->getGmkType() == gmk::GmkEnemy::TYPE &&
            static_cast<gmk::GmkEnemy*>(gmk)->m_insts.m_bdatInfo.m_smnGroups != 0) {
            GfObjUtil::destroy(handle);
        }
    }
}

void GfSmnEnemyManager::create() {
    if (get() != nullptr) {
        delete get();
    }
#line 743
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSmnEnemyManager();
}

void GfSmnEnemyManager::dispose() {
    if (get() != nullptr) {
        delete get();
    }
}

void GfSmnEnemyManager::update(float dt) {
    if (get() == nullptr) {
        return;
    }
    for (GfRelSmnEnemy** it = get()->m_relSmnEnemies.begin(); it != get()->m_relSmnEnemies.end(); ++it) {
        GfRelSmnEnemy* rel = *it;
        rel->update(dt);
        if (!rel->isValid()) {
            delete rel;
            it = get()->m_relSmnEnemies.erase(it);
            --it;
        }
    }
}

bool GfSmnEnemyManager::execAbsSummon(const AbsSmnInfo& info) {
    GfObj* obj = GfObjUtil::getObj(info.handle);
    if (obj == nullptr) {
        return false;
    }
    GfComTransform* transform = obj->getComponent<GfComTransform>(0);
    if (transform == nullptr) {
        return false;
    }
    const mm::Vec3& pos = transform->getPosition();
    float radiusSq = info.radius * info.radius;
    for (GF_OBJ_HANDLE* handle : *GfGameObj::getList(5)) {
        if (info.group != 0) {
            DataParamAcc param(handle);
            if (!param.isValid()) {
                continue;
            }
            const SDataEnemy* data = param.getSDataEnemy();
            if (data->m_genus != info.group) {
                continue;
            }
        }
        GfObjAcc acc(handle);
        GfObj* enemy = acc.getObj();
        if (enemy == nullptr || GfObjUtil::testInvincible(handle)) {
            continue;
        }
        GfComBehaviorEnemy* behavior = enemy->getComponent<GfComBehaviorEnemy>(6);
        if (behavior == nullptr) {
            continue;
        }
        const mm::Vec3& enemyPos = acc.getWorldTransformNoSync().position;
        float dx = pos.x - enemyPos.x;
        float dy = pos.y - enemyPos.y;
        float dz = pos.z - enemyPos.z;
        if (radiusSq < dx * dx + dy * dy + dz * dz) {
            continue;
        }
        behavior->reqChangeBattle();
    }
    auto forcePop = [&, info](const gmk::AGmkBase& base) {
        const gmk::GmkEnemy& gmk = static_cast<const gmk::GmkEnemy&>(base);
        if (!gmk.isValid()) {
            return;
        }
        if ((gmk.m_insts.m_bdatInfo.m_smnGroups & (1 << info.flagBit)) == 0) {
            return;
        }
        const mm::Vec3& gmkPos = *gmk.m_pos;
        float dx = pos.x - gmkPos.x;
        float dy = pos.y - gmkPos.y;
        float dz = pos.z - gmkPos.z;
        if (radiusSq < dx * dx + dy * dy + dz * dz) {
            return;
        }
        if (!gmk.m_insts.m_bdatInfo.isPopCondMatchedOfSmn()) {
            return;
        }
        gmk::ForcePopEnemyInfo popInfo;
        popInfo.pad_0 = info.group;
        gmk.m_insts.reqForcePopGobInst(popInfo);
    };
    return gmk::GmkManager::sys()->traverseGmkInst(gmk::GmkEnemy::TYPE, forcePop);
}

bool GfSmnEnemyManager::execRelSummon(const RelSmnInfo& info) {
    if (get()->m_relSmnEnemies.capacity() > get()->m_relSmnEnemies.size()) {
        GfRelSmnEnemy::CreateInfo createInfo;
        createInfo.handle = info.handle;
        createInfo.id = info.id;
#line 955
        GfRelSmnEnemy* rel = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfRelSmnEnemy();
        rel->create(createInfo);
        get()->m_relSmnEnemies.push_back(rel);
        return true;
    }
    return false;
}

}  // namespace gf

// the pop vectors' growth (their users are not written yet)
template void mm::mtl::Vector<std::pair<gf::GfRelSmnEnemy::PopInfo*, gf::GF_OBJ_HANDLE*> >::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GF_OBJ_HANDLE*>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfRelSmnEnemy::PopInfo>::push_back(const gf::GfRelSmnEnemy::PopInfo&);
