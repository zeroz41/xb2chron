#ifndef CLASSES_GF_GFMENUOBJITEMLIST2_H
#define CLASSES_GF_GFMENUOBJITEMLIST2_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/UIStr.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace gf { class GfMenuItemList; }
namespace ui { class UIObjectAcc; class UISelectObjList; }

namespace gf {
// table 0x7100B62BB0
class GfMenuObjItemList2 : public ::gf::GfMenuObject {
public:
    class FilterListener;
    class ItemListListener;
    class MainListener;
    GfMenuObjItemList2(unsigned int handle);
    virtual ~GfMenuObjItemList2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 1.0.0's helpers (0x710047BE34, 0x710047BEC0, 0x710047BEFC, 0x710047BE70; out of line there), inlined into
    // their callers in 3.0.1: the common fades with their control events hooked (setFadeOutSub: unhooked), and an event
    // of that type and first parameter to the object of that handle, frames (1/30 s) later
    static int setFadeIn(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOutSub(unsigned int handle) {
        return GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param, unsigned int frames) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, frames * (1.0f / 30.0f));
    }
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select);
    // 3.0.1 calls both with the filter index: updateItemList with three arguments (2.0.0's symbols give it a fourth,
    // which neither build's callers set), refreshItemList with four (the symbols keep 1.0.0's parameter list)
    static void updateItemList(GfMenuItemList* list, ui::UISelectObjList* select, unsigned int filter, unsigned int);
    static void refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select,
                                unsigned int filter);
    static void setupFilter(ui::UIObjectAcc& acc, unsigned int filter);
    // the filter's label (BDAT 0x11D's message of list 0x14B's entry filter + 1). Inline: setupFilter's frame puts
    // its string above setupFilter's own; the name is GfMenuObjPouch2's 1.0.0 helper of the same job, not this class's
    static void getFilterText(unsigned int filter, ui::UIStr& text) {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14B, filter + 1));
        text.copy(str);
    }
    void refreshFilterIcon();

    // the names below are not the original's
    GfMenuItemList* m_itemList;                         // initialize's
    ui::UISelectObjList* m_itemSelect;                  // initialize's
    mm::mtl::FixedVector<unsigned int, 21> m_filters;   // initialize's: the filters shown (indexes of the item types)
    unsigned int m_filterIndex;                         // the filter selected (FilterListener's)
    unsigned int pad_9C;
    bool m_fadeOnClose;  // MainListener's event 0x22 fades out while set, else closes; event 0x24 clears it
};
}  // namespace gf

#endif
