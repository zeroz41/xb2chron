#ifndef CLASSES_GF_GFMENUOBJSHOP_SELLLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SELLLISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64848
class GfMenuObjShop::SellListListener {
public:
    virtual ~SellListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
