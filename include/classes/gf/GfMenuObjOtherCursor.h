#ifndef CLASSES_GF_GFMENUOBJOTHERCURSOR_H
#define CLASSES_GF_GFMENUOBJOTHERCURSOR_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuPosAdapter; }

namespace gf {
// table 0x7100B63DD8
class GfMenuObjOtherCursor : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjOtherCursor(unsigned int handle);
    virtual ~GfMenuObjOtherCursor();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void disp(bool disp);  // shows or hides the cursor (external call 0x13)
    // the cursor (LAY_main), which initialize gives its listener and position adapter (the names of the fields
    // are not the original's)
    unsigned int m_cursor;
    // the object it shows the cursor at: GfMenuManager::getAccessObjHandle's when update last saw it change
    GF_OBJ_HANDLE* m_target;
    GfMenuPosAdapter* m_posAdapter;  // keeps the cursor at m_target
};
}  // namespace gf

#endif
