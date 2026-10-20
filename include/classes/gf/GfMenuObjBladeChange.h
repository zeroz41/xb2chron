#ifndef CLASSES_GF_GFMENUOBJBLADECHANGE_H
#define CLASSES_GF_GFMENUOBJBLADECHANGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FE78
class GfMenuObjBladeChange : public ::gf::GfMenuObject {
public:
    class BladeListener;
    virtual ~GfMenuObjBladeChange();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
