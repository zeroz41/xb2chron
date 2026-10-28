#ifndef CLASSES_GMK_GMKEVENT_H
#define CLASSES_GMK_GMKEVENT_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkEventGob; }

namespace gmk {
// table 0x7100B6C418
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
    // its node (a second, non-polymorphic base at 0x48) links it into TGmkActiveList<GmkEvent>
class alignas(16) GmkEvent : public ::gmk::AGmkBase, public mm::mtl::IntrusiveListNodeBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isCondMatched() const;
        unsigned short m_condition;  // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_eventId;    // the row's "EventID"
        // 0x4: the quest-target icon's id LocatorEventPreorder::create gives its locator (the name is not the
        // original's)
        unsigned short m_iconBdatId;  // the row's "Icon"
        ScenarioFlagCond m_scenarioFlag;  // the row's ScenarioFlagMin/Max
        QuestFlagCond m_questFlag;        // the row's QuestFlag/Min/Max
    };
    GmkEvent() {}  // inline: construct_n<GmkEvent> constructs in place with these stores
    virtual ~GmkEvent();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(10);
    unsigned char pad_58[0x8];
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    unsigned char pad_e8[0x8];
    // update() stores whether the event's pop conditions (blade, quest state, game cond) hold, creating or
    // disposing its phantom when it changes; the field locators read it. The name is not the original's.
    bool m_isCondMatched = false;
    bool pad_f1 = false;  // the constructor clears it (meaning unknown)
    bool pad_f2 = false;  // the constructor clears it (meaning unknown)
    unsigned char pad_f3[0xd];  // size from TGmkList::getInst's stride (0x100)
};
}  // namespace gmk

#endif
