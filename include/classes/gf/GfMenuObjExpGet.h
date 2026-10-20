#ifndef CLASSES_GF_GFMENUOBJEXPGET_H
#define CLASSES_GF_GFMENUOBJEXPGET_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B621C8
class GfMenuObjExpGet : public ::gf::GfMenuObject {
public:
    class ExpGetInfo;
    class ListListener;
    virtual ~GfMenuObjExpGet();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
