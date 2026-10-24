#ifndef CLASSES_GF_LOCATORTBOX_H
#define CLASSES_GF_LOCATORTBOX_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfQuestTarget.h"

namespace gf {
// table 0x7100B51C58
class LocatorTbox : public ::gf::AFieldLocator {
public:
    LocatorTbox(QuestID questId, unsigned short tboxId);
    // 1.0.0's symbols have it out of line; 3.0.1 inlines it in the constructor
    void create(QuestID questId, unsigned short tboxId) {
        m_posNum = 0;
        m_questId = questId;
        m_tboxId = tboxId;
        int gmkSetId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(gmk::GmkTbox::TYPE, tboxId);
        if (gmkSetId <= 0) {
            dispose();
            return;
        }
        m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
        int iconId = gmk::getBdatIdOfQuestTargetIcon(
            GfQuestTarget::getIconTypeCollect(1, tboxId, m_questId, m_mapBdatId, true));
        m_iconBdatId = iconId < 0 ? 0x19f : iconId;
    }
    virtual ~LocatorTbox() {  // slot 0
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
        m_tboxId = 0;
    }

    unsigned short m_tboxId;  // the treasure box's id ("TresureID"); the name is not the original's
    gmk::GmkAcc m_acc;
    unsigned char m_posNum;
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
