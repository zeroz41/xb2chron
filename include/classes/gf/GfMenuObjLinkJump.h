#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62C70
class GfMenuObjLinkJump : public ::gf::GfMenuObject {
public:
    class CategoryListener;
    class ListListener;
    class NotifyListener;
    class RootListener;
    virtual ~GfMenuObjLinkJump();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
