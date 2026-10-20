#ifndef CLASSES_GF_GFMENUOBJHELPHUD_H
#define CLASSES_GF_GFMENUOBJHELPHUD_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62A30
class GfMenuObjHelpHud : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjHelpHud();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
