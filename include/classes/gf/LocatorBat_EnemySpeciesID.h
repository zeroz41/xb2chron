#ifndef CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H
#define CLASSES_GF_LOCATORBAT_ENEMYSPECIESID_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gmk/GmkManager.h"
#include "plugin/Bdat.h"
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
    // 1.0.0 has it out of line (3.0.1's constructor inlines it)
    void create(QuestID questId, unsigned char speciesId) {
        dispose();
        m_questId = questId;
        m_speciesId = speciesId;
        m_mapBdatId = GfGameManager::getMapID();
        m_gmkSetId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(m_mapBdatId);
        int iconId = gmk::getBdatIdOfQuestTargetIcon(GfQuestTarget::getIconTypeBattle(
            3, speciesId, questId, reinterpret_cast<GF_OBJ_HANDLE*>(-1), true));
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    // Placeholder name: nothing in 1.0.0's place names it (its update calls fn_71002E14A8 there). A member because
    // update passes this; inline (weak, emitted after the unit's table slots). What it does: when the object has a
    // valid transform and its DataObjEnemy is valid with getGenus() == m_speciesId, adds its world position to
    // m_posList (defined in gf_field_locator.cpp).
    inline void fn_7100272430(GF_OBJ_HANDLE* handle);
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
