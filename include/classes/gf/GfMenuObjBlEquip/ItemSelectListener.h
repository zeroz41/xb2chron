#ifndef CLASSES_GF_GFMENUOBJBLEQUIP_ITEMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLEQUIP_ITEMSELECTLISTENER_H

#include "classes/gf/GfMenuObjBlEquip.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B604C8
class GfMenuObjBlEquip::ItemSelectListener {
public:
    virtual ~ItemSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
