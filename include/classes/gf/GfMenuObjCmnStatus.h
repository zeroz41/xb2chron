#ifndef CLASSES_GF_GFMENUOBJCMNSTATUS_H
#define CLASSES_GF_GFMENUOBJCMNSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B612C8
class GfMenuObjCmnStatus : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjCmnStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
