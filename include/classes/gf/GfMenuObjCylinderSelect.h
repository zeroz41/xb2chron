#ifndef CLASSES_GF_GFMENUOBJCYLINDERSELECT_H
#define CLASSES_GF_GFMENUOBJCYLINDERSELECT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B616F0
class GfMenuObjCylinderSelect : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjCylinderSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
