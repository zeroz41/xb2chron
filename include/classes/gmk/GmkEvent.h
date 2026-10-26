#ifndef CLASSES_GMK_GMKEVENT_H
#define CLASSES_GMK_GMKEVENT_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkEventGob; }

namespace gmk {
// table 0x7100B6C418
class GmkEvent : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x4];
        // 0x4: the quest-target icon's id LocatorEventPreorder::create gives its locator (the name is not the
        // original's)
        unsigned short m_iconBdatId;
        unsigned char pad_6[0x8];
    };
    virtual ~GmkEvent();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(10);
    unsigned char pad_48[0xa8];  // fields: size from TGmkList::getInst's stride
    // update() stores whether the event's pop conditions (blade, quest state, game cond) hold, creating or
    // disposing its phantom when it changes; the field locators read it. The name is not the original's.
    bool m_isCondMatched;
    unsigned char pad_f1[0xf];
};
}  // namespace gmk

#endif
