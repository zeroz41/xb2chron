#ifndef CLASSES_GF_GFMENUIDLIST_H
#define CLASSES_GF_GFMENUIDLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuIDList's content: an id (GfMenuIDList::sortMissionComplete orders by it)
class MenuID {
public:
    unsigned int m_id;
    // a second id: GfMenuWorldMapAdapter::ListWorkConverter's map; the name is not the original's
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
    // 2.0.0's symbols name it. What it does: when the list is not empty, sorts it with sortDescending (flag set:
    // m_subId descending) or sortAscending (flag clear: m_subId ascending), ties by m_id ascending. Called by
    // GfMenuObjAnnounce::initialize, getEvthIDList, GfMenuObjHitonowa::addNpc after filling a list. Same shape as GfMenuMsgList::sort.
    void sortFromWork(bool descending);
    // 2.0.0's symbols name them. What they do: sortDescending orders by m_subId descending, sortAscending by m_subId
    // ascending, both by m_id ascending on a tie.
    static bool sortDescending(const MenuID& a, const MenuID& b);
    static bool sortAscending(const MenuID& a, const MenuID& b);
    // 2.0.0's symbols name it. What it does: sorts the list with a copy of the given comparison
    // (UIListInfo<MenuID>::sort); its one caller is GfMenuObjNamedList::updateNamedIDList. It hides the base's sort:
    // this unit's other sorts call UIListInfo<MenuID>::sort by name.
    void sort(std::function<bool(const MenuID&, const MenuID&)> compare);
};
}  // namespace gf

#endif
