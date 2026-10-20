#ifndef CLASSES_GF_GFMENUOBJHANASUBMENU_H
#define CLASSES_GF_GFMENUOBJHANASUBMENU_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62998
class GfMenuObjHanaSubmenu : public ::gf::GfMenuObject {
public:
    class MainListener;
    class SubmenuListener;
    virtual ~GfMenuObjHanaSubmenu();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
