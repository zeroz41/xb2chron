#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_ITEMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_ITEMSELECTLISTENER_H

#include "classes/gf/GfMenuObjBlWeapon2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60678
class GfMenuObjBlWeapon2::ItemSelectListener {
public:
    virtual ~ItemSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
