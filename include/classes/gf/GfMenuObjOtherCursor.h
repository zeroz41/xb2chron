#ifndef CLASSES_GF_GFMENUOBJOTHERCURSOR_H
#define CLASSES_GF_GFMENUOBJOTHERCURSOR_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63DD8
class GfMenuObjOtherCursor : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjOtherCursor();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
