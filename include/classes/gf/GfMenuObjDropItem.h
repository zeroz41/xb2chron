#ifndef CLASSES_GF_GFMENUOBJDROPITEM_H
#define CLASSES_GF_GFMENUOBJDROPITEM_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61890
class GfMenuObjDropItem : public ::gf::GfMenuObject {
public:
    class DropItemInfo;
    class ListListener;
    virtual ~GfMenuObjDropItem();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
