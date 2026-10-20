#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61B50
class GfMenuObjDrKizunaRing : public ::gf::GfMenuObject {
public:
    class DriverStockSPListener;
    class MainListener;
    class RingListener;
    class RingPadListener;
    class SkillDetailListener;
    virtual ~GfMenuObjDrKizunaRing();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
