#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_MAINLISTENER_H

#include "classes/gf/GfMenuObjPartyStatus.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64038
class GfMenuObjPartyStatus::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
