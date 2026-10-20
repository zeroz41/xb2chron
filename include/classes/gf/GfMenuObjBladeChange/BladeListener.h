#ifndef CLASSES_GF_GFMENUOBJBLADECHANGE_BLADELISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECHANGE_BLADELISTENER_H

#include "classes/gf/GfMenuObjBladeChange.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FEC0
class GfMenuObjBladeChange::BladeListener {
public:
    virtual ~BladeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
