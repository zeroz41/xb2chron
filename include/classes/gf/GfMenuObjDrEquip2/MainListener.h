#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_MAINLISTENER_H

#include "classes/gf/GfMenuObjDrEquip2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61AA8
class GfMenuObjDrEquip2::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
