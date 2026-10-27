#ifndef CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_H
#define CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"

namespace gf { class GfMenuCallContext; class GfMenuItemList; }
namespace ui { class UICtrlCursorColor; class UIObjectAcc; class UISelectObjList; }

namespace gf {

// table 0x7100B627C8
class GfMenuObjHanaPartsCrystal : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class MainListener;
    class NumSelectListener;
    class PartsListListener;

    GfMenuObjHanaPartsCrystal(unsigned int handle);
    virtual ~GfMenuObjHanaPartsCrystal();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 1.0.0's helpers (out of line there), inlined into their callers in 3.0.1
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    // the parts the item-make table (GfDataBdat 0x17D's ITEM_MAKE column; 0x142 in 1.0.0) can make
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
    // empty in 1.0.0 too: its callers still compute the part they pass
    static void refreshItemList(GfMenuItemList* list, ui::UISelectObjList* select, unsigned int parts) {}
    static void makeCategoryItemList(GfMenuIDList* parts, GfMenuItemList* items);
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select);
    static void setupNumSelect(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> count,
                               mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price);

    // the names below are not the original's
    GfMenuIDList* m_partsList;                          // initialize's (5 rows)
    ui::UISelectObjList* m_partsSelect;                 // initialize's
    ui::UICtrlCursorColor* m_partsCursor;               // PartsListListener's (event 1)
    GfMenuItemList* m_itemList;                         // initialize's
    ui::UISelectObjList* m_itemSelect;                  // initialize's
    ui::UICtrlCursorColor* m_itemCursor;                // ItemListListener's
    GfMenuCallContext* m_context;                       // initialize's
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_count;  // initialize's (0 to 99): the number selected
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_price;  // initialize's (0 to 999999999): its total price
};

}  // namespace gf

#endif
