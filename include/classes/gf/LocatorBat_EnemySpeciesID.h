#ifndef CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H
#define CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B51B38
class LocatorBat_EnemySpeciesID : public ::gf::AFieldLocator {
public:
    LocatorBat_EnemySpeciesID(QuestID questId, unsigned char speciesId);
    virtual ~LocatorBat_EnemySpeciesID() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posList.clear();
        m_speciesId = 0;
    }

    unsigned char m_speciesId;
    int m_gmkSetId;  // the current map's gimmick set (GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList)
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;
};
}  // namespace gf

#endif
