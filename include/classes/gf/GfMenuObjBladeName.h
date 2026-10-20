#ifndef CLASSES_GF_GFMENUOBJBLADENAME_H
#define CLASSES_GF_GFMENUOBJBLADENAME_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B601E0
class GfMenuObjBladeName : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjBladeName();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
