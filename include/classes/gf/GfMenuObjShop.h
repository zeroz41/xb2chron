#ifndef CLASSES_GF_GFMENUOBJSHOP_H
#define CLASSES_GF_GFMENUOBJSHOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64738
class GfMenuObjShop : public ::gf::GfMenuObject {
public:
    class CommonListener;
    class ExcTaskListListener;
    class InnActListener;
    class MainListener;
    class NumSelectListener;
    class OrbListListener;
    class OrbRecipeListener;
    class SellFilterListener;
    class SellListListener;
    class StoreActListener;
    class StoreListListener;
    class SubListener;
    virtual ~GfMenuObjShop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
