#ifndef CLASSES_GF_GFMENUOBJLOCATIONTELOP_H
#define CLASSES_GF_GFMENUOBJLOCATIONTELOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62DC8
class GfMenuObjLocationTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjLocationTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
