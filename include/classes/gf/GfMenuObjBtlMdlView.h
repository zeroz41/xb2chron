#ifndef CLASSES_GF_GFMENUOBJBTLMDLVIEW_H
#define CLASSES_GF_GFMENUOBJBTLMDLVIEW_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B608E0
class GfMenuObjBtlMdlView : public ::gf::GfMenuObject {
public:
    virtual ~GfMenuObjBtlMdlView();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
