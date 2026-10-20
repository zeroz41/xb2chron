#ifndef CLASSES_GF_GFMENUOBJPOUCH2_PARTYINFOLISTENER_H
#define CLASSES_GF_GFMENUOBJPOUCH2_PARTYINFOLISTENER_H

#include "classes/gf/GfMenuObjPouch2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B642C8
class GfMenuObjPouch2::PartyInfoListener {
public:
    virtual ~PartyInfoListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
