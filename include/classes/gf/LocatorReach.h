#ifndef CLASSES_GF_LOCATORREACH_H
#define CLASSES_GF_LOCATORREACH_H

#include "classes/gf/AFieldLocator.h"

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
