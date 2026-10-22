#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_H

#include "classes/gf/GfMenuObject.h"

namespace ui { struct EventData; }
namespace ui { class UIListInfoBase; }
namespace ui { class UISelectObjList; }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UICtrlRevolveSelect; }

namespace gf {
// table 0x7100B62C70
class GfMenuObjLinkJump : public ::gf::GfMenuObject {
public:
    class CategoryListener;
    class ListListener;
    class NotifyListener;
    class RootListener;
    // one of the two lists setupListObject duplicates from LAY_list (0: GfMenuReference's enemies, 1: its items);
    // the destructor releases the references it holds (the names are not the original's)
    struct ListObject {
        unsigned int m_handle;              // the duplicated LAY_list
        ui::UIListInfoBase* m_list;         // the GfMenuReference list it shows
        ui::UISelectObjList* m_selectList;  // its TXT_itemNN rows
        ui::UICtrlCursorSelect* m_cursor;   // IMG_cursor's
    };
    GfMenuObjLinkJump(unsigned int handle);
    virtual ~GfMenuObjLinkJump();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    void setupListObject(unsigned int index);
    void changeCategory(int index);
    void listenerCategorySelect(const ui::EventData& event);
    ListObject m_lists[2];
    ui::UISelectObjList* m_categories;    // the two lists, as the category ring's objects
    ui::UICtrlRevolveSelect* m_revolve;   // LAY_main's ring over them
    bool m_open;  // the categories are shown: open (0x21) sets it, closing clears it
};
}  // namespace gf

#endif
