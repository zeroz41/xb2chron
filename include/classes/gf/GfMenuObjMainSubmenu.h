#ifndef CLASSES_GF_GFMENUOBJMAINSUBMENU_H
#define CLASSES_GF_GFMENUOBJMAINSUBMENU_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UISelectObjList; }

namespace gf {
class GfMenuCallContext;

// table 0x7100B632B8: the main menu's submenus (its object is named mnu094_submenu_book, _crystal or _system), a
// list of items, each opening a menu layer
class GfMenuObjMainSubmenu : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    GfMenuObjMainSubmenu(unsigned int handle);
    virtual ~GfMenuObjMainSubmenu();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // (the field names below are not the original's)
    unsigned int m_kind;          // 1 book, 2 crystal, 3 system: which item table initialize picked
    unsigned int m_guideText;     // GfMenuObjOperationInfo::setGuideText's when the list opens
    unsigned int m_subIndexText;  // GfMenuObjMainMenu2::setSubIndexText's when the list opens
    ui::UISelectObjList* m_list;  // the shown items' objects
    mm::mtl::FixedVector<unsigned int, 8> m_items;  // the shown items' indexes in the kind's table
    unsigned int m_select;        // the list's first selection: the full-screen layer's parameter on open
    bool m_fadeOnClose;           // closing fades the list out first (event 0x24 clears it)
    GfMenuCallContext* m_context; // what the common texts open with
    int m_growCtrl[5];            // the items' glow controls (startCtrl's slots), -1 for none
};
}  // namespace gf

#endif
