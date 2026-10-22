#ifndef CLASSES_GF_GFMENUOBJCYLINDERSELECT_H
#define CLASSES_GF_GFMENUOBJCYLINDERSELECT_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GfMenuItemList; }
namespace ui { class UISelectObjList; }
namespace ui { class UICtrlCursorSelect; }

namespace gf {
// table 0x7100B616F0
class GfMenuObjCylinderSelect : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjCylinderSelect(unsigned int handle);
    virtual ~GfMenuObjCylinderSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // opens the list of the salvage cylinders for the item (the other quest items are left out); the context's
    // result is the chosen one's id
    static void open(GfMenuCallContext* context, unsigned int item);
    GfMenuItemList* m_itemList;           // the cylinders (the names are not the original's)
    ui::UISelectObjList* m_selectList;    // the rows (LAY_item_base@NN)
    ui::UICtrlCursorSelect* m_cursor;     // IMG_item_cursor's
    GfMenuCallContext* m_context;         // the common text it opens when there is no cylinder
};
}  // namespace gf

#endif
