#ifndef CLASSES_GF_LOCATORBAT_ENEMYGROUPID_H
#define CLASSES_GF_LOCATORBAT_ENEMYGROUPID_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B51AF0
class LocatorBat_EnemyGroupID : public ::gf::AFieldLocator {
public:
    // inline: GfFieldLocator::createByQuest builds it in place
    LocatorBat_EnemyGroupID(QuestID questId, unsigned short groupId) : m_groupId(0), m_gmkSetId(0) {
        if (!questId.empty()) {
            create(questId, groupId);
        }
    }
    virtual ~LocatorBat_EnemyGroupID() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    void create(QuestID questId, unsigned short groupId);
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posList.clear();
        m_zoneIds.clear();
        m_enemyIds.clear();
        m_groupId = 0;
    }

    unsigned short m_groupId;  // create's row of the group table ("EnemyID%d")
    int m_gmkSetId;
    mm::mtl::FixedVector<unsigned int, 8> m_enemyIds;   // "EnemyID1".."EnemyID8"
    mm::mtl::FixedVector<unsigned char, 8> m_zoneIds;   // each enemy's "ZoneID" (else the current map's)
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;
};
}  // namespace gf

#endif
