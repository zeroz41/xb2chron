#ifndef CLASSES_GF_TUNK_B51E28_H
#define CLASSES_GF_TUNK_B51E28_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B51E28, no RTTI and no 1.0.0 symbol (new in 3.0.1). A field locator for a collection point: it reads
// the "ZoneID" of its BDAT 0x1E0 (collection table) row, asks GfQuestTarget::getIconTypeCollect with kind 4 and
// gathers the positions of the current gimmick set's GmkCollection (GmkType 0x1C) gimmicks of that row; a suggested
// name would be "LocatorCollection", not the original's
class LocatorCollection : public ::gf::AFieldLocator {
public:
    virtual ~LocatorCollection() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    // 2.0.0's symbols name it. What it does: like its siblings' create(): clears, stores the quest and the collection
    // row, reads the row's "ZoneID" from BDAT 0x1E0 (0: clears again), stores it as the map, the map's gimmick set, and
    // the icon of GfQuestTarget::getIconTypeCollect(4, row, quest, map, true) (0x19f when none)
    void create(QuestID questId, unsigned short collectionId);
    // the destructor's clearing (its siblings' 1.0.0 symbols name theirs dispose(); 3.0.1 inlines it)
    void dispose() {
        m_gmkSetId = 0;
        m_collectionId = 0;
        m_posList.clear();
    }

    unsigned short m_gmkSetId;      // the map's gimmick set (GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList)
    unsigned short m_collectionId;  // a row of BDAT 0x1E0 (GmkCollection::BdatInfo::m_collectionTable)
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;  // getPos()
};
}  // namespace gf

#endif
