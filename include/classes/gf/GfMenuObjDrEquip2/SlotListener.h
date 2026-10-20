#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_SLOTLISTENER_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_SLOTLISTENER_H

#include "classes/gf/GfMenuObjDrEquip2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61AD0
class GfMenuObjDrEquip2::SlotListener {
public:
    virtual ~SlotListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
