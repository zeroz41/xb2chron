#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameMercenaries.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "plugin/Bdat.h"

namespace gf {

namespace {
// a mercenary zone and the menu condition that opens it (GfMenuObjUtil::getMenuCondition); the names are not the original's
struct MercenaryZone {
    unsigned int m_zone;
    unsigned int m_condition;
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BD158)
const MercenaryZone s_mercenaryZones[] = {
    {1, 0x19}, {2, 0x1A}, {3, 0x1B}, {4, 0x1C}, {5, 0x1D}, {6, 0x1E}, {7, 0x1F},
};
}  // namespace

GfMenuIDList::~GfMenuIDList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuIDList* GfMenuIDList::create() {
#line 53
    GfMenuIDList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuIDList;
    list->addRef();
    return list;
}

void GfMenuIDList::setupMercenaryZoneList(const ui::UIListInfoBase::SetupParam& param, bool checkCondition) {
    ui::UIListInfoBase::SetupParam setupParam = param;
    UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR(0)), setupParam);
    for (unsigned int i = 0; i < sizeof(s_mercenaryZones) / sizeof(s_mercenaryZones[0]); i++) {
        if (checkCondition && !GfMenuObjUtil::getMenuCondition(s_mercenaryZones[i].m_condition)) {
            continue;
        }
        mm::mtl::FixedVector<unsigned short, 500> missions;
        GfGameMercenaries::getZoneMission(missions, s_mercenaryZones[i].m_zone);
        if (missions.size() != 0) {
            MenuID id = {s_mercenaryZones[i].m_zone, 0};
            addContents(id);
        }
    }
}

void GfMenuIDList::setupMissionListFromZone(const ui::UIListInfoBase::SetupParam& param, unsigned int zone) {
    mm::mtl::FixedVector<unsigned short, 500> missions;
    GfGameMercenaries::getZoneMission(missions, zone);
    ui::UIListInfoBase::SetupParam setupParam = param;
    UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR(0)), setupParam);
    if (!isValid()) {
        return;
    }
    MenuID id = {0, 0};
    for (unsigned int i = 0; i < missions.size(); i++) {
        id.m_id = missions[i];
        addContents(id);
    }
    UIListInfo<MenuID>::sort(sortMissionComplete);
}

bool GfMenuIDList::sortMissionComplete(const MenuID& a, const MenuID& b) {
    bool completeA = GfDataMercenaries::isOrderOnlyOne(a.m_id) ? GfDataMercenaries::isMissionCompleteFlag(a.m_id) : false;
    bool completeB = GfDataMercenaries::isOrderOnlyOne(b.m_id) ? GfDataMercenaries::isMissionCompleteFlag(b.m_id) : false;
    if (completeA != completeB) {
        return !completeA;
    }
    return a.m_id < b.m_id;
}

void GfMenuIDList::setupExcTaskListFromShop(const ui::UIListInfoBase::SetupParam& param, unsigned int shop) {
    UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR(0)), param);
    unsigned char* shopBdat = GfDataBdat::getFP(0xED);
    unsigned char* taskBdat = GfDataBdat::getFP(0xF0);
    if (GfMenuBdat::isValidBdatID(shopBdat, shop)) {
        unsigned char shopType = Bdat::getVal(shopBdat, "ShopType", shop);
        unsigned short tableId = Bdat::getVal(shopBdat, "TableID", shop);
        if (shopType == 1) {
            if (shop == 0x100) {
                unsigned char* listBdat = GfDataBdat::getFP(0xF1);
                if (listBdat != nullptr) {
                    for (int i = 0; i < Bdat::getIdCount(listBdat); i++) {
                        int row = Bdat::getIdTop(listBdat) + i;
                        unsigned short condition = Bdat::getVal(listBdat, "Condition", row);
                        if (condition != 0 && !GfGameCond::isGameCond(condition)) {
                            continue;
                        }
                        unsigned short condition2 = Bdat::getVal(listBdat, "Condition2", row);
                        if (condition2 != 0 && !GfGameCond::isGameCond(condition2)) {
                            continue;
                        }
                        unsigned short taskSet = Bdat::getVal(listBdat, "TaskSet", row);
                        if (taskSet != 0) {
                            MenuID id = {taskSet, 0};
                            addContents(id);
                        }
                    }
                }
            } else if (tableId) {
                mm::mtl::FixStr<32> column;
                MenuID id = {0, 0};
                int i = 1;
                column.format("DefTaskSet%d", i);
                while (Bdat::getMember(taskBdat, column.m_str) != nullptr) {
                    id.m_id = (unsigned short)Bdat::getVal(taskBdat, column.m_str, tableId);
                    if (id.m_id != 0) {
                        addContents(id);
                    }
                    column.format("DefTaskSet%d", ++i);
                }
                i = 1;
                column.format("AddTaskSet%d", i);
                while (Bdat::getMember(taskBdat, column.m_str) != nullptr) {
                    mm::mtl::FixStr<32> condition;
                    condition.format("AddCondition%d", i);
                    if (GfGameCond::isGameCond((unsigned short)Bdat::getVal(taskBdat, condition.m_str, tableId))) {
                        id.m_id = (unsigned short)Bdat::getVal(taskBdat, column.m_str, tableId);
                        if (id.m_id != 0) {
                            addContents(id);
                        }
                    }
                    column.format("AddTaskSet%d", ++i);
                }
            }
        }
    }
}

void GfMenuIDList::sortFromWork(bool descending) {
    if (getSize() == 0) {
        return;
    }
    std::function<bool(const MenuID&, const MenuID&)> compare;
    compare = descending ? sortDescending : sortAscending;
    UIListInfo<MenuID>::sort(compare);
}

bool GfMenuIDList::sortDescending(const MenuID& a, const MenuID& b) {
    if (a.m_subId == b.m_subId) {
        return a.m_id < b.m_id;
    }
    return a.m_subId > b.m_subId;
}

bool GfMenuIDList::sortAscending(const MenuID& a, const MenuID& b) {
    if (a.m_subId == b.m_subId) {
        return a.m_id < b.m_id;
    }
    return a.m_subId < b.m_subId;
}

void GfMenuIDList::sort(std::function<bool(const MenuID&, const MenuID&)> compare) {
    UIListInfo<MenuID>::sort(compare);
}

}  // namespace gf
