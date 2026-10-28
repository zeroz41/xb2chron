#ifndef CLASSES_GF_GFMENUOBJSTAFFROLL_H
#define CLASSES_GF_GFMENUOBJSTAFFROLL_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64AD8
class GfMenuObjStaffroll : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjStaffroll();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // event::UIManager::startStaffrollUI/endStaffroll's (no this: they reach the menu object by its id)
    static void start(float speed, int type);
    static void fadeout();
};
}  // namespace gf

#endif
