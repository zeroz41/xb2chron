#ifndef CLASSES_GF_GFMENUOBJBLEQUIP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLEQUIP_MAINLISTENER_H

#include "classes/gf/GfMenuObjBlEquip.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60478
class GfMenuObjBlEquip::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
