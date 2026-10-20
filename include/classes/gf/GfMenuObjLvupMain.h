#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62E38
class GfMenuObjLvupMain : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MenuListener;
    class SelectListener;
    virtual ~GfMenuObjLvupMain();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
