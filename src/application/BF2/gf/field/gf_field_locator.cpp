#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/GmkCollection.h"
#include "classes/gf/TUnk_B51DE0.h"
#include "classes/gf/TUnk_B51E28.h"
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
#include "classes/gmk/TUnk_B6D660.h"
#include "classes/gf/GfGmkLocator.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gf/DataObjEnemy.h"

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
LocatorBat_EnemySpeciesID::LocatorBat_EnemySpeciesID(QuestID questId, unsigned char speciesId)
    : m_speciesId(0), m_gmkSetId(-1) {
    if (!questId.empty() && speciesId != 0) {
        create(questId, speciesId);
    }
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
    const gmk::GmkNpcManager::NpcIdInfo* info = set->m_npcManager.getNpcIdInfoByNpcId(m_npcId);
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
        if (!gmk::fn_71005B38EC(gmk)) {
            return;
        }
        m_pos = *gmk->m_pos;
        break;
    case gmk::TUnk_B6D660::TYPE:
        if (!static_cast<const gmk::TUnk_B6D660*>(gmk)->getBdatInfo()->fn_71005B94AC()) {
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
TUnk_B51DE0::TUnk_B51DE0(QuestID questId, unsigned short row) {
    if (!questId.empty() && row != 0) {
        create(questId, row);
    }
}
void TUnk_B51DE0::update() {
    if (!isValid()) {
        return;
    }
    int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestInfo::isScenarioQuest(m_questId) ? 1 : 3);
    m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    m_posList.clear();
    const gmk::AGmkBase* gmk = gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkType(0x3a), m_enemyWaveId);
    if (gmk == nullptr || !gmk->isValid()) {
        return;
    }
    if (!gmk->isValid() || !gmk::fn_71005B38EC(gmk)) {
        return;
    }
    unsigned int num = gmk::fn_71005B3814(gmk);
    for (unsigned int i = 0; i != num; i++) {
        const gmk::GmkEnemy* enemy = gmk::fn_71005B3824(gmk, i);
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
void TUnk_B51E28::fn_710026F0FC(QuestID questId, unsigned short collectionId) {
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
void TUnk_B51E28::update() {
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
        if (gmk->isValid() && gmk->fn_710059BFFC(m_collectionId) && gmk->getBdatInfo()->isPopCondMatchedExceptDist() &&
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

const gmk::AGmkBase* GfGmkLocator::getBindedGmk() const {
    return m_isAcc ? m_acc.m_gmk : m_gmk;
}
void GfGmkLocator::dispose() {
    m_acc.dispose();
    m_gmk = nullptr;
    m_isAcc = false;
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
