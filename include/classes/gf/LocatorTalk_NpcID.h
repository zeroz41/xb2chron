#ifndef CLASSES_GF_LOCATORTALK_NPCID_H
#define CLASSES_GF_LOCATORTALK_NPCID_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51B80
class LocatorTalk_NpcID : public ::gf::AFieldLocator {
public:
    LocatorTalk_NpcID(QuestID questId, unsigned char* bdat, int row);
    virtual ~LocatorTalk_NpcID() {  // slot 0
        reset();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posNum;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // the name is not the original's
    void reset() {
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
