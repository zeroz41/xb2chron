#ifndef CLASSES_GF_GFMENUOBJCMNSTATUS_CHARSTATUSLISTENER_H
#define CLASSES_GF_GFMENUOBJCMNSTATUS_CHARSTATUSLISTENER_H

#include "classes/gf/GfMenuObjCmnStatus.h"

namespace gf {
// table 0x7100B61338
class GfMenuObjCmnStatus::CharStatusListener {
public:
    virtual ~CharStatusListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
