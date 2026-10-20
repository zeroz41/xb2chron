#ifndef CLASSES_GF_GFMENUOBJSHOP_EXCTASKLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_EXCTASKLISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace gf {
// table 0x7100B64938
class GfMenuObjShop::ExcTaskListListener {
public:
    virtual ~ExcTaskListListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
