#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60250
class GfMenuObjBladeRelease : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    virtual ~GfMenuObjBladeRelease();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
