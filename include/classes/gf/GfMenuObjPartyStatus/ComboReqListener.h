#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_COMBOREQLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_COMBOREQLISTENER_H

#include "classes/gf/GfMenuObjPartyStatus.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64060
class GfMenuObjPartyStatus::ComboReqListener {
public:
    virtual ~ComboReqListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
