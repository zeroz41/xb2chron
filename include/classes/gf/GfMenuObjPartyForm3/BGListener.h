#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_BGLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_BGLISTENER_H

#include "classes/gf/GfMenuObjPartyForm3.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63EF0
class GfMenuObjPartyForm3::BGListener {
public:
    virtual ~BGListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
