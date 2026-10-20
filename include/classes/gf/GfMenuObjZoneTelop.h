#ifndef CLASSES_GF_GFMENUOBJZONETELOP_H
#define CLASSES_GF_GFMENUOBJZONETELOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B65198
class GfMenuObjZoneTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjZoneTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
