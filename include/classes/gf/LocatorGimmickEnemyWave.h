#ifndef CLASSES_GF_TUNK_B51DE0_H
#define CLASSES_GF_TUNK_B51DE0_H

#include "classes/gf/AFieldLocator.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfGameManager.h"
#include "plugin/Bdat.h"

namespace gf {
// table 0x7100B51DE0, no RTTI and no 1.0.0 symbol (new in 3.0.1). A field locator for an enemy wave: its constructor
// reads the "EnemyWaveID" and "MapID" of a BDAT 0xD1 row; update() gathers the objects of the enemies of the wave
// gimmick (GmkType 0x3A) of that id, else the gimmick's own position; a suggested name would be
// "LocatorBat_EnemyWave", not the original's
class LocatorGimmickEnemyWave : public ::gf::AFieldLocator {
public:
    // out of line: GfFieldLocator::createByQuest calls it
    LocatorGimmickEnemyWave(QuestID questId, unsigned short row);
    virtual ~LocatorGimmickEnemyWave() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posList.size();
    }
    virtual const mm::Vec3* getPos(unsigned int index) const {  // slot 4
        return &m_posList[index];
    }
    virtual void update();  // slot 6
    // its constructor's filling, inline (no symbol; its siblings' 1.0.0 symbols name theirs create(), so the name is
    // not the original's): the row's "EnemyWaveID", its "MapID" as the map and the current map's gimmick set
    void create(QuestID questId, unsigned short row) {
        dispose();
        unsigned char* fp = GfDataBdat::getFP(0xd1);
        m_questId = questId;
        m_enemyWaveId = Bdat::getValCheck(fp, "EnemyWaveID", row, 2);
        m_mapBdatId = static_cast<unsigned short>(Bdat::getValCheck(fp, "MapID", row, 2));
        m_gmkSetId = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(GfGameManager::getMapID());
    }
    // whether create found a wave on the current map (inline, no symbol: update tests it first; the name is not the
    // original's)
    bool isValid() const { return m_gmkSetId != 0 && m_enemyWaveId != 0; }
    // the destructor's clearing (its siblings' 1.0.0 symbols name theirs dispose(); 3.0.1 inlines it)
    void dispose() {
        m_gmkSetId = 0;
        m_enemyWaveId = 0;
        m_posList.clear();
    }

    unsigned short m_gmkSetId;     // the current map's gimmick set (GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList)
    unsigned short m_enemyWaveId;  // the row's "EnemyWaveID": the wave gimmick's BDAT id
    mm::mtl::FixedVector<mm::Vec3, 16> m_posList;  // getPos()
};
}  // namespace gf

#endif
