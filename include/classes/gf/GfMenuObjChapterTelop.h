#ifndef CLASSES_GF_GFMENUOBJCHAPTERTELOP_H
#define CLASSES_GF_GFMENUOBJCHAPTERTELOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60DB8
class GfMenuObjChapterTelop : public ::gf::GfMenuObject {
public:
    class ListListener;
    virtual ~GfMenuObjChapterTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
