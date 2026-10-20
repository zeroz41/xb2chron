#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjDrEquip2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61AF8
class GfMenuObjDrEquip2::ItemListListener {
public:
    virtual ~ItemListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
