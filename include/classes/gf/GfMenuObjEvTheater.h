#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62040
class GfMenuObjEvTheater : public ::gf::GfMenuObject {
public:
    class HeaderListener;
    // TitleMenu::setupEventTheater / openEventTheater / fadeoutEventTheater pass their call context
    static void attach(GfMenuCallContext* context);
    static void fadein(GfMenuCallContext* context);
    static void fadeout(GfMenuCallContext* context);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code (a bare ret) is in
    // gf_menu_obj_ev_theater's unit. What it does: nothing in 3.0.1. TitleStatePlayEvent::enter and onLeave call it
    // with w0 = 0 (the bool parameter type is not proven).
    static void fn_71003FEE10(bool flag);
    virtual ~GfMenuObjEvTheater();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
