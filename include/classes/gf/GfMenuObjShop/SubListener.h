#ifndef CLASSES_GF_GFMENUOBJSHOP_SUBLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SUBLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B647D0
class GfMenuObjShop::SubListener {
public:
    virtual ~SubListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
