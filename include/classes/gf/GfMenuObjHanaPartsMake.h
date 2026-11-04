#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/GfMenuItemUtil.h"
#include "ui/EventData.h"

namespace gf { class GfMenuCallContext; class GfMenuItemList; }
namespace ui { class UICtrlCursorColor; class UICtrlCursorSelect; class UIObjectAcc; class UISelectObjList; }

namespace gf {
// table 0x7100B628B0
class GfMenuObjHanaPartsMake : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class MainListener;
    class NumSelectListener;
    class PartsListListener;

    GfMenuObjHanaPartsMake(unsigned int handle);
    // 2.0.0's symbols name it. What it does: sets that byte to 1. Caller: GfMenuManager::gevItemAdd when the count is
    // below 1.
    static void updateItemList();
    virtual ~GfMenuObjHanaPartsMake();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 1.0.0's helper (out of line there), inlined into its callers in 3.0.1
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    static void setupMain(ui::UIObjectAcc& acc);
    // the parts the item-make table (GfDataBdat 0x17D's ITEM_MAKE column) can make
    static void updatePartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select) {
        list->clear();
        unsigned char* fp = GfDataBdat::getFP(0x17D);
        unsigned int top = Bdat::getIdTop(fp);
        unsigned int count = Bdat::getIdCount(fp);
        for (unsigned int i = 0; i < count; i++) {
            MenuID id = MenuID();
            id.m_id = static_cast<unsigned short>(Bdat::getVal(fp, "ITEM_MAKE", top + i));
            if (id.m_id != 0) {
                list->addContents(id);
            }
        }
    }
    static void setupPartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select);
    static void makeCategoryItemList(GfMenuIDList* parts, GfMenuItemList* items, unsigned int mode,
                                     unsigned int sortIndex);
    static void refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select,
                                unsigned int parts, unsigned int mode);
    // 1.0.0 has it out of line: the sort table of the parts' list in that list mode
    static unsigned int getFirstSortTableId(unsigned int parts, unsigned int mode) {
        if (mode == 0) {
            return GfMenuHanaAdapter::getMakeSortTableId(parts);
        }
        return GfMenuHanaAdapter::getSortTableId(parts);
    }
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select);
    static void setupNumSelect(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> count,
                               mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price);
    static void updateItemList(GfMenuItemList* list, ItemType::Type type, unsigned int mode);

    // 2.0.0's symbols name it. Set by updateItemList (an item was added), cleared by initialize; update refreshes the
    // item list's counts while it is set.
    static bool s_UpdateItemList;

    // the names below are not the original's
    GfMenuIDList* m_partsList;                          // initialize's (5 rows)
    ui::UISelectObjList* m_partsSelect;                 // initialize's
    ui::UICtrlCursorSelect* m_partsCursor;              // PartsListListener's (event 1)
    GfMenuItemList* m_itemList;                         // initialize's
    ui::UISelectObjList* m_itemSelect;                  // initialize's
    ui::UICtrlCursorColor* m_itemCursor;                // ItemListListener's
    GfMenuCallContext* m_context;                       // initialize's
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_count;  // initialize's (0 to 99): the number selected
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_price;  // initialize's (0 to 999999999): its total price
    unsigned int m_listMode;   // the parts list's action 9 toggles it (0/1); update refreshes counts when 0
    unsigned int m_sortIndex;  // makeCategoryItemList's; PartsListListener zeroes it on a new part
};
}  // namespace gf

#endif
