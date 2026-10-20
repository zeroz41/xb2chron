#ifndef CLASSES_GF_GFMENUOBJITEMLIST2_H
#define CLASSES_GF_GFMENUOBJITEMLIST2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62BB0
class GfMenuObjItemList2 : public ::gf::GfMenuObject {
public:
    class FilterListener;
    class ItemListListener;
    class MainListener;
    virtual ~GfMenuObjItemList2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
