#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_DRIVERSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_DRIVERSELECTLISTENER_H

#include "classes/gf/GfMenuObjPartyForm3.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63F18
class GfMenuObjPartyForm3::DriverSelectListener {
public:
    virtual ~DriverSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
