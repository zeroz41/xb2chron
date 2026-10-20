#ifndef CLASSES_GF_GFMENUOBJBALLOON_AUTOTALKLISTENER_H
#define CLASSES_GF_GFMENUOBJBALLOON_AUTOTALKLISTENER_H

#include "classes/gf/GfMenuObjBalloon.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FC98
class GfMenuObjBalloon::AutoTalkListener {
public:
    virtual ~AutoTalkListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
