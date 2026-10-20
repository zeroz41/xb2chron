#ifndef CLASSES_GF_GFMENUOBJBLADESET2_H
#define CLASSES_GF_GFMENUOBJBLADESET2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B602E8
class GfMenuObjBladeSet2 : public ::gf::GfMenuObject {
public:
    class BladeListListener;
    class BladeSlotListener;
    class MainListener;
    virtual ~GfMenuObjBladeSet2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
