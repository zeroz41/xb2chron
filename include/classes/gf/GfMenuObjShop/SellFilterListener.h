#ifndef CLASSES_GF_GFMENUOBJSHOP_SELLFILTERLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SELLFILTERLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64870
class GfMenuObjShop::SellFilterListener {
public:
    virtual ~SellFilterListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
