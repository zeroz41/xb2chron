#ifndef CLASSES_GF_GFMENUOBJSHOP_STORELISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_STORELISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64820
class GfMenuObjShop::StoreListListener {
public:
    virtual ~StoreListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
