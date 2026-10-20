#ifndef CLASSES_GF_GFMENUOBJBLADESET2_BLADESLOTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADESET2_BLADESLOTLISTENER_H

#include "classes/gf/GfMenuObjBladeSet2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60370
class GfMenuObjBladeSet2::BladeSlotListener {
public:
    virtual ~BladeSlotListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
