#ifndef CLASSES_GF_GFMENUOBJBLEQUIP_SLOTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLEQUIP_SLOTLISTENER_H

#include "classes/gf/GfMenuObjBlEquip.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B604A0
class GfMenuObjBlEquip::SlotListener {
public:
    virtual ~SlotListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
