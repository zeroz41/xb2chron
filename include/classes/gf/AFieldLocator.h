#ifndef CLASSES_GF_AFIELDLOCATOR_H
#define CLASSES_GF_AFIELDLOCATOR_H

#include "gf/QuestID.h"
#include "mm/Vec3.h"

namespace gf {
// table none (its derived classes'): every virtual of its own is inline or pure, and the constructors' stores of it
// are overwritten by the derived classes', so no unit emits it
class AFieldLocator {
public:
    // the derived constructors (and the ones GfFieldLocator::createByQuest inlines) start with these stores
    AFieldLocator() : m_iconBdatId(-1), m_mapBdatId(-1) {}
    virtual ~AFieldLocator() {}  // slot 0
    virtual int getIconBdatId() const {  // slot 2
        return m_iconBdatId;
    }
    virtual unsigned int getPosNum() const = 0;  // slot 3
    virtual const mm::Vec3* getPos(unsigned int index) const = 0;  // slot 4
    virtual int getMapBdatId() const {  // slot 5
        return m_mapBdatId;
    }
    virtual void update() = 0;  // slot 6 (every derived table fills it)

    QuestID m_questId;  // the quest the constructors are given
    int m_iconBdatId;   // getIconBdatId(); the constructors store gmk::getBdatIdOfQuestTargetIcon's id
    int m_mapBdatId;    // getMapBdatId()
};
}  // namespace gf

#endif
