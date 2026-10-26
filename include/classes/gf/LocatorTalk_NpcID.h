#ifndef CLASSES_GF_LOCATORTALK_NPCID_H
#define CLASSES_GF_LOCATORTALK_NPCID_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gf/GfGameManager.h"

namespace gf {
// table 0x7100B51B80
class LocatorTalk_NpcID : public ::gf::AFieldLocator {
public:
    LocatorTalk_NpcID(QuestID questId, unsigned char* bdat, int row);
    // 1.0.0 has it out of line (3.0.1's GfFieldLocator::createLocatorTalkPreorder inlines it with an empty quest)
    LocatorTalk_NpcID(QuestID questId = QuestID(), unsigned short mapId = 0, unsigned short npcId = 0)
        : m_gmkSetId(0), m_npcId(0), m_posNum(0), m_pos(mm::Vec3::zero) {
        if (!questId.empty() && mapId != 0 && npcId != 0) {
            create(questId, mapId, npcId);
        }
    }
    virtual ~LocatorTalk_NpcID() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posNum;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // 1.0.0 has it out of line (3.0.1's constructor inlines it); the parameter names are not the original's
    void create(QuestID questId, unsigned short mapId, unsigned short npcId) {
        dispose();
        m_mapBdatId = mapId;
        m_questId = questId;
        m_gmkSetId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(mapId);
        m_npcId = npcId;
        int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestTarget::getIconTypeTalk(npcId, m_questId, mapId, true));
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    // a locator of an NPC on the current map, for no quest; 1.0.0 has it out of line (the parameter name is not the
    // original's)
    void createPreorder(unsigned short npcId) {
        dispose();
        m_mapBdatId = GfGameManager::getMapID();
        m_gmkSetId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(m_mapBdatId);
        m_npcId = npcId;
        int iconId = gmk::getBdatIdOfQuestTargetIcon(2);
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_npcId = 0;
        m_gmkSetId = 0;
    }

    int m_gmkSetId;  // GmkManager::findFirstBdatId_RSC_GmkSetList of the row's "MapID"
    unsigned short m_npcId;  // the row's "NpcID"
    unsigned char m_posNum;  // 1 once update() found the NPC's position
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
