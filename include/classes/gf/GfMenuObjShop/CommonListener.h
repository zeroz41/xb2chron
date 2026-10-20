#ifndef CLASSES_GF_GFMENUOBJSHOP_COMMONLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_COMMONLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B647A8
class GfMenuObjShop::CommonListener {
public:
    virtual ~CommonListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
