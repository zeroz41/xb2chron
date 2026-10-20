#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60F20
class GfMenuObjCharSelect : public ::gf::GfMenuObject {
public:
    class CharBlMoveListener;
    class CharDrListener;
    class CharDrMoveListener;
    class CharDrSoloListener;
    class CharListener;
    class DetailListener;
    class StatusListener;
    class SubMenuListener;
    virtual ~GfMenuObjCharSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
