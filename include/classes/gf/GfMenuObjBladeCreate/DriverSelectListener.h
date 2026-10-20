#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_DRIVERSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_DRIVERSELECTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60070
class GfMenuObjBladeCreate::DriverSelectListener {
public:
    virtual ~DriverSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
