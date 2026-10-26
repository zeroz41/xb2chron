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
#include "fw/Transform.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFieldLocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"

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
    unsigned short mapId = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(bdat, "MapID", row, 2)));
    unsigned short npcId = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(bdat, "NpcID", row, 2)));
    if (mapId && npcId) {
        create(questId, mapId, npcId);
    }
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

}  // namespace gf
