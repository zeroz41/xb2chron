#ifndef CLASSES_GF_GFMENUOBJBALLOON_SELMONEYLISTENER_H
#define CLASSES_GF_GFMENUOBJBALLOON_SELMONEYLISTENER_H

#include "classes/gf/GfMenuObjBalloon.h"

namespace gf {
// table 0x7100B5FC20
class GfMenuObjBalloon::SelMoneyListener {
public:
    virtual ~SelMoneyListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
