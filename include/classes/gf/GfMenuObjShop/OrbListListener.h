#ifndef CLASSES_GF_GFMENUOBJSHOP_ORBLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_ORBLISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B648E8
class GfMenuObjShop::OrbListListener {
public:
    virtual ~OrbListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
