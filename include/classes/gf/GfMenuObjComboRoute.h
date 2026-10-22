#ifndef CLASSES_GF_GFMENUOBJCOMBOROUTE_H
#define CLASSES_GF_GFMENUOBJCOMBOROUTE_H

#include "classes/gf/GfMenuObject.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B61360
class GfMenuObjComboRoute : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjComboRoute(unsigned int handle);
    virtual ~GfMenuObjComboRoute();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the routes' adapters, and their cursors' display conditions
    static void setupComboRoute(ui::UIObjectAcc& acc);
    static void open();
    static void close();
    static void disp(bool disp);
    // the control fading each route's cursor in (-1: none), and the one opening or closing the layout (the names
    // are not the original's)
    int m_cursorCtrls[7];
    int m_openCtrl;
};
}  // namespace gf

#endif
