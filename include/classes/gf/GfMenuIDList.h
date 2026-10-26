#ifndef CLASSES_GF_GFMENUIDLIST_H
#define CLASSES_GF_GFMENUIDLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuIDList's content: an id (GfMenuIDList::sortMissionComplete orders by it)
class MenuID {
public:
    unsigned int m_id;
    // a second id: GfMenuWorldMapAdapter::MissionListConverter's map; the name is not the original's
    unsigned int m_subId;
};

// table 0x7100B5F3D0
class GfMenuIDList : public ::ui::UIListInfo< ::gf::MenuID> {
public:
    virtual ~GfMenuIDList();  // slot 0
    static GfMenuIDList* create();
    // the zones (1..7) that have missions; with checkCondition only those whose menu condition is met
    void setupMercenaryZoneList(const ::ui::UIListInfoBase::SetupParam& param, bool checkCondition);
    // a zone's missions, ordered by sortMissionComplete
    void setupMissionListFromZone(const ::ui::UIListInfoBase::SetupParam& param, unsigned int zone);
    // completed one-time missions last, then by id
    static bool sortMissionComplete(const MenuID& a, const MenuID& b);
    // the exchange tasks a shop offers
    void setupExcTaskListFromShop(const ::ui::UIListInfoBase::SetupParam& param, unsigned int shop);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this
    // unit's text right after setupExcTaskListFromShop and sorts this list (UIListInfo<MenuID>::sort). What it
    // does: when the list is not empty, sorts it with fn_71003720DC (flag set: m_subId descending) or
    // fn_7100372108 (flag clear: m_subId ascending), ties by m_id ascending. Called by fn_7100382960,
    // fn_7100400054, fn_710041E6F8 after filling a list. Same shape as GfMenuMsgList::fn_7100379F9C.
    void fn_7100371F98(bool descending);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because fn_7100371F98 (this
    // class) hands them to the sort and they sit right after it. What they do: fn_71003720DC orders by m_subId
    // descending, fn_7100372108 by m_subId ascending, both by m_id ascending on a tie.
    static bool fn_71003720DC(const MenuID& a, const MenuID& b);
    static bool fn_7100372108(const MenuID& a, const MenuID& b);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this
    // unit's text after the comparators and sorts this list. What it does: sorts the list with a copy of the
    // given comparison (UIListInfo<MenuID>::sort); its one caller is fn_7100445F58.
    void fn_710037212C(const std::function<bool(const MenuID&, const MenuID&)>& compare);
};
}  // namespace gf

#endif
