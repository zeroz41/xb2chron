#ifndef CLASSES_GF_GFMENUOBJMAINSUBMENU_H
#define CLASSES_GF_GFMENUOBJMAINSUBMENU_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B632B8
class GfMenuObjMainSubmenu : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    virtual ~GfMenuObjMainSubmenu();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
