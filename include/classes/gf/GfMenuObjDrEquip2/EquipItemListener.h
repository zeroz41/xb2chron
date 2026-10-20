#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_EQUIPITEMLISTENER_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_EQUIPITEMLISTENER_H

#include "classes/gf/GfMenuObjDrEquip2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61B20
class GfMenuObjDrEquip2::EquipItemListener {
public:
    virtual ~EquipItemListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
