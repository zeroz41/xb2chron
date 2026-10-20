#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_MAINLISTENER_H

#include "classes/gf/GfMenuObjPartyForm3.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63EC8
class GfMenuObjPartyForm3::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
