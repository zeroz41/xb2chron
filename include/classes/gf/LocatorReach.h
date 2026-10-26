#ifndef CLASSES_GF_LOCATORREACH_H
#define CLASSES_GF_LOCATORREACH_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gmk/GmkManager.h"
#include "plugin/Bdat.h"

namespace gf {
// table 0x7100B51C10
class LocatorReach : public ::gf::AFieldLocator {
public:
    LocatorReach(QuestID questId, int row);
    virtual ~LocatorReach() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posNum;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // 1.0.0 has it out of line (3.0.1's constructor inlines it); row: a row of BDAT table 0xce
    void create(QuestID questId, int row) {
        dispose();
        m_questId = questId;
        unsigned char* fp = GfDataBdat::getFP(0xce);
        m_category = static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Category", row, 1)));
        m_placeId = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "PlaceID", row, 2)));
        m_mapBdatId = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "MapID", row, 2)));
        // read and unused (1.0.0 has the same call): the table isIconIdPreorder reads
        unsigned char* iconFp = GfDataBdat::getFP(0x7b);
        (void)iconFp;
        unsigned int mapId = getMapBdatId();
        int iconId = gmk::getBdatIdOfQuestTargetIcon(
            GfQuestTarget::getIconTypeReachPlace(m_category, m_placeId, m_questId, mapId, true));
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posNum = 0;
        m_placeId = 0;
        m_category = 0;
        m_questId = QuestID();
    }

    unsigned char m_category;  // the row's "Category"
    unsigned short m_placeId;  // the row's "PlaceID"
    unsigned char m_posNum;
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
