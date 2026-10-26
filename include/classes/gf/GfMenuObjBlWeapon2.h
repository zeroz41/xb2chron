#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
class GfMenuCallContext;
// table 0x7100B60608
class GfMenuObjBlWeapon2 : public ::gf::GfMenuObject {
public:
    class ChrChangeListener;
    class ItemSelectListener;
    class MainListener;
    class WeaponListener;
    virtual ~GfMenuObjBlWeapon2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // binds the blade weapon menu to that call context; false while it cannot yet (GfMenuObjShop::
    // seqWaitLoadBlWeapon retries it each update after resetting the context)
    static bool attach(GfMenuCallContext* context);
};
}  // namespace gf

#endif
