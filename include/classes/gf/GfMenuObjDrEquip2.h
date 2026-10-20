#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61A60
class GfMenuObjDrEquip2 : public ::gf::GfMenuObject {
public:
    class EquipItemListener;
    class ItemListListener;
    class MainListener;
    class SlotListener;
    virtual ~GfMenuObjDrEquip2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
