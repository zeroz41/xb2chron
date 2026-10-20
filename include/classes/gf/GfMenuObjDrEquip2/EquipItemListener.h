#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_EQUIPITEMLISTENER_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_EQUIPITEMLISTENER_H

#include "classes/gf/GfMenuObjDrEquip2.h"

namespace gf {
// table 0x7100B61B20
class GfMenuObjDrEquip2::EquipItemListener {
public:
    virtual ~EquipItemListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
