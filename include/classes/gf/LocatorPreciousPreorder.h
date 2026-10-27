#ifndef CLASSES_GF_LOCATORPRECIOUSPREORDER_H
#define CLASSES_GF_LOCATORPRECIOUSPREORDER_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gf/GfFieldGimmick.h"

namespace gf {
// table 0x7100B51D50
class LocatorPreciousPreorder : public ::gf::AFieldLocator {
public:
    // the parameter names are not the original's
    LocatorPreciousPreorder(const gmk::GmkPrecious* precious) : m_preciousId(0), m_posNum(0) {
        if (precious != nullptr) {
            create(*precious);
        }
    }
    // 1.0.0 has it out of line (3.0.1's callers inline it)
    void create(const gmk::GmkPrecious& precious) {
        dispose();
        m_preciousId = precious.m_createInfo.m_bdatId;
        int gmkSetId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(gmk::GmkPrecious::TYPE, m_preciousId);
        if (gmkSetId <= 0) {
            dispose();
            return;
        }
        m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
        int iconId = gmk::getBdatIdOfQuestTargetIcon(2);
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    virtual ~LocatorPreciousPreorder() {  // slot 0
        dispose();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_acc.isValid() ? m_posNum : 0;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // the destructor's clearing; 1.0.0's symbols name it dispose() (3.0.1 inlines it)
    void dispose() {
        m_posNum = 0;
        m_preciousId = 0;
    }

    unsigned short m_preciousId;  // the precious gimmick's id; the name is not the original's
    gmk::GmkAcc m_acc;
    unsigned char m_posNum;
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
