#ifndef CLASSES_GF_LOCATORBAT_ENEMYID_H
#define CLASSES_GF_LOCATORBAT_ENEMYID_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gmk/GmkAcc.h"

namespace gf {
// table 0x7100B51AA8
class LocatorBat_EnemyID : public ::gf::AFieldLocator {
public:
    // inline: GfFieldLocator::createByQuest builds it in place (its create() is LocatorBat_EnemyID.cpp's)
    LocatorBat_EnemyID(QuestID questId, unsigned short enemyId) : m_enemyId(0), m_gmkSetId(0) {
        if (!questId.empty()) {
            create(questId, enemyId);
        }
    }
    virtual ~LocatorBat_EnemyID() {  // slot 0
        reset();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    void create(QuestID questId, unsigned short enemyId);
    // the destructor's and create's clearing; the name is not the original's
    void reset() {
        m_posList.clear();
        m_type1Accs.clear();
        m_type0Accs.clear();
        m_enemyId = 0;
    }

    unsigned short m_enemyId;  // passed to GmkEnemyInsts::PopInfo::hasEneID
    int m_gmkSetId;            // update() passes it to GmkManager::findGmkSet
    // accesses to the gimmicks of the gimmick set's GmkType 0 and GmkType 1 lists whose pop holds the enemy (the
    // names are not the original's)
    mm::mtl::FixedVector<gmk::GmkAcc, 16> m_type0Accs;
    mm::mtl::FixedVector<gmk::GmkAcc, 16> m_type1Accs;
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;  // getPos()
};
}  // namespace gf

#endif
