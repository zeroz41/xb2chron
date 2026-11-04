#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/GmkCollection.h"
#include "classes/gf/LocatorGimmickEnemyWave.h"
#include "classes/gf/LocatorCollection.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/GmkNpcManager.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/LocatorTalk_NpcID.h"
#include "classes/gf/LocatorEventPreorder.h"
#include "classes/gf/LocatorPreciousPreorder.h"
#include "classes/gf/GfFieldLocator.h"
#include "classes/gf/LocatorBat_EnemySpeciesID.h"
#include "classes/gf/LocatorReach.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gmk/GmkLandmark.h"
#include "classes/gf/AFieldLocator.h"
#include "classes/gf/LocatorTbox.h"
#include "classes/gf/LocatorPreciousPreorder.h"
#include "classes/gf/LocatorEventPreorder.h"
#include "classes/gf/LocatorReach.h"
#include "classes/gf/LocatorPrecious.h"
#include "classes/gf/LocatorTalk_NpcID.h"
#include "classes/gf/LocatorBat_EnemySpeciesID.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/GmkNpcManager.h"
#include "classes/gmk/GmkSet.h"
#include "gf/GfObjAcc.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfGameUtil.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkEnemyWave.h"
#include "classes/gf/GfGameManager.h"
#include "fw/Transform.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFieldLocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/LocatorGimmick.h"
#include "classes/gmk/GmkSalvage.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkJump.h"
#include "classes/gmk/GmkWarp.h"
#include "classes/gmk/GmkDoor.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/gmk/GmkCamp.h"
#include "classes/gf/GfGmkLocator.h"
#include "classes/gf/GfFieldNpcLocator.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gf/DataObjEnemy.h"
#include "classes/gf/LocatorTalk_DummyGroup.h"
#include "classes/gf/LocatorBat_EnemyGroupID.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/LocatorBat_EnemyID.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "gf/GfObjInfo.h"
#include "mm/mtl/RTTI.h"

namespace gf {

void LocatorTbox::update() {
    if (m_tboxId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk = gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkTbox::TYPE, m_tboxId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkTbox* tbox = static_cast<const gmk::GmkTbox*>(m_acc.m_gmk);
        if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist()) {
            return;
        }
        if (tbox->getProgress() == 1) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorPreciousPreorder::update() {
    if (m_preciousId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk =
            gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkPrecious::TYPE, m_preciousId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkPrecious* precious = static_cast<const gmk::GmkPrecious*>(m_acc.m_gmk);
        if (precious->isObtained()) {
            return;
        }
        if (!precious->getBdatInfo()->isPopCondMatched()) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorEventPreorder::update() {
    if (m_eventId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk = gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkEvent::TYPE, m_eventId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkEvent* event = static_cast<const gmk::GmkEvent*>(m_acc.m_gmk);
        if (!event->m_isCondMatched) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorPrecious::update() {
    if (m_preciousId == 0) {
        return;
    }
    m_posList.clear();
    for (gmk::GmkAcc* it = m_accs.begin(); it != m_accs.end(); ++it) {
        if (!it->isValid()) {
            create(m_questId, m_preciousId);
            return;
        }
        const gmk::GmkPrecious* precious = static_cast<const gmk::GmkPrecious*>(it->m_gmk);
        if (precious->isObtained()) {
            continue;
        }
        if (!precious->getBdatInfo()->isPopCondMatched()) {
            continue;
        }
        m_posList.push_back(*it->m_gmk->m_pos);
    }
}
void LocatorPrecious::onTraverse(const gmk::AGmkBase& gmk) {
    if (!gmk.isValid()) {
        return;
    }
    const gmk::GmkPrecious& precious = static_cast<const gmk::GmkPrecious&>(gmk);
    if (precious.getBdatInfo()->m_itmId != m_preciousId) {
        return;
    }
    if (precious.isObtained()) {
        return;
    }
    gmk::GmkAcc::CreateInfo info;
    info.validate(gmk);
    m_accs.push_back(gmk::GmkAcc(info));
    m_posList.push_back(*gmk.m_pos);
}
void LocatorBat_EnemyID::update() {
    if (m_enemyId == 0 || m_gmkSetId <= 0) {
        return;
    }
    m_type0Accs.clear();
    m_type1Accs.clear();
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr) {
        return;
    }
    const gmk::IGmkList* list = set->getGmkList(gmk::GmkEnemy::TYPE);
    if (list != nullptr) {
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i != num; i++) {
            const gmk::GmkEnemy* enemy = static_cast<const gmk::GmkEnemy*>(list->getInst(i));
            if (enemy->isValid() && enemy->m_insts.m_popInfo.hasEneID(m_enemyId, true) && enemy->isPopCondMatched()) {
                gmk::GmkAcc::CreateInfo info;
                if (enemy != nullptr) {
                    info.validate(*enemy);
                }
                gmk::GmkAcc acc(info);
                m_type0Accs.push_back(acc);
            }
        }
    }
    list = set->getGmkList(gmk::GmkRoutedEnemy::TYPE);
    if (list != nullptr) {
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i != num; i++) {
            const gmk::GmkRoutedEnemy* enemy = static_cast<const gmk::GmkRoutedEnemy*>(list->getInst(i));
            if (enemy->isValid() && enemy->m_insts.m_popInfo.hasEneID(m_enemyId, true) && enemy->isPopCondMatched()) {
                gmk::GmkAcc::CreateInfo info;
                if (enemy != nullptr) {
                    info.validate(*enemy);
                }
                gmk::GmkAcc acc(info);
                m_type1Accs.push_back(acc);
            }
        }
    }
    m_posList.clear();
    unsigned long num = m_type0Accs.size();
    for (unsigned long i = 0; i < num; i++) {
        const gmk::GmkAcc& acc = m_type0Accs[i];
        if (!acc.isValid()) {
            continue;
        }
        const gmk::GmkEnemy* enemy = static_cast<const gmk::GmkEnemy*>(acc.m_gmk);
        unsigned int gobNum = enemy->getGobInstNum();
        if (gobNum != 0) {
            unsigned int j = 0;
            bool found = false;
            for (; j < gobNum; j++) {
                GF_OBJ_HANDLE* handle = enemy->getGobInst(j);
                GfObjAcc objAcc(handle);
                if (objAcc.isValidTransform() && !GfGameUtil::isGameObjWait(handle) &&
                    (!GfGameManager::isGameTypeIra() || m_enemyId == 0 || m_enemyId == objAcc.getEnArrangeId())) {
                    m_posList.push_back(objAcc.getWorldTransformNoSync().position);
                    found = true;
                }
            }
            if (found) {
                continue;
            }
        }
        if (enemy->getPopWait() > 0.0f || enemy->m_insts.isQuestDead()) {
            continue;
        }
        m_posList.push_back(*enemy->m_pos);
    }
    num = m_type1Accs.size();
    for (unsigned long i = 0; i < num; i++) {
        const gmk::GmkAcc& acc = m_type1Accs[i];
        if (!acc.isValid()) {
            continue;
        }
        const gmk::GmkRoutedEnemy* enemy = static_cast<const gmk::GmkRoutedEnemy*>(acc.m_gmk);
        unsigned int gobNum = enemy->getGobInstNum();
        if (gobNum != 0) {
            bool found = false;
            for (unsigned int j = 0; j < gobNum; j++) {
                GF_OBJ_HANDLE* handle = enemy->getGobInst(j);
                GfObjAcc objAcc(handle);
                if (objAcc.isValidTransform() && !GfGameUtil::isGameObjWait(handle) &&
                    (!GfGameManager::isGameTypeIra() || m_enemyId == 0 || m_enemyId == objAcc.getEnArrangeId())) {
                    m_posList.push_back(objAcc.getWorldTransformNoSync().position);
                    found = true;
                }
            }
            if (found) {
                continue;
            }
        }
        if (enemy->getPopWait() > 0.0f || enemy->m_insts.isQuestDead()) {
            continue;
        }
        mm::Vec3 pos(0.0f, 0.0f, 0.0f);
        if (enemy->getRoutePointPos(pos, 0)) {
            m_posList.push_back(pos);
        }
    }
}
void LocatorBat_EnemyGroupID::create(QuestID questId, unsigned short groupId) {
    dispose();
    m_questId = questId;
    m_groupId = groupId;
    unsigned char* groupFp = GfDataBdat::getFP(0xd9);
    // CHR_EnArrange (0x8B): each enemy's zone, 0 when it has none
    unsigned char* enemyFp = GfDataBdat::getFP(0x8b);
    mm::mtl::FixStr<16> name;
    for (int i = 1; i < 9; i++) {
        name.format("EnemyID%d", i);
        unsigned int enemyId = Bdat::getValCheckU16(groupFp, name.m_str, groupId);
        if (enemyId != 0) {
            m_enemyIds.push_back(enemyId);
            unsigned char zoneId = Bdat::getValCheckU8(enemyFp, "ZoneID", enemyId);
            if (zoneId == 0) {
                zoneId = GfGameManager::getMapID();
            }
            m_zoneIds.push_back(zoneId);
        }
    }
    if (m_enemyIds.size() == 0) {
        dispose();
        return;
    }
    unsigned char zoneId = Bdat::getValCheckU8(enemyFp, "ZoneID", m_enemyIds[0]);
    if (zoneId == 0) {
        dispose();
        return;
    }
    m_mapBdatId = zoneId;
    m_gmkSetId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    int iconId = gmk::getBdatIdOfQuestTargetIcon(
        GfQuestTarget::getIconTypeBattle(2, groupId, questId, reinterpret_cast<GF_OBJ_HANDLE*>(-1), true));
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
}
// an enemy's setup when its info holds one of its own kind (5), as DataParamAcc.cpp's _gfdac::getEnemySetup (inline,
// the name is not the original's)
static inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
// adds the object's world position (inline; the name is not the original's)
static inline void addObjPos(LocatorBat_EnemyGroupID* locator, GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    locator->m_posList.push_back(acc.getWorldTransformNoSync().position);
}
// The two passes (GmkEnemy, then GmkRoutedEnemy) share one body; the helper's name is not the original's.
template <class T>
static void addEnemyPos(LocatorBat_EnemyGroupID* locator, const gmk::GmkSet* set) {
    if (!set->isValid()) {
        return;
    }
    const gmk::IGmkList* list = set->getGmkList(T::TYPE);
    if (list == nullptr || !list->isValid()) {
        return;
    }
    unsigned int num = list->getInstNum();
    for (unsigned int i = 0; i < num; i++) {
        if (locator->m_posList.size() == locator->m_posList.capacity()) {
            return;
        }
        const gmk::AGmkBase* gmk = list->getInst(i);
        const T* enemy = static_cast<const T*>(gmk);
        if (gmk->isValid() && enemy->isPopCondMatched()) {
            unsigned int gobNum = enemy->getGobInstNum();
            if (gobNum != 0) {
                unsigned int j = 0;
                bool found = false;
                for (; j < gobNum; j++) {
                    GF_OBJ_HANDLE* handle = enemy->getGobInst(j);
                    GfObjAcc acc(handle);
                    if (acc.isValidTransform() && !GfGameUtil::isGameObjWait(handle)) {
                        if (GfObjSetupEnemy* setup = getEnemySetup(handle)) {
                            bool hit = false;
                            for (unsigned int id : locator->m_enemyIds) {
                                if (setup->m_enArrangeId == id) {
                                    hit = true;
                                    break;
                                }
                            }
                            if (hit) {
                                addObjPos(locator, handle);
                            }
                        }
                        found = true;
                    }
                }
                if (found) {
                    continue;
                }
            }
        }
        for (unsigned int id : locator->m_enemyIds) {
            if (enemy->getPopWait() > 0.0f || enemy->m_insts.isQuestDead() ||
                !enemy->m_insts.m_popInfo.hasEneID(id, true)) {
                continue;
            }
            mm::Vec3 pos;
            switch (gmk->getGmkType()) {
            case gmk::GmkEnemy::TYPE:
                pos = *gmk->m_pos;
                break;
            case gmk::GmkRoutedEnemy::TYPE:
                if (!static_cast<const gmk::GmkRoute*>(gmk)->getRoutePointPos(pos, 0)) {
                    continue;
                }
                break;
            default:
                continue;
            }
            locator->m_posList.push_back(pos);
            break;
        }
    }
}
void LocatorBat_EnemyGroupID::update() {
    if (m_groupId == 0 || m_gmkSetId <= 0) {
        return;
    }
    m_posList.clear();
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr) {
        return;
    }
    addEnemyPos<gmk::GmkEnemy>(this, set);
    addEnemyPos<gmk::GmkRoutedEnemy>(this, set);
}
LocatorBat_EnemySpeciesID::LocatorBat_EnemySpeciesID(QuestID questId, unsigned char speciesId)
    : m_speciesId(0), m_gmkSetId(-1) {
    if (!questId.empty() && speciesId != 0) {
        create(questId, speciesId);
    }
}
void LocatorTalk_DummyGroup::create(QuestID questId, unsigned short mapId, unsigned short npcId, unsigned short groupId) {
    dispose();
    m_mapBdatId = mapId;
    m_questId = questId;
    m_npcId = npcId;
    m_groupId = groupId;
    m_gmkSetId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(mapId);
    if (npcId != 0) {
        m_npcIds.push_back(npcId);
    }
    unsigned char* fp = GfDataBdat::getFP(0xd0);
    mm::mtl::FixStr<16> name;
    for (int i = 1; i < 10; i++) {
        name.format("NpcID%d", i);
        unsigned short id = Bdat::getValCheckU16(fp, name.m_str, groupId);
        if (id != 0) {
            m_npcIds.push_back(id);
        }
    }
    if (m_npcIds.size() == 0) {
        dispose();
    }
}
void LocatorTalk_DummyGroup::update() {
    if (m_gmkSetId <= 0 || m_npcIds.size() == 0) {
        return;
    }
    m_posList.clear();
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr) {
        return;
    }
    const gmk::GmkNpcManager& npcManager = set->m_npcManager;
    int mapId = getMapBdatId();
    unsigned long num = m_npcIds.size();
    if (num == 0) {
        return;
    }
    const unsigned short* it = m_npcIds.begin();
    const unsigned short* end = it + num;
    do {
        unsigned short npcId = *it;
        unsigned int iconType = GfQuestTarget::getIconTypeTalk(npcId, m_questId, mapId, true);
        if (iconType == 0) {
            continue;
        }
        m_iconBdatId = gmk::getBdatIdOfQuestTargetIcon(iconType);
        const gmk::GmkNpcIdInfo* info = npcManager.getNpcIdInfoByNpcId(npcId);
        if (info->m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjAcc acc(info->m_handle);
            if (acc.isValidTransform()) {
                m_posList.push_back(acc.getWorldTransformNoSync().position);
            }
            continue;
        }
        const gmk::AGmkNpc* npc = info->m_gmk;
        if (npc == nullptr) {
            continue;
        }
        if (!npc->isPopCondMatched()) {
            continue;
        }
        mm::Vec3 pos;
        mm::Vec3 rot;
        if (npc->findPopPosRot(pos, rot)) {
            m_posList.push_back(pos);
        }
    } while (++it != end);
}
LocatorReach::LocatorReach(QuestID questId, int row) : m_category(0), m_placeId(0), m_posNum(0), m_pos(mm::Vec3::zero) {
    if (!questId.empty() && row > 0) {
        create(questId, row);
    }
}
LocatorTbox::LocatorTbox(QuestID questId, unsigned short tboxId) : m_tboxId(0), m_posNum(0) {
    if (!questId.empty() && tboxId != 0) {
        create(questId, tboxId);
    }
}

LocatorTalk_NpcID::LocatorTalk_NpcID(QuestID questId, unsigned char* bdat, int row)
    : m_gmkSetId(0), m_npcId(0), m_posNum(0), m_pos(mm::Vec3::zero) {
    unsigned short mapId = static_cast<unsigned short>(Bdat::getValCheck(bdat, "MapID", row, 2));
    unsigned short npcId = static_cast<unsigned short>(Bdat::getValCheck(bdat, "NpcID", row, 2));
    if (mapId && npcId) {
        create(questId, mapId, npcId);
    }
}
// The two passes (GmkEnemy, then GmkRoutedEnemy) share one body; the helper's name is not the original's.
template <class T>
static void addEnemyPos(LocatorBat_EnemySpeciesID* locator, const gmk::GmkSet* set) {
    if (!set->isValid()) {
        return;
    }
    const gmk::IGmkList* list = set->getGmkList(T::TYPE);
    if (list == nullptr || !list->isValid()) {
        return;
    }
    unsigned int num = list->getInstNum();
    for (unsigned int i = 0; i < num; i++) {
        if (locator->m_posList.size() == locator->m_posList.capacity()) {
            return;
        }
        const gmk::AGmkBase* gmk = list->getInst(i);
        const T* enemy = static_cast<const T*>(gmk);
        if (gmk->isValid() && enemy->isPopCondMatched()) {
            unsigned int gobNum = enemy->getGobInstNum();
            if (gobNum != 0) {
                bool found = false;
                for (unsigned int j = 0; j < gobNum; j++) {
                    GF_OBJ_HANDLE* handle = enemy->getGobInst(j);
                    GfObjAcc acc(handle);
                    if (acc.isValidTransform() && !GfGameUtil::isGameObjWait(handle)) {
                        locator->fn_7100272430(handle);
                        found = true;
                    }
                }
                if (found) {
                    continue;
                }
            }
        }
        if (enemy->getPopWait() > 0.0f || enemy->m_insts.isQuestDead() ||
            enemy->hasTypeGenus(locator->m_speciesId, true)) {
            continue;
        }
        mm::Vec3 pos;
        switch (gmk->getGmkType()) {
        case gmk::GmkEnemy::TYPE:
            pos = *gmk->m_pos;
            break;
        case gmk::GmkRoutedEnemy::TYPE:
            if (!static_cast<const gmk::GmkRoute*>(gmk)->getRoutePointPos(pos, 0)) {
                continue;
            }
            break;
        default:
            continue;
        }
        locator->m_posList.push_back(pos);
    }
}
void LocatorBat_EnemySpeciesID::update() {
    if (m_speciesId == 0 || m_gmkSetId <= 0) {
        return;
    }
    m_posList.clear();
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr) {
        return;
    }
    addEnemyPos<gmk::GmkEnemy>(this, set);
    addEnemyPos<gmk::GmkRoutedEnemy>(this, set);
}
void LocatorTalk_NpcID::update() {
    if (m_gmkSetId <= 0 || m_npcId == 0) {
        return;
    }
    m_posNum = 0;
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr) {
        return;
    }
    const gmk::GmkNpcIdInfo* info = set->m_npcManager.getNpcIdInfoByNpcId(m_npcId);
    GfObjAcc acc(info->m_handle);
    if (acc.isValidTransform()) {
        m_pos = acc.getWorldTransformNoSync().position;
        m_posNum = 1;
        return;
    }
    const gmk::AGmkNpc* npc = info->m_gmk;
    if (npc == nullptr) {
        return;
    }
    if (!npc->isPopCondMatched()) {
        return;
    }
    mm::Vec3 rot;
    if (npc->findPopPosRot(m_pos, rot)) {
        m_posNum = 1;
    }
}
void LocatorReach::update() {
    if (!isValid()) {
        return;
    }
    m_posNum = 0;
    if (m_category == 1 || m_category == 2) {
        const gmk::GmkLandmark* landmark = static_cast<const gmk::GmkLandmark*>(
            gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkLandmark::TYPE, m_placeId));
        if (landmark != nullptr && landmark->getBdatInfo()->isCondMatched()) {
            m_pos = *landmark->m_pos;
            m_posNum = 1;
        }
    } else if (m_category == 3) {
        const gmk::GmkEvent* event = static_cast<const gmk::GmkEvent*>(
            gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkEvent::TYPE, m_placeId));
        if (event != nullptr && event->m_isCondMatched) {
            m_pos = *event->m_pos;
            m_posNum = 1;
        }
    }
}
// 1.0.0's symbols name it (0x71002DDBCC, same stores and columns, called by createByQuest); the symbols still spell
// it LocatorGimmick::create
void LocatorGimmick::create(QuestID questId, unsigned short row) {
    dispose();
    m_questId = questId;
    unsigned char* fp = GfDataBdat::getFP(0xd1);
    m_mapBdatId = Bdat::getValCheckU16(fp, "MapID", row);
    unsigned short doorId = Bdat::getValCheckU16(fp, "DoorGimmickID", row);
    unsigned short elevatorId = Bdat::getValCheckU16(fp, "ElevatorGimmickID", row);
    unsigned short jumpId = Bdat::getValCheckU16(fp, "JumpGimmickID", row);
    unsigned short mapGimmickId = Bdat::getValCheckU16(fp, "MapGimmickID", row);
    unsigned short warpId = Bdat::getValCheckU16(fp, "WarpGimmickID", row);
    unsigned short salvageId = Bdat::getValCheckU16(fp, "SalvagePointID", row);
    unsigned short tboxId = Bdat::getValCheckU16(fp, "TboxPopID", row);
    unsigned short enemyWaveId = Bdat::getValCheckU16(fp, "EnemyWaveID", row);
    unsigned short campId = Bdat::getValCheckU16(fp, "CampPopID", row);
    unsigned short collectionId = Bdat::getValCheckU16(fp, "CollectionPopID", row);
    if (doorId != 0) {
        m_gmkType = gmk::GmkDoor::TYPE;
        m_gmkId = doorId;
    } else if (elevatorId != 0) {
        m_gmkType = gmk::GmkElevator::TYPE;
        m_gmkId = elevatorId;
    } else if (jumpId != 0) {
        m_gmkType = gmk::GmkJump::TYPE;
        m_gmkId = jumpId;
    } else if (mapGimmickId != 0) {
        m_gmkType = gmk::GmkMapGimmick::TYPE;
        m_gmkId = mapGimmickId;
    } else if (warpId != 0) {
        m_gmkType = gmk::GmkWarp::TYPE;
        m_gmkId = warpId;
    } else if (salvageId != 0) {
        m_gmkType = gmk::GmkSalvage::TYPE;
        m_gmkId = salvageId;
    } else if (tboxId != 0) {
        m_gmkType = gmk::GmkTbox::TYPE;
        m_gmkId = tboxId;
    } else if (enemyWaveId != 0) {
        m_gmkType = 0x3a;
        m_gmkId = enemyWaveId;
    } else if (campId != 0) {
        m_gmkType = gmk::GmkCamp::TYPE;
        m_gmkId = campId;
    } else if (collectionId != 0) {
        m_gmkType = gmk::GmkCollection::TYPE;
        m_gmkId = collectionId;
    }
}
void LocatorGimmick::update() {
    m_posNum = 0;
    if (m_gmkType == 0x41 || m_gmkId == 0) {
        return;
    }
    int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestInfo::isScenarioQuest(m_questId) ? 1 : 3);
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    const gmk::AGmkBase* gmk =
        gmk::GmkManager::sys()->findFirstGmkInstByBdatId(static_cast<gmk::GmkType>(m_gmkType), m_gmkId);
    if (gmk == nullptr || !gmk->isValid()) {
        return;
    }
    switch (m_gmkType) {
    case gmk::GmkTbox::TYPE: {
        const gmk::GmkTbox* tbox = static_cast<const gmk::GmkTbox*>(gmk);
        if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist() || tbox->getProgress() == 1) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    }
    case gmk::GmkCollection::TYPE:
        if (!static_cast<const gmk::GmkCollection*>(gmk)->getBdatInfo()->isPopCondMatchedExceptDist()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    case gmk::GmkSalvage::TYPE:
        if (!static_cast<const gmk::GmkSalvage*>(gmk)->getBdatInfo()->isCondMatched()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    case gmk::GmkWarp::TYPE: {
        const gmk::GmkWarp* warp = static_cast<const gmk::GmkWarp*>(gmk);
        if (!warp->getBdatInfo()->isPopCondCommonMatched()) {
            return;
        }
        const mm::Vec3NA& pos = warp->getPoints()->m_pos;
        m_pos.x = pos.x;
        m_pos.y = pos.y;
        m_pos.z = pos.z;
        break;
    }
    case gmk::GmkDoor::TYPE:
        if (!static_cast<const gmk::GmkDoor*>(gmk)->getBdatInfo()->isPopCondMatched()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    case gmk::GmkElevator::TYPE:
        if (!static_cast<const gmk::GmkElevator*>(gmk)->getPosForCompass(m_pos)) {
            return;
        }
        break;
    case gmk::GmkMapGimmick::TYPE: {
        const gmk::GmkMapGimmick* mapGimmick = static_cast<const gmk::GmkMapGimmick*>(gmk);
        if (!mapGimmick->isNotSolved() || !mapGimmick->getBdatInfo()->isPopCondMatched()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    }
    case gmk::GmkJump::TYPE: {
        const gmk::GmkJump* jump = static_cast<const gmk::GmkJump*>(gmk);
        if (!jump->getBdatInfo()->isPopCondMatched()) {
            return;
        }
        const mm::Vec3NA& pos = jump->getData()->m_startPos;
        m_pos.x = pos.x;
        m_pos.y = pos.y;
        m_pos.z = pos.z;
        break;
    }
    case 0x3a:
        if (!static_cast<const gmk::GmkEnemyWave*>(gmk)->isPopCondMatched()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    case gmk::GmkCamp::TYPE:
        if (!static_cast<const gmk::GmkCamp*>(gmk)->getBdatInfo()->isCondMatched()) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    default:
        m_pos = mm::Vec3::zero;
        break;
    }
    m_posNum = 1;
}
LocatorGimmickEnemyWave::LocatorGimmickEnemyWave(QuestID questId, unsigned short row) {
    if (!questId.empty() && row != 0) {
        create(questId, row);
    }
}
void LocatorGimmickEnemyWave::update() {
    if (!isValid()) {
        return;
    }
    int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestInfo::isScenarioQuest(m_questId) ? 1 : 3);
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    m_posList.clear();
    gmk::GmkEnemyWave* gmk = static_cast<gmk::GmkEnemyWave*>(
        gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkType(0x3a), m_enemyWaveId));
    if (gmk == nullptr || !gmk->isValid()) {
        return;
    }
    if (!gmk->isValid() || !gmk->isPopCondMatched()) {
        return;
    }
    unsigned int num = gmk->getBindedEnemyNum();
    for (unsigned int i = 0; i != num; i++) {
        const gmk::GmkEnemy* enemy = gmk->getBindedEnemy(i);
        if (!enemy->isValid()) {
            continue;
        }
        unsigned int gobNum = enemy->getGobInstNum();
        for (unsigned int j = 0; j != gobNum; j++) {
            GF_OBJ_HANDLE* handle = enemy->getGobInst(j);
            GfObjAcc acc(handle);
            if (acc.isValidTransform() && !GfGameUtil::isGameObjWait(handle)) {
                m_posList.push_back(acc.getWorldTransformNoSync().position);
            }
        }
    }
    if (m_posList.size() == 0) {
        m_posList.push_back(*gmk->m_pos);
    }
}
void LocatorCollection::create(QuestID questId, unsigned short collectionId) {
    dispose();
    m_questId = questId;
    m_collectionId = collectionId;
    unsigned short zoneId = Bdat::getValCheck(GfDataBdat::getFP(0x1e0), "ZoneID", m_collectionId, 2);
    if (!zoneId) {
        dispose();
        return;
    }
    m_mapBdatId = zoneId;
    int mapId = getMapBdatId();
    m_gmkSetId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(mapId);
    int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestTarget::getIconTypeCollect(4, collectionId, m_questId, mapId, true));
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
}
void LocatorCollection::update() {
    if (m_collectionId == 0) {
        return;
    }
    m_posList.clear();
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(m_gmkSetId);
    if (set == nullptr || !set->isValid()) {
        return;
    }
    const gmk::IGmkList* list = set->getGmkList(gmk::GmkCollection::TYPE);
    if (list == nullptr) {
        return;
    }
    unsigned int num = list->getInstNum();
    for (unsigned int i = 0; i != num; i++) {
        const gmk::GmkCollection* gmk = static_cast<const gmk::GmkCollection*>(list->getInst(i));
        if (gmk->isValid() && gmk->isSameTableID(m_collectionId) && gmk->getBdatInfo()->isPopCondMatchedExceptDist() &&
            !gmk->isWaitRepop()) {
            m_posList.push_back(*gmk->m_pos);
        }
    }
}
GfFieldLocator::GfFieldLocator(const CreateInfoByQuest* info) : m_locator(nullptr) {
    if (info != nullptr) {
        createByQuest(*info);
    }
}
GfFieldLocator::GfFieldLocator(const GfFieldLocator& other) : m_locator(nullptr) {
    if (!other.m_info.m_questId.empty() && other.m_info.m_type >= 0 && other.m_info.m_id >= 0) {
        createByQuest(other.m_info);
    }
}
void GfFieldLocator::createLocatorTalkPreorder(unsigned short npcId) {
    dispose();
#line 2983
    LocatorTalk_NpcID* locator = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LocatorTalk_NpcID;
    locator->createPreorder(npcId);
    m_locator = locator;
}
void GfFieldLocator::createLocatorEventPreorder(const gmk::GmkEvent& event) {
    dispose();
#line 2995
    m_locator = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LocatorEventPreorder(&event);
}
void GfFieldLocator::createLocatorPreciousPreorder(const gmk::GmkPrecious& precious) {
    dispose();
#line 3006
    m_locator = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LocatorPreciousPreorder(&precious);
}
bool GfFieldLocator::isOtherMap() const {
    return m_locator->getMapBdatId() != gmk::getCurrentMapBdatId();
}
void GfFieldLocator::dispose() {
    if (m_locator != nullptr) {
        delete m_locator;
        m_locator = nullptr;
    }
    m_info = CreateInfoByQuest();
}
void GfFieldLocator::update() {
    if (m_locator != nullptr) {
        m_locator->update();
    }
}
bool GfFieldLocator::isIconIdPreorder(int iconId) {
    return static_cast<unsigned short>(Bdat::getValCheck(GfDataBdat::getFP(0x7b), 1, 0x10, 2)) == iconId;
}
GfFieldNpcLocator::GfFieldNpcLocator(const CreateInfo* info) : m_id(0), m_posNum(0), m_pos(mm::Vec3::zero), pad_20(0) {
    if (info != nullptr) {
        dispose();
        m_id = info->m_id;
    }
}
void GfFieldNpcLocator::dispose() {
    pad_20 = 0;
    m_posNum = 0;
    m_pos = mm::Vec3::zero;
    m_id = 0;
}
void GfFieldNpcLocator::update() {
    if (m_id == 0) {
        return;
    }
    m_posNum = 0;
    pad_20 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(GfGameManager::getMapID());
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(pad_20);
    if (set == nullptr) {
        return;
    }
    const gmk::GmkNpcIdInfo* info = set->m_npcManager.getNpcIdInfoByNpcId(m_id);
    GfObjAcc acc(info->m_handle);
    if (acc.isValidTransform()) {
        m_pos = acc.getWorldTransformNoSync().position;
        m_posNum = 1;
        return;
    }
    const gmk::AGmkNpc* npc = info->m_gmk;
    if (npc == nullptr) {
        return;
    }
    if (!npc->isPopCondMatched()) {
        return;
    }
    mm::Vec3 rot;
    if (npc->findPopPosRot(m_pos, rot)) {
        m_posNum = 1;
    }
}

const gmk::AGmkBase* GfGmkLocator::getBindedGmk() const {
    return m_isAcc ? m_acc.m_gmk : m_gmk;
}
void GfGmkLocator::dispose() {
    m_acc.dispose();
    m_gmk = nullptr;
    m_isAcc = false;
}

bool GfGmkLocator::isShop(const gmk::AGmkBase& gmk) {
    unsigned int type = gmk.getGmkType();
    if (type - 3 > 1) {
        return false;
    }
    unsigned short shopId = Bdat::getValCheckU16(gmk.getBindedBdatFp(), "ShopID", gmk.m_createInfo.m_bdatId);
    if (shopId == 0) {
        return false;
    }
    unsigned short icon = Bdat::getValCheckU16(GfDataBdat::getFP(0xED), "ShopIcon", shopId);
    return icon != 0x1A3 && icon != 0x1A4;
}
GfGmkLocatorAtlas::GfGmkLocatorAtlas(const CreateInfo* info)
    : m_bdatIdTop(-1), m_curGmkSet(nullptr), m_gmkSet(nullptr), m_seq(nullptr) {
    if (info != nullptr) {
        create(*info);
    }
}
void GfGmkLocatorAtlas::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    if (m_bdatInfos.size() == 0) {
        createBdatInfos();
    }
    if (GfGameManager::getMapID() == info.m_mapId) {
        m_seq = &GfGmkLocatorAtlas::seqWaitToCreateCurMapGmkSet;
        return;
    }
    gmk::GmkSet::CreateInfo setInfo;
    setInfo.m_allocHandle = getAllocator(ALLOCATOR(8))->getMemHandle();
    setInfo.m_bdatId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(info.m_mapId);
    setInfo.m_flag = true;
    m_gmkSet.create(setInfo);
    m_curGmkSet = &m_gmkSet;
    m_seq = &GfGmkLocatorAtlas::seqWaitToCreateGmkSet;
}
void GfGmkLocatorAtlas::dispose() {
    m_seq = nullptr;
    m_locators.destroy();
    m_gmkSet.dispose();
    m_curGmkSet = nullptr;
    m_bdatIdTop = -1;
    m_bdatInfos.destroy();
    m_info = CreateInfo();
}
void GfGmkLocatorAtlas::createBdatInfos() {
    m_bdatIdTop = -1;
    m_bdatInfos.destroy();
    unsigned char* fp = GfDataBdat::getFP(0x17a);
    m_bdatInfos.setAllocator(getAllocator(ALLOCATOR(0)));
    int num = Bdat::getIdCount(fp);
    m_bdatInfos.reserve(num);
    m_bdatInfos.resize(num);
    m_bdatIdTop = Bdat::getIdTop(fp);
    for (int i = 0; i < num; ++i) {
        BdatInfo& bdatInfo = m_bdatInfos[i];
        int id = i + m_bdatIdTop;
        bdatInfo.m_levelName = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "level_name", id, 7));
        bdatInfo.m_levelPriority = Bdat::getValCheck(fp, "level_priority", id, 2);
    }
}
void GfGmkLocatorAtlas::seqWaitToCreateCurMapGmkSet(float) {
    const gmk::GmkManager* manager = gmk::GmkManager::sys();
    if (manager->m_gmkSets.size() != 0) {
        m_curGmkSet = manager->m_gmkSets[0];
        m_seq = &GfGmkLocatorAtlas::seqWaitToCreateGmkSet;
    }
}
void GfGmkLocatorAtlas::update(float delta) {
    if (m_info.m_mapId <= 0) {
        return;
    }
    if (m_gmkSet.isValid()) {
        m_gmkSet.update(delta);
    }
    if (m_seq) {
        (this->*m_seq)(delta);
    }
}

inline void LocatorBat_EnemySpeciesID::fn_7100272430(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (!acc.isValidTransform()) {
        return;
    }
    DataObjEnemy enemy(handle);
    if (enemy.isValid() && enemy.getGenus() == m_speciesId) {
        m_posList.push_back(acc.getWorldTransformNoSync().position);
    }
}
}  // namespace gf

// the locator vectors' growth (their users are not written yet)
template void mm::mtl::Vector<gf::GfGmkLocators>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocators>::push_back(const gf::GfGmkLocators&);
