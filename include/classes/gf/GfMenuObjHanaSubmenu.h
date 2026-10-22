#ifndef CLASSES_GF_GFMENUOBJHANASUBMENU_H
#define CLASSES_GF_GFMENUOBJHANASUBMENU_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIManager.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B62998
class GfMenuObjHanaSubmenu : public ::gf::GfMenuObject {
public:
    class MainListener;
    class SubmenuListener;
    GfMenuObjHanaSubmenu(unsigned int handle);
    virtual ~GfMenuObjHanaSubmenu();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void setupSubmenu(ui::UIObjectAcc& acc);  // the three entries' icons and the texts docked to them
    static void returnHanaSubMenu();  // back from a submenu entry's menu (event 0x101)
    // 1.0.0's (out of line there; 3.0.1 has no copies): the common fades, heard by the handle's object
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
    // 1.0.0's (out of line there): an event of that type and first parameter, through UIManager
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    ui::UICtrlCursorSelect* m_cursor;  // the entries' cursor, from GfMenuObjUtil::createCursor
    unsigned int m_select;             // the entry the cursor is on (the name is not the original's)
    float m_iconScale;                 // an entry icon's scale, and the selected one's (1.5 times it)
    float m_iconSelectScale;           // (the names are not the original's)
};
}  // namespace gf

#endif
