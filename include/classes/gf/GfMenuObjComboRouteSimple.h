#ifndef CLASSES_GF_TUNK_B61408_H
#define CLASSES_GF_TUNK_B61408_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61408: the menu object of gf_menu_obj_combo_route_simple.cpp (new in 3.0.1; nothing names the class
// yet). It shows the element combo route GfMenuReference::getIraBladeComboInfo answers (LAY_route); GfMenuManager::reciveEvent
// creates it, and GfMenuObjComboRoute's open, close and disp call its open, close and disp (open,
// close, disp).
class GfMenuObjComboRouteSimple : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjComboRouteSimple(unsigned int handle);
    virtual ~GfMenuObjComboRouteSimple();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: unless the object is missing or terminating, requests the open event
    // (0x21) on it through the ui::UIManager; GfMenuObjComboRoute::open calls it.
    static void open();
    // 2.0.0's symbols name it. What it does: as open with the close event (0x22); GfMenuObjComboRoute::close calls it.
    static void close();
    // 2.0.0's symbols name it. What it does: unless the object is missing or terminating, shows or hides it;
    // GfMenuObjComboRoute::disp calls it.
    static void disp(bool disp);
    // 2.0.0's symbols name it. What it does: unless the object is missing or terminating, sends it event 0x100 (its
    // listener then redraws the route); GfMenuReference::resetIraBladeCombo / updateIraBladeCombo tail-call it when the combo
    // route record changed.
    static void refresh();
};

// table 0x7100B61450: GfMenuObjComboRouteSimple's listener on "LAY_main" (2.0.0's symbols name it)
class GfMenuObjComboRouteSimple::MainListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    MainListener(GfMenuObjComboRouteSimple* owner) : m_open(0), m_ctrl(0), pad_14(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_open;  // 1 between the open event (0x21) and the close one (0x22) (the name is not the original's)
    int m_ctrl;  // the control opening or closing LAY_route, -1 for none (the name is not the original's)
    unsigned char pad_14[8];
    GfMenuObjComboRouteSimple* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
