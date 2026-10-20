#ifndef CLASSES_GF_GFMENUOBJMAINMENU2BG_H
#define CLASSES_GF_GFMENUOBJMAINMENU2BG_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B630E8
class GfMenuObjMainMenu2BG : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjMainMenu2BG();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
